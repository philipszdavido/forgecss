//
//  TokenType.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 17/04/2026.
//

#include "./TokenType.h"

void printTokenType(TokenType type) {
    switch (type) {
        case TokenType::LBRACE: std::cout << "LBRACE"; break;
        case TokenType::RBRACE: std::cout << "RBRACE"; break;
        case TokenType::LPAREN: std::cout << "LPAREN"; break;
        case TokenType::RPAREN: std::cout << "RPAREN"; break;
        case TokenType::LBRACKET: std::cout << "LBRACKET"; break;
        case TokenType::RBRACKET: std::cout << "RBRACKET"; break;

        case TokenType::COLON: std::cout << "COLON"; break;
        case TokenType::SEMICOLON: std::cout << "SEMICOLON"; break;
        case TokenType::COMMA: std::cout << "COMMA"; break;

        case TokenType::DOT: std::cout << "DOT"; break;
        case TokenType::HASH: std::cout << "HASH"; break;
        case TokenType::IDENT: std::cout << "IDENT"; break;
        case TokenType::DOUBLE_COLON: std::cout << "DOUBLE_COLON"; break;

        case TokenType::NUMBER: std::cout << "NUMBER"; break;
        case TokenType::DIMENSION: std::cout << "DIMENSION"; break;
        case TokenType::PERCENTAGE: std::cout << "PERCENTAGE"; break;
        case TokenType::STRING: std::cout << "STRING"; break;
        case TokenType::FUNCTION: std::cout << "FUNCTION"; break;
        case TokenType::URL: std::cout << "URL"; break;
        case TokenType::VARIABLE: std::cout << "VARIABLE"; break;
        case TokenType::VALUE_START: std::cout << "VALUE_START"; break;
        case TokenType::VALUE_END: std::cout << "VALUE_END"; break;
        case TokenType::SELECTOR_START: std::cout << "SELECTOR_START"; break;
        case TokenType::SELECTOR_END: std::cout << "SELECTOR_END"; break;


        case TokenType::AT_KEYWORD: std::cout << "AT_KEYWORD"; break;
            
        case TokenType::DECLARATION_NAME_START: std::cout << "DECLARATION_NAME_START"; break;
        case TokenType::DECLARATION_NAME_END: std::cout << "DECLARATION_NAME_END"; break;
        case TokenType::DECLARATION_VALUE_START: std::cout << "DECLARATION_VALUE_START"; break;
        case TokenType::DECLARATION_VALUE_END: std::cout << "DECLARATION_VALUE_END"; break;

        case TokenType::WHITESPACE: std::cout << "WHITESPACE"; break;
        case TokenType::DELIM: std::cout << "DELIM"; break;

        case TokenType::END_OF_FILE: std::cout << "EOF"; break;

        default:
            std::cout << "UNKNOWN";
            break;
    }
}
