//
//  CSSAST.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 20/04/2026.
//

#ifndef CSSAST_hpp
#define CSSAST_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "./selectors/includes.h"

using namespace std;

struct Color {};
struct Dimension {};
struct Variable {};

struct Declaration {
    string name;
    string value;
};

struct Rule;

struct StyleRule {
    vector<string> selectors;
    vector<Selector> _selectors;
    vector<Declaration> declarations;
    vector<Rule> nestedRules;
};

struct AtRule {
    string name;
    string prelude;
    vector<Rule> rules;
};

struct Rule {
    bool isAtRule;
    StyleRule style;
    AtRule at;
};

struct Stylesheet {
    vector<Rule> rules;
};

#endif /* CSSAST_hpp */
