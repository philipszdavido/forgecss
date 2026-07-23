//
//  parse-css.cpp
//  ForgeEngine
//
//  Created by Chidume Nnamdi on 13/07/2026.
//

#include "parse-css.hpp"

Stylesheet* parseCSS(std::string css) {
    
    Tokenizer lex(css);
    std::vector<Token> tokens = lex.tokenize();
    
    Parser parser(tokens);
    Stylesheet* styleSheet = parser.parse();
    
    return styleSheet;
    
}
