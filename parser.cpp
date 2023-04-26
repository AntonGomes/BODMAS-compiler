/*
TERMINALS: +, -, *, /, (, ), NUM, i
NON-TERMINALS: E, E', T, T', F

PRODUCTIONS: 
E -> T E'
E'-> + T E' | - T E' | i
T -> F T'
T'-> * F T' | / F T' | i
F -> ( E ) | NUM

FIRST(E) = FIRST(T) = FIRST(F) = {(, NUM}
FIRST(E') = {+, -, i}
FIRST(T') = {*, /, i}

FOLLOW(E) = FOLLOW(E`) = {), $}
FOLLOW(T) = FOLLOW(T`) = {+, -, ), $}
FOLLOW(F) = {*, /, +, -, ), $}
*/

#include<iostream>
#include<set>
#include "lexer.cpp"

const TokenType i;

std::set<TokenType> TERMINALS = {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LEFT_PAREN,
    RIGHT_PAREN,
    NUMBER,
    i
    };

std::set<TokenType> FIRST_E = {LEFT_PAREN, NUMBER};
std::set<TokenType> FIRST_E_PRIME = {PLUS, MINUS, i};
std::set<TokenType> FIRST_T = {LEFT_PAREN, NUMBER};
std::set<TokenType> FIRST_T_PRIME = {MULTIPLY, DIVIDE, i};
std::set<TokenType> FIRST_F = {LEFT_PAREN, NUMBER};

std::set<TokenType> FOLLOW_E = {RIGHT_PAREN, END_OF_FILE};
std::set<TokenType> FOLLOW_E_PRIME = {RIGHT_PAREN, END_OF_FILE};
std::set<TokenType> FOLLOW_T = {PLUS, MINUS, RIGHT_PAREN, END_OF_FILE};
std::set<TokenType> FOLLOW_T_PRIME = {PLUS, MINUS, RIGHT_PAREN, END_OF_FILE};
std::set<TokenType> FOLLOW_F = {MULTIPLY, DIVIDE, PLUS, MINUS, RIGHT_PAREN, END_OF_FILE};

