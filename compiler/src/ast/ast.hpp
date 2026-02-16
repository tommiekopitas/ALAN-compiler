#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <string>

#include "symbol.hpp"
#include "llvmsymbol.hpp"


#include <llvm/Pass.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

using namespace llvm;

void yyerror(const char *msg);

extern llvmSymbolTable new_st;
extern bool debug;
extern std::string program_name;
extern std::string tabcount;


class AST {
public:
    virtual ~AST() {}
    virtual void printOn(std::ostream &out) const = 0;
    virtual void sem() {}

    virtual Value* igen() const {return nullptr;}

    void declareLibraryFunctions();
    void llvm_igen(bool optimize=false);
protected:
    static LLVMContext TheContext;
    static IRBuilder<> Builder;
    static std::unique_ptr<Module> TheModule;
    static std::unique_ptr<legacy::FunctionPassManager> TheFPM;


    static Type *i8;
    static Type *i32;
    static Type *i64;

    static ConstantInt* c8(char c);
    static ConstantInt* c32(int n);
    static ConstantInt* c1(bool b);
};


inline std::ostream& operator<< (std::ostream &out, const AST &t){
    t.printOn(out);
    return out;
}

inline std::ostream& operator<< (std::ostream &out, const RType &t){
    switch (t) {
        case TYPE_int: out << "int"; break;
        case TYPE_char: out << "char"; break;
        case TYPE_void: out << "void"; break;
        case TYPE_int_array: out << "int array"; break;
        case TYPE_char_array: out << "char array"; break;

    }
    return out;
}


class Expr: public AST {
public:
    void type_check(RType t);
    RType get_type();
    virtual bool is_lvalue_id() const;
    virtual Value* ref_gen() const;
    virtual bool is_string_literal() const;
protected:
    RType type;
};


class ExprList: public AST {
public:
    ExprList();
    ~ExprList();
    std::vector<Expr*>* get_expr_list();
    void append_expr(Expr* e);
    virtual void printOn(std::ostream &out) const override; 
private:
    std::vector<Expr*> *expr_list;
};

class Stmt: public AST {
public:
    virtual bool returns() const;
protected:
    bool returning;
};

class Cond: public AST {
public:
    void type_check(RType t);
protected:
    RType type;
};

class LocalDef: public AST {
public:
    virtual std::string get_name() const;
    bool is_function_def() const;

protected:
    bool is_function;
};


class DefList: public AST {
public:
    DefList();
    ~DefList();
    std::vector<LocalDef*>* get_def_list();
    void append_def(LocalDef* decl) { def_list->push_back(decl);}
    virtual void printOn(std::ostream &out) const override;
private:
    std::vector<LocalDef*> *def_list;
};


class Fpar: public AST {
public:
    Fpar(std::string *n, bool ref, RType t): name(*n), ref(ref), type(t) {}
    void sem() override;
    virtual void printOn(std::ostream &out) const override;
    RType get_type();
    bool is_ref();
    std::string get_name();
private:
    std::string name;
    bool ref;
    RType type;
};

class Fparlist: public AST {
public:
    Fparlist();
    ~Fparlist();
    std::vector<Fpar*>* get_fpar_list();
    void append_fpar(Fpar* fpar);
    
    virtual void printOn(std::ostream &out) const override;
private:
    std::vector<Fpar*> *fpar_list;
};

class BiOp: public Expr {
public:
    BiOp(Expr* l, char o, Expr* r): left(l), op(o), right(r) {}
    ~BiOp() { delete left; delete right; }
    Value* igen() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    Expr* left;
    char op;
    Expr* right;
};

class UnOp: public Expr {
public:
    UnOp(char o, Expr* e): op(o), expr(e) {}
    ~UnOp() { delete expr; }
    Value* igen() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    char op;
    Expr* expr;
};

class Const: public Expr {
public:
    Const(int n): num(n) {}
    virtual void printOn(std::ostream &out) const override;
    void sem() override;
    int get_num();
    Value* igen() const override;
private:
    int num;
};


class Character: public Expr {
public:
    Character(char c): ch(c) {}
    virtual void printOn(std::ostream &out) const override;
    void sem() override;
    Value* igen() const override;
private:
    char ch;
};

class Lvalue: public Expr {
public:
    virtual std::string get_name() = 0;
};

class Lvalue_id: public Lvalue {
public:
    Lvalue_id(std::string *n, Expr* e): name(*n), index(e) {}
    Lvalue_id(std::string *n): name(*n), index(nullptr) {}
    ~Lvalue_id() { if (index) delete index;}
    std::string get_name();
    Value *igen() const override;
    Value* ref_gen() const override;
    void set_type(RType t);
    virtual bool is_lvalue_id() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    std::string name;
    Expr* index;
};

class Lvalue_string: public Lvalue { 
public:
    Lvalue_string(std::string *n);
    virtual std::string get_name();
    virtual void printOn(std::ostream &out) const override ;
    Value* igen() const override;
    Value* ref_gen() const override ;
    virtual bool is_string_literal() const override;
    void sem() override ;
private:
    std::string value;
};    

class Func_call: public Expr, public Stmt {
public:
    Func_call(std::string *n);
    Func_call(std::string *n, ExprList *a);
    ~Func_call();
    Value* igen() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    std::string name;
    std::vector<Expr*> *args;
    std::vector<closurevar*> *closures = nullptr;
};

class C_UnOp: public Cond {
public:
    C_UnOp(char o, Cond* e): op(o), cond(e) {}
    ~C_UnOp() { delete cond; }
    Value* igen() const override ;
    void sem() override ;
    virtual void printOn(std::ostream &out) const override;
private:
    char op;
    Cond* cond;
};

class C_BiOp: public Cond {
public:
    C_BiOp(Expr* l, char o, Expr* r): left(l), op(o), right(r), leftc(nullptr), rightc(nullptr) {}
    C_BiOp(Cond* l, char o, Cond* r): left(nullptr), op(o), right(nullptr), leftc(l), rightc(r) {}
    ~C_BiOp();
    Value *igen() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    Expr* left;
    char op;
    Expr* right;
    Cond* leftc;
    Cond* rightc;
};

class ConstBool: public Cond {
public:
    ConstBool(bool b): value(b) {}
    virtual void printOn(std::ostream &out) const override;
    void sem() override;
    Value* igen() const override;
private:
    bool value;
};

class NoOp: public Stmt {
public:
    NoOp();
    virtual void printOn(std::ostream &out) const override;
    Value* igen() const override;
};

class Let: public Stmt {
public:
    Let(Lvalue* v, Expr* e): var(v), expr(e) {
        returning = false;
    }
    ~Let();
    Value* igen() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    Lvalue* var;
    Expr* expr;
};

class CompoundStmt: public Stmt {
public: 
    CompoundStmt(): stmt_list() {
        returning = false;
    }
    ~CompoundStmt();
    Value* igen() const override;
    void append_stmt(Stmt* stmt);
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    std::vector<Stmt*> stmt_list;
};

class If: public Stmt {
public:
    If(Cond* c, Stmt* t): cond(c), then(t), els(nullptr) {
        returning = false;
    }
    If(Cond* c, Stmt* t, Stmt* e): cond(c), then(t), els(e) {
        returning = false;
    }
    ~If();
    Value *igen( ) const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    Cond* cond;
    Stmt* then;
    Stmt* els;
};

class While: public Stmt {
public:
    While(Cond* c, Stmt* b): cond(c), body(b) {}
    ~While();
    Value* igen() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    Cond* cond;
    Stmt* body;
};

class Return: public Stmt {
public:
    Return(): expr(nullptr){
        returning = true;
    }
    Return(Expr* e): expr(e) {
        returning = true;
    }
    ~Return();
    Value* igen() const override;
    virtual void sem() override;
    virtual bool returns() const override;
    virtual void printOn(std::ostream &out) const override;
private:
    Expr* expr;
};

class Func_def: public LocalDef {
public:
    Func_def(std::string *n, RType t, DefList* d, CompoundStmt* b);
    Func_def(std::string *n, Fparlist* a, RType t, DefList* d, CompoundStmt* b);
    std::string get_name() const override;
    Function *igen() const override;
    ~Func_def();
    virtual void sem() override;
    std::vector<closurevar*>* get_closures();
    virtual void printOn(std::ostream &out) const override;
private:
    std::string name;
    std::vector<Fpar*>* args;
    std::vector<closurevar*> *closures;
    RType type;
    std::vector<LocalDef*>* decls;
    CompoundStmt* body;
};

class Var_def: public LocalDef {
public:
    Var_def(std::string *n, RType t);
    Var_def(std::string *n, RType t, int e);
    Value *igen() const override;
    virtual void sem() override;
    virtual void printOn(std::ostream &out) const override;
private:
    std::string name;
    RType type;
    int c;
};

#endif