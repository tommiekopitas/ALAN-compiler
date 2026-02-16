#include "ast.hpp"

LLVMContext AST::TheContext;
IRBuilder<> AST::Builder(AST::TheContext);
std::unique_ptr<Module> AST::TheModule;
std::unique_ptr<legacy::FunctionPassManager> AST::TheFPM;

Type *AST::i8 = IntegerType::get(TheContext, 8);
Type *AST::i32 = IntegerType::get(TheContext, 32);
Type *AST::i64 = IntegerType::get(TheContext, 64);

ExprList::ExprList(){
    expr_list = new std::vector<Expr*>();
}
ExprList::~ExprList() {
    for (auto expr: *expr_list) {
        delete expr;
    }
    delete expr_list;
}
std::vector<Expr*>* ExprList::get_expr_list() {
    return expr_list;
}
void ExprList::append_expr(Expr* e) {
    expr_list->push_back(e);
}

bool Stmt::returns() const {
    return returning;
}

std::string LocalDef::get_name() const {
    return "main";
}
bool LocalDef::is_function_def() const {
    return is_function;
}

DefList::DefList() {
    def_list = new std::vector<LocalDef*>();
}

DefList::~DefList() {
    for (auto def: *def_list) {
        delete def;
    }
    delete def_list;
}

std::vector<LocalDef*>* DefList::get_def_list() {
    return def_list;
}
 

RType Fpar::get_type() {
    return type;
}
bool Fpar::is_ref() {
    return ref;
}
std::string Fpar::get_name() {
    return name;
}

Fparlist::Fparlist()  {
    fpar_list = new std::vector<Fpar*>();
}
Fparlist::~Fparlist() {
    for (auto fpar: *fpar_list) {
        delete fpar;
    }
    delete fpar_list;
}
std::vector<Fpar*>* Fparlist::get_fpar_list() {
    return fpar_list;
}
void Fparlist::append_fpar(Fpar* fpar) {
    fpar_list->push_back(fpar);
}

int Const::get_num() {
    return num;
}

std::string Lvalue_id::get_name() {
    return name;
}

void Lvalue_id::set_type(RType t) {
    type = t;
}

Lvalue_string::Lvalue_string(std::string *n) {
    if (debug) std::cout << "Lvalue_string: " << *n << "||"<<std::endl;
    value = *n;
}

std::string Lvalue_string::get_name() {
    yyerror("Not a variable");
    return "";
}

Func_call::Func_call(std::string *n){
    if (*n == "main") name = "alan_" + *n;
    else name = *n;
    args = new std::vector<Expr*>();
    returning = false;
}

Func_call::Func_call(std::string *n, ExprList *a){
    if (*n == "main") name = "alan_" + *n;
    else name = *n;
    args = a->get_expr_list();
    returning = false;
}

Func_call::~Func_call() {
    for (auto arg: *args) {
        delete arg;
    }
    delete args;
}

C_BiOp::~C_BiOp() { 
    delete left; 
    delete right;
    delete leftc;
    delete rightc;
}

NoOp::NoOp() {
    returning = false;
}

Let::~Let() {
    delete var;
    delete expr;
}

CompoundStmt::~CompoundStmt() {
    for (auto stmt: stmt_list) {
        delete stmt;
    }
}

void CompoundStmt::append_stmt(Stmt* stmt) {
    stmt_list.push_back(stmt);
}

If::~If() {
    delete cond;
    delete then;
    if (els) delete els;
}

While::~While() {
    delete cond;
    delete body;
}

Return::~Return() {
    delete expr;
}

bool Return::returns() const {
    return true;
}

Func_def::Func_def(std::string *n, RType t, DefList* d, CompoundStmt* b){
    args = nullptr;
    type = t;
    body = b;
    if (*n == "main") name = "alan_" + *n;
    else name = *n;
    this->is_function = true;
    if (d) {
        decls = d->get_def_list();
    }
    else decls = new std::vector<LocalDef*>();
    args = new std::vector<Fpar*>();
    closures = new std::vector<closurevar*>();
}

Func_def::Func_def(std::string *n, Fparlist* a, RType t, DefList* d, CompoundStmt* b){
    type = t;
    body = b;
    if (*n == "main") name = "alan_" + *n;
    else name = *n;
    this->is_function = true;
    if (a) args = a->get_fpar_list();
    else args = new std::vector<Fpar*>();
    if (d) decls = d->get_def_list();
    else decls = new std::vector<LocalDef*>();
    closures = new std::vector<closurevar*>();

}

std::string Func_def::get_name() const { 
    return name;
}


Func_def::~Func_def() {
    delete body;
    if (args){
        for (auto arg: *args) {
            delete arg;
        }
        delete args;
    }
    if (decls){
        for (auto decl: *decls) {
            delete decl;
        }
        delete decls;
    }
    if (closures){
        for (auto closure: *closures) {
            delete closure;
        }
        delete closures;
    }
}

std::vector<closurevar*>* Func_def::get_closures() {
    if (closures == nullptr) yyerror("Closures not found while calling get_closures");
    return closures;
    }

Var_def::Var_def(std::string *n, RType t){
    name = *n;
    type  = t;
    c = -1;
    this->is_function = false;
}
Var_def::Var_def(std::string *n, RType t, int e){
    name = *n;
    c = e;
    this->is_function = false;
    if (t == TYPE_int) {
        type = TYPE_int_array;
    }
    else if (t == TYPE_char) {
        type = TYPE_char_array;
    
    }
    else {
        yyerror("Array type mismatch");
    }
}

