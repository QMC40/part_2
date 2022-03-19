#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include "definitions.h"

extern int yylex();

int errCount = 0, lookAhead = 0, token;
//global pass/fail flag/
bool goodFlag = true;

void parse();

void declarations();

void var_list();

bool peek(int expected);

void nextToken();

bool match(int expected);

void arrayDec();

void statements();

void statement();

void doTok();

void whileTok();

void forTok();

void ifTok();

void elseTok();

void variableTok();

void expr();

void print();

void rel_expr();

void operand();

void rel_op();

void error(int token, int expected);

void program();

int getToken();

int yywrap();

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main() {
    parse();
    return 0;
}

void parse() {
    //take first token and start...
    nextToken();
    program();
    if (errCount > 0) {
        printf("Compilation was unsuccessful with %d errors\n", errCount);
    } else { printf("it freakin' worked!\n"); }

}

void program() {
    match(PROGRAM);
    declarations();
    match(COMMENCE);
    statements();
    match(END);
    match(SEMICOLON);
}

void declarations() {
    int start = errCount;
    while (token != COMMENCE && token) {
        match(token);
        var_list();
        if (start == errCount) { printf("valid declaration\n"); }
        else { printf("declaration invalid\n"); }
    }
}

void var_list() {
    //strip var, see if list continues or array dec
    match(VARIABLE);
    if (token == COMMA) {
        match(COMMA);
        var_list();
    } else if (token == OPN_BRKT) { arrayDec(); }
    else {
        match(SEMICOLON);
    }
}

void arrayDec() {
    match(OPN_BRKT);
    match(NUMBER);
    match(CLS_BRKT);
}

void statements() {
    int start = errCount, stop = 10;
    while (token != END && token) {
//    while (token != END && token && stop) {
        statement();
//        stop--;
    }
}

void statement() {
    int start = errCount;
    char tokType[100];
    switch (token) {
        case IF: {
            strcpy(tokType, "if");
            ifTok(); break;
        }
        case DO: {
            strcpy(tokType, "do");
            doTok(); break;
        }
        case FOR: {
            strcpy(tokType, "for");
            forTok(); break;
        }
        case WHILE: {
            strcpy(tokType, "while");
            whileTok(); break;
        }
        case VARIABLE: {
            strcpy(tokType, "variable");
            variableTok(); break;
        }
        case EXPR: {
            strcpy(tokType, "expression");
            expr(); break;
        }
        default: {
            //default fail, need to readdress error system to make useful
            error(token, 999);
        }
    }
    if (start == errCount) { printf("valid %s\n", tokType); }
    else { printf("invalid %s\n", tokType); }
}

/* bool assignment(){
	bool good = true;
	while(token != commence) {
		if(token == integer) { match(integer); match(left_assignment); match(number); }
		else(token == float) { match(float); ; match(left_assignment); match(number); }
	}
} */

//matches terminals and draws next token or calls error on fail. returns bool if needed but can be ignored
bool match(int expected) {
    if (token == expected) {
        printf("%d matched!\n", token);
        nextToken();
    } else error(token, expected);
}

//prints error of mismatched token and incrs error count
void error(int tok, int expected) {
    //print error message incr error count, reset
    printf("failed!: token %d didn't match expected %d\n", tok, expected);
    errCount++;
    goodFlag = true;
    nextToken(); // test code to advance past failed match
    //exit(1);
}

void nextToken() {
    //getToken if lookAhead is empty, otherwise use token in lookAhead
    if (!lookAhead) {
        token = getToken();
    } else {
        token = lookAhead;
        lookAhead = 0;
    }
    printf("token drawn: %d\n", token);
}

int getToken() {
    return yylex();
}

bool peek(int expected) {
    if (lookAhead) {
        return (lookAhead == expected);
    } else {
        lookAhead = getToken();
        return (lookAhead == expected);
    }
}

int yywrap() {
    return 1;
}

void doTok() {}

void whileTok() {}

void forTok() {}

void ifTok() {

    match(IF);
        rel_expr();
    match(THEN);
        match(VARIABLE); //test
        match(ASSIGNMENT); //test
        match(NUMBER); //test
        match(SEMICOLON);
    //statements();
    if (token == ELSE) { elseTok(); }
    else {
        match(END);
        match(IF);
        match(SEMICOLON);
    }
}

void elseTok() {}

void rel_expr() {
    operand(); //test
    rel_op(); //test
    operand(); //test
}

void operand() {
    if(token == NUMBER) { match(NUMBER); }
    else { match(VARIABLE); }
}

void rel_op() {
    switch(token) {
        case LT_OP: {
            match(LT_OP); break;
        }
        case GT_OP: {
            match(GT_OP); break;
        }
        case GE_OP: {
            match(GE_OP); break;
        }
        case LE_OP: {
            match(LE_OP); break;
        }
        case NE_OP: {
            match(NE_OP); break;
        }
        case EQ_OP: {
            match(EQ_OP); break;
        }
        default: { error(token,999); }
    }
}

void variableTok() {}

void expr() {}

void print() {}