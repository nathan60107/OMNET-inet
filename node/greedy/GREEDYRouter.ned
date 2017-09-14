//
// This program is property of its copyright holder. All rights reserved.
//

package inet.node.greedy;

import inet.node.inet.WirelessHost;
import inet.routing.greedy.IGREEDY;


//
// TODO
//
module GREEDYRouter extends WirelessHost
{
    parameters:
        @display("i=device/cellphone");
        forwarding = true;
        wlan[*].mgmtType = default("Ieee80211MgmtAdhoc");
        string greedyType = default("GREEDY");
    submodules:
        greedy: <greedyType> like IGREEDY {
            @display("p=527,287");
        }
    connections:
        greedy.ipOut --> networkLayer.transportIn++;
        greedy.ipIn <-- networkLayer.transportOut++;
}
