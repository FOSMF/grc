#pragma once

#include <memory>
#include <map>
#include <string>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

#include "expr.hpp"

using namespace llvm;

namespace MIR {

    class LLVMCodegen {
    public:
        LLVMCodegen(std::string name, ExprList exprs)
            : exprs(exprs), context(std::make_unique<LLVMContext>()),
                builder(std::make_unique<IRBuilder<>>(*this->context)),
                module(std::make_unique<Module>(name, *this->context)) {}

        void generate_ir();
    private:
        void gen_expr(FunctionType *ftype, Expr &expr);
        void gen_func(Expr &expr);
    private:
        ExprList exprs;

        std::unique_ptr<LLVMContext> context;
        std::unique_ptr<IRBuilder<>> builder;
        std::unique_ptr<Module> module;
        std::map<std::string, Value*> symbol_table;
    };

}
