//
//  TokenType.h
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#ifndef TokenType_h
#define TokenType_h

enum TokenType {
    SELECTOR_START,
    DECLARATION_START,
    PROPERTY,
    COLON, // :
    VALUE,
    COMMA, // ,
    DOT, // .
    LPAREN, // (
    RPAREN, // )
    LBRACE, // {
    RBRACE, // }
    L_SBRACE, // ]
    R_SBRACE, // [
    SEMI_COLON, // ;
    IDENTIFIER,
    DECLARATION_END,
};

#endif /* TokenType_h */
