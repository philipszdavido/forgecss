//
//  token.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#ifndef tokens_hpp
#define tokens_hpp

#include <stdio.h>
#include <string>
#include "../TokenType/TokenType.h"

namespace css {
class Token {
    
public:
    const TokenType type;
    const std::string value;
    const std::string unit;
    
    Token(const TokenType type, const std::string value = "", const std::string unit = "") : type(type), value(value), unit(unit) {
    }
    
};

}

#endif /* token_hpp */
