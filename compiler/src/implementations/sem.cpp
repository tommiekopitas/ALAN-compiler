#include "../ast/ast.hpp"

void Expr::type_check(RType t){
    // sem();
    if (type != t) {
        std::string s = "Type mismatch expected " + std::to_string(t) + " got " + std::to_string(type);
        yyerror(s.c_str());
    }
}

RType Expr::get_type(){
    return type;
}

bool Expr::is_lvalue_id() const {
    return false;
}

bool Expr::is_string_literal() const{
    return false;
}

void Cond::type_check(RType t) {
    // sem();
    if (type != t) {
        yyerror("Type mismatch");
    }
}

void Fpar::sem() {
    st.insert(name, type, ref);
}

void BiOp::sem() {
    left->sem();
    right->sem();
    left->type_check(TYPE_int);
    right->type_check(TYPE_int);
    type = TYPE_int;
}

void UnOp::sem() {
    expr->sem();
    expr->type_check(TYPE_int);
    type = TYPE_int;
}

void Const::sem(){
    type = TYPE_int;
}

void Character::sem(){
    type = TYPE_char;
}

bool Lvalue_id::is_lvalue_id() const {
    return true;
}

void Lvalue_string::sem(){
    type = TYPE_char_array;
}

bool Lvalue_string::is_string_literal() const {
    return true;
}


void C_UnOp::sem(){
    cond->sem();
    cond->type_check(TYPE_int);
    type = TYPE_int;
}

void C_BiOp::sem(){
    if (leftc) {
        leftc->sem();
        rightc->sem();
        leftc->type_check(TYPE_int);
        rightc->type_check(TYPE_int);
        type = TYPE_int;
        return;
    }

    left->sem();
    right->sem();
    left->type_check(right->get_type());
    type = TYPE_int;
}

void ConstBool::sem(){
    type = TYPE_int;
}

void Let::sem(){
    if (var->is_string_literal()){
        // the variable is a string literal
        // I can't give it a new value
        yyerror("Can't assign to a string literal");
    }
    var->sem();
    expr->sem();
    var->type_check(expr->get_type());
}

void CompoundStmt::sem() {
    long unsigned int i = 0;
    for (auto stmt: stmt_list) {
        stmt->sem();
        if (stmt->returns()) returning = true;
        if (stmt->returns() && i < stmt_list.size() - 1)  yyerror("Unreachable code");
        i++;
    }
        
}

void If::sem(){
    cond->sem();
    cond->type_check(TYPE_int);
    then->sem();
    if (els) els->sem();
    if (then->returns() && els && els->returns()) returning = true;
}

void While::sem(){
    cond->sem();
    cond->type_check(TYPE_int);
    body->sem();
}

void Return::sem() {
    if (expr) {
        expr->sem();
        expr->type_check(st.getReturnType());
    }
    else {
        if (st.getReturnType() != TYPE_void) {
            yyerror("Return type mismatch on return statement");
        }
    }
}

void Func_def::sem(){
    std::vector<RType> *arg_types = new std::vector<RType>();
    std::vector<bool> *arg_ref = new std::vector<bool>();
    //insert the function into the symbol table
    // one argument is the a pointer to myself
    st.insert(name, type, true, arg_types, arg_ref, this);
    // open scope with a pointer to myself as a second argument *Func_Def
    st.openScope(type, this);
    if (args) {
        for (auto arg: *args) {
            arg->sem();
            arg_types->push_back(arg->get_type());
            arg_ref->push_back(arg->is_ref());
        }
    }
    if (decls){
        for (auto decl: *decls) {
            decl->sem();
        }
    }
    body->sem();
    st.closeScope();
} 


void Var_def::sem() {
    if (c == -1) {
        st.insert(name, type);
        return;
    }
    st.insert(name, type, c);
}

void Lvalue_id::sem(){
    
    Func_def *func = nullptr;

    if (index) {
        index->sem();
        index->type_check(TYPE_int);

        type = st.lookup(name, func)->type;


        if (type == TYPE_int_array) {
            type = TYPE_int;
        }
        else if (type == TYPE_char_array) {
            type = TYPE_char;
        }
        else {
            yyerror("Not an array");
        }

    }
    else {
        type = st.lookup(name, func)->type;

    }


    std::vector<Func_def*> upperlevels = st.getFuncsFrom(func);
    // if this is not empty then I need to add the name and type to a closure var to every level returned
    if (upperlevels.size() > 0 && func != nullptr) {
        closurevar *cv = new closurevar(name, type);
        for (Func_def* f: upperlevels) {
            std::vector<closurevar*> *closure = f->get_closures();

            bool invector = false;
            for (closurevar *c: *closure) {
                if (*c == *cv) {
                    invector = true;
                    break;
                }
            }
            if (!invector) {
                closure->push_back(cv);
            }
        }
    }
}

void Func_call::sem()  {
    Func_def * func = nullptr;
    SymbolEntry *entry = st.lookup(name, func);
    type = entry->type;

    
    if (func != nullptr)
        closures = entry->func->get_closures();
    else {
        closures = new std::vector<closurevar*>();
    }
    if (!entry->function) {
        yyerror("Not a function");
    }
    if (args) {
        for (auto arg: *args) {
            arg->sem();
        }
        std::vector<RType> *arg_types = new std::vector<RType>();
        for (auto arg: *args) {
            arg_types->push_back(arg->get_type());
        }
        std::vector<RType> *func_args = entry->args;
        std::vector<bool> *func_ref = entry->args_ref;
        if (arg_types->size() != func_args->size()) {
            std::string error = "Argument count mismatch on function " + name + " expected " + std::to_string(func_args->size()) + " got " + std::to_string(arg_types->size());
            yyerror(error.c_str());
        }
        for (long unsigned int i = 0; i < arg_types->size(); i++) {
            if ((*arg_types)[i] != (*func_args)[i]) {
                std::string s = "Argument type mismatch on function "+ name + " on argument " + std::to_string(i);
                yyerror(s.c_str());
            }
            if ((*func_ref)[i] && !((*args)[i]->is_lvalue_id() || (*args)[i]->is_string_literal())) {
                std::string s = "Argument reference mismatch on function "+ name + " on argument " + std::to_string(i);
                yyerror(s.c_str()); 

            }
        }
        delete arg_types;
    }
}

