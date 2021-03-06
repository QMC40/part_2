%{
#include <stdio.h>
#include <string.h>

void yyerror(const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

int yywrap()
{
	return 1;
}

main()
{
	yyparse();
}

%}

%token STRING_LIT	75
%token NUMBER		25
%token VARIABLE		50

%token ASSIGNMENT	101
%token MINUS		102
%token PLUS			103
%token STAR 		104
%token DIVIDE		105
%token MODULUS		106
%token NE_OP 		107
%token GT_OP		108
%token LT_OP		109
%token LE_OP    	110
%token GE_OP		111
%token EQ_OP		112

%token OPN_PAREN 	201
%token CLS_PAREN	202
%token SEMICOLON	203
%token COMMA		204
%token OPN_BRKT		205
%token CLS_BRKT		206

%token COMMENCE 	301
%token DO  			302
%token ELSE 		303
%token END 			304
%token FLOAT 		305
%token FOR 			306
%token IF 			307
%token INTEGER 		308
%token THEN 		309
%token PRINT 		310
%token PROGRAM  	311
%token UNTIL 		312
%token WHILE 		313
%token AND 			314
%token OR 			315
%token RETURN		316

%token BOOLEAN 		401
%token FUNC 		402
%token POINTER 		403
%token STRUCT		404
%token BOOL_EXPR 	405
%token REL_EXPR 	406
%token INT_EXPR 	407
%token FLT_EXPR		408

%%
expre:
	NUMBER	{ printf("we be parsin' "); }
	;

