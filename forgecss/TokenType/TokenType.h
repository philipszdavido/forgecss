//
//  TokenType.h
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#ifndef TokenType_h
#define TokenType_h

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

    AT_KEYWORD,

    WHITESPACE,
    DELIM,
    END_OF_FILE
};

#endif /* TokenType_h */
