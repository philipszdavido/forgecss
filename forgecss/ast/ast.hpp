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
#include "ast/values/Value/Value.hpp"

using namespace std;

struct Declaration {
    string name;
    vector<shared_ptr<Value>> value;
    bool important;
};

struct Rule;

// Style Rule
// ----------
// div { <-- selector(s)
//     border: 1px sold black; <-- declarations
// }
struct StyleRule {
    std::vector<ComplexSelector> selectors;
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
