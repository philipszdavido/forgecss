//
//  parser.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include <vector>
#include "./../token/token.hpp"

class Parser {
    
  public:
    const std::vector<Token> tokens;
    Parser(const std::vector<Token> tokens) : tokens(tokens) {};
    
    void parse();
    
};

#endif /* parser_hpp */
