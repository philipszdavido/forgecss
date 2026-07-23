//
//  Id.hpp
//  ForgeEngine
//
//  Created by Chidume Nnamdi on 14/07/2026.
//

#ifndef Id_hpp
#define Id_hpp

#include <stdio.h>
#include <string>
#include "../Selector/Selector.hpp"

using namespace std;

class IdSelector : public Selector {
public:
    IdSelector(const string name): name(name), Selector(SelectorType::IdSelector) {};
    
    const string name;
};

#endif /* Id_hpp */
