#include "../ast/ast.hpp"

void ExprList::printOn(std::ostream &out) const{
    out << "If you're seeing this, the temporary object Exprlist remained after its job was completed" << std::endl;
} 

void DefList::printOn(std::ostream &out) const {
    out << tabcount << "DefList(" << std::endl;
    tabcount += ' ';
    for (auto decl: *def_list) {
        out << tabcount << *decl << std::endl;
    }
    tabcount.pop_back();
    out << tabcount << ")" << std::endl;
    out << "If you're seeing this, the temporary object Deflist remained after its job was completed" << std::endl;
}


void Fpar::printOn(std::ostream &out) const  {
    if (ref) {
        out << "Fpar(" << name << ", " << type << ", reference)";
        return;
    }
    out << "Fpar(" << name << ", " << type << ")";
}

void Fparlist::printOn(std::ostream &out) const {
    out << tabcount << "Fparlist(" << std::endl;
    tabcount += ' ';
    for (auto fpar: *fpar_list) {
        out << tabcount << *fpar << std::endl;
    }
    tabcount.pop_back();
    out << tabcount << ")" << std::endl;
    out << "If you're seeing this, the temporary object Fparlist remained after its job was completed" << std::endl;
}

void BiOp::printOn(std::ostream &out) const {
    out << op << "(" << std::endl;
    tabcount += ' ';
    out << tabcount << *left << std::endl;
    out << tabcount << *right << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}

void UnOp::printOn(std::ostream &out) const  {
    out << op << "(" << std:: endl;
    tabcount += ' ';
    out << tabcount << *expr << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}

void Const::printOn(std::ostream &out) const  {
    out << "Const(" << num << ")";
}

void Character::printOn(std::ostream &out) const {
    out << "Character(" << ch << ")";
}


void Lvalue_id::printOn(std::ostream &out) const{
    if (index) {
        out << "Lvalue_id(" << std::endl;
        tabcount += ' ';
        out << tabcount << name << std::endl;
        out << tabcount << *index << std::endl;
        tabcount.pop_back();
        out << tabcount << ")";
        return;
    }
    out << "Lvalue_id(" << name << ")";
}

void Lvalue_string::printOn(std::ostream &out) const  {
    out << "Lvalue_string(" << value << ")";
}

void Func_call::printOn(std::ostream &out) const {
    if (!args) {
        out << "Func_call(" << name << ")";
        return;
    }
    out << "Func_call(" << std::endl;
    tabcount += ' ';
    out<< tabcount << name << std::endl;
    if (!(args->empty())) {
        out<< tabcount << "ExprList(" << std::endl;
        tabcount += ' ';
        for (auto arg: *args) {
            out << tabcount << *arg << std::endl;
        }
        tabcount.pop_back();
        out << tabcount << ")" << std::endl;
    }
    tabcount.pop_back();
    out << tabcount << ")";
}

void C_UnOp::printOn(std::ostream &out) const {
    out << op << "(" << std::endl;
    tabcount += ' ';
    out << tabcount << *cond << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}


void C_BiOp::printOn(std::ostream &out) const  {
    out << op << "(" << std::endl;
    tabcount += ' ';
    if (leftc) out << tabcount << *leftc << std::endl;
    if (rightc) out << tabcount << *rightc << std::endl;
    if (left) out << tabcount << *left << std::endl;
    if (right) out << tabcount << *right << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}

void ConstBool::printOn(std::ostream &out) const {
    out << "ConstBool(" << value << ")";
}

void NoOp::printOn(std::ostream &out) const {
    out << "NoOp" << std::endl;
}

void Let::printOn(std::ostream &out) const  {
    out << "Let(" << std::endl;
    tabcount += ' ';
    out << tabcount << *var << std::endl;
    out << tabcount << *expr << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}

void CompoundStmt::printOn(std::ostream &out) const {
    out <<"CompoundStmt(" << std:: endl;
    tabcount += ' ';
    for (auto stmt: stmt_list) {
        out << tabcount << *stmt << std::endl;
    }
    tabcount.pop_back();
    out << tabcount << ")";
}

void If::printOn(std::ostream &out) const {
    out << "If(" << std::endl;
    tabcount += ' ';
    out << tabcount << *cond << std::endl;
    out << tabcount << *then << std::endl;
    if (els) out << tabcount << *els << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}

void While::printOn(std::ostream &out) const  {
    out << "While(" << std::endl;
    tabcount += ' ';
    out << tabcount << *cond << std::endl;
    out << tabcount << *body << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}

void Return::printOn(std::ostream &out) const {
    if (!expr) {
        out <<"Return()" << std::endl;
        return;
    }
    out << "Return(" << std:: endl;
    tabcount += ' ';
    out << tabcount << *expr << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";
}

void Func_def::printOn(std::ostream &out) const {
    out << "Func_def(" << std:: endl;
    tabcount += ' ';
    out<< tabcount << name << std::endl;
    if (args && !(args->empty())) {
        out << tabcount << "Fparlist(" << std::endl;
        tabcount += ' ';
        for (auto fpar: *args) {
            out << tabcount << *fpar << std::endl;
        }
        tabcount.pop_back();
        out << tabcount << ")" << std::endl;
    }
    out << tabcount << type << std::endl;
    if (!(decls->empty())) {
        out << tabcount << "DefList(" << std::endl;
        tabcount += ' ';
        for (auto decl: *decls) {
            out << tabcount << *decl << std::endl;
        }
        tabcount.pop_back();
        out << tabcount << ")" << std::endl;
    }
    if (body) out << tabcount << *body << std::endl;
    tabcount.pop_back();
    out << tabcount << ")";

}

void Var_def::printOn(std::ostream &out) const {
    if (c == -1) {
        out << "Var_def(" << name << ", " << type << ")" ;
        return;
    }
    out << "Var_def(" << name << ", " << type << ", " << c << ")";
}