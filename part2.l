%{
char buf[100];
char *s;
int count = 0;
int lineNum = 1;

#include <stdio.h>
#include <string.h>
#include <malloc.h>

char *chopper(char *subj);
%}

%x STRING
%x COMMENT

LETTER	[a-zA-Z]
DIGIT	[0-9]
WS		[\t \r]
NL		[\n\r]
NQ		[^"\n]	
DQ		[\"\"]

%%
\/\/.*{NL}					{ lineNum++; /*single line comment ignored and removed */ } 
"/*"[^*\n\r]*				{ BEGIN COMMENT; /*enter block comment state */ }
<COMMENT>[^*\n\r]*			{}
<COMMENT>"*"+[^*/\n/\r]*	{}
<COMMENT>{NL}+				{ lineNum++; }
<COMMENT>"*"+"/"			{ BEGIN 0; /*exit block comment state*/ }
\" { BEGIN STRING; s = buf; }
<STRING>[^\"\n\r] 			{ *s++ = *yytext; }
<STRING>\" { *s = 0; 
			BEGIN 0;
			yytext = buf;
			count++;
			return 75;
			}
<STRING>\"\"/([^\"\n\r]|\") { *s++ = '"'; /* enclosed escaped double quotes */ }
<STRING>[\n\r]+ 			{BEGIN 0; yytext = "\""; count++; return 555; }

{WS}				{/* ignore white space */}
{NL}				{lineNum++; /* line counter increment */ }
{DIGIT}+			{ count++; return 25; /* integer */ }
{DIGIT}+\.{DIGIT}*  { count++; return 25; /* float */ }
{DIGIT}*\.{DIGIT}+  { count++; return 25; /* float */ }
":=" 				{count++; return 101;}
"-" 				{count++; return 102;}
"+" 				{count++; return 103;}
"*" 				{count++; return 104;}
"/" 				{count++; return 105;}
"%" 				{count++; return 106;}
"<>" 				{count++; return 107;}
">" 				{count++; return 108;}
"<" 				{count++; return 109;}
"<=" 				{count++; return 110;}
">=" 				{count++; return 111;}
"=" 				{count++; return 112;}
"(" 				{count++; return 201;}
")" 				{count++; return 202;}
";" 				{count++; return 203;}
"," 				{count++; return 204;}
"[" 				{count++; return 205;}
"]" 				{count++; return 206;}
(?i:BEGIN) 			{count++; return 301;}
(?i:DO) 			{count++; return 302;}
(?i:ELSE) 			{count++; return 303;}
(?i:END) 			{count++; return 304;}
(?i:FLOAT) 			{count++; return 305;}
(?i:FOR) 			{count++; return 306;}
(?i:IF) 			{count++; return 307;}
(?i:INTEGER) 		{count++; return 308;}
(?i:THEN) 			{count++; return 309;}
(?i:PRINT) 			{count++; return 310;}
(?i:PROGRAM) 		{count++; return 311;}
(?i:UNTIL) 			{count++; return 312;}
(?i:WHILE) 			{count++; return 313;}
(?i:AND) 			{count++; return 314;}
(?i:OR) 			{count++; return 315;}
(?i:return) 		{count++; return 316;}
{LETTER}({LETTER}|{DIGIT}|"_")* 	{ count++; yytext = chopper(yytext); return 50; /* variable */ }
_[^ \n\r\t]+						{return 555; }
. 									{return 555; /* garbage collector */}
%%

char *chopper(char *subj) {
    char *buff = subj;
    if (strlen(subj) > 29) {
        buff = (char *) malloc(30);
        memcpy(buff, subj, 29);
        buff[30] = '\0';
    }
    return buff;
}