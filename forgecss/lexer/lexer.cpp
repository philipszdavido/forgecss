//
//  lexer.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 16/04/2026.
//

#include "lexer.hpp"

unordered_map<string, string> keywords = {
    {"solid", "solid"}
};

Lexer::Lexer(string input) : input(input) {
    add(TokenType::SELECTOR_START, "");
}

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
    
    // run phases
    skipWhiteSpaces();
    
}

void Lexer::skipWhiteSpaces() {
    for (int i = int(tokens.size() - 1); i >= 0; i--) {
        if (tokens[i].type == TokenType::WHITESPACE) {
            tokens.erase(tokens.begin() + i);
        }
    }
}

void Lexer::removeStandaloneSelector(vector<Token> &tokens) {
    
    int seen = 0;
    int index;
    
    for (int i = 0; i <= (tokens.size() - 1); i++) {
        
        Token newToken = tokens[i];
        
        if (newToken.type == TokenType::SELECTOR_START) {
            seen++;
            index = i;
        }
        
        if (newToken.type == TokenType::SELECTOR_END) {
            seen--;
        }
                
    }
    
    if (seen > 0) {
        // remove SELECTOR_START
//        tokens.erase(tokens.begin() + index);
    }
    
}

void Lexer::tokenizeSelector() {
    char c = current();
    
    if (c == '{') {
        changeMode(LexerMode::DECLARATION_NAME);
        add(TokenType::LBRACE, "{");
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
        add(TokenType::IDENT, ident /*consumeIdent()*/ );
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
        add(TokenType::COLON, ":");
        changeMode(LexerMode::DECLARATION_VALUE);
        advance();
        return;
    }

    if (isAlpha(current()) || current() == '-') {
        add(TokenType::DECLARATION_NAME_START, "");
        add(TokenType::IDENT, consumeIdent());
        add(TokenType::DECLARATION_NAME_END, "");
        return;
    }

    advance();
}

void Lexer::tokenizeDeclarationValue() {

    char c = current();

    if (c == ';') {
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

    add(TokenType::DECLARATION_VALUE_START, "");

    if (c == '"' || c == '\'') {
        add(TokenType::STRING, consumeString());

        add(TokenType::DECLARATION_VALUE_END, "");

        return;
    }

    if (isDigit(c) || (c == '.' && isDigit(next()))) {
        consumeNumber();
        
        add(TokenType::DECLARATION_VALUE_END, "");

        return;
    }

    if (isAlpha(c)) {
        consumeIdentLike();
        
        add(TokenType::DECLARATION_VALUE_END, "");

        return;
    }

    if (c == '#') {
        advance();
        add(TokenType::HASH, consumeIdent());
        
        add(TokenType::DECLARATION_VALUE_END, "");

        return;
    }

    if (c == ',') {
        add(TokenType::COMMA, ",");
        advance();
        
        add(TokenType::DECLARATION_VALUE_END, "");

        return;
    }

    if (c == '(') {
        add(TokenType::LPAREN, "(");
        advance();
        
        add(TokenType::DECLARATION_VALUE_END, "");

        return;
    }

    if (c == ')') {
        add(TokenType::RPAREN, ")");
        advance();
        
        add(TokenType::DECLARATION_VALUE_END, "");

        return;
    }
    
    if (c == '-') {
        if (next() == '-') {
            advance(); advance();
            string value = consumeVariable();
            add(TokenType::VARIABLE, value);
            
            add(TokenType::DECLARATION_VALUE_END, "");

            return;
        }
    }

    advance();
}

void Lexer::changeMode(LexerMode modeToSet) {
    
    if (mode != LexerMode::SELECTOR && modeToSet == LexerMode::SELECTOR) {
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
