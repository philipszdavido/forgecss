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

class AttributeSelector : Selector {

    SelectorType type = SelectorType::AttributeSelector;

    AttributeSelector(string name) : name(name) {};

    string name;
    
//    operator,
//    value

};

#endif /* Attribute_hpp */
