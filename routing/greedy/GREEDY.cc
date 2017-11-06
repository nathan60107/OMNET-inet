//
// Copyright (C) 2013 Opensim Ltd
// Author: Levente Meszaros
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

#include "inet/routing/greedy/GREEDY.h"
#include "inet/networklayer/common/IPProtocolId_m.h"
#include "inet/networklayer/common/IPSocket.h"
#include "inet/common/INETUtils.h"
#include "inet/common/lifecycle/NodeOperations.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/common/ModuleAccess.h"

#ifdef WITH_IPv4
#include "inet/networklayer/ipv4/IPv4Datagram.h"
#endif

#ifdef WITH_IPv6
#include "inet/networklayer/ipv6/IPv6ExtensionHeaders.h"
#include "inet/networklayer/ipv6/IPv6InterfaceData.h"
#endif

#ifdef WITH_GENERIC
#include "inet/networklayer/generic/GenericDatagram.h"
#endif


namespace inet {

Define_Module(GREEDY);

static inline double determinant(double a1, double a2, double b1, double b2)
{
    return a1 * b2 - a2 * b1;
}

// KLUDGE: implement position registry protocol
PositionTable GREEDY::globalPositionTable;

GREEDY::GREEDY()
{
}

GREEDY::~GREEDY()
{
    cancelAndDelete(beaconTimer);
    cancelAndDelete(purgeNeighborsTimer);
}

//
// module interface
//

void GREEDY::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        // GREEDY parameters
        planarizationMode = (GREEDYPlanarizationMode)(int)par("planarizationMode");
        interfaces = par("interfaces");
        beaconInterval = par("beaconInterval");
        maxJitter = par("maxJitter");
        neighborValidityInterval = par("neighborValidityInterval");
        // context
        host = getContainingNode(this);
        nodeStatus = dynamic_cast<NodeStatus *>(host->getSubmodule("status"));
        interfaceTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        mobility = check_and_cast<IMobility *>(host->getSubmodule("mobility"));
        routingTable = getModuleFromPar<IRoutingTable>(par("routingTableModule"), this);
        networkProtocol = getModuleFromPar<INetfilter>(par("networkProtocolModule"), this);
        // internal
        beaconTimer = new cMessage("BeaconTimer");
        purgeNeighborsTimer = new cMessage("PurgeNeighborsTimer");

        // packet size
        positionByteLength = par("positionByteLength");
    }
    else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {
        IPSocket socket(gate("ipOut"));
        socket.registerProtocol(IP_PROT_MANET);

        globalPositionTable.clear();
        host->subscribe(NF_LINK_BREAK, this);
        addressType = getSelfAddress().getAddressType();
        networkProtocol->registerHook(0, this);
        if (isNodeUp()) {
            configureInterfaces();
            scheduleBeaconTimer();
            schedulePurgeNeighborsTimer();
        }
        WATCH(neighborPositionTable);
    }
}

void GREEDY::handleMessage(cMessage *message)
{
    if(printFunctionName)EV_DEBUG << " handleMessage()\n";
    if (message->isSelfMessage())
        processSelfMessage(message);
    else
        processMessage(message);
}

//
// handling messages
//

void GREEDY::processSelfMessage(cMessage *message)
{
    if(printFunctionName)EV_DEBUG << "In processSelfMessage()\n";
    //EV_DEBUG << "Receive a beacon timer" <<endl;
    if (message == beaconTimer)
        processBeaconTimer();
    else if (message == purgeNeighborsTimer)
        processPurgeNeighborsTimer();
    else
        throw cRuntimeError("Unknown self message");
}

void GREEDY::processMessage(cMessage *message)
{
    if(printFunctionName)EV_DEBUG << "In processMessage()\n";
    if (dynamic_cast<UDPPacket *>(message)){
        std::string str("ACK of");
        std::string str2(static_cast<UDPPacket *>(message)->getName());
        if(str2.compare(0, 6,str)!=0){
            processUDPPacket(static_cast<UDPPacket *>(message));
        }else{
            EV_DEBUG << str2 <<" detected!! do something.\n";
            std::size_t found = str2.find("UDP");
            if(found!=std::string::npos){
                str2 = str2.substr(found);
                networkProtocol->dropQueuedDatagramByString(str2);
            }
        }
    }else
        throw cRuntimeError("Unknown message");
}

//
// beacon timers
//

void GREEDY::scheduleBeaconTimer()
{
    if(printFunctionName)EV_DEBUG << "In scheduleBeaconTimer()\n";
    EV_DEBUG << "Scheduling beacon timer, beaconInterval:" << beaconInterval <<endl;///已修改
    scheduleAt(simTime() + beaconInterval, beaconTimer);
}

void GREEDY::processBeaconTimer()
{
    if(printFunctionName)EV_DEBUG << "In processBeaconTimer()\n";
    EV_DEBUG << "Processing beacon timer" << endl;
    L3Address selfAddress = getSelfAddress();
    if (!selfAddress.isUnspecified()) {
        sendBeacon(createBeacon(), uniform(0, maxJitter).dbl());
        // KLUDGE: implement position registry protocol
        globalPositionTable.setPosition(selfAddress, mobility->getCurrentPosition());
    }
    scheduleBeaconTimer();
    schedulePurgeNeighborsTimer();
    networkProtocol->reinjectAllQueuedDatagram();
}

//
// handling purge neighbors timers
//

void GREEDY::schedulePurgeNeighborsTimer()
{
    if(printFunctionName)EV_DEBUG << "In schedulePurgeNeighborsTimer()\n";
    EV_DEBUG << "Scheduling purge neighbors timer" << endl;
    simtime_t nextExpiration = getNextNeighborExpiration();
    if (nextExpiration == SimTime::getMaxTime()) {
        if (purgeNeighborsTimer->isScheduled())
            cancelEvent(purgeNeighborsTimer);
    }
    else {
        if (!purgeNeighborsTimer->isScheduled())
            scheduleAt(nextExpiration, purgeNeighborsTimer);
        else {
            if (purgeNeighborsTimer->getArrivalTime() != nextExpiration) {
                cancelEvent(purgeNeighborsTimer);
                scheduleAt(nextExpiration, purgeNeighborsTimer);
            }
        }
    }
}

void GREEDY::processPurgeNeighborsTimer()
{
    if(printFunctionName)EV_DEBUG << "In processPurgeNeighborsTimer()\n";
    EV_DEBUG << "Processing purge neighbors timer" << endl;
    purgeNeighbors();
    schedulePurgeNeighborsTimer();
}

//
// handling UDP packets
//

void GREEDY::sendUDPPacket(UDPPacket *packet, double delay)
{
    if(printFunctionName)EV_DEBUG << "In sendUDPPacket()\n";
    if (delay == 0)
        send(packet, "ipOut");
    else
        sendDelayed(packet, delay, "ipOut");
}

void GREEDY::processUDPPacket(UDPPacket *packet)
{
    if(printFunctionName)EV_DEBUG << "In processUDPPacket()\n";
    cPacket *encapsulatedPacket = packet->decapsulate();
    if (dynamic_cast<GREEDYBeacon *>(encapsulatedPacket)){
        EV_DEBUG << "I receive a UDP packet~. name:" << dynamic_cast<GREEDYBeacon *>(encapsulatedPacket)->getName()
                << "" << encapsulatedPacket->getDisplayString() << "\n";
        processBeacon(static_cast<GREEDYBeacon *>(encapsulatedPacket));
    }else
        throw cRuntimeError("Unknown UDP packet");
    delete packet;
}

//
// handling beacons
//

GREEDYBeacon *GREEDY::createBeacon()
{
    if(printFunctionName)EV_DEBUG << "In createBeacon()\n";
    GREEDYBeacon *beacon = new GREEDYBeacon("GREEDYBeacon");
    beacon->setAddress(getSelfAddress());
    beacon->setPosition(mobility->getCurrentPosition());
    beacon->setByteLength(getSelfAddress().getAddressType()->getAddressByteLength() + positionByteLength);
    return beacon;
}

GREEDYBeacon *GREEDY::createACK(const char *name, const L3Address& address, Coord coordinate)
{
    if(printFunctionName)EV_DEBUG << "In createACK()" << name << "\n";
    GREEDYBeacon *beacon = new GREEDYBeacon(name);
    beacon->setAddress(address);
    beacon->setPosition(coordinate);
    beacon->setByteLength(address.getAddressType()->getAddressByteLength() + positionByteLength);
    return beacon;
}

void GREEDY::sendBeacon(GREEDYBeacon *beacon, double delay)
{
    if(printFunctionName)EV_DEBUG << "In sendBeacon()\n";
    EV_INFO << "Sending beacon: address = " << beacon->getAddress() << ", position = " << beacon->getPosition() << endl;
    INetworkProtocolControlInfo *networkProtocolControlInfo = addressType->createNetworkProtocolControlInfo();
    networkProtocolControlInfo->setTransportProtocol(IP_PROT_MANET);
    networkProtocolControlInfo->setHopLimit(255);
    networkProtocolControlInfo->setDestinationAddress(addressType->getLinkLocalManetRoutersMulticastAddress());
    networkProtocolControlInfo->setSourceAddress(getSelfAddress());
    UDPPacket *udpPacket = new UDPPacket(beacon->getName());
    udpPacket->encapsulate(beacon);
    udpPacket->setSourcePort(GREEDY_UDP_PORT);
    udpPacket->setDestinationPort(GREEDY_UDP_PORT);
    udpPacket->setControlInfo(dynamic_cast<cObject *>(networkProtocolControlInfo));
    sendUDPPacket(udpPacket, delay);
}

void GREEDY::sendACK(GREEDYBeacon *beacon, double delay, const L3Address& address)
{
    if(printFunctionName)EV_DEBUG << "In sendACK()\n";
    EV_INFO << "Sending ACK: address = " << beacon->getAddress() << ", position = " << beacon->getPosition() << endl;
    INetworkProtocolControlInfo *networkProtocolControlInfo = addressType->createNetworkProtocolControlInfo();
    networkProtocolControlInfo->setTransportProtocol(IP_PROT_MANET);
    networkProtocolControlInfo->setHopLimit(255);
    networkProtocolControlInfo->setDestinationAddress(address);
    networkProtocolControlInfo->setSourceAddress(getSelfAddress());
    UDPPacket *udpPacket = new UDPPacket(beacon->getName());
    udpPacket->encapsulate(beacon);
    udpPacket->setSourcePort(GREEDY_UDP_PORT);
    udpPacket->setDestinationPort(GREEDY_UDP_PORT);
    udpPacket->setControlInfo(dynamic_cast<cObject *>(networkProtocolControlInfo));
    sendUDPPacket(udpPacket, delay);
}

void GREEDY::processBeacon(GREEDYBeacon *beacon)
{
    if(printFunctionName)EV_DEBUG << "In processBeacon()\n";
    EV_INFO << "Processing beacon: address = " << beacon->getAddress() << ", position = " << beacon->getPosition() << endl;
    neighborPositionTable.setPosition(beacon->getAddress(), beacon->getPosition());
    delete beacon;
}

//
// handling packets
//

GREEDYOption *GREEDY::createGreedyOption(L3Address destination, cPacket *content)
{
    if(printFunctionName)EV_DEBUG << "In createGreedyOption()\n";
    GREEDYOption *greedyOption = new GREEDYOption();
    greedyOption->setRoutingMode(GREEDY_GREEDY_ROUTING);
    // KLUDGE: implement position registry protocol
    greedyOption->setDestinationPosition(getDestinationPosition(destination));
    greedyOption->setLength(computeOptionLength(greedyOption));
    return greedyOption;
}

int GREEDY::computeOptionLength(GREEDYOption *option)
{
    if(printFunctionName)EV_DEBUG << "In computeOptionLength()\n";
    // routingMode
    int routingModeBytes = 1;
    // destinationPosition, perimeterRoutingStartPosition, perimeterRoutingForwardPosition
    int positionsBytes = 3 * positionByteLength;
    // currentFaceFirstSenderAddress, currentFaceFirstReceiverAddress, senderAddress
    int addressesBytes = 3 * getSelfAddress().getAddressType()->getAddressByteLength();
    // type and length
    int tlBytes = 1 + 1;

    return tlBytes + routingModeBytes + positionsBytes + addressesBytes;
}

//
// configuration
//

bool GREEDY::isNodeUp() const
{
    if(printFunctionName)EV_DEBUG << "In isNodeUp()\n";
    return !nodeStatus || nodeStatus->getState() == NodeStatus::UP;
}

void GREEDY::configureInterfaces()
{
    if(printFunctionName)EV_DEBUG << "In configureInterfaces()\n";
    // join multicast groups
    cPatternMatcher interfaceMatcher(interfaces, false, true, false);
    for (int i = 0; i < interfaceTable->getNumInterfaces(); i++) {
        InterfaceEntry *interfaceEntry = interfaceTable->getInterface(i);
        if (interfaceEntry->isMulticast() && interfaceMatcher.matches(interfaceEntry->getName()))
            interfaceEntry->joinMulticastGroup(addressType->getLinkLocalManetRoutersMulticastAddress());
    }
}

//
// position
//

Coord GREEDY::intersectSections(Coord& begin1, Coord& end1, Coord& begin2, Coord& end2)
{
    //if(printFunctionName) EV_DEBUG << "In intersectSections()\n";
    double x1 = begin1.x;
    double y1 = begin1.y;
    double x2 = end1.x;
    double y2 = end1.y;
    double x3 = begin2.x;
    double y3 = begin2.y;
    double x4 = end2.x;
    double y4 = end2.y;
    double a = determinant(x1, y1, x2, y2);
    double b = determinant(x3, y3, x4, y4);
    double c = determinant(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
    double x = determinant(a, x1 - x2, b, x3 - x4) / c;
    double y = determinant(a, y1 - y2, b, y3 - y4) / c;
    if (x1 < x && x < x2 && x3 < x && x < x4 && y1 < y && y < y2 && y3 < y && y < y4)
        return Coord(x, y, 0);
    else
        return Coord(NaN, NaN, NaN);
}

Coord GREEDY::getDestinationPosition(const L3Address& address) const
{
    if(printFunctionName)EV_DEBUG << "In getDestinationPosition()\n";
    // KLUDGE: implement position registry protocol
    return globalPositionTable.getPosition(address);
}

Coord GREEDY::getNeighborPosition(const L3Address& address) const
{
    if(printFunctionName)EV_DEBUG << "In getNeighborPosition()\n";
    return neighborPositionTable.getPosition(address);
}

//
// angle
//

double GREEDY::getVectorAngle(Coord vector)
{
    //if(printFunctionName)EV_DEBUG << "In getVectorAngle()\n";
    double angle = atan2(-vector.y, vector.x);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

double GREEDY::getDestinationAngle(const L3Address& address)
{
    if(printFunctionName)EV_DEBUG << "In getDestinationAngle()\n";
    return getVectorAngle(getDestinationPosition(address) - mobility->getCurrentPosition());
}

double GREEDY::getNeighborAngle(const L3Address& address)
{
    if(printFunctionName)EV_DEBUG << "In getNeighborAngle()\n";
    return getVectorAngle(getNeighborPosition(address) - mobility->getCurrentPosition());
}

//
// address
//

std::string GREEDY::getHostName() const
{
    if(printFunctionName)EV_DEBUG << "In getHostName()\n";
    return host->getFullName();
}

L3Address GREEDY::getSelfAddress() const
{
    if(printFunctionName)EV_DEBUG << "In getSelfAddress()\n";
    //TODO choose self address based on a new 'interfaces' parameter
    L3Address ret = routingTable->getRouterIdAsGeneric();
#ifdef WITH_IPv6
    if (ret.getType() == L3Address::IPv6) {
        for (int i = 0; i < interfaceTable->getNumInterfaces(); i++) {
            InterfaceEntry *ie = interfaceTable->getInterface(i);
            if ((!ie->isLoopback()) && ie->ipv6Data() != nullptr) {
                ret = interfaceTable->getInterface(i)->ipv6Data()->getPreferredAddress();
                break;
            }
        }
    }
#endif
    return ret;
}

L3Address GREEDY::getSenderNeighborAddress(INetworkDatagram *datagram) const
{
    if(printFunctionName)EV_DEBUG << "In getSenderNeighborAddress()\n";
    const GREEDYOption *greedyOption = getGreedyOptionFromNetworkDatagram(datagram);
    return greedyOption->getSenderAddress();
}

//
// neighbor
//

simtime_t GREEDY::getNextNeighborExpiration()
{
    if(printFunctionName)EV_DEBUG << "In getNextNeighborExpiration()\n";
    simtime_t oldestPosition = neighborPositionTable.getOldestPosition();
    if (oldestPosition == SimTime::getMaxTime())
        return oldestPosition;
    else
        return oldestPosition + neighborValidityInterval;
}

void GREEDY::purgeNeighbors()
{
    if(printFunctionName)EV_DEBUG << "In purgeNeighbors()\n";
    neighborPositionTable.removeOldPositions(simTime() - neighborValidityInterval);
}

std::vector<L3Address> GREEDY::getPlanarNeighbors()
{
    if(printFunctionName)EV_DEBUG << "In getPlanarNeighbors()\n";
    std::vector<L3Address> planarNeighbors;
    std::vector<L3Address> neighborAddresses = neighborPositionTable.getAddresses();
    Coord selfPosition = mobility->getCurrentPosition();
    for (auto it = neighborAddresses.begin(); it != neighborAddresses.end(); it++) {
        const L3Address& neighborAddress = *it;
        Coord neighborPosition = neighborPositionTable.getPosition(neighborAddress);
        if (planarizationMode == GREEDY_RNG_PLANARIZATION) {
            double neighborDistance = (neighborPosition - selfPosition).length();
            for (auto & neighborAddresse : neighborAddresses) {
                const L3Address& witnessAddress = neighborAddresse;
                Coord witnessPosition = neighborPositionTable.getPosition(witnessAddress);
                double witnessDistance = (witnessPosition - selfPosition).length();
                ;
                double neighborWitnessDistance = (witnessPosition - neighborPosition).length();
                if (*it == neighborAddresse)
                    continue;
                else if (neighborDistance > std::max(witnessDistance, neighborWitnessDistance))
                    goto eliminate;
            }
        }
        else if (planarizationMode == GREEDY_GG_PLANARIZATION) {
            Coord middlePosition = (selfPosition + neighborPosition) / 2;
            double neighborDistance = (neighborPosition - middlePosition).length();
            for (auto & neighborAddresse : neighborAddresses) {
                const L3Address& witnessAddress = neighborAddresse;
                Coord witnessPosition = neighborPositionTable.getPosition(witnessAddress);
                double witnessDistance = (witnessPosition - middlePosition).length();
                ;
                if (*it == neighborAddresse)
                    continue;
                else if (witnessDistance < neighborDistance)
                    goto eliminate;
            }
        }
        else
            throw cRuntimeError("Unknown planarization mode");
        planarNeighbors.push_back(*it);
      eliminate:;
    }
    return planarNeighbors;
}

L3Address GREEDY::getNextPlanarNeighborCounterClockwise(const L3Address& startNeighborAddress, double startNeighborAngle)
{
    if(printFunctionName)EV_DEBUG << "In getNextPlanarNeighborCounterClockwise()\n";
    EV_DEBUG << "Finding next planar neighbor (counter clockwise): startAddress = " << startNeighborAddress << ", startAngle = " << startNeighborAngle << endl;
    L3Address bestNeighborAddress = startNeighborAddress;
    double bestNeighborAngleDifference = 2 * M_PI;
    std::vector<L3Address> neighborAddresses = getPlanarNeighbors();
    for (auto & neighborAddress : neighborAddresses) {
        double neighborAngle = getNeighborAngle(neighborAddress);
        double neighborAngleDifference = neighborAngle - startNeighborAngle;
        if (neighborAngleDifference < 0)
            neighborAngleDifference += 2 * M_PI;
        EV_DEBUG << "Trying next planar neighbor (counter clockwise): address = " << neighborAddress << ", angle = " << neighborAngle << endl;
        if (neighborAngleDifference != 0 && neighborAngleDifference < bestNeighborAngleDifference) {
            bestNeighborAngleDifference = neighborAngleDifference;
            bestNeighborAddress = neighborAddress;
        }
    }
    return bestNeighborAddress;
}

//
// next hop
//

L3Address GREEDY::findNextHop(INetworkDatagram *datagram, const L3Address& destination)
{
    if(printFunctionName)EV_DEBUG << "In findNextHop()";
    GREEDYOption *greedyOption = getGreedyOptionFromNetworkDatagram(datagram);
    if(printFunctionName)EV_DEBUG << greedyOption->getRoutingMode() << endl;
    switch (greedyOption->getRoutingMode()) {
        case GREEDY_GREEDY_ROUTING: return findGreedyRoutingNextHop(datagram, destination);
        case GREEDY_PERIMETER_ROUTING: return findPerimeterRoutingNextHop(datagram, destination);
        default: throw cRuntimeError("Unknown routing mode");
    }
}

L3Address GREEDY::findGreedyRoutingNextHop(INetworkDatagram *datagram, const L3Address& destination)
{
    if(printFunctionName)EV_DEBUG << "In findGreedyRoutingNextHop()\n";
    EV_DEBUG << "Finding next hop using greedy routing: destination = " << destination << endl;
    GREEDYOption *greedyOption = getGreedyOptionFromNetworkDatagram(datagram);
    L3Address selfAddress = getSelfAddress();
    Coord selfPosition = mobility->getCurrentPosition();
    Coord destinationPosition = (greedyOption->getDestinationPosition().isUnspecified())?
            getDestinationPosition(destination):greedyOption->getDestinationPosition();
    double bestDistance = (destinationPosition - selfPosition).length();
    L3Address bestNeighbor;
    std::vector<L3Address> neighborAddresses = neighborPositionTable.getAddresses();
    for (auto& neighborAddress: neighborAddresses) {
        Coord neighborPosition = neighborPositionTable.getPosition(neighborAddress);
        double neighborDistance = (destinationPosition - neighborPosition).length();
        EV_DEBUG << "Pos:" << neighborPosition << " Dis:" << neighborDistance << " dest:" << destinationPosition
                <<" Bes:" << bestDistance << endl;
        if (neighborDistance < bestDistance) {
            bestDistance = neighborDistance;
            bestNeighbor = neighborAddress;
        }
    }
    /*if (bestNeighbor.isUnspecified()) {
        EV_DEBUG << "Switching to perimeter routing: destination = " << destination << endl;
        greedyOption->setRoutingMode(GREEDY_PERIMETER_ROUTING);
        greedyOption->setPerimeterRoutingStartPosition(selfPosition);
        greedyOption->setCurrentFaceFirstSenderAddress(selfAddress);
        greedyOption->setCurrentFaceFirstReceiverAddress(L3Address());
        return findPerimeterRoutingNextHop(datagram, destination);
    }
    else*/
        return bestNeighbor;
}

L3Address GREEDY::findPerimeterRoutingNextHop(INetworkDatagram *datagram, const L3Address& destination)
{
    if(printFunctionName)EV_DEBUG << "In findPerimeterRoutingNextHop()\n";
    EV_DEBUG << "Finding next hop using perimeter routing: destination = " << destination << endl;
    GREEDYOption *greedyOption = getGreedyOptionFromNetworkDatagram(datagram);
    L3Address selfAddress = getSelfAddress();
    Coord selfPosition = mobility->getCurrentPosition();
    Coord perimeterRoutingStartPosition = greedyOption->getPerimeterRoutingStartPosition();
    Coord destinationPosition = greedyOption->getDestinationPosition();
    double selfDistance = (destinationPosition - selfPosition).length();
    double perimeterRoutingStartDistance = (destinationPosition - perimeterRoutingStartPosition).length();
    EV_DEBUG << "Perimeter Routing Start Position: " << destinationPosition.x << "," << destinationPosition.y << endl;
    if (selfDistance < perimeterRoutingStartDistance) {
        EV_DEBUG << "Switching to greedy routing: destination = " << destination << endl;
        greedyOption->setRoutingMode(GREEDY_GREEDY_ROUTING);
        greedyOption->setPerimeterRoutingStartPosition(Coord());
        greedyOption->setPerimeterRoutingForwardPosition(Coord());
        return findGreedyRoutingNextHop(datagram, destination);
    }
    else {
        L3Address& firstSenderAddress = greedyOption->getCurrentFaceFirstSenderAddress();
        L3Address& firstReceiverAddress = greedyOption->getCurrentFaceFirstReceiverAddress();
        L3Address nextNeighborAddress = getSenderNeighborAddress(datagram);
        bool hasIntersection;
        do {
            if (nextNeighborAddress.isUnspecified())
                nextNeighborAddress = getNextPlanarNeighborCounterClockwise(nextNeighborAddress, getDestinationAngle(destination));
            else
                nextNeighborAddress = getNextPlanarNeighborCounterClockwise(nextNeighborAddress, getNeighborAngle(nextNeighborAddress));
            if (nextNeighborAddress.isUnspecified())
                break;
            EV_DEBUG << "Intersecting towards next hop: nextNeighbor = " << nextNeighborAddress << ", firstSender = " << firstSenderAddress << ", firstReceiver = " << firstReceiverAddress << ", destination = " << destination << endl;
            Coord nextNeighborPosition = getNeighborPosition(nextNeighborAddress);
            Coord intersection = intersectSections(perimeterRoutingStartPosition, destinationPosition, selfPosition, nextNeighborPosition);
            hasIntersection = !std::isnan(intersection.x);
            if (hasIntersection) {
                EV_DEBUG << "Edge to next hop intersects: intersection = " << intersection << ", nextNeighbor = " << nextNeighborAddress << ", firstSender = " << firstSenderAddress << ", firstReceiver = " << firstReceiverAddress << ", destination = " << destination << endl;
                greedyOption->setCurrentFaceFirstSenderAddress(selfAddress);
                greedyOption->setCurrentFaceFirstReceiverAddress(L3Address());
            }
        } while (hasIntersection);
        if (firstSenderAddress == selfAddress && firstReceiverAddress == nextNeighborAddress) {
            EV_DEBUG << "End of perimeter reached: firstSender = " << firstSenderAddress << ", firstReceiver = " << firstReceiverAddress << ", destination = " << destination << endl;
            return L3Address();
        }
        else {
            if (greedyOption->getCurrentFaceFirstReceiverAddress().isUnspecified())
                greedyOption->setCurrentFaceFirstReceiverAddress(nextNeighborAddress);
            return nextNeighborAddress;
        }
    }
}

//
// routing
//

INetfilter::IHook::Result GREEDY::routeDatagram(INetworkDatagram *datagram, const InterfaceEntry *& outputInterfaceEntry, L3Address& nextHop)
{
    if(printFunctionName)EV_DEBUG << "In routeDatagram()\n";
    const L3Address& source = datagram->getSourceAddress();
    const L3Address& destination = datagram->getDestinationAddress();
    EV_INFO << "Finding next hop: source = " << source << ", destination = " << destination << endl;
    nextHop = findNextHop(datagram, destination);
    if (nextHop.isUnspecified()) {
        EV_WARN << "[QUEUE]No next hop found, dropping packet: source = " << source << ", destination = " << destination << endl;
        delayDatagram(datagram);
        return QUEUE;
    }
    else {
        EV_INFO << "Next hop found: source = " << source << ", destination = " << destination << ", nextHop: " << nextHop << endl;
        GREEDYOption *greedyOption = getGreedyOptionFromNetworkDatagram(datagram);
        greedyOption->setSenderAddress(getSelfAddress());
        // KLUDGE: find output interface
        outputInterfaceEntry = interfaceTable->getInterface(1);
        //networkProtocol->reinjectAllQueuedDatagram();
        return ACCEPT;
    }
}

void GREEDY::setGreedyOptionOnNetworkDatagram(INetworkDatagram *datagram)
{
    if(printFunctionName)EV_DEBUG << "In setGreedyOptionOnNetworkDatagram()\n";
    cPacket *networkPacket = check_and_cast<cPacket *>(datagram);
    GREEDYOption *greedyOption = createGreedyOption(datagram->getDestinationAddress(), networkPacket->getEncapsulatedPacket());
#ifdef WITH_IPv4
    if (dynamic_cast<IPv4Datagram *>(networkPacket)) {
        greedyOption->setType(IPOPTION_TLV_GPSR);
        IPv4Datagram *dgram = static_cast<IPv4Datagram *>(networkPacket);
        int oldHlen = dgram->calculateHeaderByteLength();
        ASSERT(dgram->getHeaderLength() == oldHlen);
        dgram->addOption(greedyOption);
        int newHlen = dgram->calculateHeaderByteLength();//<----------------!!
        dgram->setHeaderLength(newHlen);
        dgram->addByteLength(newHlen - oldHlen);
        dgram->setTotalLengthField(dgram->getTotalLengthField() + newHlen - oldHlen);
    }
    else
#endif
#ifdef WITH_IPv6
    if (dynamic_cast<IPv6Datagram *>(networkPacket)) {
        greedyOption->setType(IPv6TLVOPTION_TLV_GPSR);
        IPv6Datagram *dgram = static_cast<IPv6Datagram *>(networkPacket);
        int oldHlen = dgram->calculateHeaderByteLength();
        IPv6HopByHopOptionsHeader *hdr = check_and_cast_nullable<IPv6HopByHopOptionsHeader *>(dgram->findExtensionHeaderByType(IP_PROT_IPv6EXT_HOP));
        if (hdr == nullptr) {
            hdr = new IPv6HopByHopOptionsHeader();
            hdr->setByteLength(8);
            dgram->addExtensionHeader(hdr);
        }
        hdr->getTlvOptions().add(greedyOption);
        hdr->setByteLength(utils::roundUp(2 + hdr->getTlvOptions().getLength(), 8));
        int newHlen = dgram->calculateHeaderByteLength();
        dgram->addByteLength(newHlen - oldHlen);
    }
    else
#endif
#ifdef WITH_GENERIC
    if (dynamic_cast<GenericDatagram *>(networkPacket)) {
        greedyOption->setType(GENERIC_TLVOPTION_TLV_GPSR);
        GenericDatagram *dgram = static_cast<GenericDatagram *>(networkPacket);
        int oldHlen = dgram->getTlvOptions().getLength();
        dgram->getTlvOptions().add(greedyOption);
        int newHlen = dgram->getTlvOptions().getLength();
        dgram->addByteLength(newHlen - oldHlen);
    }
    else
#endif
    {
    }
}

GREEDYOption *GREEDY::findGreedyOptionInNetworkDatagram(INetworkDatagram *datagram)
{
    if(printFunctionName)EV_DEBUG << "In findGreedyOptionInNetworkDatagram()\n";
    cPacket *networkPacket = check_and_cast<cPacket *>(datagram);
    GREEDYOption *greedyOption = nullptr;

#ifdef WITH_IPv4
    if (dynamic_cast<IPv4Datagram *>(networkPacket)) {
        IPv4Datagram *dgram = static_cast<IPv4Datagram *>(networkPacket);
        greedyOption = check_and_cast_nullable<GREEDYOption *>(dgram->findOptionByType(IPOPTION_TLV_GPSR));
    }
    else
#endif
#ifdef WITH_IPv6
    if (dynamic_cast<IPv6Datagram *>(networkPacket)) {
        IPv6Datagram *dgram = static_cast<IPv6Datagram *>(networkPacket);
        IPv6HopByHopOptionsHeader *hdr = check_and_cast_nullable<IPv6HopByHopOptionsHeader *>(dgram->findExtensionHeaderByType(IP_PROT_IPv6EXT_HOP));
        if (hdr != nullptr) {
            int i = (hdr->getTlvOptions().findByType(IPv6TLVOPTION_TLV_GPSR));
            if (i >= 0)
                greedyOption = check_and_cast_nullable<GREEDYOption *>(&(hdr->getTlvOptions().at(i)));
        }
    }
    else
#endif
#ifdef WITH_GENERIC
    if (dynamic_cast<GenericDatagram *>(networkPacket)) {
        GenericDatagram *dgram = static_cast<GenericDatagram *>(networkPacket);
        int i = (dgram->getTlvOptions().findByType(GENERIC_TLVOPTION_TLV_GPSR));
        if (i >= 0)
            greedyOption = check_and_cast_nullable<GREEDYOption *>(&(dgram->getTlvOptions().at(i)));
    }
    else
#endif
    {
    }
    return greedyOption;
}

GREEDYOption *GREEDY::getGreedyOptionFromNetworkDatagram(INetworkDatagram *datagram)
{
    if(printFunctionName)EV_DEBUG << "In getGreedyOptionFromNetworkDatagram()\n";
    GREEDYOption *greedyOption = findGreedyOptionInNetworkDatagram(datagram);
    if (greedyOption == nullptr)
        throw cRuntimeError("GREEDY option not found in datagram!");
    return greedyOption;
}

//
// netfilter
//

INetfilter::IHook::Result GREEDY::datagramPreRoutingHook(INetworkDatagram *datagram, const InterfaceEntry *inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, L3Address& nextHop)
{
    Enter_Method("datagramPreRoutingHook");


    cPacket *networkPacket = check_and_cast<cPacket *>(datagram);
    GREEDYOption *greedyOption = nullptr;

    IPv4Datagram *dgram = static_cast<IPv4Datagram *>(networkPacket);
    greedyOption = check_and_cast_nullable<GREEDYOption *>(dgram->findOptionByType(IPOPTION_TLV_GPSR));

    std::string str("ACK of");
    std::string str2(dgram->getName());
    if(str2.compare(0, 6,str)!=0){
        if(printFunctionName)EV_DEBUG << "In datagramPreRoutingHook GREEDY() " << dgram->getName() << ","<< dgram->getSourceAddress()<< "\n";
        std::string str(dgram->getName());
        str="ACK of "+str;

        sendACK(createACK(str.c_str(), dgram->getSourceAddress(), neighborPositionTable.getPosition(dgram->getSourceAddress()) ),
                uniform(0, maxJitter).dbl(), dgram->getSourceAddress());
    }
    const L3Address& destination = datagram->getDestinationAddress();
    if (destination.isMulticast() || destination.isBroadcast() || routingTable->isLocalAddress(destination)){
        //networkProtocol->reinjectAllQueuedDatagram();
        return ACCEPT;
    }else
        return routeDatagram(datagram, outputInterfaceEntry, nextHop);
}

INetfilter::IHook::Result GREEDY::datagramLocalOutHook(INetworkDatagram *datagram, const InterfaceEntry *& outputInterfaceEntry, L3Address& nextHop)
{
    if(printFunctionName)EV_DEBUG << "In datagramLocalOutHook() of GREEDY\n";
    Enter_Method("datagramLocalOutHook");
    const L3Address& destination = datagram->getDestinationAddress();
    if (destination.isMulticast() || destination.isBroadcast() || routingTable->isLocalAddress(destination)){
        //networkProtocol->reinjectAllQueuedDatagram();
        return ACCEPT;
    }else {
        cPacket *networkPacket = check_and_cast<cPacket *>(datagram);
        IPv4Datagram *dgram = static_cast<IPv4Datagram *>(networkPacket);
        int oldHlen = dgram->calculateHeaderByteLength();
        EV_DEBUG << "length::" << oldHlen << endl;
        if(oldHlen==60){
            return routeDatagram(datagram, outputInterfaceEntry, nextHop);
        }else{
            setGreedyOptionOnNetworkDatagram(datagram);
            return routeDatagram(datagram, outputInterfaceEntry, nextHop);
        }
    }
}

//
// lifecycle
//

bool GREEDY::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
{
    if(printFunctionName)EV_DEBUG << "In handleOperationStage()\n";
    Enter_Method_Silent();
    if (dynamic_cast<NodeStartOperation *>(operation)) {
        if ((NodeStartOperation::Stage)stage == NodeStartOperation::STAGE_APPLICATION_LAYER)
            configureInterfaces();
    }
    else if (dynamic_cast<NodeShutdownOperation *>(operation)) {
        if ((NodeShutdownOperation::Stage)stage == NodeShutdownOperation::STAGE_APPLICATION_LAYER) {
            // TODO: send a beacon to remove ourself from peers neighbor position table
            neighborPositionTable.clear();
            cancelEvent(beaconTimer);
            cancelEvent(purgeNeighborsTimer);
        }
    }
    else if (dynamic_cast<NodeCrashOperation *>(operation)) {
        if ((NodeCrashOperation::Stage)stage == NodeCrashOperation::STAGE_CRASH) {
            neighborPositionTable.clear();
            cancelEvent(beaconTimer);
            cancelEvent(purgeNeighborsTimer);
        }
    }
    else
        throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName());
    return true;
}

//
// notification
//

void GREEDY::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj DETAILS_ARG)
{
    if(printFunctionName)EV_DEBUG << "In receiveSignal()\n";
    Enter_Method("receiveChangeNotification");
    if (signalID == NF_LINK_BREAK) {
        EV_WARN << "Received link break" << endl;
        // TODO: shall we remove the neighbor?
    }
}

//
//以下自行新增
//

void GREEDY::delayDatagram(INetworkDatagram *datagram)
{
    EV_DETAIL << "Queuing datagram, source " << datagram->getSourceAddress() << ", destination " << datagram->getDestinationAddress() << endl;
    const L3Address& target = datagram->getDestinationAddress();
    targetAddressToDelayedPackets.insert(std::pair<L3Address, INetworkDatagram *>(target, datagram));
}

/*void GREEDY::reinjectAllDatagram()
{
    networkProtocol->

    /*EV_DETAIL << "Time up, reinject all datagram, originator " << getSelfIPAddress() << endl;
    ASSERT(hasOngoingRouteDiscovery(target));

    auto lt = targetAddressToDelayedPackets.lower_bound(target);
    auto ut = targetAddressToDelayedPackets.upper_bound(target);

    // reinject the delayed datagrams
    for (auto it = lt; it != ut; it++) {
        INetworkDatagram *datagram = it->second;
        EV_DETAIL << "Sending queued datagram: source " << datagram->getSourceAddress() << ", destination " << datagram->getDestinationAddress() << endl;
        networkProtocol->reinjectQueuedDatagram(const_cast<const INetworkDatagram *>(datagram));
    }

    // clear the multimap
    targetAddressToDelayedPackets.erase(lt, ut);

    // we have a route for the destination, thus we must cancel the WaitForRREPTimer events
    auto waitRREPIter = waitForRREPTimers.find(target);
    ASSERT(waitRREPIter != waitForRREPTimers.end());
    cancelAndDelete(waitRREPIter->second);
    waitForRREPTimers.erase(waitRREPIter);*
}*/

////注意不要超過namespace inet的範圍

} // namespace inet



