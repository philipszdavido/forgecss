//
//  lexer.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <stdio.h>
#include <vector>
#include "../token/token.hpp"

class Tokenizer {
public:
    Tokenizer(const std::string& input);
    vector<Token> tokenize();

private:
    string input;
    size_t pos = 0;

    char current();
    char next(int offset = 1);
    void advance();
    bool eof();

    bool isWhitespace(char c);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isNameStart(char c);
    bool isNameChar(char c);

    void consumeWhitespace(vector<Token>& tokens);
    void consumeIdentLike(vector<Token>& tokens);
    void consumeNumber(vector<Token>& tokens);
    void consumeString(vector<Token>& tokens, char quote);
};

#endif /* lexer_hpp */
