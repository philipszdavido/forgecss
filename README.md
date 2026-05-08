# forgecss

forgecss is a C++ CSS parser project that tokenizes CSS input, builds a stylesheet AST, and returns the parsed rules.

## Overview

This project demonstrates a CSS parser architecture with separate tokenizer, parser, AST, and logging components.

It supports:

- CSS tokenization into identifiers, selectors, declarations, values, at-rules, functions, dimensions, hashes, and more
- Parsing of style rules, nested rules, and basic at-rules
- Selector parsing for simple selectors, class selectors, attribute selectors, pseudo-classes, and pseudo-elements
- Declaration parsing with values such as keywords, dimensions, colors, and function calls
- Console output of the parsed stylesheet using a simple AST printer

## Project structure

- `main.cpp` - example driver that tokenizes CSS, prints tokens, parses a stylesheet, and dumps the parsed output
- `lexer/` - tokenizer implementation
- `parser/` - recursive parser for rules, declarations, selectors, and values
- `ast/` - AST node definitions for stylesheets, rules, declarations, selectors, and values
- `log/` - debug printing helpers for the parsed stylesheet
- `TokenType/` - token kind definitions used by the lexer and parser
- `forgecss.xcodeproj/` - Xcode project for building the executable on macOS

## Usage

1. Open `forgecss.xcodeproj` in Xcode and build the `forgecss` target.
2. Run the resulting executable from Xcode or from the terminal.
3. The current `main.cpp` uses hard-coded CSS examples and prints:
   - the token stream produced by the lexer
   - the parsed stylesheet structure

Example workflow from terminal:

```bash
cd forgecss/forgecss
xcodebuild -project ../forgecss.xcodeproj
# or use Xcode directly
```

## Features

- Tokenizes CSS input into a sequence of typed tokens
- Parses selectors and style rules
- Supports nested rules inside style blocks
- Handles `@media` and other at-rules with nested rule parsing
- Parses declaration values including:
  - numeric dimensions (e.g. `10px`)
  - color hashes (e.g. `#d9d9d9`)
  - functions (e.g. `var(--color-outline)`)
  - identifiers and keywords

## Limitations

The current parser is intentionally limited and does not yet support full CSS grammar.

Known gaps include:

- full descendant and combinator selector parsing (e.g. `div span`, `div > span`)
- advanced selector groups and complex selector nesting
- full parsing of all CSS at-rule forms and prelude grammar
- complete cascade, specificity, and stylesheet evaluation

## Notes

The project is designed as a learning engine for CSS parsing rather than a production CSS processor. It is especially useful for experimenting with lexer/parser architecture and AST modeling in C++.
