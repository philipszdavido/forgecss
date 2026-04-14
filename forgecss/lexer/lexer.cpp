//
//  lexer.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#include "lexer.hpp"

void Lexer::parse() {
    
    while (index < cssString.length()) {
        char _currentChar = currentChar();
        
        switch (_currentChar) {
                
            case ':':
                addToken(TokenType::COLON, to_string(_currentChar));
                break;
                
            case ';':
                addToken(TokenType::SEMI_COLON, to_string(_currentChar));
                break;
                
            case ',':
                addToken(TokenType::COMMA, to_string(_currentChar));
                break;
                
            case '.':
                addToken(TokenType::DOT, to_string(_currentChar));
                break;
                
            case '{':
                addToken(TokenType::LBRACE, to_string(_currentChar));
                break;
            
            case '}':
                addToken(TokenType::RBRACE, to_string(_currentChar));
                break;
                
            case '-':
                addToken(TokenType::HYPEN, to_string(_currentChar));
                break;
                
            default:
                if (isAlpha()) {
                    collectIdentifier();
                }
                break;
        }
        advance();
    }
}

void Lexer::collectIdentifier() {
    
    string ident = "";
    ident += (currentChar());
    
    while (!isEOF() && isAlpha()) {
        advance();
        if(isAlpha()) {
            ident += currentChar();
        }
    }
    addToken(TokenType::IDENTIFIER, ident);
    index--;

}

void Lexer::addToken(const TokenType type, const string value) {
    tokens.push_back(Token(type, value));
}

char Lexer::currentChar() { return cssString[index]; }

bool Lexer::isAlpha() {
    
    char _char = currentChar();
        
    return (_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z');
}

void Lexer::advance() {
    index++;
}

bool Lexer::isEOF() {
    if (index > cssString.length()) {
        return true;
    }
    
    return false;
}

string Lexer::to_string(const char v) {
    std::string temp = "";
    temp += v;
    return temp;
}
