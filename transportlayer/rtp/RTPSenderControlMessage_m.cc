//
// Generated file, do not edit! Created by nedtool 5.0 from inet/transportlayer/rtp/RTPSenderControlMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RTPSenderControlMessage_m.h"

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
namespace rtp {

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

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::rtp::RTPSenderControlMessageCommands");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::rtp::RTPSenderControlMessageCommands"));
    e->insert(RTP_CONTROL_PLAY, "RTP_CONTROL_PLAY");
    e->insert(RTP_CONTROL_PLAY_UNTIL_TIME, "RTP_CONTROL_PLAY_UNTIL_TIME");
    e->insert(RTP_CONTROL_PLAY_UNTIL_BYTE, "RTP_CONTROL_PLAY_UNTIL_BYTE");
    e->insert(RTP_CONTROL_PAUSE, "RTP_CONTROL_PAUSE");
    e->insert(RTP_CONTROL_STOP, "RTP_CONTROL_STOP");
    e->insert(RTP_CONTROL_SEEK_TIME, "RTP_CONTROL_SEEK_TIME");
    e->insert(RTP_CONTROL_SEEK_BYTE, "RTP_CONTROL_SEEK_BYTE");
);

Register_Class(RTPSenderControlMessage);

RTPSenderControlMessage::RTPSenderControlMessage(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->command = 0;
    this->commandParameter1 = 0;
    this->commandParameter2 = 0;
}

RTPSenderControlMessage::RTPSenderControlMessage(const RTPSenderControlMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RTPSenderControlMessage::~RTPSenderControlMessage()
{
}

RTPSenderControlMessage& RTPSenderControlMessage::operator=(const RTPSenderControlMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void RTPSenderControlMessage::copy(const RTPSenderControlMessage& other)
{
    this->command = other.command;
    this->commandParameter1 = other.commandParameter1;
    this->commandParameter2 = other.commandParameter2;
}

void RTPSenderControlMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->command);
    doParsimPacking(b,this->commandParameter1);
    doParsimPacking(b,this->commandParameter2);
}

void RTPSenderControlMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->command);
    doParsimUnpacking(b,this->commandParameter1);
    doParsimUnpacking(b,this->commandParameter2);
}

short RTPSenderControlMessage::getCommand() const
{
    return this->command;
}

void RTPSenderControlMessage::setCommand(short command)
{
    this->command = command;
}

float RTPSenderControlMessage::getCommandParameter1() const
{
    return this->commandParameter1;
}

void RTPSenderControlMessage::setCommandParameter1(float commandParameter1)
{
    this->commandParameter1 = commandParameter1;
}

float RTPSenderControlMessage::getCommandParameter2() const
{
    return this->commandParameter2;
}

void RTPSenderControlMessage::setCommandParameter2(float commandParameter2)
{
    this->commandParameter2 = commandParameter2;
}

class RTPSenderControlMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RTPSenderControlMessageDescriptor();
    virtual ~RTPSenderControlMessageDescriptor();

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

Register_ClassDescriptor(RTPSenderControlMessageDescriptor);

RTPSenderControlMessageDescriptor::RTPSenderControlMessageDescriptor() : omnetpp::cClassDescriptor("inet::rtp::RTPSenderControlMessage", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

RTPSenderControlMessageDescriptor::~RTPSenderControlMessageDescriptor()
{
    delete[] propertynames;
}

bool RTPSenderControlMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RTPSenderControlMessage *>(obj)!=nullptr;
}

const char **RTPSenderControlMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RTPSenderControlMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RTPSenderControlMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int RTPSenderControlMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *RTPSenderControlMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "command",
        "commandParameter1",
        "commandParameter2",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int RTPSenderControlMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "commandParameter1")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "commandParameter2")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RTPSenderControlMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",
        "float",
        "float",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **RTPSenderControlMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RTPSenderControlMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "inet::rtp::RTPSenderControlMessageCommands";
            return nullptr;
        default: return nullptr;
    }
}

int RTPSenderControlMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RTPSenderControlMessage *pp = (RTPSenderControlMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RTPSenderControlMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RTPSenderControlMessage *pp = (RTPSenderControlMessage *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getCommand(), "inet::rtp::RTPSenderControlMessageCommands");
        case 1: return double2string(pp->getCommandParameter1());
        case 2: return double2string(pp->getCommandParameter2());
        default: return "";
    }
}

bool RTPSenderControlMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RTPSenderControlMessage *pp = (RTPSenderControlMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setCommand((inet::rtp::RTPSenderControlMessageCommands)string2enum(value, "inet::rtp::RTPSenderControlMessageCommands")); return true;
        case 1: pp->setCommandParameter1(string2double(value)); return true;
        case 2: pp->setCommandParameter2(string2double(value)); return true;
        default: return false;
    }
}

const char *RTPSenderControlMessageDescriptor::getFieldStructName(int field) const
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

void *RTPSenderControlMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RTPSenderControlMessage *pp = (RTPSenderControlMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace rtp
} // namespace inet
