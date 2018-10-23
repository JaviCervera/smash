#include "rapidxml.hpp"
#include "../common/refcounter.h"
#include "../core/array.h"
#include "../core/string.h"
#include "../sdk/smashsdk.h"
#include "../sdk/angelscript.h"

using namespace rapidxml;

static SmashSDK* globSDK = NULL;

class XMLAttribute {
public:
    // (Don't export constructors)
    XMLAttribute() {}
    XMLAttribute(const String& name, const String& value) : name(name), value(value) {}

    const String& Name() const { return name; }
    const String& Value() const { return value; }
private:
    String name;
    String value;
};

class XMLElement {
public:
    // (Don't export constructors)
    XMLElement() {}
    XMLElement(const String& name, const String& value, const Array<XMLAttribute>& attributes, const Array<XMLElement*>& children) : name(name), value(value), attributes(attributes), children(children) {}
    ~XMLElement() { for ( int i = 0; i < children.Size(); i++ ) delete children[i]; }

    const String& Name() const { return name; }
    const String& Value() const { return value; }

    unsigned int CountAttributes() const { return attributes.Size(); }
    const XMLAttribute* Attribute(unsigned int index) const { return &attributes[index]; }
    const XMLAttribute* FindAttribute(const String& name) const;

    unsigned int CountChildren(const String& name = "") const;
    const XMLElement* Child(unsigned int index, const String& name = "") const;
private:
    String name;
    String value;
    Array<XMLAttribute> attributes;
    Array<XMLElement*> children;    // If i change this to Array<XMLElement> it crashes. WHY ?!?!?!
};

class XMLDocument : public RefCounter {
public:
    XMLDocument(const String& contents);
    ~XMLDocument() { if ( root ) delete root; }

    bool IsOk() const { return isOk; }
    const XMLElement* Root() const { return root; }
    const String& Error() const { return error; }
protected:
    XMLElement* _ParseElement(xml_node<>* node);
private:
    bool isOk;
    XMLElement* root;
    String error;
};

inline XMLDocument::XMLDocument(const String& contents) {
    // isOk is false until the end of the constructor
    isOk = false;
    root = NULL;
    error = "";

    try {
        // Parse XML
        xml_document<> doc;
        doc.parse<0>((char*)contents.ToCString());

        // Parse root element
        root = _ParseElement(doc.first_node());

        // We are done
        isOk = true;
    } catch ( parse_error& e ) {
        error = e.what();
    }
}

inline XMLElement* XMLDocument::_ParseElement(xml_node<>* node) {
    // Parse attributes
    Array<XMLAttribute> attributes;
    xml_attribute<>* attr = node->first_attribute();
    while ( attr ) {
        attributes.Add(XMLAttribute(attr->name(), attr->value()));
        attr = attr->next_attribute();
    }

    // Parse children
    Array<XMLElement*> children;
    xml_node<>* child = node->first_node();
    while ( child ) {
        children.Add(_ParseElement(child));
        child = child->next_sibling();
    }

    // Return element
    return new XMLElement(node->name(), node->value(), attributes, children);
}

inline const XMLAttribute* XMLElement::FindAttribute(const String& name) const {
    for ( int i = 0; i < attributes.Size(); i++ ) {
        if ( attributes[i].Name() == name ) return &attributes[i];
    }
    return NULL;
}

inline unsigned int XMLElement::CountChildren(const String& name) const {
    if ( name == "" ) {
        return children.Size();
    } else {
        unsigned int count = 0;
        for ( int i = 0; i < children.Size(); i++ ) {
            if ( children[i]->Name() == name ) count++;
        }
        return count;
    }
}

inline const XMLElement* XMLElement::Child(unsigned int index, const String& name) const {
    if ( name == "" ) {
        return children[index];
    } else {
        unsigned int count = 0;
        for ( int i = 0; i < children.Size(); i++ ) {
            if ( children[i]->Name() == name ) {
                if ( count == index ) return children[i];
                count++;
            }
        }
    }
    return NULL;
}

static XMLDocument* XMLDocumentFactory(const String& contents) {
    return new XMLDocument(contents);
}

extern "C" SDKFUNC void LoadModule(SmashSDK* sdk) {
    globSDK = sdk;

    // XMLAttribute
    sdk->RegisterClass("XMLAttribute", 0, asOBJ_REF | asOBJ_NOCOUNT);
    sdk->RegisterMethod("XMLAttribute", "const String& Name() const", asMETHOD(XMLAttribute, Name), asCALL_THISCALL);
    sdk->RegisterMethod("XMLAttribute", "const String& Value() const", asMETHOD(XMLAttribute, Value), asCALL_THISCALL);

    // XMLElement
    sdk->RegisterClass("XMLElement", 0, asOBJ_REF | asOBJ_NOCOUNT);
    sdk->RegisterMethod("XMLElement", "const String& Name() const", asMETHOD(XMLElement, Name), asCALL_THISCALL);
    sdk->RegisterMethod("XMLElement", "const String& Value() const", asMETHOD(XMLElement, Value), asCALL_THISCALL);
    sdk->RegisterMethod("XMLElement", "uint CountAttributes() const", asMETHOD(XMLElement, CountAttributes), asCALL_THISCALL);
    sdk->RegisterMethod("XMLElement", "const XMLAttribute& Attribute(uint) const", asMETHOD(XMLElement, Attribute), asCALL_THISCALL);
    sdk->RegisterMethod("XMLElement", "const XMLAttribute& Attribute(const String& in) const", asMETHOD(XMLElement, FindAttribute), asCALL_THISCALL);
    sdk->RegisterMethod("XMLElement", "uint CountChildren(const String& in = \"\") const", asMETHOD(XMLElement, CountChildren), asCALL_THISCALL);
    sdk->RegisterMethod("XMLElement", "const XMLElement& Child(uint i, const String& in = \"\") const", asMETHOD(XMLElement, Child), asCALL_THISCALL);

    // XMLDocument
    sdk->RegisterClass("XMLDocument", 0, asOBJ_REF);
    sdk->RegisterBehaviour("XMLDocument", asBEHAVE_FACTORY, "XMLDocument@ f(const String& in)", asFUNCTION(XMLDocumentFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("XMLDocument", asBEHAVE_ADDREF, "void f()", asMETHOD(XMLDocument, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("XMLDocument", asBEHAVE_RELEASE, "void f()", asMETHOD(XMLDocument, Release), asCALL_THISCALL);
    sdk->RegisterMethod("XMLDocument", "bool IsOk() const", asMETHOD(XMLDocument, IsOk), asCALL_THISCALL);
    sdk->RegisterMethod("XMLDocument", "const XMLElement& Root() const", asMETHOD(XMLDocument, Root), asCALL_THISCALL);
    sdk->RegisterMethod("XMLDocument", "const String& Error() const", asMETHOD(XMLDocument, Error), asCALL_THISCALL);
}
