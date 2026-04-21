//
//  log.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#include "log.hpp"

void printStylesheet(const Stylesheet& sheet) {
    for (const auto& rule : sheet.rules) {
        printRule(rule, 0);
    }
}

void printRule(const Rule& rule, int indent) {
    if (rule.isAtRule) {
        printAtRule(rule.at, indent);
    } else {
        printStyleRule(rule.style, indent);
    }
}

void printAtRule(const AtRule& at, int indent) {
    printIndent(indent);
    cout << "@" << at.name;

    if (!at.prelude.empty()) {
        cout << " " << at.prelude;
    }

    cout << " {" << endl;

    for (const auto& rule : at.rules) {
        printRule(rule, indent + 1);
    }

    printIndent(indent);
    cout << "}" << endl;
}

void printStyleRule(const StyleRule& rule, int indent) {
    printIndent(indent);

    for (size_t i = 0; i < rule.selectors.size(); i++) {
        cout << rule.selectors[i];
        if (i < rule.selectors.size() - 1) {
            cout << ", ";
        }
    }

    cout << " {" << endl;

    for (const auto& decl : rule.declarations) {
        printDeclaration(decl, indent + 1);
    }

    for (const auto& nested : rule.nestedRules) {
        printRule(nested, indent + 1);
    }

    printIndent(indent);
    cout << "}" << endl;
}

void printDeclaration(const Declaration& decl, int indent) {
    printIndent(indent);
    cout << decl.name << ": " << decl.value << ";" << endl;
}

void printIndent(int level) {
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
}
