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

using namespace css;

namespace css {
class Tokenizer {
public:
    Tokenizer(const std::string& input);
    vector<css::Token> tokenize();
    
private:
    string input;
    size_t pos = 0;
    
    char current();
    char next(int offset = 1);
    void advance(int level = 1);
    bool eof();
    
    bool isWhitespace(char c);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isNameStart(char c);
    bool isNameChar(char c);
    
    void consumeWhitespace(vector<css::Token>& tokens);
    void consumeIdentLike(vector<css::Token>& tokens);
    void consumeNumber(vector<css::Token>& tokens);
    void consumeString(vector<css::Token>& tokens, char quote);
    void consumeComment();
    
    bool isColor(string name);
};
}

#endif /* lexer_hpp */
