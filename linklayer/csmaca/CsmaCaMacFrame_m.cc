//
// Generated file, do not edit! Created by nedtool 5.0 from inet/linklayer/csmaca/CsmaCaMacFrame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CsmaCaMacFrame_m.h"

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

Register_Class(CsmaCaMacFrame);

CsmaCaMacFrame::CsmaCaMacFrame(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
}

CsmaCaMacFrame::CsmaCaMacFrame(const CsmaCaMacFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

CsmaCaMacFrame::~CsmaCaMacFrame()
{
}

CsmaCaMacFrame& CsmaCaMacFrame::operator=(const CsmaCaMacFrame& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void CsmaCaMacFrame::copy(const CsmaCaMacFrame& other)
{
    this->transmitterAddress = other.transmitterAddress;
    this->receiverAddress = other.receiverAddress;
}

void CsmaCaMacFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->transmitterAddress);
    doParsimPacking(b,this->receiverAddress);
}

void CsmaCaMacFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->transmitterAddress);
    doParsimUnpacking(b,this->receiverAddress);
}

MACAddress& CsmaCaMacFrame::getTransmitterAddress()
{
    return this->transmitterAddress;
}

void CsmaCaMacFrame::setTransmitterAddress(const MACAddress& transmitterAddress)
{
    this->transmitterAddress = transmitterAddress;
}

MACAddress& CsmaCaMacFrame::getReceiverAddress()
{
    return this->receiverAddress;
}

void CsmaCaMacFrame::setReceiverAddress(const MACAddress& receiverAddress)
{
    this->receiverAddress = receiverAddress;
}

class CsmaCaMacFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CsmaCaMacFrameDescriptor();
    virtual ~CsmaCaMacFrameDescriptor();

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

Register_ClassDescriptor(CsmaCaMacFrameDescriptor);

CsmaCaMacFrameDescriptor::CsmaCaMacFrameDescriptor() : omnetpp::cClassDescriptor("inet::CsmaCaMacFrame", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

CsmaCaMacFrameDescriptor::~CsmaCaMacFrameDescriptor()
{
    delete[] propertynames;
}

bool CsmaCaMacFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsmaCaMacFrame *>(obj)!=nullptr;
}

const char **CsmaCaMacFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CsmaCaMacFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CsmaCaMacFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CsmaCaMacFrameDescriptor::getFieldTypeFlags(int field) const
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

const char *CsmaCaMacFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "transmitterAddress",
        "receiverAddress",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CsmaCaMacFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmitterAddress")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiverAddress")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CsmaCaMacFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "MACAddress",
        "MACAddress",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CsmaCaMacFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *CsmaCaMacFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CsmaCaMacFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacFrame *pp = (CsmaCaMacFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CsmaCaMacFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacFrame *pp = (CsmaCaMacFrame *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getTransmitterAddress(); return out.str();}
        case 1: {std::stringstream out; out << pp->getReceiverAddress(); return out.str();}
        default: return "";
    }
}

bool CsmaCaMacFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacFrame *pp = (CsmaCaMacFrame *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CsmaCaMacFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(MACAddress));
        case 1: return omnetpp::opp_typename(typeid(MACAddress));
        default: return nullptr;
    };
}

void *CsmaCaMacFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacFrame *pp = (CsmaCaMacFrame *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getTransmitterAddress()); break;
        case 1: return (void *)(&pp->getReceiverAddress()); break;
        default: return nullptr;
    }
}

Register_Class(CsmaCaMacAckFrame);

CsmaCaMacAckFrame::CsmaCaMacAckFrame(const char *name, int kind) : ::inet::CsmaCaMacFrame(name,kind)
{
}

CsmaCaMacAckFrame::CsmaCaMacAckFrame(const CsmaCaMacAckFrame& other) : ::inet::CsmaCaMacFrame(other)
{
    copy(other);
}

CsmaCaMacAckFrame::~CsmaCaMacAckFrame()
{
}

CsmaCaMacAckFrame& CsmaCaMacAckFrame::operator=(const CsmaCaMacAckFrame& other)
{
    if (this==&other) return *this;
    ::inet::CsmaCaMacFrame::operator=(other);
    copy(other);
    return *this;
}

void CsmaCaMacAckFrame::copy(const CsmaCaMacAckFrame& other)
{
}

void CsmaCaMacAckFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::CsmaCaMacFrame::parsimPack(b);
}

void CsmaCaMacAckFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::CsmaCaMacFrame::parsimUnpack(b);
}

class CsmaCaMacAckFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CsmaCaMacAckFrameDescriptor();
    virtual ~CsmaCaMacAckFrameDescriptor();

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

Register_ClassDescriptor(CsmaCaMacAckFrameDescriptor);

CsmaCaMacAckFrameDescriptor::CsmaCaMacAckFrameDescriptor() : omnetpp::cClassDescriptor("inet::CsmaCaMacAckFrame", "inet::CsmaCaMacFrame")
{
    propertynames = nullptr;
}

CsmaCaMacAckFrameDescriptor::~CsmaCaMacAckFrameDescriptor()
{
    delete[] propertynames;
}

bool CsmaCaMacAckFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsmaCaMacAckFrame *>(obj)!=nullptr;
}

const char **CsmaCaMacAckFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CsmaCaMacAckFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CsmaCaMacAckFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int CsmaCaMacAckFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *CsmaCaMacAckFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int CsmaCaMacAckFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CsmaCaMacAckFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **CsmaCaMacAckFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *CsmaCaMacAckFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CsmaCaMacAckFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacAckFrame *pp = (CsmaCaMacAckFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CsmaCaMacAckFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacAckFrame *pp = (CsmaCaMacAckFrame *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool CsmaCaMacAckFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacAckFrame *pp = (CsmaCaMacAckFrame *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CsmaCaMacAckFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *CsmaCaMacAckFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacAckFrame *pp = (CsmaCaMacAckFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(CsmaCaMacDataFrame);

CsmaCaMacDataFrame::CsmaCaMacDataFrame(const char *name, int kind) : ::inet::CsmaCaMacFrame(name,kind)
{
    this->priority = 0;
}

CsmaCaMacDataFrame::CsmaCaMacDataFrame(const CsmaCaMacDataFrame& other) : ::inet::CsmaCaMacFrame(other)
{
    copy(other);
}

CsmaCaMacDataFrame::~CsmaCaMacDataFrame()
{
}

CsmaCaMacDataFrame& CsmaCaMacDataFrame::operator=(const CsmaCaMacDataFrame& other)
{
    if (this==&other) return *this;
    ::inet::CsmaCaMacFrame::operator=(other);
    copy(other);
    return *this;
}

void CsmaCaMacDataFrame::copy(const CsmaCaMacDataFrame& other)
{
    this->priority = other.priority;
}

void CsmaCaMacDataFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::CsmaCaMacFrame::parsimPack(b);
    doParsimPacking(b,this->priority);
}

void CsmaCaMacDataFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::CsmaCaMacFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->priority);
}

int CsmaCaMacDataFrame::getPriority() const
{
    return this->priority;
}

void CsmaCaMacDataFrame::setPriority(int priority)
{
    this->priority = priority;
}

class CsmaCaMacDataFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CsmaCaMacDataFrameDescriptor();
    virtual ~CsmaCaMacDataFrameDescriptor();

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

Register_ClassDescriptor(CsmaCaMacDataFrameDescriptor);

CsmaCaMacDataFrameDescriptor::CsmaCaMacDataFrameDescriptor() : omnetpp::cClassDescriptor("inet::CsmaCaMacDataFrame", "inet::CsmaCaMacFrame")
{
    propertynames = nullptr;
}

CsmaCaMacDataFrameDescriptor::~CsmaCaMacDataFrameDescriptor()
{
    delete[] propertynames;
}

bool CsmaCaMacDataFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsmaCaMacDataFrame *>(obj)!=nullptr;
}

const char **CsmaCaMacDataFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CsmaCaMacDataFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CsmaCaMacDataFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int CsmaCaMacDataFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CsmaCaMacDataFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "priority",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int CsmaCaMacDataFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CsmaCaMacDataFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **CsmaCaMacDataFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *CsmaCaMacDataFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CsmaCaMacDataFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacDataFrame *pp = (CsmaCaMacDataFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CsmaCaMacDataFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacDataFrame *pp = (CsmaCaMacDataFrame *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPriority());
        default: return "";
    }
}

bool CsmaCaMacDataFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacDataFrame *pp = (CsmaCaMacDataFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setPriority(string2long(value)); return true;
        default: return false;
    }
}

const char *CsmaCaMacDataFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *CsmaCaMacDataFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CsmaCaMacDataFrame *pp = (CsmaCaMacDataFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace inet
