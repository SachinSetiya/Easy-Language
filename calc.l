%{
#include<stdio.h>
#include"y.tab.h"
#include<strings.h>
%}
 /* float exponent */

%%
	/* normal operator */
"+"    	|
"="	|
"-"	|
"*"	|
"/" 	|
"{"	|
"."	|
"("	|
")"	|
":"	|
"}"	{return yytext[0];}

 /* now the comparision operator */
"<"	{yylval.comp = 1;return CMP;}
">"	{yylval.comp = 2;return CMP;} 
"!="	{yylval.comp = 3;return CMP;}
"=="	{yylval.comp = 4;return CMP;}
"<="	{yylval.comp = 5;return CMP;}
">="	{yylval.comp = 6;return CMP;}
","	{return COMMA;}
 /*number double + int both */
[0-9]+"."[0-9]+		|
"."?[0-9]+		{yylval.d = atof(yytext);return NUMBER;}
"//"[.]*		;
[ ]+ 		;
";"		return SEMI;
[\n]+		;
[.]*	{printf("something bad happend");}
"if" 	{return IF;}
"else"	{return ELSE;}
"then"	{return THEN;}
"while"	{return WHILE;}
"class" {return CLASS;}
"public" {return PUBLIC;}
"private" {return PRIVATE;}
"fun"  {return FUN;}
"endfun" {return ENDFUN;}
"inherits" {return INHER;}
"endif"    {return ENDIF;}
"endelse"	{return ENDELSE;}
"endwhile"	{return ENDWHILE;}
"switch"	{return SWITCH;}
"case"		{return CASE;}
"endcase"	{return ENDCASE;}
"endswitch" {return ENDSWITCH;}
[a-zA-Z][a-zA-Z]* {strcpy(yylval.s,yytext);return NAME;}
%%
int yywrap(void){return 1;}
