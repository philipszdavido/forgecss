//
//  log.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef log_hpp
#define log_hpp

#include <stdio.h>
#include <iostream>
#include "../ast/ast.hpp"

using namespace std;

void printStyleRule(const StyleRule& rule, int indent);
void printIndent(int level);
void printRule(const Rule& rule, int indent);
void printAtRule(const AtRule& at, int indent);
void printDeclaration(const Declaration& decl, int indent);
void printStylesheet(const Stylesheet& sheet);

#endif /* log_hpp */
