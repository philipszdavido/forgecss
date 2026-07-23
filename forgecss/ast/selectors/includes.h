//
//  includes.h
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef includes_h
#define includes_h

#include <vector>
#include "./Selector/Selector.hpp"
#include "./Class/Class.hpp"
#include "./Pseudo/Pseudo.hpp"
#include "./Attribute/Attribute.hpp"

using namespace std;

//Compound Selector
//struct CompoundSelector {
//    vector<Selector> simpleSelectors;
//};

//enum class Combinator { DESCENDANT, CHILD, ADJACENT, GENERAL_SIBLING };
//
//struct ComplexSelector {
//    vector<pair<Combinator, CompoundSelector>> parts;
//};

//Selector List (comma-separated)

enum class Combinator {
    DESCENDANT,
    CHILD,
    NEXT_SIBLING,
    SUBSEQUENT_SIBLING
};

class TypeSelector : public Selector {
public:
    std::string name;

    TypeSelector(std::string name)
        : Selector(SelectorType::TypeSelector),
          name(std::move(name))
    {}
};

class UniversalSelector : public Selector {
public:
    UniversalSelector()
        : Selector(SelectorType::UniversalSelector)
    {}
};

class IdSelector : public Selector {
public:
    std::string name;

    IdSelector(std::string name)
        : Selector(SelectorType::IdSelector),
          name(std::move(name))
    {}
};

class CompoundSelector : public Selector {
public:
    std::vector<std::shared_ptr<Selector>> parts;

    CompoundSelector()
        : Selector(SelectorType::CompoundSelector)
    {}
};

class ComplexSelectorPart {
public:
    Combinator combinator;
    CompoundSelector compound;
};

using ComplexSelector = std::vector<ComplexSelectorPart>;

#endif /* includes_h */
