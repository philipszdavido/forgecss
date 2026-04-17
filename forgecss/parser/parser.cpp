//
//  parser.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#include "parser.hpp"

void Parser::parse() {
    
    while (currentToken().type != TokenType::END_OF_FILE) {
        
        Token token = currentToken();
        
        // if selector_start
        // consume till }
        if (token.type == TokenType::SELECTOR_START) {
            consumeSelector();
        }

        advance();
    }
    
}

void Parser::consumeSelector() {
    
    vector<Token> selector;
    
    consumeToken(TokenType::SELECTOR_START);
    
    while (currentToken().type != TokenType::SELECTOR_END) {
        selector.push_back(currentToken());
        advance();
    }
    
    consumeToken(TokenType::SELECTOR_END);
    
    consumeToken(TokenType::LBRACE);
    
    // pick declarations till }
    
}

void Parser::parseSelector() {
    
}

void Parser::parseDeclarationName() {
    
}

void Parser::parseDeclarationValue() {
    
}

bool Parser::isNestedRule() {
  // Look ahead until we find '{' or ':'
//  let j = i;
//
//  while (j < tokens.length) {
//    if (tokens[j].type === "LBRACE") return true;  // nested rule
//    if (tokens[j].type === "COLON") return false;  // declaration
//    j++;
//  }

  return false;
}

void Parser::consumeToken(TokenType type) {

    if (currentToken().type != type) {
        throw "Error";
    }
    
    advance();

}

Token Parser::currentToken() {
    return tokens[index];
}

size_t Parser::size() {
    return tokens.size();
}

void Parser::advance() {
    
    if ((index + 1) > tokens.size()) {
        throw "Out of bounds.";
    }
    
    index++;
    
}
