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
#include "../ast/values/Value/Value.hpp"

using namespace std;
using namespace css;

class Parser {
public:
    Parser(const std::vector<css::Token>& tokens);
    Stylesheet* parse();

private:
    const std::vector<css::Token>& tokens;
    size_t pos = 0;

    css::Token current();
    css::Token next();
    void advance();
    bool eof();

    bool match(TokenType type);

    Rule parseRule();
    StyleRule parseStyleRule();
    AtRule parseAtRule();

//    vector<string> parseSelectorList();
    std::vector<ComplexSelector> parseSelectorList();
    vector<Declaration> parseDeclarations();

    string parseComponentValue();
    void consumeWhiteSpaces();
    void consumeTokenType(TokenType type, string errorMsg);
    
    ComplexSelector parseSelector(const vector<css::Token>& tokens);
//    vector<shared_ptr<Value>> parseValue(const vector<css::Token>& tokens, size_t& j);
    vector<shared_ptr<Value>> parseValue(const vector<css::Token>& tokens, size_t& j, bool* important);
};

#endif /* CSSParser_hpp */
