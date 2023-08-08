%{ 
#include<stdio.h> 
%}

%%
if|else|then { printf("\n%s - keyword", yytext);}
"*" {printf("\n%s - multiplication operator", yytext);}
"**" {printf("\n%s - Exponent operator", yytext);}
[a-zA-Z]+"-"[a-zA-Z]+ {printf("\n%s - Binary Minus", yytext);}
"-"[a-zA-Z]+ {printf("\n%s - Unary Minus", yytext);}
"=" {printf("\n%s - Assignment operator", yytext);}
"#"[a-zA-Z0-9](0,25) {printf("\n%s - Identifier", yytext);}
"[+ -]"[0-9](0,10) {printf("\n%s - Constant", yytext);}
.|\n {ECHO;}
%%

int main()
{
printf("\nEnter the string: ");
yylex();
}

int yywrap()
{
return 1;
}
