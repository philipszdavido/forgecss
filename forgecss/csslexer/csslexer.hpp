//
//  csslexer.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#ifndef csslexer_hpp
#define csslexer_hpp

#include <stdio.h>
#include <vector>
#include "CSSToken.hpp"

class CSSTokenizer {
public:
    CSSTokenizer(const std::string& input);
    std::vector<CSSToken> tokenize();

private:
    std::string input;
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

    void consumeWhitespace(std::vector<CSSToken>& tokens);
    void consumeIdentLike(std::vector<CSSToken>& tokens);
    void consumeNumber(std::vector<CSSToken>& tokens);
    void consumeString(std::vector<CSSToken>& tokens, char quote);
};

#endif /* csslexer_hpp */
