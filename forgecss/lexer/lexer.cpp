////
////  lexer.cpp
////  forgecss
////
////  Created by Chidume Nnamdi on 13/04/2026.
////
//
//#include "lexer.hpp"
//
//#include <unordered_set>
//
//const std::unordered_set<char> IDENTIFIER_SYMBOLS = {
//    '_', '-', '$', '.', '(', ')'
//};
//
//void Lexer::parse() {
//    
//    bool isSelector = false;
//    bool isProperty = false;
//    int insideRulesCounter = 0;
//    
//    while (index < cssString.length()) {
//        char _currentChar = currentChar();
//        
//        switch (_currentChar) {
//                
//            case ':':
//                
//                if (matchNext(':')) {
//                    addToken(TokenType::DOUBLE_COLON, "::");
//                    break;
//                }
//                addToken(TokenType::COLON, to_string(_currentChar));
//                
//                // we might be in the propertty
//                // collect identifier till ;
//                
//                break;
//                
//            case ';':
//                addToken(TokenType::SEMI_COLON, to_string(_currentChar));
//                break;
//                
//            case ',':
//                addToken(TokenType::COMMA, to_string(_currentChar));
//                break;
//                
//            case '.':
//                
//                if (isAlphaNumeric(nextChar())) {
//                    collectIdentifier();
//                    break;
//                }
//                
//                addToken(TokenType::DOT, to_string(_currentChar));
//                break;
//                
//            case '{':
//                
//                insideRulesCounter++;
//                
//                addToken(TokenType::LBRACE, to_string(_currentChar));
//                
//                break;
//            
//            case '}':
//                
//                insideRulesCounter--;
//                
//                addToken(TokenType::RBRACE, to_string(_currentChar));
//                
//                break;
//                
//            case '[':
//                addToken(TokenType::L_SBRACE, to_string(_currentChar));
//                break;
//            
//            case ']':
//                addToken(TokenType::R_SBRACE, to_string(_currentChar));
//                break;
//                
//            case '(':
//                addToken(TokenType::LPAREN, to_string(_currentChar));
//                break;
//            
//            case ')':
//                addToken(TokenType::RPAREN, to_string(_currentChar));
//                break;
//
//            case '-':
//                
//                if (matchNext('-')) {
//                    
//                    advance();
//                    
//                    if (isAlphaNumeric(currentChar())) {
//                        collectIdentifier("--");
//                        break;
//                    }
//                    
//                    addToken(TokenType::DOUBLE_HYPEN, "--");
//                    break;
//                }
//
//                addToken(TokenType::HYPEN, to_string(_currentChar));
//                break;
//                
//            case '#':
//                // pick till you hit ; or space or newline
//                collectIdentifier();
//                break;
//                
//            default:
//                if (isAlphaNumeric()) {
//                    collectIdentifier();
//                }
//                break;
//        }
//        advance();
//    }
//}
//
//bool Lexer::matchNext(const char value) {
//    
//    if (isEOF()) {
//        return false;
//    }
//    
//    auto next = cssString[index + 1];
//    if (next && next == value) {
//        advance();
//        return true;
//    }
//    
//    return false;
//}
//
//void Lexer::collectIdentifier() {
//    
//    string ident = "";
//    ident += (currentChar());
//    advance();
//
//    while (!isEOF() && (isAlphaNumeric() || IDENTIFIER_SYMBOLS.contains(currentChar()))) {
//        ident += currentChar();
//        advance();
//    }
//    
//    addToken(TokenType::IDENTIFIER, ident);
//    index--;
//
//}
//
//void Lexer::collectIdentifier(const string str) {
//    
//    string ident = str;
//
//    while (!isEOF() && (isAlphaNumeric() || IDENTIFIER_SYMBOLS.contains(currentChar()))) {
//        ident += currentChar();
//        advance();
//    }
//    
//    addToken(TokenType::IDENTIFIER, ident);
//    index--;
//
//}
//
////void Lexer::collectIdentifierTillSemiColon() {
////    
////}
//
//void Lexer::addToken(const TokenType type, const string value) {
//    tokens.push_back(Token(type, value));
//}
//
//char Lexer::currentChar() { return cssString[index]; }
//char Lexer::nextChar() { return cssString[index + 1]; }
//
//bool Lexer::isAlphaNumeric() {
//    
//    char _char = currentChar();
//        
//    return (_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z') || (_char >= '0' && _char <= '9');
//}
//
//bool Lexer::isAlphaNumeric(const char _char) {
//    return (_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z') || (_char >= '0' && _char <= '9');
//}
//
//bool Lexer::isAlpha() {
//    
//    char _char = currentChar();
//        
//    return (_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z');
//}
//
//void Lexer::advance() {
//    index++;
//}
//
//bool Lexer::isEOF() {
//    if (index > cssString.length()) {
//        return true;
//    }
//    
//    return false;
//}
//
//string Lexer::to_string(const char v) {
//    std::string temp = "";
//    temp += v;
//    return temp;
//}
