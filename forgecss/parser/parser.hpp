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
#include "../token/token.hpp"
#include "../ast/ast.hpp"

using namespace std;

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    Stylesheet parse();

private:
    const std::vector<Token>& tokens;
    size_t pos = 0;

    Token current();
    Token next();
    void advance();
    bool eof();

    bool match(TokenType type);

    Rule parseRule();
    StyleRule parseStyleRule();
    AtRule parseAtRule();

    vector<string> parseSelectorList();
    vector<Declaration> parseDeclarations();

    string parseComponentValue();
    void consumeWhiteSpaces();
    void consumeTokenType(TokenType type, string errorMsg);
};

#endif /* CSSParser_hpp */
