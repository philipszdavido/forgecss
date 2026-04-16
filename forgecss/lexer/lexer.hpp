//
//  lexer.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 16/04/2026.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <stdio.h>

#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include "../TokenType/TokenType.h"
#include "../token/token.hpp"

using namespace std;

enum class LexerMode {
    SELECTOR,
    DECLARATION_NAME,
    DECLARATION_VALUE
};

class Lexer {
public:
    Lexer(string input);
    void tokenize();
    vector<Token> tokens;
    void printTokenType(TokenType type);

private:
    string input;
    size_t index = 0;
    LexerMode mode = LexerMode::SELECTOR;

    char current();
    char next();
    bool eof();
    void advance();

    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);

    void add(TokenType type, string value);

    void consumeWhitespace();
    string consumeIdent();
    string consumeString();
    void consumeNumber();
    void consumeIdentLike();
    void consumeURL();
    void consumeAtRule();
    string consumeToSemiColon();
    string consumeVariable();

    void tokenizeSelector();
    void tokenizeDeclarationName();
    void tokenizeDeclarationValue();
    
};

#endif /* lexer_hpp */
