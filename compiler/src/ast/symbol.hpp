#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <string>
#include <vector>
#include <map>

enum RType { TYPE_int, TYPE_int_array, TYPE_char, TYPE_char_array, TYPE_void};

void yyerror(const char *msg);

extern bool debug;
class Func_def;

struct SymbolEntry {
    RType type;
    int size;
    bool function;
    Func_def *func = nullptr;
    bool isByReference;
    std::vector<RType> *args;
    std::vector<bool> *args_ref;
    SymbolEntry(): isByReference(false) {}
    SymbolEntry(RType t): type(t), function(false), isByReference(false){
        args = nullptr;
        args_ref = nullptr;
        size = -1;
    }
    SymbolEntry(RType t, bool f, std::vector<RType> *a, std::vector<bool> *r): type(t), function(f), isByReference(false) {
        if (f) {
            if (a!=nullptr) {
                args = a;
                args_ref = r;
            } else {
                args = new std::vector<RType>();
                args_ref = new std::vector<bool>();
            }
        }
        size = -1;
    }
    SymbolEntry(RType t, bool f, std::vector<RType> *a, std::vector<bool> *r, Func_def *pointer_to_func): type(t), function(f), isByReference(false) {
        if (f) {
            if (a!=nullptr) {
                args = a;
                args_ref = r;
            } else {
                args = new std::vector<RType>();
                args_ref = new std::vector<bool>();
            }
        }
        size = -1;
        func = pointer_to_func;
    }
    SymbolEntry(RType t, int s): type(t), size(s), function(false), isByReference(false) {
        args = nullptr;
        args_ref = nullptr;
    }
};

class Scope {
public:
    Scope(Func_def *f) {
        size = 0;
        returnType = TYPE_void;
        func = f;
    }
    Scope(RType t, Func_def *f) {
        size = 0;
        returnType = t;
        func = f;
    }

    RType getreturnType() const {return returnType;}

    SymbolEntry * lookup(std::string name, Func_def *& f) {
        if (locals.find(name) == locals.end()) return nullptr;
        f = func;
        return &locals[name];

    }

    Func_def * getFunc() const {return func;}

    void insert(std::string name, RType t) {
        if (locals.find(name) != locals.end()) yyerror("Dublicate entry");
        locals[name] = SymbolEntry(t);
        ++size;
    }
    void insert(std::string name, RType t, bool f, std::vector<RType> *args, std::vector<bool> *ref) {
        if (locals.find(name) != locals.end()) yyerror("Dublicate entry");
        locals[name] = SymbolEntry(t, f, args, ref);
        ++size;
    }

    void insert(std::string name, RType t, bool f, std::vector<RType> *args, std::vector<bool> *ref, Func_def *pointer_to_func) {
        if (locals.find(name) != locals.end()) yyerror("Dublicate entry");
        locals[name] = SymbolEntry(t, f, args, ref, pointer_to_func);
        ++size;
    }
    void insert(std::string name, RType t, int s) {
        if (locals.find(name) != locals.end()) yyerror("Dublicate entry");
        locals[name] = SymbolEntry(t, s);
        size += s;
    }



    int getSize() const {return size;}
private:
    std::map<std::string, SymbolEntry> locals;
    int size;
    RType returnType;
    Func_def *func;
};


class SymbolTable {
public:
    SymbolTable() {
        openScope(TYPE_void, nullptr);

        std::vector<RType> *args1 = new std::vector<RType>();
        args1->push_back(TYPE_int);
        std::vector<bool> *ref1 = new std::vector<bool>();
        ref1->push_back(false);
        insert("writeInteger", TYPE_void, true, args1, ref1);

        std::vector<RType> *args2 = new std::vector<RType>();
        args2->push_back(TYPE_char);
        std::vector<bool> *ref2 = new std::vector<bool>();
        ref2->push_back(false);
        insert("writeByte", TYPE_void, true, args2, ref2);

        std::vector<RType> *args3 = new std::vector<RType>();
        args3->push_back(TYPE_char);
        std::vector<bool> *ref3 = new std::vector<bool>();
        ref3->push_back(false);
        insert("writeChar", TYPE_void, true, args3, ref3);

        std::vector<RType> *args4 = new std::vector<RType>();
        args4->push_back(TYPE_char_array);
        std::vector<bool> *ref4 = new std::vector<bool>();
        ref4->push_back(true);
        insert("writeString", TYPE_void, true, args4, ref4);

        insert("readInteger", TYPE_int, true, nullptr, nullptr);
        insert("readByte", TYPE_char, true, nullptr, nullptr);
        insert("readChar", TYPE_char, true, nullptr, nullptr);

        std::vector<RType> *args5 = new std::vector<RType>();
        args5->push_back(TYPE_int);
        args5->push_back(TYPE_char_array);
        std::vector<bool> *ref5 = new std::vector<bool>();
        ref5->push_back(false);
        ref5->push_back(true);
        insert("readString", TYPE_void, true, args5, ref5);

        std::vector<RType> *args6 = new std::vector<RType>();
        args6->push_back(TYPE_char);
        std::vector<bool> *ref6 = new std::vector<bool>();
        ref6->push_back(false);
        insert("extend", TYPE_int, true, args6, ref6);

        std::vector<RType> *args7 = new std::vector<RType>();
        args7->push_back(TYPE_int);
        std::vector<bool> *ref7 = new std::vector<bool>();
        ref7->push_back(false);
        insert("shrink", TYPE_char, true, args7, ref7);

        std::vector<RType> *args8 = new std::vector<RType>();
        args8->push_back(TYPE_char_array);
        std::vector<bool> *ref8 = new std::vector<bool>();
        ref8->push_back(true);
        insert("strlen", TYPE_int, true, args8, ref8);

        std::vector<RType> *args9 = new std::vector<RType>();
        args9->push_back(TYPE_char_array);
        args9->push_back(TYPE_char_array);
        std::vector<bool> *ref9 = new std::vector<bool>();
        ref9->push_back(true);
        ref9->push_back(true);
        insert("strcmp", TYPE_int, true, args9, ref9);

        std::vector<RType> *args10 = new std::vector<RType>();
        args10->push_back(TYPE_char_array);
        args10->push_back(TYPE_char_array);
        std::vector<bool> *ref10 = new std::vector<bool>();
        ref10->push_back(true);
        ref10->push_back(true);
        insert("strcpy", TYPE_void, true, args10, ref10);

        std::vector<RType> *args11 = new std::vector<RType>();
        args11->push_back(TYPE_char_array);
        args11->push_back(TYPE_char_array);
        std::vector<bool> *ref11 = new std::vector<bool>();
        ref11->push_back(true);
        ref11->push_back(true);
        insert("strcat", TYPE_void, true, args11, ref11);
    }
    
    void openScope(Func_def *f) {
        scopes.push_back(Scope(f));
    }
    void openScope(RType t, Func_def *f) {
        scopes.push_back(Scope(t, f));
    }

    void closeScope() {
        scopes.pop_back();
    }

    RType getReturnType() const {
        return scopes.back().getreturnType();
    }

    SymbolEntry * lookup(std::string name, Func_def *&f) {
        for ( auto i = scopes.rbegin(); i != scopes.rend(); i++) {
            SymbolEntry * entry = i->lookup(name, f);
            if (entry != nullptr) {
                return entry;
            }
        }
        std::string msg = "Symbol not found " + name;
        yyerror(msg.c_str());
        return nullptr;
    }

    void insert(std::string name, RType t) {
        scopes.back().insert(name, t);
    }
    void insert(std::string name, RType t, bool f, std::vector<RType> *args, std::vector<bool> *ref, Func_def *pointer_to_func) {
        scopes.back().insert(name, t, f, args, ref, pointer_to_func);
    }
    void insert(std::string name, RType t, bool f, std::vector<RType> *args, std::vector<bool> *ref) {
        scopes.back().insert(name, t, f, args, ref);
    }
    void insert(std::string name, RType t, int s) {
        scopes.back().insert(name, t, s);
    }

    std::vector<Func_def*> getFuncsFrom(Func_def* f){
        std::vector<Func_def*> funcs;
        for (auto i = scopes.rbegin(); i != scopes.rend(); i++) {
            if (i->getFunc() == f) {
                break;
            }
            if (i->getFunc() != nullptr) {
                funcs.push_back(i->getFunc());
            }
        }
        return funcs;
    }

    int getSize() const {return scopes.back().getSize();}
private:
    std::vector<Scope> scopes;
};





extern SymbolTable st;




#endif