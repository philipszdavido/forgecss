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
    UniversalSelector,
    TypeSelector,
    IdSelector,
    ClassSelector,
    AttributeSelector,
    PseudoSelector,
    CompoundSelector,
};

class Selector {
public:
    SelectorType type;

    Selector(SelectorType t)
        : type(t) {}

    virtual ~Selector() = default;
};

#endif /* Selector_hpp */
