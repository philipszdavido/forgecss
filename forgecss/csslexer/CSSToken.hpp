//
//  CSSToken.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#ifndef CSSToken_hpp
#define CSSToken_hpp

#include <stdio.h>
#include <string>
#include "../TokenType/TokenType.h"

using namespace std;

struct CSSToken {
    TokenType type;
    string value;

    CSSToken(TokenType t, string v = "") : type(t), value(v) {}
};

#endif /* CSSToken_hpp */
