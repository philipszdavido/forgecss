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

enum class ParserMode {
    SELECTOR,
    DECLARATION_NAME,
    DECLARATION_VALUE
};

class Parser {

private:
    int index = 0;
    Token currentToken();
    ParserMode mode = ParserMode::SELECTOR;
    
  public:
    const std::vector<Token> tokens;
    Parser(const std::vector<Token> tokens) : tokens(tokens) {};
    
    void parse();
    void advance();
    size_t size();
    
    bool isNestedRule();
    void parseSelector();
    void parseDeclarationName();
    void parseDeclarationValue();
    
//    pushState(DeclarationList);
//    popState();
    void consumeSelector();
    void consumeToken(TokenType type);
};

#endif /* parser_hpp */
