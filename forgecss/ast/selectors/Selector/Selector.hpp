//
//  Selector.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Selector_hpp
#define Selector_hpp

#include <stdio.h>

enum class SelectorType {
    ClassSelector,
    AttributeSelector,
    PseudoSelector
};

class Selector {
public:
    SelectorType type;
};

#endif /* Selector_hpp */
