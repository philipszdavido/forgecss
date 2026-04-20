////
////  parser.cpp
////  forgecss
////
////  Created by Chidume Nnamdi on 13/04/2026.
////
//
//#include "parser.hpp"
//
//void Parser::parse() {
//    
//    while (currentToken().type != TokenType::END_OF_FILE) {
//        
//        Token token = currentToken();
//        
//        // if selector_start
//        // consume till }
//        if (token.type == TokenType::SELECTOR_START && tokens[index + 1].type != TokenType::END_OF_FILE) {
//            Rule rule = consumeSelector();
//            CSSRule r;
//            r.rule = rule;
//            r.type = 0;
//            rules.push_back(r);
//        }
//        
//        if (token.type == TokenType::AT_KEYWORD) {
//            MediaRule mediaRule = consumeMedia();
//            CSSRule r;
//            r.mediaRule = mediaRule;
//            r.type = 1;
//            rules.push_back(r);
//        }
//
//        advance();
//    }
//    
//}
//
//Rule Parser::consumeSelector() {
//    
//    vector<Token> selector;
//    
//    consumeToken(TokenType::SELECTOR_START, "Expected to be start of selector.");
//    
//    while (currentToken().type != TokenType::SELECTOR_END) {
//        selector.push_back(currentToken());
//        advance();
//    }
//    
//    consumeToken(TokenType::SELECTOR_END, "Expected to be end of selector.");
//    
//    consumeToken(TokenType::LBRACE, "Expected to see '{'.");
//    
//    // pick declarations till }
//    R declarations = consumeDeclList();
//    string selectorName = vectorToString(selector);
//        
//    Rule rule;
//    rule.declarations = declarations.declList;
//    rule.children = declarations.rules;
//    rule.mediaRules = declarations.mediaRules;
//    
//    rule.selectors = { vectorToString(selector) };
//    return rule;
//    
//}
//
//R Parser::consumeDeclList() {
//
//    vector<Declaration> declList;
//    vector<Rule> rules;
//    vector<MediaRule> mediaRules;
//    R decls;
//
//    while(currentToken().type != TokenType::RBRACE) {
//
//        if (currentToken().type == TokenType::SELECTOR_START) {
//            Rule r = consumeSelector();
//            rules.push_back(r);
//            consumeToken(TokenType::RBRACE, "Expected '}'");
//
//        } else if (currentToken().type == TokenType::AT_KEYWORD) {
//            MediaRule mediaRule = consumeMedia();
//            mediaRules.push_back(mediaRule);
//            // consume }
//            consumeToken(TokenType::RBRACE, "Expected '}'.");
//        }
//        else {
//            
//            Declaration decl = consumeDeclItem();
//            declList.push_back(decl);
//            consumeToken(TokenType::SEMICOLON, "Expected to see ';'");
//            
//        }
//    }
//    
//    decls.declList = declList;
//    decls.rules = rules;
//    decls.mediaRules = mediaRules;
//
//    return decls;
//}
//
//Declaration Parser::consumeDeclItem() {
//    
//    vector<Token> name;
//    vector<Token> value;
//    Declaration dcl;
//    
//    while (currentToken().type != TokenType::SEMICOLON) {
//            
//        // pick the decl name
//
//        consumeToken(TokenType::DECLARATION_NAME_START, "Expected to see 'DECLARATION_NAME_START'");
//        while (currentToken().type != TokenType::DECLARATION_NAME_END) {
//            name.push_back(currentToken());
//            advance();
//        }
//        
//        consumeToken(TokenType::DECLARATION_NAME_END, "Expected to see 'DECLARATION_NAME_END'");
//        
//        consumeToken(TokenType::COLON, "Expected to see ':'");
//        
//        // pick value
//        if (currentToken().type == TokenType::DECLARATION_VALUE_START) {
//            advance();
//            while (currentToken().type != TokenType::DECLARATION_VALUE_END) {
//                value.push_back(currentToken());
//                advance();
//            }
//            advance();
//        }
//        
//    }
//    
//    dcl.property = vectorToString(name);
//    dcl.value = vectorToString(value);
//    
//    return dcl;
//}
//
//MediaRule Parser::consumeMedia() {
//    
//    // consume till {
//    vector<Token> media;
//    vector<Rule> rules;
//    vector<MediaRule> mediaRules;
//    
//    advance();
//
//    while(currentToken().type != TokenType::LBRACE) {
//        media.push_back(currentToken());
//        advance();
//    }
//    
//    // {
//    consumeToken(TokenType::LBRACE, "Expected '{'.");
//
//    while (currentToken().type != TokenType::RBRACE) {
//        
//        if (currentToken().type == TokenType::SELECTOR_START && tokens[index + 1].type != TokenType::END_OF_FILE) {
//            Rule rule = consumeSelector();
//            rules.push_back(rule);
//        } else if (currentToken().type == TokenType::AT_KEYWORD) {
//            MediaRule mediaRule = consumeMedia();
//            mediaRules.push_back(mediaRule);
//        }
//        
//    }
//    
//    consumeToken(TokenType::RBRACE, "Expected '}'.");
//    
//    MediaRule mediaRule;
//    mediaRule.rules = rules;
//    mediaRule.mediaRules = mediaRules;
//    
//    return mediaRule;
//    
//}
//
//void Parser::parseSelector(vector<Token> selectors) {
//    
//}
//
//void Parser::parseDeclarationName(vector<Token> selectors) {
//    
//}
//
//void Parser::parseDeclarationValue(vector<Token> selectors) {
//    
//}
//
//bool Parser::isNestedRule() {
//  // Look ahead until we find '{' or ':'
////  let j = i;
////
////  while (j < tokens.length) {
////    if (tokens[j].type === "LBRACE") return true;  // nested rule
////    if (tokens[j].type === "COLON") return false;  // declaration
////    j++;
////  }
//
//  return false;
//}
//
//std::string Parser::vectorToString(vector<Token> _tokens) {
//    std::string name = "";
//    for (int i = 0; i <= (_tokens.size() - 1); i++) {
//        name += _tokens[i].value;
//    }
//    return name;
//}
//
//void Parser::consumeToken(TokenType type, string msg) {
//    
//    if (currentToken().type != type) {
//        throw runtime_error(msg);
//    }
//    
//    advance();
//
//}
//
//Token Parser::currentToken() {
//    return tokens[index];
//}
//
//size_t Parser::size() {
//    return tokens.size();
//}
//
//void Parser::advance() {
//    
//    if ((index + 1) > tokens.size()) {
//        throw "Out of bounds.";
//    }
//    
//    index++;
//    
//}
