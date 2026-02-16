#include "../ast/ast.hpp"


void AST::declareLibraryFunctions(){
    // Declare void writeInteger(int x);
    FunctionType *writeIntegerType = FunctionType::get(
        Type::getVoidTy(TheContext),
        {Type::getInt32Ty(TheContext)},
        false
    );
    Function::Create(writeIntegerType, Function::ExternalLinkage, "writeInteger", TheModule.get());

    // Declare void writeByte(char x);
    FunctionType *writeByteType = FunctionType::get(
        Type::getVoidTy(TheContext),
        {Type::getInt8Ty(TheContext)},
        false
    );
    Function::Create(writeByteType, Function::ExternalLinkage, "writeByte", TheModule.get());

    // Declare void writeChar(char x);
    FunctionType *writeCharType = FunctionType::get(
        Type::getVoidTy(TheContext),
        {Type::getInt8Ty(TheContext)},
        false
    );
    Function::Create(writeCharType, Function::ExternalLinkage, "writeChar", TheModule.get());

    // Declare void writeString(const char* x);
    FunctionType *writeStringType = FunctionType::get(
        Type::getVoidTy(TheContext),
        {Type::getInt8PtrTy(TheContext)},
        false
    );
    Function::Create(writeStringType, Function::ExternalLinkage, "writeString", TheModule.get());

    // Declare int readInteger();
    FunctionType *readIntegerType = FunctionType::get(
        Type::getInt32Ty(TheContext),
        false
    );
    Function::Create(readIntegerType, Function::ExternalLinkage, "readInteger", TheModule.get());

    // Declare char readByte();
    FunctionType *readByteType = FunctionType::get(
        Type::getInt8Ty(TheContext),
        false
    );
    Function::Create(readByteType, Function::ExternalLinkage, "readByte", TheModule.get());

    // Declare char readChar();
    FunctionType *readCharType = FunctionType::get(
        Type::getInt8Ty(TheContext),
        false
    );
    Function::Create(readCharType, Function::ExternalLinkage, "readChar", TheModule.get());

    // Declare void readString(int n, char* x);
    FunctionType *readStringType = FunctionType::get(
        Type::getVoidTy(TheContext),
        {Type::getInt32Ty(TheContext), Type::getInt8PtrTy(TheContext)},
        false
    );
    Function::Create(readStringType, Function::ExternalLinkage, "readString", TheModule.get());

    // Declare int extend(char c);
    FunctionType *extendType = FunctionType::get(
        Type::getInt32Ty(TheContext),
        {Type::getInt8Ty(TheContext)},
        false
    );
    Function::Create(extendType, Function::ExternalLinkage, "extend", TheModule.get());

    // Declare char shrink(int i);
    FunctionType *shrinkType = FunctionType::get(
        Type::getInt8Ty(TheContext),
        {Type::getInt32Ty(TheContext)},
        false
    );
    Function::Create(shrinkType, Function::ExternalLinkage, "shrink", TheModule.get());

    // Declare int strlen(const char* x);
    FunctionType *strlenType = FunctionType::get(
        Type::getInt32Ty(TheContext),
        {Type::getInt8PtrTy(TheContext)},
        false
    );
    Function::Create(strlenType, Function::ExternalLinkage, "strlen", TheModule.get());

    // strcmp
    FunctionType *strcmpType = FunctionType::get(
        Type::getInt32Ty(TheContext),
        {Type::getInt8PtrTy(TheContext), Type::getInt8PtrTy(TheContext)},
        false
    );
    Function::Create(strcmpType, Function::ExternalLinkage, "strcmp", TheModule.get());

    // strcpy
    FunctionType *strcpyType = FunctionType::get(
        Type::getVoidTy(TheContext),
        {Type::getInt8PtrTy(TheContext), Type::getInt8PtrTy(TheContext)},
        false
    );
    Function::Create(strcpyType, Function::ExternalLinkage, "strcpy", TheModule.get());

    //strcat
    FunctionType *strcatType = FunctionType::get(
        Type::getVoidTy(TheContext),
        {Type::getInt8PtrTy(TheContext), Type::getInt8PtrTy(TheContext)},
        false
    );
    Function::Create(strcatType, Function::ExternalLinkage, "strcat", TheModule.get());

}

void AST::llvm_igen(bool optimize){
    // Initialize
    TheModule = std::make_unique<Module>("alan program", TheContext);
    TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());
    if (optimize) {
        TheFPM->add(createPromoteMemoryToRegisterPass());
        TheFPM->add(createInstructionCombiningPass());
        TheFPM->add(createReassociatePass());
        TheFPM->add(createGVNPass());
        TheFPM->add(createCFGSimplificationPass());
    }
    TheFPM->doInitialization();

    // Initialize types
    i8 = IntegerType::get(TheContext, 8);
    i32 = IntegerType::get(TheContext, 32);
    i64 = IntegerType::get(TheContext, 64);


    // Declare library functions
    declareLibraryFunctions();
    // Emit the program code
    igen();
    // Define and start the main function
    FunctionType *FT = FunctionType::get(i32, false);
    Function *main = Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", main);
    Builder.SetInsertPoint(BB);

    // Call the program
    Function *outerFunction = TheModule->getFunction(program_name);
    if (!outerFunction) {
        std::cerr << "Error: Outermost function not found." << std::endl;
        exit(1);
    }
    Builder.CreateCall(outerFunction);

    Builder.CreateRet(c32(0));

    // Verify the IR
    bool bad = verifyModule(*TheModule, &errs());
    if (bad) {
        std::cerr << "The IR is bad" << std::endl;
        TheModule->print(errs(), nullptr);
        std::exit(1);
    } 
    // Optimize
    for (Function &F : *TheModule) {
        TheFPM->run(F);
    }
    // Print the IR
    TheModule->print(outs(), nullptr);

}

ConstantInt* AST::c8(char c) {
    return ConstantInt::get(TheContext, APInt(8, c, true));
}
ConstantInt* AST::c32(int n) {
    return ConstantInt::get(TheContext, APInt(32, n, true));
}
ConstantInt* AST::c1(bool b) {
    return ConstantInt::get(TheContext, APInt(1, b, true));
}

Value* Expr::ref_gen() const {
    return nullptr;
}

Value* BiOp::igen() const {
    if (debug) std::cout<< "Generating BiOp " << op <<std::endl;
    Value *l = left->igen();
    Value *r = right->igen();
    switch(op) {
        case '+': return Builder.CreateAdd(l, r, "addtmp");
        case '-': return Builder.CreateSub(l, r, "subtmp");
        case '*': return Builder.CreateMul(l, r, "multmp");
        case '/': return Builder.CreateSDiv(l, r, "divtmp");
        case '%': return Builder.CreateSRem(l, r, "modtmp");
    }
    return nullptr;
}
  

Value* UnOp::igen() const {
    if (debug) std::cout << "Generating UnOp" << std::endl;
    Value *e = expr->igen();
    switch(op) {
        case '-': return Builder.CreateNeg(e, "negtmp");
        case '+': return e;
    }
    return nullptr;
}

Value* Const::igen() const  {
    return c32(num);
}

Value* Character::igen() const {
    return c8(ch);
}

Value * Lvalue_id::igen() const  {
    if (debug) {
        std::string s = "";
        if (index) {
            s = "[]";
        }
        std::cout << "Generating Lvalue_id for with igen " << name << s << " ";
    
    }

    AllocaInst *alloca = new_st.lookup(name);
    if (alloca == nullptr) {
        yyerror("Variable not found");
    }
    bool isRef = new_st.isReference(name);

    if (isRef && index) {
        if (debug) std::cout << "IsRef and Index" << std::endl;


        Value *basePtr = Builder.CreateLoad(alloca->getAllocatedType(), alloca, "refLoad");
        Value *indexVal = index->igen();
        std::vector<Value*> indices; // For the alloca pointer
        indices.push_back(indexVal); // The index into the array

        // if the type is TYPE_int then the pointer is i32* and the value is i32
        // if the type is TYPE_char then the pointer is i8* and the value is i8
        Type *elemType = nullptr;
        if (type == TYPE_int) {
            elemType = Type::getInt32Ty(TheContext);
        } else if (type == TYPE_char) {
            elemType = Type::getInt8Ty(TheContext);
        }

        Value *basePtrCast = Builder.CreateBitCast(basePtr, elemType->getPointerTo(), "basePtrCast");



        Value *resultPtr = Builder.CreateGEP(elemType, basePtrCast, indices, name + "_array_index");
        LoadInst *loadInst = Builder.CreateLoad(elemType, resultPtr, name + "_array_value");
        loadInst->setAlignment(Align((type == TYPE_int) ? 4 : 1));

        return loadInst;
    }
    if (isRef && !index) {
        if (debug) std::cout << "IsRef and Not Index" << std::endl;
        
        // Load the first pointer (dereference the reference to get the actual pointer)
        Value *loadedPtr = Builder.CreateLoad(alloca->getAllocatedType(), alloca, name + "_ref");

        // Determine the element type (i32 for TYPE_int, i8 for TYPE_char)
        Type *elemType = nullptr;
        if (type == TYPE_int) {
            elemType = Type::getInt32Ty(TheContext);
        } else if (type == TYPE_char) {
            elemType = Type::getInt8Ty(TheContext);
        }

        // Load the actual value using the element type
        LoadInst *result = Builder.CreateLoad(elemType, loadedPtr, name + "_value");
        result->setAlignment(Align((type == TYPE_int) ? 4 : 1)); // Proper alignment
        return result;
    }

    else if (!isRef && index) {
        if (debug) std::cout << "Not IsRef and Index" << std::endl;
        // the alloca is an array type and we return the pointer to the i-th element
        Type *allocatedType = alloca->getAllocatedType();    
        ArrayType *arrType = cast<ArrayType>(allocatedType);
        Type *elemType = arrType->getElementType();

        Value *zero = c32(0);
        Value *i = index->igen();
        Value *indices[] = {zero, i};

        Value *elemPtr = Builder.CreateGEP(allocatedType, alloca, indices, "elemPtr");
        return Builder.CreateLoad(elemType, elemPtr, "elemValue");
    } else {
        if (debug) std::cout << "Not IsRef and Not Index" << std::endl;
        // not a ref and not an index, just load the value
        return Builder.CreateLoad(alloca->getAllocatedType(), alloca, name.c_str());
    }
}

Value* Lvalue_id::ref_gen() const  {
    if (debug) {
        std::string s = "";
        if (index) {
            s = "[]";
        }
        std::cout << "Generating Lvalue_id for with refgen" << name << s << " ";
    
    }

    // Look up the variable's allocation in the symbol table.
    AllocaInst *alloca = new_st.lookup(name);
    if (!alloca) {
        yyerror("Variable not found");
        return nullptr;
    }

    // Check if the variable is already stored by reference.
    bool isRef = new_st.isReference(name);

    if (isRef && index){
        if (debug) std::cout << "IsRef and Index" << std::endl;
        // the stack has the address of the first element and we return the address of the i-th element
        Value *basePtr = Builder.CreateLoad(alloca->getAllocatedType(), alloca, "refLoad");
        Value *indexVal = index->igen();
        std::vector<Value*> indices;
        indices.push_back(indexVal); // The index into the array

        // this is a 64 bit pointer to the element
        Type *elemType = nullptr;
        if (type == TYPE_int) {
            elemType = Type::getInt32Ty(TheContext);
        } else if (type == TYPE_char) {
            elemType = Type::getInt8Ty(TheContext);
        }

        Value *basePtrCast = Builder.CreateBitCast(basePtr, elemType->getPointerTo(), "basePtrCast");


        Value *resultPtr = Builder.CreateGEP(elemType, basePtrCast, indices, name + "_array_index");
        return resultPtr;
    } 
    else if (isRef && !index) {
        if (debug) std::cout << "IsRef and not Index" << std::endl;
        // This is a reference to a value, just load the address from the stack and send it 
        LoadInst * result = Builder.CreateLoad(alloca->getAllocatedType(), alloca, name + "_ref");
        return result;
    }
    else if (!isRef && index) {
        if (debug) std::cout << "not IsRef and Index" << std::endl;
        // this is an array type and we return the address of the i-th element
        Type *allocatedType = alloca->getAllocatedType();

        Value *zero = c32(0);
        Value *i = index->igen();
        Value *indices[] = {zero, i};

        Value *elemPtr = Builder.CreateGEP(allocatedType, alloca, indices, "elemPtr");
        return elemPtr;
    } else {
        
        // this is just a name, but it could be an array
        Type *allocatedType = alloca->getAllocatedType();
        if (allocatedType->isArrayTy()) {
            if (debug) std::cout << "not IsRef and not Index and array" << std::endl;
            // If it is an array, return the pointer to the first element.
            Value *zero = c32(0);
            Value *indices[] = {zero, zero};
            Value *elemPtr = Builder.CreateGEP(allocatedType, alloca, indices, "elemPtr");

            return elemPtr;
        } else {
            if (debug) std::cout << "not IsRef and not Index and not array" << std::endl;
            // If it is not an array, return the pointer to the variable.
            return alloca;
        }
    }

}

Value* Lvalue_string::igen() const {
    if (debug) std::cout << "Generating Lvalue_string "<< value << std::endl;
    return Builder.CreateGlobalStringPtr(value, "str");
}

Value* Lvalue_string::ref_gen() const {
    if (debug) std::cout << "Generating Lvalue_string "<< value << std::endl;
    return Builder.CreateGlobalStringPtr(value, "str");
}


Value* Func_call::igen() const {
    if (debug) std::cout << "Generating Func_call" << std::endl;

    llvmFunctionEntry * entry = new_ft.lookup(name);
    std::vector<bool> *args_ref = entry->args_ref;
    std::string llvm_name = entry->llvm_given_name;
    if (debug) std::cout << "Function found and accorging to the symbol table needs :"<< args->size()<<" arguments" << std::endl;

    Function *func = TheModule->getFunction(llvm_name);
    if (func == nullptr) yyerror("Function not found");

    if (debug) std::cout << "Generating arguments" << std::endl;

    std::vector<Value*> arg_values;
    int index = 0;
    for (auto arg: *args) {
        
        if (debug) std::cout << "Generating argument " << index << std::endl;
        if (!(*args_ref)[index]) {

            if (debug) std::cout << "Argument is not a reference" << std::endl;
            Value *arg_val = arg->igen();
            if (!arg_val) yyerror("Argument value not found");
            arg_values.push_back(arg_val);
        } else {

            if (debug) std::cout << "Argument is a reference" << std::endl;

            if (!arg->is_lvalue_id() && !arg->is_string_literal()) {
                yyerror("Argument reference mismatch");
            }
            Value *arg_address = arg->ref_gen();

            if (!arg_address) yyerror("Argument address not found");
            arg_values.push_back(arg_address);
        }

        index++;
    }

    // now I need to pass the closure variables
    for (auto c: *closures)  {
        // create a dummy Lvalue id, pass the name and the type and call ref_gen
        Lvalue_id *lv = new Lvalue_id(new std::string(c->get_name()));
        lv->set_type(c->get_type());
        Value *closure_address = lv->ref_gen();
        arg_values.push_back(closure_address);

        delete lv;
    }
    
    if (debug) std::cout << "Generating call" << std::endl;
    
    if (func->arg_size() != args->size() + closures->size()) {
        std::string s = "Argument count mismatch expected " + std::to_string(func->arg_size()) + " got " + std::to_string(args->size() + closures->size());
        yyerror(s.c_str());
        return nullptr;
    }

    if (debug) std::cout << "done (I return th createcall)" << std::endl;

    return Builder.CreateCall(func, arg_values, func->getReturnType()->isVoidTy() ? "" : "calltmp");
}
  

Value* C_UnOp::igen() const {
    if (debug) std::cout << "Generating C_UnOp" << std::endl;

    Value *e = cond->igen();
    return Builder.CreateNot(e, "nottmp");
}

Value *C_BiOp::igen() const {
    if (debug) std::cout << "Generating C_BiOp" << std::endl;
    Function *currentFunction = Builder.GetInsertBlock()->getParent();
    // get the context
    LLVMContext &context = TheContext;
    if (debug) std::cout << *this << std::endl;
    if (leftc) {
        if (debug) std::cout << "GEN leftc" << std::endl;
        Value *l = leftc->igen(); // Generate code for left operand
        
        if (op == '&') {
            BasicBlock *thenBB = BasicBlock::Create(context, "then", currentFunction);
            BasicBlock *elseBB = BasicBlock::Create(context, "else", currentFunction);
            BasicBlock *mergeBB = BasicBlock::Create(context, "merge", currentFunction);

            // Conditional branch: if left operand is true, go to 'thenBB', otherwise 'elseBB'
            Builder.CreateCondBr(l, thenBB, elseBB);

            // Then block: evaluate rightc
            Builder.SetInsertPoint(thenBB);
            Value *r = rightc->igen(); // Generate code for right operand
            Builder.CreateBr(mergeBB);

            // Else block: short-circuit to false
            Builder.SetInsertPoint(elseBB);
            Value *falseVal = ConstantInt::getFalse(context);
            Builder.CreateBr(mergeBB);

            // Merge block: create PHI node to combine results
            Builder.SetInsertPoint(mergeBB);
            PHINode *phi = Builder.CreatePHI(Type::getInt1Ty(context), 2, "andtmp");
            phi->addIncoming(r, thenBB);
            phi->addIncoming(falseVal, elseBB);
            return phi;

        } else if (op == '|') {
            BasicBlock *thenBB = BasicBlock::Create(context, "then", currentFunction);
            BasicBlock *elseBB = BasicBlock::Create(context, "else", currentFunction);
            BasicBlock *mergeBB = BasicBlock::Create(context, "merge", currentFunction);

            // Conditional branch: if left operand is false, go to 'thenBB', otherwise 'elseBB'
            Builder.CreateCondBr(l, elseBB, thenBB);

            // Then block: evaluate rightc
            Builder.SetInsertPoint(thenBB);
            Value *r = rightc->igen();
            Builder.CreateBr(mergeBB);

            // Else block: short-circuit to true
            Builder.SetInsertPoint(elseBB);
            Value *trueVal = ConstantInt::getTrue(context);
            Builder.CreateBr(mergeBB);

            // Merge block: create PHI node to combine results
            Builder.SetInsertPoint(mergeBB);
            PHINode *phi = Builder.CreatePHI(Type::getInt1Ty(context), 2, "ortmp");
            phi->addIncoming(trueVal, elseBB);
            phi->addIncoming(r, thenBB);
            return phi;
        }
    }

    if (debug) std::cout << "GEN left" << std::endl;
    Value *l = left->igen();
    // print the type of the left value for debugging
    if (debug) std::cout << "Type of left value: " << l->getType()->getIntegerBitWidth() << std::endl;
    
    if (debug) std::cout << "GEN right" << std::endl;
    Value *r = right->igen();
    // print the type of the right value for debugging
    if (debug) std::cout << "Type of right value: " << r->getType()->getIntegerBitWidth() << std::endl;


    if (debug) std::cout << "GEN cmp" << std::endl;
    switch (op) {
        case '<': return Builder.CreateICmpSLT(l, r, "lttmp");
        case '>': return Builder.CreateICmpSGT(l, r, "gttmp");
        case 'e': return Builder.CreateICmpEQ( l, r, "eqtmp");
        case 'n': return Builder.CreateICmpNE( l, r, "netmp");
        case 'l': return Builder.CreateICmpSLE(l, r, "letmp");
        case 'm': return Builder.CreateICmpSGE(l, r, "metmp");
    }
    if (debug) std::cout << "GEN done" << std::endl;
    return nullptr;
}

Value* ConstBool::igen() const {
    return c1(value);
}

Value* NoOp::igen() const {
    if (debug) std::cout << "Generating NoOp" << '\t';
    if (debug) std::cout << "done" << std::endl;
    return nullptr;
}

Value* Let::igen() const {
    if (debug) std::cout << "Generating Let" << '\t';

    Value *v = expr->igen();
    
    // get the alloca for the variable fron the symbol table
    Value *storage = var->ref_gen();

    if (storage == nullptr) {
        yyerror("Variable not found");
    }
    
    Builder.CreateStore(v, storage);

    if (debug) std::cout << "done" << std::endl;
    return v;
}

Value* CompoundStmt::igen() const{
    if (debug) std::cout << "Generating CompoundStmt" << std::endl;

    
    // I want to know if the last statement is a return statement
    // if it is, I want to let the parent node know that

    int i = 0;
    for (auto stmt: stmt_list) {
        if (debug) std::cout << "Generating stmt " << i++ << std::endl;
        stmt->igen();

    }
    return nullptr;
}

Value *If::igen( ) const {
    if (debug) std::cout << "Generating If" << '\t';

    Value *condValue = cond->igen();

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *ThenBB = BasicBlock::Create(TheContext, "then", TheFunction);
    BasicBlock *ElseBB = BasicBlock::Create(TheContext, "else", TheFunction);
    BasicBlock *MergeBB = nullptr;
    // do we need a mergebb?
    if(!(then->returns() && els && els->returns())) MergeBB = BasicBlock::Create(TheContext, "ifcont", TheFunction);

    Builder.CreateCondBr(condValue, ThenBB, ElseBB);
    Builder.SetInsertPoint(ThenBB);
    then->igen();
    // if then returns then I can't put the break into the merge block
    if (!then->returns()) Builder.CreateBr(MergeBB);
    Builder.SetInsertPoint(ElseBB);
    
    if (els) {
        els->igen();
        if (!els->returns()) Builder.CreateBr(MergeBB);
    }
    else {
        Builder.CreateBr(MergeBB);

    }

    if (MergeBB) {
        Builder.SetInsertPoint(MergeBB);
    }
    
    if (debug) std::cout << "done" << std::endl;
    return nullptr;
}


Value* While::igen() const {
    if (debug) std::cout << "Generating While" << std::endl;

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *CondBB = BasicBlock::Create(TheContext, "whilecond", TheFunction);
    BasicBlock *LoopBB = BasicBlock::Create(TheContext, "whileloop", TheFunction);
    BasicBlock *AfterBB = BasicBlock::Create(TheContext, "whileafter", TheFunction);


    if (debug) std::cout << "Creating the blocks" << std::endl;

    Builder.CreateBr(CondBB);
    Builder.SetInsertPoint(CondBB);

    if (debug) std::cout << "Generating the condition" << std::endl;

    Value *Cond = cond->igen();
    // Value *Cond = Builder.CreateICmpNE(CondV, c32(0), "whilecond");
    Builder.CreateCondBr(Cond, LoopBB, AfterBB);


    Builder.SetInsertPoint(LoopBB);

    if (debug) std::cout << "Generating the body" << '\t';

    body->igen();
    Builder.CreateBr(CondBB);

    Builder.SetInsertPoint(AfterBB);

    if (debug) std::cout << "done" << std::endl;
    return nullptr;
}

Value* Return::igen() const {
    if (debug) std::cout << "Generating Return" << '\t';
    if (expr) {
        Value *retVal = expr->igen();
        Builder.CreateRet(retVal);

        if (debug) std::cout << "done" << std::endl;
        return retVal;
    } else {
        Builder.CreateRetVoid();

        if (debug) std::cout << "done" << std::endl;
        return nullptr;
    }
}

Function *Func_def::igen() const {
    // function type eg: int(int,int)
    if (debug) std::cout << "Generating code for function " << name << std::endl;
    std::vector<Type*> arg_types;

    for (auto arg: *args) {

        if (debug) std::cout << "Arg: " << arg->get_name() << std::endl;

        if (arg->get_type() == TYPE_int) { // int
            if (arg->is_ref()) {  // check if it's a reference
                arg_types.push_back(i32->getPointerTo());
            }
            else {
                arg_types.push_back(i32);
            }
        }
        else if (arg->get_type() == TYPE_char) { // char
            if (arg->is_ref()) {  // check if it's a reference
                arg_types.push_back(i8->getPointerTo());
            }
            else {
                arg_types.push_back(i8);
            }
        }
        else if (arg->get_type() == TYPE_int_array) { // int array
            arg_types.push_back(i32->getPointerTo());
        }
        else if (arg->get_type() == TYPE_char_array) { // char array
            arg_types.push_back(i8->getPointerTo());
        }
        else {
            yyerror("Function argument type mismatch");
        }

        if (debug) std::cout << "done with argument" << std::endl;
    }

    for (auto closvar: *closures) {
        if (debug) std:: cout << "Closure: " << closvar->get_name() << std::endl;

        if (closvar->get_type() == TYPE_int) { // int
            arg_types.push_back(i32->getPointerTo());
        }
        else if (closvar->get_type() == TYPE_char) { // char
            arg_types.push_back(i8->getPointerTo());
        }
        else if (closvar->get_type() == TYPE_int_array) { // int array
            arg_types.push_back(i32->getPointerTo());
        }
        else if (closvar->get_type() == TYPE_char_array) { // char array
            arg_types.push_back(i8->getPointerTo());
        }
        else {
            yyerror("Function argument type mismatch");
        }
    }

    // create the Function table entry
    std::vector<bool> *arg_ref = new std::vector<bool>();
    for (auto arg: *args) {
        arg_ref->push_back(arg->is_ref());
    }
    

    // return type int, char or void
    Type *returnType = nullptr;
    if (type == TYPE_char) {
        returnType = i8;
    } else if (type == TYPE_int) {
        returnType = i32;
    } else {
        returnType = Type::getVoidTy(TheContext);
    }

// Create the function
    FunctionType *FT = FunctionType::get(returnType, arg_types, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, name, TheModule.get());


    // get the name set by llvm
    std::string llvm_name = F->getName().str();
    new_ft.insert(name,arg_ref,llvm_name);

    if (debug) std::cout << "creating function arguments"  << std::endl;
    // set names for the arguments
    unsigned int i = 0;
    for (auto &arg: F->args()) {
        if (i < args->size()) arg.setName((*args)[i]->get_name());
        else {
            arg.setName((*closures)[i - args->size()]->get_name());
        }
        ++i;
    }

    if (debug) std::cout << "creating function body" << std::endl;
    // create a new basic block to start insertion into
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
    Builder.SetInsertPoint(BB);

    // create a new scope for the function
    if (debug) std::cout << "creating new scope" << std::endl;
    new_st.openScope();
    new_ft.openScope();
    
    // add arguments to the symbol table
    i = 0;
    for (auto &arg: F->args()) {
        bool isRefParam = true;
        if (i < args->size()) {
            isRefParam = (*args)[i]->is_ref();
        }


        //create an alloca with paramType
        //it is i32** if param is a reference to an int
        //
        AllocaInst *Alloca = Builder.CreateAlloca(arg.getType(), nullptr, arg.getName());
        Builder.CreateStore(&arg, Alloca);
        new_st.insert(arg.getName().str(), Alloca, isRefParam);
        ++i;
    }

    // deal with the declarations
    if (debug) std::cout << "dealing with declarations" << std::endl;
        // Generate code for variable declarations
    for (auto decl : *decls) {
        if (!decl->is_function_def()) {
            decl->igen();
        }
    }

    // Save the current insertion point before generating nested functions
    IRBuilder<>::InsertPoint savedIP = Builder.saveIP();

    // Generate code for nested function declarations
    for (auto decl : *decls) {
        if (decl->is_function_def()) {
            decl->igen();
        }
    }

    // Restore the insertion point to continue in the current function
    Builder.restoreIP(savedIP);

    if (debug) std::cout << "dealing with body" << std::endl;
    // deal with the body
    if (debug) {
        // print the class of the body
        if (body == nullptr) std::cout << "there is a problem" << std::endl;
    }
    body->igen();
    if (debug) std::cout << "done with body" << std::endl;
    // Ensure there's a return instruction
    if (!Builder.GetInsertBlock()->getTerminator()) {
        if (returnType->isVoidTy()) {
            Builder.CreateRetVoid();
        } else if (returnType->isIntegerTy()) {
            Builder.CreateRet(ConstantInt::get(returnType, 0));
        } else {
            yyerror("Unhandled function return type");
        }
    }

    if (debug) std::cout << "verifying function" << std::endl;
    verifyFunction(*F);

    if (debug) std::cout << "closing scope" << std::endl;
    new_st.closeScope();
    new_ft.closeScope();

    if (debug) std::cout << "done" << std::endl;

    return F;
}

Value *Var_def::igen() const {
    if (debug) std::cout << "Generating Var_def for "<< name << '\t';
    Type *varType;
    if (c == -1) {
        if (type == TYPE_int) {
            varType = i32;
        } else if (type == TYPE_char) {
            varType = i8;
        } else {
            yyerror("Array type mismatch");
        }

        AllocaInst *alloca = Builder.CreateAlloca(varType, nullptr, name);
        new_st.insert(name, alloca);
    }
    else {
        // this is if it's an array
        if (debug) std::cout << "It's an array " << '\t';
        if (type == TYPE_int_array) {
            varType = i32;
        } else if (type == TYPE_char_array) {
            varType = i8;
        } else {
            yyerror("Array type mismatch");
        }
        ArrayType *arrayType = ArrayType::get(varType, c);
        AllocaInst *alloca = Builder.CreateAlloca(arrayType, nullptr, name);
        new_st.insert(name, alloca);
    }
    if (debug) std::cout << "done" << std::endl;
    return nullptr;
}

