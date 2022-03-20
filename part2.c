#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include "definitions.h"

extern int yylex();

extern int yyget_lineno();

//global pass/fail flag/
bool goodFlag = true;
int tokenNum = 1, errCount = 0, lookAhead = 0, token;

void parse();

void declarations();

void type();

void var_list();

void peek();

void nextToken();

bool match(int expected);

void arrayDec();

void statements();

void statement();

void assignment();

void if_stmt();

void for_stmt();

void while_stmt();

void do_stmt();

void else_stmt();

void variable();

void expr();

void print();

void rel_expr();

void math_expr();

void operand();

void number();

void rel_op();

void math_op();

void error(int token, int expected);

void errorText(char *subj, char *expected);

void errorClear();

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
    printf("commence the parsing!\n");      //DEBUG CODE!!! REMOVE BEFORE TURN IN!!!
    match(PROGRAM); //311
    declarations();
    match(COMMENCE); //301
    statements();
    match(END); //304
    match(SEMICOLON); //203
}

void statements() {
    int start = errCount;
    int stop = 10;                                  //DEBUG CODE!!! REMOVE BEFORE TURN IN!!!
//    while (token != END && token) {
    while (token != END && token != ELSE && token && stop) {         //DEBUG CODE!!! REMOVE BEFORE TURN IN!!!
//        printf("statement queue  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        statement();
        stop;                                     //DEBUG CODE!!! REMOVE BEFORE TURN IN!!!
    }
}

void statement() {
    int start = errCount;
    char statementType[100] = {"statement type"};
    switch (token) {
        case VARIABLE: {
            printf("assignment stmt\n");
            strcpy(statementType, "assignment statement");
            assignment();
            break;
        }
        case IF: {
//            printf("if stmt\n");
            strcpy(statementType, "if / then statement");
            if_stmt();
            break;
        }
        case FOR: {
            printf("for============================================================\n");
            strcpy(statementType, "for loop statement");
            for_stmt();
            break;
        }
        case WHILE: {
//            printf("while\n");
            strcpy(statementType, "while loop statement");
            while_stmt();
            break;
        }
        case DO: {
//            printf("do\n");
            strcpy(statementType, "do/until statement");
            do_stmt();
            break;
        }
        case PRINT: {
//            printf("print\n");
            strcpy(statementType, "print statement");
            print();
            break;
        }
        default: {
            errorText("invalid statement type", "");
            errorClear();
        }
    }
    if (start == errCount) {
        match(SEMICOLON);
        printf("valid %s\n", statementType);
    } else {
        errorClear();
        printf("invalid %s\n", statementType);
        match(SEMICOLON);
    }
    printf("here+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ switch\n");
}

void assignment() {
    match(VARIABLE);
    while (token == ASSIGNMENT) {
        match(ASSIGNMENT);
        expr();
    }
}

void expr() {
    switch (token) {
        case VARIABLE: {
            peek();
//            printf("lookahead: %d\n",lookAhead);

            if (lookAhead < NE_OP && lookAhead > ASSIGNMENT) {
                math_expr();
            } else if (lookAhead < OPN_PAREN && lookAhead > MODULUS) {
                rel_expr();
            } else if (lookAhead == SEMICOLON) { match(VARIABLE);
            } else { errorText("invalid operator in math expression", "math or rel operator"); }
            break;
        }
        case NUMBER: {
            number();
            break;
        }
        default: {
            errorText("expression ", "math expression or operand");
        }
    }
}

void rel_expr() {
//    printf("rel_expr\n");
    operand();
    rel_op();
    operand();
}

void math_expr() {
    printf("math_expr\n");
    operand();
    while (token < NE_OP && token > ASSIGNMENT) {
        math_op();
        operand();
    }
    printf("end math_expr\n");
}

void operand() {
    switch (token) {
        case NUMBER: {
            number();
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

void number() {
    if (token == NUMBER) {
        printf("here+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ number\n");
        match(NUMBER);
    } else {
        printf("here+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ minus\n");
        match(MINUS);
        match(NUMBER);
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
            errorText("invalid rel op", ">,<,>=,<=,=,<>");
        }
    }
}

void math_op() {
    switch (token) {
        case MINUS: {
            match(MINUS);
            break;
        }
        case PLUS: {
            match(PLUS);
            break;
        }
        case STAR: {
            match(STAR);
            break;
        }
        case DIVIDE: {
            match(DIVIDE);
            break;
        }
        case MODULUS: {
            match(MODULUS);
            break;
        }
        default: {
            errorText("invalid math op", "+,-,*,/,%");
        }
    }
}

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

void do_stmt() {}

void while_stmt() {
    match(WHILE);
    rel_expr();
    match(COMMENCE);
    statements();
    match(END);
    match(WHILE);
}

void for_stmt() {
    match(FOR);
    assignment();
    match(COMMA);
    number();
    if (token == COMMA) {
        match(COMMA);
        number();
    }
    statements();
    match(END);
    match(FOR);
}

void if_stmt() {

    match(IF);
    rel_expr();
    match(THEN);
    statements();
    if (token == ELSE) {
        match(ELSE);
        statements();
    }
    match(END); //304
    match(IF);

}

void print() {
    match(PRINT);
    match(OPN_PAREN);
    if (token == VARIABLE) { match(VARIABLE); }
    else { match(STRING_LIT); }
    match(CLS_PAREN);
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
                errorText("var_list", "?");
            }
        }
    } while (token != SEMICOLON && token != 0);
}

void arrayDec() {
    do {
        switch (token) {
            case NUMBER: {
                number();
                break;
            }
            case COMMA: {
                match(COMMA);
                break;
            }
            default: {
                errorText("arrayDec", "?");
            }
        }
    } while (token != CLS_BRKT && token != 0);
    match(CLS_BRKT);
}

//matches terminals and draws next token or calls error on fail. returns bool if needed but can be ignored
bool match(int expected) {
    if (token == expected) {
        printf("token %d : %d matched!\n", tokenNum, token);
        tokenNum++;
        nextToken();
        return true;
    } else error(token, expected);
    return false;
}

//prints error of mismatched token and increments error count
void error(int tok, int expected) {
    //print error message incr error count, reset
    printf("line %d failed!: token %d didn't match expected %d\n", yyget_lineno(), tok, expected);
    errCount++;
    goodFlag = true;
    nextToken(); // test code to advance past failed match
    //exit(1);
}

void errorText(char *subj, char *expected) {
    //print error message incr error count, reset
    printf("line %d failed!: %s expected %s got token %d\n", yyget_lineno(), subj, expected, token);
    errCount++;
    goodFlag = true;
    nextToken(); // test code to advance past failed match
    //exit(1);
}

//voids tokens in current statement(s) till reaching a semicolon or end of the source code
void errorClear() {
    while (token != SEMICOLON && token != END && token != 0) {
        printf("burned token %d\n", token);
        nextToken();
    }
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

void peek() {
    lookAhead = getToken();
}

int yywrap() {
    return 1;
}