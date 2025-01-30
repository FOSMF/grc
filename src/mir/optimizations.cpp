#include "optimizations.hpp"

namespace MIR {

    void MIROptimizations::remove_unused() {
        for (auto &expr : this->mir_code) {
            if (auto function = dynamic_cast<Function*>(expr.get())) {
                for (auto &block : function->blocks) {
                    size_t returns = 0;

                    for (size_t i = 0 ; i < block.body.size(); i++) {
                        if (returns > 0) {
                            block.body.erase(block.body.begin() + i);
                            i--;
                        } else if (dynamic_cast<Return*>(block.body[i].get())) {
                            returns++;        
                        }
                    }
                }
            }
        }
    }

}