#pragma once

#include "expr.hpp"

namespace MIR {

    class MIROptimizations {
    public:
        MIROptimizations(ExprList &mir_code)
            : mir_code(mir_code) {}

        void remove_unused();
    private:
        ExprList &mir_code;
    };

}