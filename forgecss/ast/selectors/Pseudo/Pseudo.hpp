//
//  Pseudo.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Pseudo_hpp
#define Pseudo_hpp

#include <stdio.h>
#include <string>
#include "../Selector/Selector.hpp"

using namespace std;

class PseudoSelector : public Selector {
public:
    SelectorType type = SelectorType::PseudoSelector;
    string name;
    string arg;
    bool isPseudoElement;
    
    PseudoSelector(string name, string arg) : name(name), arg(arg), Selector(SelectorType::PseudoSelector) {}
    PseudoSelector(string name, string arg, bool isPseudoElement) : name(name), arg(arg), isPseudoElement(isPseudoElement), Selector(SelectorType::PseudoSelector) {
    }

};

class PseudoElementSelector : public Selector {
public:
    SelectorType type = SelectorType::PseudoSelector;
    string name;
    string arg;

    PseudoElementSelector(string name, string arg) : name(name), arg(arg), Selector(SelectorType::PseudoSelector) {}

};

class PseudoClassSelector : public Selector {
public:
    SelectorType type = SelectorType::PseudoSelector;
    string name;
    string arg;

    PseudoClassSelector(string name, string arg) : name(name), arg(arg), Selector(SelectorType::PseudoSelector) {}

};

#endif /* Pseudo_hpp */
