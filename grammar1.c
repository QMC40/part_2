%token STRING_LIT NUMBER VARIABLE GARBAGE 
%token LEFT_ASSIGN MINUS PLUS STAR DIVIDER MODULUS 
%token NE_OP GR_OP LS_OP LE_OP GE_OP EQ_OP
%token OPENPAREN CLOSEPAREN SEMICOLON COMMA OPENBRKET CLOSEBRKET
%token COMMENCE DO ELSE END FLOAT FOR IF INTEGER THEN PRINT 
%token PROGRAM UNTIL WHILE AND OR RETURN
%token BOOLEAN FUNC POINTER STRUCT
%token BOOL_EXPR REL_EXPR INT_EXPR FLT_EXPR

#ifndef YYSTYPE
#define YYSTYPE int
#endif

#define STRING_LIT	75
#define NUMBER		25
#define VARIABLE	50

#define LEFT_ASSIGN 101
#define MINUS 		102
#define PLUS		103
#define STAR		104
#define DIVIDER		105
#define MODULUS     106
#define NE_OP		107
#define GR_OP		108
#define LS_OP		109
#define LE_OP		110
#define GE_OP		111
#define EQ_OP		112

#define OPENPAREN	201
#define CLOSEPAREN	202
#define SEMICOLON	203
#define COMMA		204
#define OPENBRKET	205
#define CLOSEBRKET	206

#define COMMENCE	301
#define DO			302
#define ELSE		303
#define END			304
#define FLOAT		305
#define FOR			306
#define IF			307
#define INTEGER		308
#define THEN		309
#define PRINT		310
#define PROGRAM		311
#define UNTIL		312
#define WHILE		313
#define AND			314
#define OR			315
#define RETURN		316
#define BOOLEAN		317
#define FUNC		318
#define POINTER		319
#define STRUCT		320

#define BOOL_EXPR	401
#define REL_EXPR	402
#define INT_EXPR	403
#define FLT_EXPR	404


extern YYSTYPE yylval;