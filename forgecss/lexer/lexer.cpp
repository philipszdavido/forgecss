//
//  lexer.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#include "lexer.hpp"
#include <cctype>

Tokenizer::Tokenizer(const std::string& input) : input(input) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;

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
            case '&': tokens.emplace_back(TokenType::AND); break;
            case '>': tokens.emplace_back(TokenType::GT); break;
            case '<': tokens.emplace_back(TokenType::LT); break;
            case '.': tokens.emplace_back(TokenType::DOT); break;
            default:
                tokens.emplace_back(TokenType::DELIM, std::string(1, c));
        }

        advance();
    }

    tokens.emplace_back(TokenType::END_OF_FILE);
    return tokens;
}

char Tokenizer::current() { return eof() ? '\0' : input[pos]; }
char Tokenizer::next(int o) { return (pos + o < input.size()) ? input[pos + o] : '\0'; }
void Tokenizer::advance() { pos++; }
bool Tokenizer::eof() { return pos >= input.size(); }

bool Tokenizer::isWhitespace(char c) { return isspace(c); }
bool Tokenizer::isDigit(char c) { return isdigit(c); }
bool Tokenizer::isAlpha(char c) { return isalpha(c); }

bool Tokenizer::isNameStart(char c) {
    return isAlpha(c) || c == '_' || c == '-';
}

bool Tokenizer::isNameChar(char c) {
    return isNameStart(c) || isDigit(c);
}

void Tokenizer::consumeWhitespace(std::vector<Token>& tokens) {
    while (isWhitespace(current())) advance();
    tokens.emplace_back(TokenType::WHITESPACE);
}

void Tokenizer::consumeString(std::vector<Token>& tokens, char quote) {
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

void Tokenizer::consumeIdentLike(std::vector<Token>& tokens) {
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

void Tokenizer::consumeNumber(std::vector<Token>& tokens) {
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
