//
//  lexer.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 16/04/2026.
//

#include "lexer.hpp"

Lexer::Lexer(string input) : input(input) {}

void Lexer::tokenize() {
    while (!eof()) {

        if (isspace(current())) {
            consumeWhitespace();
            continue;
        }

        if (current() == '@') {
            consumeAtRule();
            continue;
        }

        switch (mode) {

            case LexerMode::SELECTOR:
                tokenizeSelector();
                break;

            case LexerMode::DECLARATION_NAME:
                tokenizeDeclarationName();
                break;

            case LexerMode::DECLARATION_VALUE:
                tokenizeDeclarationValue();
                break;
        }
    }

    add(TokenType::END_OF_FILE, "");
}

void Lexer::tokenizeSelector() {
    char c = current();

    if (c == '{') {
        add(TokenType::LBRACE, "{");
        mode = LexerMode::DECLARATION_NAME;
        advance();
        return;
    }

    if (c == '.') {
        advance();
        add(TokenType::DOT, consumeIdent());
        return;
    }

    if (c == '#') {
        advance();
        add(TokenType::HASH, consumeIdent());
        return;
    }

    if (c == ':' && next() == ':') {
        advance(); advance();
        add(TokenType::DOUBLE_COLON, "::");
        return;
    }

    if (isAlpha(c)) {
        add(TokenType::IDENT, consumeIdent());
        return;
    }

    advance();
}

void Lexer::tokenizeDeclarationName() {

    if (current() == '}') {
        add(TokenType::RBRACE, "}");
        mode = LexerMode::SELECTOR;
        advance();
        return;
    }

    if (current() == ':') {
        add(TokenType::COLON, ":");
        mode = LexerMode::DECLARATION_VALUE;
        advance();
        return;
    }

    if (isAlpha(current()) || current() == '-') {
        add(TokenType::IDENT, consumeIdent());
        return;
    }

    advance();
}

void Lexer::tokenizeDeclarationValue() {

    char c = current();

    if (c == ';') {
        add(TokenType::SEMICOLON, ";");
        mode = LexerMode::DECLARATION_NAME;
        advance();
        return;
    }

    if (c == '}') {
        add(TokenType::RBRACE, "}");
        mode = LexerMode::SELECTOR;
        advance();
        return;
    }

    if (c == '"' || c == '\'') {
        add(TokenType::STRING, consumeString());
        return;
    }

    if (isDigit(c) || (c == '.' && isDigit(next()))) {
        consumeNumber();
        return;
    }

    if (isAlpha(c)) {
        consumeIdentLike();
        return;
    }

    if (c == '#') {
        advance();
        add(TokenType::HASH, consumeIdent());
        return;
    }

    if (c == ',') {
        add(TokenType::COMMA, ",");
        advance();
        return;
    }

    if (c == '(') {
        add(TokenType::LPAREN, "(");
        advance();
        return;
    }

    if (c == ')') {
        add(TokenType::RPAREN, ")");
        advance();
        return;
    }

    advance();
}

void Lexer::consumeNumber() {
    string num = "";

    if (current() == '.') {
        num += '.';
        advance();
    }

    while (isDigit(current())) {
        num += current();
        advance();
    }

    if (current() == '.') {
        num += '.';
        advance();
        while (isDigit(current())) {
            num += current();
            advance();
        }
    }

    if (current() == '%') {
        advance();
        add(TokenType::PERCENTAGE, num + "%");
        return;
    }

    if (isAlpha(current())) {
        string unit = "";
        while (isAlpha(current())) {
            unit += current();
            advance();
        }
        add(TokenType::DIMENSION, num + unit);
        return;
    }

    add(TokenType::NUMBER, num);
}

void Lexer::consumeIdentLike() {

    string ident = consumeIdent();

    if (current() == '(') {

        if (ident == "url") {
            consumeURL();
            return;
        }

        add(TokenType::FUNCTION, ident);
        advance();

        while (!eof() && current() != ')') {
            tokenizeDeclarationValue();
        }

        if (current() == ')') {
            add(TokenType::RPAREN, ")");
            advance();
        }

        return;
    }

    add(TokenType::IDENT, ident);
}

void Lexer::consumeURL() {

    advance();

    string value = "";

    while (!eof() && current() != ')') {
        value += current();
        advance();
    }

    advance();

    add(TokenType::URL, value);
}

string Lexer::consumeString() {
    char quote = current();
    advance();

    string value = "";

    while (!eof() && current() != quote) {
        value += current();
        advance();
    }

    advance();

    return value;
}

string Lexer::consumeIdent() {
    string ident = "";

    while (!eof() && isAlphaNumeric(current())) {
        ident += current();
        advance();
    }

    return ident;
}

void Lexer::consumeAtRule() {
    advance();

    string name = consumeIdent();
    add(TokenType::AT_KEYWORD, name);

    while (!eof() && current() != '{') {
        tokenizeDeclarationValue();
    }
}

void Lexer::consumeWhitespace() {
    string ws = "";
    while (!eof() && isspace(current())) {
        ws += current();
        advance();
    }
    add(TokenType::WHITESPACE, ws);
}

char Lexer::current() {
    return eof() ? '\0' : input[index];
}

char Lexer::next() {
    return (index + 1 < input.size()) ? input[index + 1] : '\0';
}

bool Lexer::eof() {
    return index >= input.size();
}

void Lexer::advance() {
    index++;
}

bool Lexer::isAlpha(char c) {
    return isalpha(c);
}

bool Lexer::isDigit(char c) {
    return isdigit(c);
}

bool Lexer::isAlphaNumeric(char c) {
    return isalnum(c) || c == '-' || c == '_';
}

void Lexer::add(TokenType type, string value) {
    tokens.emplace_back(type, value);
}

void Lexer::printTokenType(TokenType type) {
    switch (type) {
        case TokenType::LBRACE: std::cout << "LBRACE"; break;
        case TokenType::RBRACE: std::cout << "RBRACE"; break;
        case TokenType::LPAREN: std::cout << "LPAREN"; break;
        case TokenType::RPAREN: std::cout << "RPAREN"; break;
        case TokenType::LBRACKET: std::cout << "LBRACKET"; break;
        case TokenType::RBRACKET: std::cout << "RBRACKET"; break;

        case TokenType::COLON: std::cout << "COLON"; break;
        case TokenType::SEMICOLON: std::cout << "SEMICOLON"; break;
        case TokenType::COMMA: std::cout << "COMMA"; break;

        case TokenType::DOT: std::cout << "DOT"; break;
        case TokenType::HASH: std::cout << "HASH"; break;
        case TokenType::IDENT: std::cout << "IDENT"; break;
        case TokenType::DOUBLE_COLON: std::cout << "DOUBLE_COLON"; break;

        case TokenType::NUMBER: std::cout << "NUMBER"; break;
        case TokenType::DIMENSION: std::cout << "DIMENSION"; break;
        case TokenType::PERCENTAGE: std::cout << "PERCENTAGE"; break;
        case TokenType::STRING: std::cout << "STRING"; break;
        case TokenType::FUNCTION: std::cout << "FUNCTION"; break;
        case TokenType::URL: std::cout << "URL"; break;

        case TokenType::AT_KEYWORD: std::cout << "AT_KEYWORD"; break;

        case TokenType::WHITESPACE: std::cout << "WHITESPACE"; break;
        case TokenType::DELIM: std::cout << "DELIM"; break;

        case TokenType::END_OF_FILE: std::cout << "EOF"; break;

        default:
            std::cout << "UNKNOWN";
            break;
    }
}
