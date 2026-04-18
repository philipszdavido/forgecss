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
#include "../types/Rule/Rule.hpp"

enum class ParserMode {
    SELECTOR,
    DECLARATION_NAME,
    DECLARATION_VALUE
};

struct CSSRule {
    int type;
    Rule rule;
    MediaRule mediaRule;
};

class Parser {

private:
    int index = 0;
    Token currentToken();
    
    void advance();
    size_t size();
    
    bool isNestedRule();
    void parseSelector();
    void parseDeclarationName();
    void parseDeclarationValue();
    
    Rule consumeSelector();
    void consumeToken(TokenType type);
    std::string vectorToString(vector<Token> _tokens);
    Declaration consumeDeclItem();
    vector<Declaration> consumeDeclList();
    MediaRule consumeMedia();
    
  public:
    std::vector<CSSRule> rules;
    const std::vector<Token> tokens;
    Parser(const std::vector<Token> tokens) : tokens(tokens) {};
    
    void parse();
};

#endif /* parser_hpp */
