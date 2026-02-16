#ifndef __LLVMSYMBOL_HPP__
#define __LLVMSYMBOL_HPP__

#include <map>
#include <string>
#include <vector>

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

struct llvmScopeEntry {
    llvmScopeEntry(AllocaInst *a, bool r): isRef(r) {
        alloca = a;
    }
    llvmScopeEntry(): isRef(false) {
        alloca = nullptr;
    }
    llvmScopeEntry(AllocaInst *a){
        alloca = a;
        isRef = false;
    }
    AllocaInst *alloca;
    bool isRef;
};


class llvmScope {
public:
    llvmScope() {
        size = 0;
    }
    
    AllocaInst *lookup(std::string name) {
        if (NamedValues.find(name) == NamedValues.end()) return nullptr;
        return NamedValues[name].alloca;
    }

    void insert(std::string name, AllocaInst *alloca) {
        if (NamedValues.find(name) != NamedValues.end()) {
            yyerror("Duplicate entry");
        }
        llvmScopeEntry entry(alloca, false);
        NamedValues[name] = entry;
        ++size;
    }

    void insert(std::string name, AllocaInst *alloca, bool IsRef) {
        if (NamedValues.find(name) != NamedValues.end()) {
            yyerror("Duplicate entry");
        }
        llvmScopeEntry entry(alloca, IsRef);
        NamedValues[name] = entry;
        ++size;
    }

    bool isReference(std::string name){
        if (NamedValues.find(name) == NamedValues.end()) return false;
        return NamedValues[name].isRef;
    }

    int get_size() {
        return size;
    }

private:
    std::map<std::string, llvmScopeEntry> NamedValues;
    int size;
};

class llvmSymbolTable {
public:
    llvmSymbolTable() {
        openScope();

    }
    void openScope() {
        scopes.push_back(llvmScope());
    }
    void closeScope() {
        scopes.pop_back();
    }
    AllocaInst *lookup(std::string name) {
        for (auto i = scopes.rbegin(); i != scopes.rend(); i++) {
            AllocaInst *alloca = i->lookup(name);
            if (alloca != nullptr) {
                return alloca;
            }
        }
        std::string msg = "Symbol not found " + name;
        yyerror(msg.c_str());
        return nullptr;
    }

    bool isReference(std::string name){
        for (auto i = scopes.rbegin(); i != scopes.rend(); i++) {
            AllocaInst *alloca = i->lookup(name);
            if (alloca != nullptr) {
                return i->isReference(name);
            }
        }
        std::string msg = "Symbol not found " + name;
        yyerror(msg.c_str());
        return false;
    }

    void insert(std::string name, AllocaInst *alloca, bool IsRef) {
        scopes.back().insert(name, alloca, IsRef);
    }
    void insert(std::string name, AllocaInst *alloca) {
        scopes.back().insert(name, alloca);
    }
private:
    std::vector<llvmScope> scopes;
};



struct llvmFunctionEntry {
    std::vector<bool> *args_ref;
    std::string llvm_given_name;
    llvmFunctionEntry(std::vector<bool> *ref, std::string name){
        args_ref = ref;
        llvm_given_name = name;
    }
};

class llvmFunctionScope {
public:
    llvmFunctionScope() {
        size = 0;
    }
    llvmFunctionEntry *lookup(std::string name) {
        if (functions.find(name) == functions.end()) return nullptr;
        return functions[name];
    }
    void insert(std::string name, std::vector<bool> *ref, std::string llvm_name) {
        if (functions.find(name) != functions.end()) {
            yyerror("Duplicate entry");
        }
        llvmFunctionEntry *entry = new llvmFunctionEntry(ref, llvm_name);
        functions[name] = entry;
        ++size;
    }
    int get_size() {
        return size;
    }
private:
    std::map<std::string, llvmFunctionEntry*> functions;
    int size;
};

class llvmFunctionTable {
public:
    llvmFunctionTable() {
        openScope();

        // library functions

        std::vector<bool> *args1 = new std::vector<bool>();
        args1->push_back(false);
        insert("writeInteger", args1, "writeInteger");

        std::vector<bool> *args2 = new std::vector<bool>();
        args2->push_back(false);
        insert("writeByte", args2, "writeByte");

        std::vector<bool> *args3 = new std::vector<bool>();
        args3->push_back(false);
        insert("writeChar", args3, "writeChar");

        std::vector<bool> *args4 = new std::vector<bool>();
        args4->push_back(true);
        insert("writeString", args4, "writeString");

        std::vector<bool> *args5 = new std::vector<bool>();
        insert("readInteger", args5, "readInteger");

        std::vector<bool> *args6 = new std::vector<bool>();
        insert("readByte", args6, "readByte");

        std::vector<bool> *args7 = new std::vector<bool>();
        insert("readChar", args7, "readChar");

        std::vector<bool> *args8 = new std::vector<bool>();
        args8->push_back(false);
        args8->push_back(true);
        insert("readString", args8, "readString");

        std::vector<bool> *args9 = new std::vector<bool>();
        args9->push_back(false);
        insert("extend", args9, "extend");

        std::vector<bool> *args10 = new std::vector<bool>();
        args10->push_back(false);
        insert("shrink", args10, "shrink");

        std::vector<bool> *args11 = new std::vector<bool>();
        args11->push_back(true);
        insert("strlen", args11, "strlen");

        std::vector<bool> *args12 = new std::vector<bool>();
        args12->push_back(true);
        args12->push_back(true);
        insert("strcmp", args12, "strcmp");

        std::vector<bool> *args13 = new std::vector<bool>();
        args13->push_back(true);
        args13->push_back(true);
        insert("strcpy", args13, "strcpy");

        std::vector<bool> *args14 = new std::vector<bool>();
        args14->push_back(true);
        args14->push_back(true);
        insert("strcat", args14, "strcat");
    }
    void openScope() {
        scopes.push_back(llvmFunctionScope());
    }
    void closeScope() {
        scopes.pop_back();
    }
    llvmFunctionEntry *lookup(std::string name) {
        // we should begin from the last scope
        for (auto i = scopes.rbegin(); i != scopes.rend(); i++) {
            llvmFunctionEntry *entry = i->lookup(name);
            if (entry != nullptr) {
                return entry;
            }
        }
        return nullptr;
    }
    void insert(std::string name, std::vector<bool> *ref, std::string llvm_name) {
        scopes.back().insert(name, ref, llvm_name);
    }
private:
    std::vector<llvmFunctionScope> scopes;
};

extern llvmFunctionTable new_ft;


struct closurevar {
    closurevar(std::string n, RType t): name(n), type(t) {}
    std::string name;
    RType type;

    std::string get_name() {
        return name;
    }

    RType get_type() {
        return type;
    }

    // Check if 2 closurevars are the same
    bool operator==(const closurevar &other) const {
        return name == other.name && type == other.type;
    }
};

#endif