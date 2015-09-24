%{
#include<stdio.h>
#include"Ast.h"
#define d(x)  x
//struct symbol * _t1;
extern char * yytext;
extern int yylineno;
struct c_member *  _t1 = NULL,* _t2 =NULL;
struct c_function *_fn;
struct class *_c=NULL;
char  _f[31]; 
int _f_a=0;
struct ast * _tmp;
%}
%union {
struct ast * a;
double  d; 
char s[33];
int comp;
struct c_member * m;
}
%start calclist
%token IF ELSE THEN
%right '='
%left CMP 
%left '+' '-'
%left '*' '/'
%token <comp> CMP
%token SEMI COMMA WHILE 
%token <s>  NAME
%token <d> NUMBER
%token CLASS PUBLIC PRIVATE FUN ENDFUN INHER ENDIF  ENDELSE ENDWHILE
%token SWITCH CASE ENDCASE ENDSWITCH
%type <a> exp   list  stmt case
%type <m> args
%%
calclist :  stmt {printf("Ans = %f",eval($1));}	
	|calclist  stmt {printf("Ans = %f ",eval($2));}
	|s_exp{;} 
        | CLASS  NAME INHER  NAME {_c=lookup_c($4);inherits(_c,$2);_c=lookup_c($2);}'{'  add_class '}' {_c=NULL;}
        |calclist CLASS NAME INHER NAME {_c=lookup_c($5);inherits(_c,$3);_c=lookup_c($3);}'{'  add_class '}' {_c=NULL;}
	|CLASS NAME {add_class($2);_c=lookup_c($2);} '{'  add_class '}' {_c=NULL;}
	| calclist CLASS NAME {add_class($3);_c=lookup_c($3);} '{'  add_class '}' {_c=NULL;}
        |NAME NAME SEMI {_make_object(lookup_c($1),$2);}
        |calclist NAME NAME SEMI {_make_object(lookup_c($2),$3);}
;
add_class: add_var{;}
	|add_class add_var{;}
	|add_fun{;}
	|add_class add_fun{;}
add_var : NAME '=' exp SEMI {add_c_var( _c,$1,1,eval($3));}
	| PUBLIC NAME '=' exp SEMI {add_c_var( _c,$2,1,eval($4));}
	| PRIVATE NAME '=' exp SEMI {add_c_var( _c,$2,0,eval($4));}
add_fun :FUN NAME '(' {strcpy(_f,$2);add_c_func(_c,_f);} args ')'{make_c_f(lookup_c_f(_c,_f),$5,NULL);} '=' list SEMI  {make_c_f(lookup_c_f(_c,_f),$5,$9); _c_f_start_arg=NULL;_c_f_end_arg=NULL;}
args :  NAME {$$= addsymlist($1);}
	|args COMMA NAME {$$=addsymlist($3);}
;
stmt :  IF exp THEN  stmt ENDIF   {$$ = newflow('I',$2,$4,NULL);}
        |IF exp THEN  stmt ELSE stmt  ENDELSE   {$$ = newflow('I',$2,$4,$6);}
	|list SEMI {$$=$1;}
	|WHILE exp THEN  stmt ENDWHILE  {$$ = newflow('W',$2,$4,NULL);}
        |SWITCH exp {_tmp=$2;} case ENDSWITCH {$$=$4;}
case :  CASE exp ':' stmt ENDCASE {$$=newflow('W',newnum(eval($2)==eval(_tmp)),$4,NULL);}
        | CASE exp ':' stmt ENDCASE case  {$$=newflow('W',newnum(eval($2)==eval(_tmp)),$4,$6);}
/*
	|stmt IF exp THEN '{' stmt '}' ELSE '{' stmt  '}'    {$$ = newflow('I',$3,$6,$10);}
        |stmt  IF exp THEN '{' stmt '}'{$$ = newflow('I',$3,$6,NULL);}
	*/;

list	 : exp   {if(_f_a==0){$$=$1;}else{setvalue(_fn,eval($1));}}
	| list  COMMA  exp    {if(_f_a==0){$$=newast('L',$1,$3);}else{setvalue(_fn,eval($3));}}	
;
s_exp : exp SEMI {printf("Ans = %f \n",eval($1) );}
	| s_exp exp SEMI {printf("Ans = %f \n",eval($2));}    
exp :    exp '+' exp {$$=newast('+',$1,$3);}
       	 |exp '-' exp {$$=newast('-',$1,$3);}
	 |exp '*' exp {$$=newast('*',$1,$3);}
	 |exp '/' exp {$$=newast('/',$1,$3);}		
	 |NAME {$$=var(lookup_u(_c,lookup_c_f(_c,_f),$1));}
	 |NAME'.'NAME {$$= var(lookup_r(lookup_c($1),NULL,$3)); }
	 |NAME'.'NAME'('{_c= lookup_c($1);strcpy(_f,$3);_f_a = 1;_fn= lookup_c_f(lookup_c($1),$3);}list')'{_f_a = 0;$$=newnum(eval(_fn->body));_fn=NULL;_c=NULL;strcpy(_f,"");_count_arg=0;}
	 |NUMBER {$$=newnum($1);}
	 |NAME '=' exp  {$$ = newasgn(lookup_u(_c,lookup_c_f(_c,_f),$1),$3);}
         |NAME'.'NAME{_c = lookup_c($1);} '='exp{$$ = newasgn(lookup_u(_c,NULL,$3),$6);}
	 |exp CMP  exp {$$= newast($2,$1,$3);}
%%
void yyerror(char * s){
printf("%s \n at line number %d  \n because of this token %s \n ",s,yylineno,yytext);
}

