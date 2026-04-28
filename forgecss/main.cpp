//
//  main.cpp
//  forgecss
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#include <iostream>
#include <ostream>
#include "./lexer/lexer.hpp"
#include "./parser/parser.hpp"
#include "./log/log.hpp"

int main(int argc, const char * argv[]) {
    std::string css_ = R"(.baseline-status[data-astro-cid-7wt35nye]::part(root) { --animation-duration: .3s; --color-outline--light: #d9d9d9; --color-background--light: transparent; --color-text--light: inherit; --color-link--light: #1a73e8; --color-badge-background--light: #3367d6; --color-badge-text--light: #fff; --color-limited--light: #ea8600; --color-limited-secondary--light: #c6c6c6; --color-newly--light: #1a73e8; --color-newly-secondary--light: #a8c7fa; --color-widely--light: #1e8e3e; --color-widely-secondary--light: #c4eed0; --color-no_data--light: #707070; --color-no_data-secondary--light: #909090; --color-outline--dark: #666; --color-background--dark: transparent; --color-text--dark: inherit; --color-link--dark: #5aa1ff; --color-badge-background--dark: #3367d6; --color-badge-text--dark: #fff; --color-limited--dark: #f09418; --color-limited-secondary--dark: #565656; --color-newly--dark: #4185ff; --color-newly-secondary--dark: #2d509e; --color-widely--dark: #24a446; --color-widely-secondary--dark: #125225; --color-no_data--dark: #868686; --color-no_data-secondary--dark: #666; --color-limited: var(--color-limited--light); --color-newly: var(--color-newly--light); --color-widely: var(--color-widely--light); --color-no_data: var(--color-no_data--light); --color-outline: var(--color-outline--light); --color-background: var(--color-background--light); --color-text: var(--color-text--light); --color-link: var(--color-link--light); --color-badge-background: var(--color-badge-background--light); --color-badge-text: var(--color-badge-text--light); --color-limited-secondary: var(--color-limited-secondary--light); --color-widely-secondary: var(--color-widely-secondary--light); --color-newly-secondary: var(--color-newly-secondary--light); --color-no_data-secondary: var(--color-no_data-secondary--light); background: var(--color-background); border: 1px solid var(--color-outline); border-radius: 0.5rem; color: var(--color-text); font-family: Roboto, sans-serif; font-size: 0.875rem; font-style: normal; line-height: 1.71429; max-width: 50rem; padding-top: 1rem; padding-inline: 1.5rem; }

    body {
    color: red;
    margin: 10px;
  }

    .innerDiv p:first-letter {
        color: lightcoral;
        font-size: 40px;
    }

    p:first-of-type {
        color: orangered;
    }

    .innerDiv p:nth-last-of-type() {
        color: orangered;
    }

    p[lang|="fr"] {
        background: yellow;
    }

    @media screen and (min-width: 480px) {
        body {
            background-color: lightgreen;
          color: var(--green);
        }
    }

.card {
  color: red;

  &:hover {
    color: blue;
  }

  &.active {
    border: 1px solid black;
  }

  .title {
    font-weight: bold;
  }

  > .icon {
    margin-right: 8px;
  }
}

.card { color: red; }
.card:hover { color: blue; }
.card.active { border: 1px solid black; }
.card .title { font-weight: bold; }
.card > .icon { margin-right: 8px; }

)";
    
    std::string css = R"(

    p {
        @media screen and (min-width: 480px) {
            body {
                background-color: lightgreen;
              color: var(--green);
            }
        }

        bg: red;
        div {
            font-family: Roboto, sans-serif;
        }
    }

.card {
  color: red;

  &:hover {
    color: blue;
  }

  &.active {
    border: 1px solid black;
  }

  .title {
    font-weight: bold;
  }

  > .icon {
    margin-right: 8px;
  }
}

@keyframes
@supports
@layer
)";
    
    Tokenizer lex(css);
    std::vector<Token> tokens = lex.tokenize();
    
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << "[" << i << "] ";
        printTokenType(tokens[i].type);
        std::cout << ' ' << tokens[i].value << ' ' << endl;
    }
    
    std::cout << "===============================" << std::endl;
    
    Parser p(tokens);
    Stylesheet styleSheet = p.parse();

    printStylesheet(styleSheet);
    
    
    return EXIT_SUCCESS;
}
