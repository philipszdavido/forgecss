//
//  TokenType.h
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#ifndef TokenType_h
#define TokenType_h

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

enum class TokenType {
    
    LBRACE, RBRACE,
    LPAREN, RPAREN,
    LBRACKET, RBRACKET,
    COLON, SEMICOLON,
    COMMA,

    DOT, HASH, IDENT,
    DOUBLE_COLON,

    NUMBER,
    DIMENSION,
    PERCENTAGE,
    STRING,
    FUNCTION,
    URL,
    VARIABLE,
    FUNCTION_ARG,
    VALUE_END,
    VALUE_START,

    AT_KEYWORD,
    
    DECLARATION_NAME_START,
    DECLARATION_NAME_END,
    DECLARATION_VALUE_START,
    DECLARATION_VALUE_END,
    SELECTOR_START,
    SELECTOR_END,

    WHITESPACE,
    DELIM,
    END_OF_FILE
};

void printTokenType(TokenType type);

#endif /* TokenType_h */
