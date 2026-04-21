//
//  Pseudo.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Pseudo_hpp
#define Pseudo_hpp

#include <stdio.h>
#include "../Selector/Selector.hpp"

class PseudoSelector : public Selector {
    SelectorType type = SelectorType::PseudoSelector;
};

#endif /* Pseudo_hpp */
