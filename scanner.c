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

// returns true if next character matches the given character. Returns false if source is at end or does not match the character.
static bool match(char expected){
    if (isAtEnd()) return false;
    if (*scanner.current != expected) return false; // because current is on the next character than the one currently in the switch
    scanner.current++;

    return true;
}

// returns the next character (at position current) without consuming it i.e. incrementing the current pointer
static char peek(){
    return *scanner.current;
}

static char peekNext(){

    if(isAtEnd()) return '\0';
    return scanner.current[1];

}

// skips any whitespace and comments
static void skipWhiteSpace(){
    for(;;){
        char c = peek();
        switch (c){
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        
        case '\n':
            scanner.line++;
            advance();
            break;

        case '/':
            if(peekNext() == '/'){
                // goes until the end of the line;
                while(peek() != '\n' && !isAtEnd()) advance();
            }else {
                return;
            }

            break;

        default:
            return;
        }
    }
}

// makes string token when found
static Token string(){

    while(peek() != '"' && !isAtEnd()){
        if(peek() == '\n') scanner.line++;
        advance();
    }

    if(isAtEnd()) return errorToken("Unterminated string.");

    // the closing quote
    advance();
    return makeToken(TOKEN_STRING);
}

static bool isDigit(char c){

    return c >= '0' && c <= '9';

}

// makes number  token
static Token number(){

    while(isDigit(peek())) advance();

    // looking for a fractional part
    if(peek() == '.'  && isDigit(peekNext())){
        
        advance();
        

        while(isDigit(peek())) advance();
    }

    return makeToken(TOKEN_NUMBER);
}

static bool isAlpha(char c){
    
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

static TokenType checkKeyword(int start, int length, const char* rest, TokenType type){

    if(scanner.current - scanner.start == start + length && memcmp(scanner.start + start, rest, length) == 0){
        return type;
    }

    return TOKEN_IDENTIFIER;
}


static TokenType identifierType(){

    switch (scanner.start[0]){
        case 'a': return checkKeyword(1, 2, "nd", TOKEN_AND);
        case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
        case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);

        // false, fun and for
        case 'f': 
            if(scanner.current - scanner.start > 1){
                switch (scanner.start[1])
                {
                case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
                case 'o': return checkKeyword(2,1, 'r', TOKEN_FOR);
                case 'u': return checkKeyword(2, 1, "n", TOKEN_FUN);
                }
            }
            break;

        case 'i': return checkKeyword(1, 1, "f", TOKEN_IF);
        case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
        case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
        case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
        case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);

        // for true, this
        case 't':  

            if(scanner.current - scanner.start > 1) { // not just t
                switch (scanner.start[1]){
                case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
                case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
                }
            } 

            break; 

        case 'v': return checkKeyword(1, 2, "ar", TOKEN_VAR);
        case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
            
    }

    return TOKEN_IDENTIFIER;    
}

static Token identifier(){
    
    while (isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}


Token scanToken(){

    skipWhiteSpace();
    scanner.start = scanner.current; 
    
    if(isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    if(isAlpha(c)) return identifier();
    if(isDigit(c)) return number();

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

        // literal tokens
        case '"': return string();

    }

    return errorToken("Unexpected character.");
}