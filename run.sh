yacc -d parse.y
lex calc.l
gcc -std=c99 lex.yy.c y.tab.c
./a.out
