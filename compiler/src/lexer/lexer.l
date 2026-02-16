%option noyywrap

%{
#include <cstdio>
#include <cstdlib>
#include "../ast/ast.hpp"
#include "lexer.hpp"
#include "../parser/parser.hpp"

#define T_eof       0


int lineno = 1;
int c_stack = 0;

std::string parseEscapes(const char* str, int length) {
    std::string result;
    for (int i = 0; i < length; ++i) {
        if (str[i] == '\\' && i + 1 < length) {
            switch (str[i + 1]) {
                case 'n': result += '\n'; break;
                case 't': result += '\t'; break;
                case 'r': result += '\r'; break;
                case '\\': result += '\\'; break;
                case '\'': result += '\''; break;
                case '\"': result += '\"'; break;
                default: result += str[i + 1]; break;  // Handle any unknown escape character
            }
            ++i;  // Skip the next character since it's part of the escape sequence
        } else {
            result += str[i];
        }
    }
    return result;
}

%}

L [A-Za-z]
D [0-9]
W [ \t\r]
H [0-9a-f]



%x COMMENT

%%

"byte"              {return T_byte;}
"int"               {return T_int;}
"if"                {return T_if;}
"else"              {return T_else;}
"true"              {return T_true;}
"false"             {return T_false;}
"proc"              {return T_proc;}
"reference"         {return T_reference;}
"return"            {return T_return;}
"while"             {return T_while;}

{L}({L}|{D}|_)*     {yylval.var = new std::string(yytext); return T_id;}
{D}+                {yylval.num = atoi(yytext); return T_const;}
\"([^"\\\n]|\\[ntr\\\"\'\\])*\"  { yylval.var = new std::string(parseEscapes(yytext + 1, yyleng - 2)); return T_string; }
\'\\n\'          { yylval.character = '\n'; return T_char; }
\'\\t\'          { yylval.character = '\t'; return T_char; }
\'\\r\'          { yylval.character = '\r'; return T_char; }
\'\\0\'         { yylval.character = '\0'; return T_char; }
\'\\\'           { yylval.character = '\''; return T_char; }
\'\\\\\'         { yylval.character = '\\'; return T_char; }
\'\\\"\'         { yylval.character = '\"'; return T_char; }
\'[^\\\']\'      { yylval.character = yytext[1]; return T_char; }
\'\\x[0-9a-fA-F]{2}\' { 
    unsigned int hex_val;
    sscanf(yytext + 3, "%2x", &hex_val);
    yylval.character = (char)hex_val; 
    return T_char; 
}

[\(\)\{\}\[\]\=\+\-\*\/\%\!\&\|\>\<\:\;\,]  {yylval.op = yytext[0]; return yytext[0];}

"=="                {yylval.op = 'e'; return T_equal;}
"!="                {yylval.op = 'n'; return T_notEq;}
"<="                {yylval.op = 'l'; return T_lessEq;}
">="                {yylval.op = 'm'; return T_moreEq;}

\n                  { ++lineno; }
{W}+                { /* nothing */ }
"--".*"\n"          { ++lineno; }
"--"[^\n\x00]*      { /* nothing */ }

"(*"                {++c_stack; BEGIN(COMMENT);}
<COMMENT>"(*"       {++c_stack;}
<COMMENT>"*)"       {--c_stack; if (c_stack == 0) BEGIN(INITIAL);}
<COMMENT>\n         {lineno++;}
<COMMENT>"*"        { /* nothing */ }
<COMMENT>[^*\n]+    { /* nothing */ }               



.                   { yyerror("lexical error"); }


%%

void yyerror(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}