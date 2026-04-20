//
//  csslexer.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#include "csslexer.hpp"
#include <cctype>

CSSTokenizer::CSSTokenizer(const std::string& input) : input(input) {}

std::vector<CSSToken> CSSTokenizer::tokenize() {
    std::vector<CSSToken> tokens;

    while (!eof()) {
        char c = current();

        if (isWhitespace(c)) {
            consumeWhitespace(tokens);
            continue;
        }

        if (c == '"') {
            consumeString(tokens, '"');
            continue;
        }

        if (c == '\'') {
            consumeString(tokens, '\'');
            continue;
        }

        if (c == '#') {
            advance();
            if (isNameChar(current())) {
                std::string value;
                while (isNameChar(current())) {
                    value += current();
                    advance();
                }
                tokens.emplace_back(TokenType::HASH, value);
            } else {
                tokens.emplace_back(TokenType::DELIM, "#");
            }
            continue;
        }

        if (c == '@') {
            advance();
            std::string name;
            while (isNameChar(current())) {
                name += current();
                advance();
            }
            tokens.emplace_back(TokenType::AT_KEYWORD, name);
            continue;
        }

        if (isDigit(c) || (c == '.' && isDigit(next()))) {
            consumeNumber(tokens);
            continue;
        }

        if (isNameStart(c)) {
            consumeIdentLike(tokens);
            continue;
        }

        switch (c) {
            case '{': tokens.emplace_back(TokenType::LEFT_BRACE); break;
            case '}': tokens.emplace_back(TokenType::RIGHT_BRACE); break;
            case '(': tokens.emplace_back(TokenType::LEFT_PAREN); break;
            case ')': tokens.emplace_back(TokenType::RIGHT_PAREN); break;
            case '[': tokens.emplace_back(TokenType::LEFT_BRACKET); break;
            case ']': tokens.emplace_back(TokenType::RIGHT_BRACKET); break;
            case ':': tokens.emplace_back(TokenType::COLON); break;
            case ';': tokens.emplace_back(TokenType::SEMICOLON); break;
            case ',': tokens.emplace_back(TokenType::COMMA); break;
            default:
                tokens.emplace_back(TokenType::DELIM, std::string(1, c));
        }

        advance();
    }

    tokens.emplace_back(TokenType::END_OF_FILE);
    return tokens;
}

char CSSTokenizer::current() { return eof() ? '\0' : input[pos]; }
char CSSTokenizer::next(int o) { return (pos + o < input.size()) ? input[pos + o] : '\0'; }
void CSSTokenizer::advance() { pos++; }
bool CSSTokenizer::eof() { return pos >= input.size(); }

bool CSSTokenizer::isWhitespace(char c) { return isspace(c); }
bool CSSTokenizer::isDigit(char c) { return isdigit(c); }
bool CSSTokenizer::isAlpha(char c) { return isalpha(c); }

bool CSSTokenizer::isNameStart(char c) {
    return isAlpha(c) || c == '_' || c == '-';
}

bool CSSTokenizer::isNameChar(char c) {
    return isNameStart(c) || isDigit(c);
}

void CSSTokenizer::consumeWhitespace(std::vector<CSSToken>& tokens) {
    while (isWhitespace(current())) advance();
    tokens.emplace_back(TokenType::WHITESPACE);
}

void CSSTokenizer::consumeString(std::vector<CSSToken>& tokens, char quote) {
    advance();
    std::string value;

    while (!eof() && current() != quote) {
        value += current();
        advance();
    }

    if (current() == quote) {
        advance();
        tokens.emplace_back(TokenType::STRING, value);
    } else {
        tokens.emplace_back(TokenType::BAD_STRING);
    }
}

void CSSTokenizer::consumeIdentLike(std::vector<CSSToken>& tokens) {
    std::string name;

    while (isNameChar(current())) {
        name += current();
        advance();
    }

    if (current() == '(') {
        advance();
        tokens.emplace_back(TokenType::FUNCTION, name);
    } else {
        tokens.emplace_back(TokenType::IDENT, name);
    }
}

void CSSTokenizer::consumeNumber(std::vector<CSSToken>& tokens) {
    std::string number;

    while (isDigit(current()) || current() == '.') {
        number += current();
        advance();
    }

    if (current() == '%') {
        advance();
        tokens.emplace_back(TokenType::PERCENTAGE, number);
        return;
    }

    if (isNameStart(current())) {
        std::string unit;
        while (isNameChar(current())) {
            unit += current();
            advance();
        }
        tokens.emplace_back(TokenType::DIMENSION, number + unit);
        return;
    }

    tokens.emplace_back(TokenType::NUMBER, number);
}
