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
            if (tokens[temp].type == TokenType::LEFT_BRACE) {
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

Token Parser::current() { return tokens[pos]; }
Token Parser::next() { return tokens[pos + 1]; }

void Parser::advance() { pos++; }

bool Parser::eof() {
    return pos >= tokens.size() || tokens[pos].type == TokenType::END_OF_FILE;
}

bool Parser::match(TokenType type) {
    if (current().type == type) {
        advance();
        return true;
    }
    return false;
}

void Parser::consumeWhiteSpaces() {
    while (current().type == TokenType::WHITESPACE) {
        advance();
    }
}
