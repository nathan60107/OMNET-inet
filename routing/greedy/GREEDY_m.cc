//
// Generated file, do not edit! Created by nedtool 5.0 from inet/routing/greedy/GREEDY.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GREEDY_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(GREEDYBeacon);

GREEDYBeacon::GREEDYBeacon(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
}

GREEDYBeacon::GREEDYBeacon(const GREEDYBeacon& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

GREEDYBeacon::~GREEDYBeacon()
{
}

GREEDYBeacon& GREEDYBeacon::operator=(const GREEDYBeacon& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GREEDYBeacon::copy(const GREEDYBeacon& other)
{
    this->address = other.address;
    this->position = other.position;
}

void GREEDYBeacon::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->position);
}

void GREEDYBeacon::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->position);
}

L3Address& GREEDYBeacon::getAddress()
{
    return this->address;
}

void GREEDYBeacon::setAddress(const L3Address& address)
{
    this->address = address;
}

Coord& GREEDYBeacon::getPosition()
{
    return this->position;
}

void GREEDYBeacon::setPosition(const Coord& position)
{
    this->position = position;
}

class GREEDYBeaconDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GREEDYBeaconDescriptor();
    virtual ~GREEDYBeaconDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GREEDYBeaconDescriptor);

GREEDYBeaconDescriptor::GREEDYBeaconDescriptor() : omnetpp::cClassDescriptor("inet::GREEDYBeacon", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

GREEDYBeaconDescriptor::~GREEDYBeaconDescriptor()
{
    delete[] propertynames;
}

bool GREEDYBeaconDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GREEDYBeacon *>(obj)!=nullptr;
}

const char **GREEDYBeaconDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GREEDYBeaconDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GREEDYBeaconDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GREEDYBeaconDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GREEDYBeaconDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "position",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GREEDYBeaconDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "address")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "position")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GREEDYBeaconDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "L3Address",
        "Coord",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GREEDYBeaconDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GREEDYBeaconDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GREEDYBeaconDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GREEDYBeacon *pp = (GREEDYBeacon *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GREEDYBeaconDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GREEDYBeacon *pp = (GREEDYBeacon *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getAddress(); return out.str();}
        case 1: {std::stringstream out; out << pp->getPosition(); return out.str();}
        default: return "";
    }
}

bool GREEDYBeaconDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GREEDYBeacon *pp = (GREEDYBeacon *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GREEDYBeaconDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(L3Address));
        case 1: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *GREEDYBeaconDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GREEDYBeacon *pp = (GREEDYBeacon *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getAddress()); break;
        case 1: return (void *)(&pp->getPosition()); break;
        default: return nullptr;
    }
}

GREEDYOption::GREEDYOption() : ::inet::TLVOptionBase()
{
    this->routingMode = (GREEDYForwardingMode)-1;
}

GREEDYOption::GREEDYOption(const GREEDYOption& other) : ::inet::TLVOptionBase(other)
{
    copy(other);
}

GREEDYOption::~GREEDYOption()
{
}

GREEDYOption& GREEDYOption::operator=(const GREEDYOption& other)
{
    if (this==&other) return *this;
    ::inet::TLVOptionBase::operator=(other);
    copy(other);
    return *this;
}

void GREEDYOption::copy(const GREEDYOption& other)
{
    this->routingMode = other.routingMode;
    this->destinationPosition = other.destinationPosition;
    this->perimeterRoutingStartPosition = other.perimeterRoutingStartPosition;
    this->perimeterRoutingForwardPosition = other.perimeterRoutingForwardPosition;
    this->currentFaceFirstSenderAddress = other.currentFaceFirstSenderAddress;
    this->currentFaceFirstReceiverAddress = other.currentFaceFirstReceiverAddress;
    this->senderAddress = other.senderAddress;
}

void GREEDYOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::inet::TLVOptionBase&)*this);
    doParsimPacking(b,this->routingMode);
    doParsimPacking(b,this->destinationPosition);
    doParsimPacking(b,this->perimeterRoutingStartPosition);
    doParsimPacking(b,this->perimeterRoutingForwardPosition);
    doParsimPacking(b,this->currentFaceFirstSenderAddress);
    doParsimPacking(b,this->currentFaceFirstReceiverAddress);
    doParsimPacking(b,this->senderAddress);
}

void GREEDYOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::inet::TLVOptionBase&)*this);
    doParsimUnpacking(b,this->routingMode);
    doParsimUnpacking(b,this->destinationPosition);
    doParsimUnpacking(b,this->perimeterRoutingStartPosition);
    doParsimUnpacking(b,this->perimeterRoutingForwardPosition);
    doParsimUnpacking(b,this->currentFaceFirstSenderAddress);
    doParsimUnpacking(b,this->currentFaceFirstReceiverAddress);
    doParsimUnpacking(b,this->senderAddress);
}

GREEDYForwardingMode& GREEDYOption::getRoutingMode()
{
    return this->routingMode;
}

void GREEDYOption::setRoutingMode(const GREEDYForwardingMode& routingMode)
{
    this->routingMode = routingMode;
}

Coord& GREEDYOption::getDestinationPosition()
{
    return this->destinationPosition;
}

void GREEDYOption::setDestinationPosition(const Coord& destinationPosition)
{
    this->destinationPosition = destinationPosition;
}

Coord& GREEDYOption::getPerimeterRoutingStartPosition()
{
    return this->perimeterRoutingStartPosition;
}

void GREEDYOption::setPerimeterRoutingStartPosition(const Coord& perimeterRoutingStartPosition)
{
    this->perimeterRoutingStartPosition = perimeterRoutingStartPosition;
}

Coord& GREEDYOption::getPerimeterRoutingForwardPosition()
{
    return this->perimeterRoutingForwardPosition;
}

void GREEDYOption::setPerimeterRoutingForwardPosition(const Coord& perimeterRoutingForwardPosition)
{
    this->perimeterRoutingForwardPosition = perimeterRoutingForwardPosition;
}

L3Address& GREEDYOption::getCurrentFaceFirstSenderAddress()
{
    return this->currentFaceFirstSenderAddress;
}

void GREEDYOption::setCurrentFaceFirstSenderAddress(const L3Address& currentFaceFirstSenderAddress)
{
    this->currentFaceFirstSenderAddress = currentFaceFirstSenderAddress;
}

L3Address& GREEDYOption::getCurrentFaceFirstReceiverAddress()
{
    return this->currentFaceFirstReceiverAddress;
}

void GREEDYOption::setCurrentFaceFirstReceiverAddress(const L3Address& currentFaceFirstReceiverAddress)
{
    this->currentFaceFirstReceiverAddress = currentFaceFirstReceiverAddress;
}

L3Address& GREEDYOption::getSenderAddress()
{
    return this->senderAddress;
}

void GREEDYOption::setSenderAddress(const L3Address& senderAddress)
{
    this->senderAddress = senderAddress;
}

class GREEDYOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GREEDYOptionDescriptor();
    virtual ~GREEDYOptionDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GREEDYOptionDescriptor);

GREEDYOptionDescriptor::GREEDYOptionDescriptor() : omnetpp::cClassDescriptor("inet::GREEDYOption", "inet::TLVOptionBase")
{
    propertynames = nullptr;
}

GREEDYOptionDescriptor::~GREEDYOptionDescriptor()
{
    delete[] propertynames;
}

bool GREEDYOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GREEDYOption *>(obj)!=nullptr;
}

const char **GREEDYOptionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GREEDYOptionDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GREEDYOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int GREEDYOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *GREEDYOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routingMode",
        "destinationPosition",
        "perimeterRoutingStartPosition",
        "perimeterRoutingForwardPosition",
        "currentFaceFirstSenderAddress",
        "currentFaceFirstReceiverAddress",
        "senderAddress",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int GREEDYOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routingMode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPosition")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "perimeterRoutingStartPosition")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "perimeterRoutingForwardPosition")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "currentFaceFirstSenderAddress")==0) return base+4;
    if (fieldName[0]=='c' && strcmp(fieldName, "currentFaceFirstReceiverAddress")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GREEDYOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "GREEDYForwardingMode",
        "Coord",
        "Coord",
        "Coord",
        "L3Address",
        "L3Address",
        "L3Address",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **GREEDYOptionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GREEDYOptionDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GREEDYOptionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GREEDYOption *pp = (GREEDYOption *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GREEDYOptionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GREEDYOption *pp = (GREEDYOption *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRoutingMode(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDestinationPosition(); return out.str();}
        case 2: {std::stringstream out; out << pp->getPerimeterRoutingStartPosition(); return out.str();}
        case 3: {std::stringstream out; out << pp->getPerimeterRoutingForwardPosition(); return out.str();}
        case 4: {std::stringstream out; out << pp->getCurrentFaceFirstSenderAddress(); return out.str();}
        case 5: {std::stringstream out; out << pp->getCurrentFaceFirstReceiverAddress(); return out.str();}
        case 6: {std::stringstream out; out << pp->getSenderAddress(); return out.str();}
        default: return "";
    }
}

bool GREEDYOptionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GREEDYOption *pp = (GREEDYOption *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GREEDYOptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(GREEDYForwardingMode));
        case 1: return omnetpp::opp_typename(typeid(Coord));
        case 2: return omnetpp::opp_typename(typeid(Coord));
        case 3: return omnetpp::opp_typename(typeid(Coord));
        case 4: return omnetpp::opp_typename(typeid(L3Address));
        case 5: return omnetpp::opp_typename(typeid(L3Address));
        case 6: return omnetpp::opp_typename(typeid(L3Address));
        default: return nullptr;
    };
}

void *GREEDYOptionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GREEDYOption *pp = (GREEDYOption *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRoutingMode()); break;
        case 1: return (void *)(&pp->getDestinationPosition()); break;
        case 2: return (void *)(&pp->getPerimeterRoutingStartPosition()); break;
        case 3: return (void *)(&pp->getPerimeterRoutingForwardPosition()); break;
        case 4: return (void *)(&pp->getCurrentFaceFirstSenderAddress()); break;
        case 5: return (void *)(&pp->getCurrentFaceFirstReceiverAddress()); break;
        case 6: return (void *)(&pp->getSenderAddress()); break;
        default: return nullptr;
    }
}

} // namespace inet

