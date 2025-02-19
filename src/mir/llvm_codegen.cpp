#include "llvm_codegen.hpp"

#include <iostream>

namespace MIR {

    void LLVMCodegen::gen_expr(FunctionType *ftype, Expr &expr) {
        if (auto ret = dynamic_cast<Return*>(expr.get())) {
            if (ftype->getReturnType()->isIntegerTy(32)) {
                if (auto num_signed = dynamic_cast<NumberSigned*>(ret->value.get())) {
                    Value *return_value = ConstantInt::get(*this->context, APInt(32, (uint64_t)num_signed->value, true));
                    this->builder->CreateRet(return_value);
                } else { }
            }
        }
    }

    void LLVMCodegen::gen_func(Expr &expr) {
        auto func = dynamic_cast<Function*>(expr.get());

        FunctionType *ftype = FunctionType::get(Type::getInt32Ty(*this->context), false);
        llvm::Function *llvm_func = llvm::Function::Create(ftype, llvm::Function::ExternalLinkage, func->name, *this->module);

        for (Block &block : func->blocks) {
            BasicBlock *llvm_block = BasicBlock::Create(*this->context, block.name, llvm_func);
            this->builder = std::make_unique<IRBuilder<>>(llvm_block);
            for (Expr &expr : block.body) {
                this->gen_expr(ftype, expr);
            }
        }

        llvm::verifyFunction(*llvm_func);

        this->module->print(llvm::outs(), nullptr);
    }

    void LLVMCodegen::generate_ir() {
        for (Expr &expr : this->exprs) {
            gen_func(expr);
        }
    }

}