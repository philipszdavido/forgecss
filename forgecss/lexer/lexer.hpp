////
////  lexer.hpp
////  forgecss
////
////  Created by Chidume Nnamdi on 13/04/2026.
////
//
//#ifndef lexer_hpp
//#define lexer_hpp
//
//#include <stdio.h>
//#include <string>
//#include <vector>
//#include <cctype>
//#include <ostream>
//#include <iostream>
//#include "./../token/token.hpp"
//#include "./../TokenType/TokenType.h"
//
//using namespace std;
//
//class Lexer {
//
//public:
//    string cssString;
//    int index = 0;
//    vector<Token> tokens;
//    
//    Lexer(string cssString) : cssString(cssString) {};
//    
//    void parse();
//    void addToken(const TokenType type, const string value);
//    bool isAlpha();
//    bool isAlphaNumeric();
//    bool isAlphaNumeric(const char _char);
//    void collectIdentifier();
//    void collectIdentifier(const string str);
//    char currentChar();
//    char nextChar();
//    void advance();
//    bool matchNext(const char value);
//    string to_string(const char v);
//    bool isEOF();
//    
//};
//
//#endif /* lexer_hpp */
