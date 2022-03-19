#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include "definitions.h"

extern int yylex();

int tokenNum = 1, errCount = 0, lookAhead = 0, token;
//global pass/fail flag/
bool goodFlag = true;

void parse();

void declarations();

void type();

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

void print(char *arg);

void rel_expr();

void operand();

void rel_op();

void error(int token, int expected);

void errorText(char *subj, char *expected);

void program();

int getToken();

int yywrap();

//DEBUG CODE!!! REMOVE BEFORE TURN IN!!!
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
    } else { printf("it freakin' worked!\n"); } //DEBUG CODE!!! REMOVE BEFORE TURN IN!!!

}

void program() {
    print("commence the parsing!\n");      //DEBUG CODE!!! REMOVE BEFORE TURN IN!!!
    match(PROGRAM); //311
    declarations();
    match(COMMENCE); //301
    statements();
    match(END); //304
    match(SEMICOLON); //203
}

void statements() {
    int start = errCount, stop = 10;
//    while (token != END && token) {
    while (token != END && token && stop) {         //DEBUG CODE!!! REMOVE BEFORE TURN IN!!!
        statement();
        stop--;
    }
}

void statement() {
    int start = errCount;
    char tokType[100];
    switch (token) {
        case IF: {
            strcpy(tokType, "if");
            ifTok();
            break;
        }
        case FOR: {
            strcpy(tokType, "for");
            forTok();
            break;
        }
        case WHILE: {
            strcpy(tokType, "while");
            whileTok();
            break;
        }
        case DO: {
            strcpy(tokType, "do");
            doTok();
            break;
        }
//        case VARIABLE: {
//            strcpy(tokType, "variable");
//            variableTok();
//            break;
//        }
//        case EXPR: {
//            strcpy(tokType, "expression");
//            expr();
//            break;
//        }
        default: {
            //default fail, need to readdress error system to make useful
            error(token, 999);
        }
    }
    if (start == errCount) { printf("valid %s\n", tokType); }
    else { printf("invalid %s\n", tokType); }
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
    match(SEMICOLON); //203
    //statements();
    if (token == ELSE) { elseTok(); }
    else {
        match(END); //304
        match(IF);
        match(SEMICOLON); //203
    }
}

void elseTok() {}

void rel_expr() {
    operand();
    rel_op();
    operand();
}

void operand() {
    switch (token) {
        case NUMBER: {
            match(NUMBER);
            break;
        }
        case VARIABLE: {
            match(VARIABLE);
            break;
        }
        default: {
            errorText("invalid operand", "number or variable");
        }
    }
}

void rel_op() {
    switch (token) {
        case LT_OP: {
            match(LT_OP);
            break;
        }
        case GT_OP: {
            match(GT_OP);
            break;
        }
        case GE_OP: {
            match(GE_OP);
            break;
        }
        case LE_OP: {
            match(LE_OP);
            break;
        }
        case NE_OP: {
            match(NE_OP);
            break;
        }
        case EQ_OP: {
            match(EQ_OP);
            break;
        }
        default: {
            errorText("invalid rel op",">,<,>=,<=,=,<>");
        }
    }
}

void variableTok() {}

void expr() {}

void declarations() {
    int start = errCount;
    bool empty = true;
    //take in var declarations till token comes back as my SIL 'BEGIN' token
    while (token != COMMENCE && token != 0) {
        type();
        var_list();
        match(SEMICOLON); //203
        empty = false;
        if (start == errCount) { printf("valid declaration\n"); }
        else { printf("declaration invalid\n"); }
    }
    if (empty) { printf("no valid declarations\n"); }
}

void type() {
    switch (token) {
        case INTEGER: {
            match(INTEGER); //308
            break;
        }
        case FLOAT: {
            match(FLOAT);
            break;
        }
        default: {
            error(VARIABLE, token);
            break;
        }
    }
}

void var_list() {
    //strip var, see what's next
    do {
        switch (token) {
            case VARIABLE: {
                match(VARIABLE);
                break;
            }
            case COMMA: {
                match(COMMA);
                var_list();
                break;
            }
            case OPN_BRKT: {
                match(OPN_BRKT);
                arrayDec();
                break;
            }
            default: {
                errorText("var_list","?");
            }
        }
    } while (token != SEMICOLON && token != 0);
}

void arrayDec() {
    do {
        switch (token) {
            case NUMBER: {
                match(NUMBER);
                break;
            }
            case COMMA: {
                match(COMMA);
                break;
            }
            default: {
                errorText("arrayDec","?");
            }
        }
    }while(token != CLS_BRKT && token != 0);
    match(CLS_BRKT);
}

bool match(int expected) {
    if (token == expected) {
        printf("token %d : %d matched!\n",tokenNum, token);
        tokenNum++;
        nextToken();
        return true;
    } else error(token, expected);
    return false;
}

//prints error of mismatched token and increments error count
void error(int tok, int expected) {
    //print error message incr error count, reset
    printf("failed!: token %d didn't match expected %d\n", tok, expected);
    errCount++;
    goodFlag = true;
    nextToken(); // test code to advance past failed match
    //exit(1);
}

void errorText(char *subj, char *expected) {
    //print error message incr error count, reset
    printf("token at fail is %d\n",token);
    printf("failed!: %s expected %s\n",subj, expected);
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
    //printf("token drawn: %d\n", token);
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

void print(char *arg) {
    printf("%s", arg);
}

int yywrap() {
    return 1;
}

/* bool assignment(){
	bool good = true;
	while(token != commence) {
		if(token == integer) { match(INTEGER); //308
		    match(left_assignment);
		    match(number);
		    }
		else(token == float) { match(float);
		match(left_assignment);
		match(number); }
	}
} */

//matches terminals and draws next token or calls error on fail. returns bool if needed but can be ignored
//bool match(int expected) {
//    if (token == expected) {
//        nextToken();
//        return true;
//    } else error(token, expected);
//    return false;
//}

//testing code that prints token info for portion being tested but the rest are silenced