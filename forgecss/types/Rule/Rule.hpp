//
//  Rule.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#ifndef Rule_hpp
#define Rule_hpp

#include <stdio.h>
#include <vector>

class Declaration {
public:
    std::string property;
    std::string value;
};

class Rule {
public:
    std::vector<std::string> selectors;
    std::vector<Declaration> declarations;
    std::vector<Rule> children;
};

#endif /* Rule_hpp */
