//Write a lex program to recognize tokens and ignore others

%{
#include<stdio.h>
%}
%%
;|,|>>|<< {printf("\n%s is a separator\n", yytext);}
[a-z0-9A-Z | \n] {ECHO;}
%%
int main()
{
printf("\nEnter a string: ");
yylex();
}
int yywrap()
{
return 1;
}
