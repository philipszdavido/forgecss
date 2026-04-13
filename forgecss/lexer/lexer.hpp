//
//  lexer.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Lexer {
public:
    string cssString;
    Lexer(string cssString) : cssString(cssString) {};
    
    void parse();
};

#endif /* lexer_hpp */
