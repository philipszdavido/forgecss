//
//  CSSParser.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#ifndef CSSParser_hpp
#define CSSParser_hpp

#include <stdio.h>
#include <vector>
#include "CSSToken.hpp"
#include "CSSAST.hpp"

using namespace std;

class CSSParser {
public:
    CSSParser(const std::vector<CSSToken>& tokens);
    Stylesheet parse();

private:
    const std::vector<CSSToken>& tokens;
    size_t pos = 0;

    CSSToken current();
    CSSToken next();
    void advance();
    bool eof();

    bool match(TokenType type);

    Rule parseRule();
    StyleRule parseStyleRule();
    AtRule parseAtRule();

    std::vector<std::string> parseSelectorList();
    std::vector<Declaration> parseDeclarations();

    std::string parseComponentValue();
};

#endif /* CSSParser_hpp */
