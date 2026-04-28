//
//  Parser.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#include "Parser.hpp"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

Stylesheet Parser::parse() {
    Stylesheet sheet;

    while (!eof()) {
        if (current().type == TokenType::WHITESPACE) {
            advance();
            continue;
        }

        sheet.rules.push_back(parseRule());
    }

    return sheet;
}

Rule Parser::parseRule() {
    Rule rule;

    if (current().type == TokenType::AT_KEYWORD) {
        rule.isAtRule = true;
        rule.at = parseAtRule();
    } else {
        rule.isAtRule = false;
        rule.style = parseStyleRule();
    }

    return rule;
}

StyleRule Parser::parseStyleRule() {
    StyleRule rule;

    rule.selectors = parseSelectorList();

    if (current().type == TokenType::LEFT_BRACE) {
        advance();
    }

    while (!eof() && current().type != TokenType::RIGHT_BRACE) {

        if (current().type == TokenType::AT_KEYWORD) {
            rule.nestedRules.push_back(parseRule());
            continue;
        }
        
        if (current().type == TokenType::WHITESPACE) {
            advance();
            continue;
        }

        size_t temp = pos;
        bool isNested = false;

        while (temp < tokens.size()) {
            if (tokens[temp].type == TokenType::LEFT_BRACE || tokens[temp].type == TokenType::AND) {
                isNested = true;
                break;
            }
            if (tokens[temp].type == TokenType::COLON) {
                break;
            }
            if (tokens[temp].type == TokenType::AT_KEYWORD) {
                isNested = true;
                break;
            }
            temp++;
        }

        if (isNested) {
            rule.nestedRules.push_back(parseRule());
        } else {
            auto decls = parseDeclarations();
            rule.declarations.insert(rule.declarations.end(), decls.begin(), decls.end());
        }
    }
    
    consumeWhiteSpaces();

    if (current().type == TokenType::RIGHT_BRACE) {
        advance();
    }

    return rule;
}

AtRule Parser::parseAtRule() {
    AtRule rule;

    rule.name = current().value;
    advance();

    while (!eof() && current().type != TokenType::LEFT_BRACE) {
        rule.prelude += parseComponentValue() + " ";
    }

    if (current().type == TokenType::LEFT_BRACE) {
        advance();
    }

    while (!eof() && current().type != TokenType::RIGHT_BRACE) {
        if (current().type == TokenType::WHITESPACE) {
            advance();
            continue;
        }
        rule.rules.push_back(parseRule());
    }
    
    consumeWhiteSpaces();

    if (current().type == TokenType::RIGHT_BRACE) {
        advance();
    }

    return rule;
}

std::vector<std::string> Parser::parseSelectorList() {
    vector<string> selectors;
    string currentSelector;

    while (!eof()) {
        if (current().type == TokenType::LEFT_BRACE) {
            break;
        }

        if (current().type == TokenType::COMMA) {
            selectors.push_back(currentSelector);
            currentSelector.clear();
            advance();
            continue;
        }

        currentSelector += current().value;
        advance();
    }

    if (!currentSelector.empty()) {
        selectors.push_back(currentSelector);
    }

    return selectors;
}

std::vector<Declaration> Parser::parseDeclarations() {
    vector<Declaration> decls;

    while (!eof()) {

        if (current().type == TokenType::AT_KEYWORD) break;
        if (current().type == TokenType::RIGHT_BRACE) break;
        if (current().type == TokenType::SEMICOLON) {
            advance();
            continue;
        }

        if (current().type != TokenType::IDENT) {
            advance();
            continue;
        }

        Declaration decl;
        decl.name = current().value;
        advance();

        if (current().type == TokenType::COLON) {
            advance();
        }

        while (!eof() && current().type != TokenType::SEMICOLON) {
            decl.value += parseComponentValue() + " ";
        }

        decls.push_back(decl);

        if (current().type == TokenType::SEMICOLON) {
            advance();
        }
        
        return decls;
        
    }

    return decls;
}

string Parser::parseComponentValue() {
    
    string value;
    
    if (current().type == TokenType::FUNCTION) {
        value += current().value + "(";
        advance();

        while (!eof() && current().type != TokenType::RIGHT_PAREN) {
            value += parseComponentValue();
        }

        if (current().type == TokenType::RIGHT_PAREN) {
            value += ")";
            advance();
        }

        return value;
    }

    value = current().value;
    advance();
    return value;
}

vector<Selector> Parser::parseSelector(const vector<Token>& tokens) {
    
    vector<Selector> parts;
    
    size_t j = 0;

    auto advance = [&]() {
        if (j < tokens.size()) j++;
    };

    auto current = [&]() -> const Token& {
        return tokens[j];
    };

    auto hasNext = [&]() -> bool {
        return j < tokens.size();
    };

    while (hasNext()) {
        Token t = current();

        // .class, this is a class
        if (t.type == TokenType::DOT) {
            advance();

            if (!hasNext()) break;

            string name = current().value;
            parts.push_back(ClassSelector(name));
            advance();
        }

        // [attr=value]: we know we have hit an attribute
        else if (t.type == TokenType::LEFT_BRACKET) {
            advance();

            string name;
            string value;
            bool hasValue = false;

            if (hasNext() && current().type == TokenType::IDENT) {
                name = current().value;
                advance();
            }

            if (hasNext() && current().type == TokenType::EQUALS) {
                advance();
                hasValue = true;

                if (hasNext()) {
                    value = current().value;
                    advance();
                }
            }

            while (hasNext() && current().type != TokenType::RIGHT_BRACKET) {
                advance();
            }

            if (hasNext()) advance();

            parts.push_back(AttributeSelector(name, value, hasValue));
        }

        // ::pseudo-element(arg): pseudo element selector
        else if (t.type == TokenType::DOUBLE_COLON) {
            advance();

            if (!hasNext()) break;

            string name = current().value;
            advance();

            string arg;
            if (hasNext() && current().type == TokenType::LEFT_PAREN) {
                advance();

                if (hasNext()) {
                    arg = current().value;
                    advance();
                }

                if (hasNext() && current().type == TokenType::RIGHT_PAREN) {
                    advance();
                }
            }

            parts.push_back(PseudoElementSelector(name, arg));
        }

        // :pseudo-class(arg): we have a pseudo class selector
        else if (t.type == TokenType::COLON) {
            advance();

            if (!hasNext()) break;

            string name = current().value;
            advance();

            string arg;
            if (hasNext() && current().type == TokenType::LEFT_PAREN) {
                advance();

                while (hasNext() && current().type != TokenType::RIGHT_PAREN) {
                    arg += current().value;
                    advance();
                }

                if (hasNext()) advance();
            }

            parts.push_back(PseudoClassSelector(name, arg));
        }

        else {
            break;
        }
    }

    return parts;
}

vector<shared_ptr<Value>> Parser::parseValue(const vector<Token>& tokens, size_t& j) {
    
    vector<shared_ptr<Value>> values;

    auto hasNext = [&]() {
        return j < tokens.size();
    };

    auto current = [&]() -> const Token& {
        return tokens[j];
    };

    auto advance = [&]() {
        if (j < tokens.size()) j++;
    };

    while (hasNext() && current().type != TokenType::SEMICOLON) {

        Token t = current();

        // values like 10px, 2em, 50%
        if (t.type == TokenType::DIMENSION) {
            auto v = make_shared<DimensionValue>();
            v->value = stod(t.value);
            v->unit = t.unit;

            values.push_back(v);
            advance();
        }

        // values like #fff, #ff0000
        else if (t.type == TokenType::HASH) {
            auto v = make_shared<ColorValue>();
            v->value = t.value;

            values.push_back(v);
            advance();
        }

        // values like rgb(), calc(), url()
        else if (t.type == TokenType::FUNCTION) {
            string name = t.value;
            advance();

            vector<shared_ptr<Value>> args;

            if (hasNext() && current().type == TokenType::LEFT_PAREN) {
                advance();

                while (hasNext() && current().type != TokenType::RIGHT_PAREN) {
                    auto inner = parseValue(tokens, j);
                    args.insert(args.end(), inner.begin(), inner.end());
                }

                if (hasNext()) advance();
            }

            auto v = make_shared<FunctionValue>();
            v->name = name;
            v->args = args;

            values.push_back(v);
        }

        // values like solid, red, auto
        else if (t.type == TokenType::IDENT) {
            auto v = make_shared<KeywordValue>();
            v->value = t.value;

            values.push_back(v);
            advance();
        }

        else if (t.type == TokenType::COMMA) {
            advance();
        }

        else {
            advance();
        }
    }

    return values;
}

Token Parser::current() { return tokens[pos]; }
Token Parser::next() { return tokens[pos + 1]; }

void Parser::advance() { pos++; }

bool Parser::eof() {
    return pos >= tokens.size() || tokens[pos].type == TokenType::END_OF_FILE;
}

bool Parser::match(TokenType type) {
    if (current().type != type) return false;

    advance();
    return true;

}

void Parser::consumeWhiteSpaces() {
    while (current().type == TokenType::WHITESPACE) advance();
}

void Parser::consumeTokenType(TokenType type, string errorMsg) {
    if (eof()) return;
    
    if (current().type != type) throw runtime_error(errorMsg);
    
    advance();
    
}
