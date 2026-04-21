//
//  Class.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Class_hpp
#define Class_hpp

#include <stdio.h>
#include <string>
#include "../Selector/Selector.hpp"

using namespace std;

class ClassSelector : public Selector {
public:
    SelectorType type = SelectorType::ClassSelector;
    ClassSelector(const string name): name(name) {};
    
    const string name;
};

#endif /* Class_hpp */
