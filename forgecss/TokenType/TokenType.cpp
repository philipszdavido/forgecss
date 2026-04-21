//
//  TokenType.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 17/04/2026.
//

#include "./TokenType.h"

void printTokenType(TokenType type) {
    switch (type) {
            
        case TokenType::LEFT_BRACE: std::cout << "LEFT_BRACE"; break;
        case TokenType::RIGHT_BRACE: std::cout << "RIGHT_BRACE"; break;
        case TokenType::LEFT_PAREN: std::cout << "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN: std::cout << "RIGHT_PAREN"; break;
        case TokenType::LEFT_BRACKET: std::cout << "LEFT_BRACKET"; break;
        case TokenType::RIGHT_BRACKET: std::cout << "RIGHT_BRACKET"; break;
        case TokenType::BAD_STRING: std::cout << "BAD_STRING"; break;

        case TokenType::COLON: std::cout << "COLON"; break;
        case TokenType::SEMICOLON: std::cout << "SEMICOLON"; break;
        case TokenType::COMMA: std::cout << "COMMA"; break;

        case TokenType::DOT: std::cout << "DOT"; break;
        case TokenType::HASH: std::cout << "HASH"; break;
        case TokenType::IDENT: std::cout << "IDENT"; break;
        case TokenType::DOUBLE_COLON: std::cout << "DOUBLE_COLON"; break;
        case TokenType::LEFT_SQUARE_BRACE: std::cout << "LEFT_SQUARE_BRACE"; break;
        case TokenType::RIGHT_SQUARE_BRACE: std::cout << "RIGHT_SQUARE_BRACE"; break;

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
        case TokenType::MEDIA_START: std::cout << "MEDIA_START"; break;
        case TokenType::MEDIA_END: std::cout << "MEDIA_END"; break;


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
