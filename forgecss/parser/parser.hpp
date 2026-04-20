////
////  parser.hpp
////  forgecss
////
////  Created by Chidume Nnamdi on 13/04/2026.
////
//
//#ifndef parser_hpp
//#define parser_hpp
//
//#include <stdio.h>
//#include <vector>
//#include "./../token/token.hpp"
//#include "../types/Rule/Rule.hpp"
//
//struct CSSRule {
//    int type;
//    Rule rule;
//    MediaRule mediaRule;
//};
//
//class Parser {
//
//private:
//    int index = 0;
//    Token currentToken();
//    
//    void advance();
//    size_t size();
//    
//    bool isNestedRule();
//    void parseSelector(vector<Token> selectors);
//    void parseDeclarationName(vector<Token> selectors);
//    void parseDeclarationValue(vector<Token> selectors);
//    
//    Rule consumeSelector();
//    void consumeToken(TokenType type, string msg);
//    std::string vectorToString(vector<Token> _tokens);
//    Declaration consumeDeclItem();
//    R consumeDeclList();
//    MediaRule consumeMedia();
//    
//  public:
//    std::vector<CSSRule> rules;
//    const std::vector<Token> tokens;
//    Parser(const std::vector<Token> tokens) : tokens(tokens) {};
//    
//    void parse();
//};
//
//#endif /* parser_hpp */
