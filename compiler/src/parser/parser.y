%{
#include <cstdio>
#include "../ast/ast.hpp"
#include "../lexer/lexer.hpp"

SymbolTable st;
llvmSymbolTable new_st;
llvmFunctionTable new_ft;
std::string tabcount;
bool debug = 0;
bool optimization_enabled = false;
std::string program_name = "main";


%}

%token T_byte      "byte"
%token T_int       "int"
%token T_if        "if"
%token T_else      "else"
%token T_true      "true"
%token T_false     "false"
%token T_proc      "proc"
%token T_reference "reference"
%token T_return    "return"
%token T_while     "while"

%token<var> T_id
%token<num> T_const
%token<character> T_char
%token<var> T_string

%token T_equal  "=="
%token T_notEq  "!="
%token T_lessEq "<="
%token T_moreEq ">="

%left<op> '|'
%left<op> '&'
%nonassoc<op> "==" "!=" '>' '<' "<=" ">="
%left<op> '+' '-'
%left<op> '*' '/' '%'
%nonassoc<op> '!'

%expect 1

%union {
    LocalDef *lcl_def;
    DefList *local_def_list;
    Fparlist *fpar_list;
    Fpar *fpar_def;
    Stmt *stmt;
    CompoundStmt *cmpdstmt;
    Func_call *func_call;
    ExprList *expr_list;
    Expr *expr;
    Lvalue *lvalue;
    Cond *cond ;

    RType rtype;
    std::string *var;
    int num;
    char character;
    char op;
}

%type<lcl_def> local_def var_def program func_def
%type<local_def_list> local_def_list
%type<fpar_list> fpar_list
%type<fpar_def> fpar_def
%type<rtype> data_type r_type type 
%type<stmt> stmt 
%type<cmpdstmt> compound_stmt compound_stmt_helper
%type<func_call> func_call
%type<expr_list> expr_list
%type<expr> expr
%type<lvalue> l_value
%type<cond> cond


%%

program:
    func_def    {$1->sem(); program_name = $1->get_name() ;$1->llvm_igen(optimization_enabled); }
;

func_def:
    T_id '(' fpar_list ')' ':' r_type local_def_list compound_stmt  { $$ = new Func_def($1,$3,$6,$7,$8); }
|   T_id '(' ')' ':' r_type local_def_list compound_stmt { $$ = new Func_def($1,$5,$6,$7); }
;

local_def_list:
    /* nothing */               { $$ = new DefList(); }
|   local_def_list local_def    { $1->append_def($2); $$ = $1; }
;

fpar_list:
    fpar_def                { $$ = new Fparlist(); $$->append_fpar($1); }
|   fpar_list ',' fpar_def  { $1->append_fpar($3); $$ = $1; }
;



fpar_def:
    T_id ':' "reference" type   { $$ = new Fpar($1,true,$4); }
|   T_id ':' type               { $$ = new Fpar($1,false,$3); }
;

data_type:
    "int"   { $$ = TYPE_int; }
|   "byte"  { $$ = TYPE_char; }
;

type:
    data_type           { $$ = $1; }
|   data_type '[' ']'   { if ($1 == TYPE_int) $$ = TYPE_int_array; else $$ = TYPE_char_array; }
;

r_type:
    data_type   { $$ = $1; }
|   "proc"      { $$ = TYPE_void; }
;

local_def:
    func_def    { $$ = $1; }
|   var_def     { $$ = $1; }
;


var_def:
    T_id ':' data_type ';'                  { $$ = new Var_def($1,$3); }
|   T_id ':' data_type '[' T_const ']' ';'  { $$ = new Var_def($1,$3,$5); }
;


stmt:
    ';'                                 { $$ = new NoOp(); }
|   l_value '=' expr ';'                { $$ = new Let($1,$3); }
|   compound_stmt                       { $$ = $1; }
|   func_call ';'                       { $$ = $1; }
|   "if" '(' cond ')' stmt              { $$ = new If($3,$5); } 
|   "if" '(' cond ')' stmt "else" stmt  { $$ = new If($3,$5,$7); }
|   "while" '(' cond ')' stmt           { $$ = new While($3,$5); }
|   "return" ';'                        { $$ = new Return(); }
|   "return" expr ';'                   { $$ = new Return($2); }
;

compound_stmt:
    '{' compound_stmt_helper '}'        { $$ = $2; }
;

compound_stmt_helper:
    /* nothing */                       { $$ = new CompoundStmt(); }
|   compound_stmt_helper stmt           { $1->append_stmt($2); $$ = $1; }
;

func_call:
    T_id '(' ')'            { $$ = new Func_call($1); }
|   T_id '(' expr_list ')'  { $$ = new Func_call($1,$3); }
;

expr_list:
    expr                { $$ = new ExprList(); $$->append_expr($1); }
|   expr_list ',' expr  { $1->append_expr($3); $$ = $1; }
;

expr:
    T_const         { $$ = new Const($1); }
|   T_char          { $$ = new Character($1); }
|   l_value         { $$ = $1; }
|   '(' expr ')'    { $$ = $2; }
|   func_call       { $$ = $1; }
|   '+' expr        { $$ = new UnOp($1,$2); }
|   '-' expr        { $$ = new UnOp($1,$2); }
|   expr '+' expr   { $$ = new BiOp($1,$2,$3); }
|   expr '-' expr   { $$ = new BiOp($1,$2,$3); }
|   expr '*' expr   { $$ = new BiOp($1,$2,$3); }
|   expr '/' expr   { $$ = new BiOp($1,$2,$3); }
|   expr '%' expr   { $$ = new BiOp($1,$2,$3); }
;

l_value:
    T_id                { $$ = new Lvalue_id($1); }
|   T_id '[' expr ']'   { $$ = new Lvalue_id($1,$3); }
|   T_string            { $$ = new Lvalue_string($1); }            
;

cond:
    "true"          { $$ = new ConstBool(1); }
|   "false"         { $$ = new ConstBool(0); }
|   '(' cond ')'    { $$ = $2; }
|   '!' cond        { $$ = new C_UnOp($1, $2); }
|   expr "==" expr  { $$ = new C_BiOp($1,$2,$3); }
|   expr "!=" expr  { $$ = new C_BiOp($1,$2,$3); }
|   expr '<' expr   { $$ = new C_BiOp($1,$2,$3); }
|   expr '>' expr   { $$ = new C_BiOp($1,$2,$3); }
|   expr "<=" expr  { $$ = new C_BiOp($1,$2,$3); }
|   expr ">=" expr  { $$ = new C_BiOp($1,$2,$3); }
|   cond '&' cond   { $$ = new C_BiOp($1,$2,$3); }
|   cond '|' cond   { $$ = new C_BiOp($1,$2,$3); }
;


%%

int main(int argc, char* argv[]) { 
    for (int i =1; i<argc; ++i){
        std::string arg = argv[i];
        if (arg == "-O") {
            optimization_enabled = true;
        }
    } 
    int result = yyparse();
    return result;
}