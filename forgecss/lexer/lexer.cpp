//
//  lexer.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 16/04/2026.
//

#include "lexer.hpp"

unordered_map<string, string> keywords = {
    { "solid", "solid" }
};

Lexer::Lexer(string input) : input(input) {
    add(TokenType::SELECTOR_START, "");
}

void Lexer::tokenize() {
    while (!eof()) {

        if (isspace(current())) {
            advance();
            continue;
        }

        if (current() == '@') {
            consumeAtRule();
            continue;
        }
        
        if (current() == '}') {
            add(TokenType::RBRACE, "}");
            advance();
            changeMode(LexerMode::SELECTOR);
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
        changeMode(LexerMode::DECLARATION_NAME);
        add(TokenType::LBRACE, "{");
        add(TokenType::DECLARATION_NAME_START, "");

        advance();
        return;
    }
        
    if (c == '.') {
        advance();
        add(TokenType::DOT, ".");
        return;
    }
    
    if (c == ',') {
        advance();
        add(TokenType::COMMA, ",");
        return;
    }
    
    if (c == '>') {
        advance();
        add(TokenType::GT, ">");
        return;
    }
    
    if (c == '<') {
        advance();
        add(TokenType::LT, "<");
        return;
    }
    
    if (c == '+') {
        advance();
        add(TokenType::PLUS, "+");
        return;
    }
    
    if (c == '|') {
        advance();
        add(TokenType::PIPE, "|");
        return;
    }
    
    if (c == '=') {
        advance();
        add(TokenType::EQUALS, "=");
        return;
    }

    if (c == '~') {
        advance();
        add(TokenType::TILDE, "~");
        return;
    }
    
    if (isspace(current())) {
        advance();
        add(TokenType::WHITESPACE, " ");
        return;
    }

    if (c == ' ') {
        advance();
        add(TokenType::WHITESPACE, " ");
        return;
    }

    if (c == '#') {
        advance();
        add(TokenType::HASH, consumeIdent());
        return;
    }
    
    if (c == '[') {
        advance();
        add(TokenType::LEFT_SQUARE_BRACE, "[");
        return;
    }

    if (c == ']') {
        advance();
        add(TokenType::RIGHT_SQUARE_BRACE, "]");
        return;
    }

    if (c == ':') {
        if (next() == ':') {
            advance(); advance();
            add(TokenType::DOUBLE_COLON, "::");
            return;
        }
        advance();
        add(TokenType::COLON, ":");
        return;
    }

    if (isAlpha(c)) {
        
        string ident = consumeIdent();
        c = current();
        
        if (c == '(') {
            
            add(TokenType::FUNCTION, ident);
            add(TokenType::LPAREN, "(");
            advance();

            while (!eof() && current() != ')') {
                // tokenizeDeclarationValue();
                consumeFunctionCallArgs();
            }

            if (current() == ')') {
                add(TokenType::RPAREN, ")");
                advance();
            }

            return;

        }
        add(TokenType::IDENT, ident);
        return;
    }

    advance();
    
}

void Lexer::tokenizeDeclarationName() {

    if (current() == '}') {
        add(TokenType::RBRACE, "}");
        changeMode(LexerMode::SELECTOR);
        advance();
        return;
    }

    if (current() == ':') {
        add(TokenType::DECLARATION_NAME_END, "");

        add(TokenType::COLON, ":");
        changeMode(LexerMode::DECLARATION_VALUE);
        add(TokenType::DECLARATION_VALUE_START, "");

        advance();
        return;
    }
    
    if (tokens[tokens.size() - 1].type != TokenType::DECLARATION_NAME_START) {
        add(TokenType::DECLARATION_NAME_START, "");
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
        add(TokenType::DECLARATION_VALUE_END, "");
        add(TokenType::SEMICOLON, ";");
        changeMode(LexerMode::DECLARATION_NAME);
        advance();
        return;
    }

    if (c == '}') {
        add(TokenType::RBRACE, "}");
        changeMode(LexerMode::SELECTOR);
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
    
    if (c == '-') {
        if (next() == '-') {
            advance(); advance();
            string value = consumeVariable();
            add(TokenType::VARIABLE, value);
            
            return;
        }
    }

    advance();
}

void Lexer::changeMode(LexerMode modeToSet) {
    
    if (mode != LexerMode::SELECTOR && modeToSet == LexerMode::SELECTOR) {
        
        // check if we reached end of file
        if (index >= (input.size() - 1)) {
            return;
        }
        
        // check if the next thing is not @
        int i = (int)index + 1;
        while(isspace(input[i])) {
            if (input[i + 1] == '@') {
                return;
            } else if (!isspace(input[i + 1])) break;
            i++;
        }
        
        add(TokenType::SELECTOR_START, "");
        
    } else if (mode == LexerMode::SELECTOR && modeToSet != LexerMode::SELECTOR) {
        add(TokenType::SELECTOR_END, "");
    }

    mode = modeToSet;
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
        add(TokenType::LPAREN, "(");

        advance();

        while (!eof() && current() != ')') {
            // tokenizeDeclarationValue();
            consumeFunctionCallArgs();
        }

        if (current() == ')') {
            add(TokenType::RPAREN, ")");
            advance();
        }

        return;
    } else if (current() == ' ' || current() == ',') {
        if (!keywords.contains(ident)) {
            ident += consumeToSemiColon();
        }
    }

    add(TokenType::IDENT, ident);
}

string Lexer::consumeToSemiColon() {
    
    string value = "";

    while (!eof() && current() != ';') {
        value += current();
        advance();
    }
    
    return value;

}

string Lexer::consumeVariable() {
    
    string value = "";

    while (!eof() && (isAlphaNumeric(current()) || current() == '-')) {
        value += current();
        advance();
    }
    
    return value;

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
    
    int blockDepth = 0;
//    if (c == '{') blockDepth++;
//    if (c == '}') blockDepth--;
    
    string name = consumeIdent();
    add(TokenType::AT_KEYWORD, name);

    while (!eof() && current() != '{') {
        char c = current();

        if (isspace(c)) {
            consumeWhitespace();
            continue;
        }

        if (isAlpha(c)) {
            add(TokenType::IDENT, consumeIdent());
            continue;
        }

        if (c == '(') {
            add(TokenType::LPAREN, "(");
            advance();
            continue;
        }

        if (c == ')') {
            add(TokenType::RPAREN, ")");
            advance();
            continue;
        }

        if (c == ':') {
            add(TokenType::COLON, ":");
            advance();
            continue;
        }

        if (isDigit(c)) {
            consumeNumber();
            continue;
        }

        advance();
    }

    if (current() == '{') {
        add(TokenType::LBRACE, "{");
        advance();
    }

    changeMode(LexerMode::SELECTOR);
}

void Lexer::consumeWhitespace() {
    string ws = "";
    while (!eof() && isspace(current())) {
        ws += current();
        advance();
    }
    add(TokenType::WHITESPACE, ws);
}

void Lexer::consumeFunctionCallArgs() {
    char c = current();

    add(TokenType::VALUE_START, "");

    if (c == '"' || c == '\'') {
        add(TokenType::STRING, consumeString());

        add(TokenType::VALUE_END, "");

        return;
    }

    if (isDigit(c) || (c == '.' && isDigit(next()))) {
        consumeNumber();
        
        add(TokenType::VALUE_END, "");

        return;
    }

    if (isAlpha(c)) {
        consumeIdentLike();
        
        add(TokenType::VALUE_END, "");

        return;
    }

    if (c == '#') {
        advance();
        add(TokenType::HASH, consumeIdent());
        
        add(TokenType::VALUE_END, "");

        return;
    }

    if (c == ',') {
        add(TokenType::COMMA, ",");
        advance();
        
        add(TokenType::VALUE_END, "");

        return;
    }

    if (c == '(') {
        add(TokenType::LPAREN, "(");
        advance();
        
        add(TokenType::VALUE_END, "");

        return;
    }

    if (c == ')') {
        add(TokenType::RPAREN, ")");
        advance();
        
        add(TokenType::VALUE_END, "");

        return;
    }
    
    if (c == '-') {
        if (next() == '-') {
            advance(); advance();
            string value = consumeVariable();
            add(TokenType::VARIABLE, value);
            
            add(TokenType::VALUE_END, "");

            return;
        }
    }

    advance();
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
