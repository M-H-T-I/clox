#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"


typedef struct{

    const char* start;
    const char* current; 
    int line;

}Scanner;

Scanner scanner;

void initScanner(const char* source){

    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;

}

// helper functions:

// returns true if current is at the end of the file.
static bool isAtEnd(){
    return *scanner.current == '\0';
}

// makes a tokn of the given type.
static Token makeToken(TokenType type){

    Token token;

    token.type = type;
    token.start = scanner.start;
    token.line = scanner.line;
    token.length = (int) (scanner.start - scanner.current);

    return token;

}

// creates an error token for the compiler to process when an error occurs.
static Token errorToken(const char* message){
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int) strlen(message);
    token.line = scanner.line;

    return token;
}

static char advance(){
    scanner.current++;
    return scanner.current[-1];
}

Token scanToken(){
    scanner.start = scanner.current; 
    
    if(isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    switch (c) {

        // single character tokens
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT);
        case '-': return makeToken(TOKEN_MINUS);
        case '+': return makeToken(TOKEN_PLUS);
        case '/': return makeToken(TOKEN_SLASH);
        case '*': return makeToken(TOKEN_STAR);

        // single character tokens which can be double character tokens:
        case '!': 
            return makeToken(match('=') ? TOKEN_BANG_EQUAL:TOKEN_BANG);
        case '=':
            return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>':
            return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    }

    return errorToken("Unexpected character.");
}