//
//  Attribute.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Attribute_hpp
#define Attribute_hpp

#include <stdio.h>
#include <string>
#include "../Selector/Selector.hpp"

using namespace std;

class AttributeSelector : public Selector {

public:
    
    SelectorType type = SelectorType::AttributeSelector;

    AttributeSelector(string name) : name(name), Selector(SelectorType::AttributeSelector) {};
    AttributeSelector(string name, string value, bool hasValue) : name(name), value(value), hasValue(hasValue), Selector(SelectorType::AttributeSelector) {};
    AttributeSelector(string name, string value, bool hasValue, string op, bool caseInsensitive) : name(name), value(value), hasValue(hasValue), op(op), caseInsensitive(caseInsensitive), Selector(SelectorType::AttributeSelector) {
    };

    string name;
    string op;
    bool caseInsensitive;
    // operator
    string value;
    bool hasValue;

};

#endif /* Attribute_hpp */
