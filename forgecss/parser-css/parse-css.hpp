//
//  parse-css.hpp
//  ForgeEngine
//
//  Created by Chidume Nnamdi on 13/07/2026.
//

#ifndef parse_css_hpp
#define parse_css_hpp

#include <stdio.h>
#include <iostream>
#include <ostream>
#include "forgecss/lexer/lexer.hpp"
#include "forgecss/parser/parser.hpp"

using namespace css;

Stylesheet* parseCSS(std::string css);

#endif /* parse_css_hpp */
