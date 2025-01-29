#pragma once

#include <memory>
#include <string>
#include <vector>

namespace HIR {

    struct HIRExpr {
        virtual ~HIRExpr() = default;
        virtual std::string to_string() const = 0;
    };
    
    typedef std::shared_ptr<HIRExpr> Expr;
    typedef std::vector<Expr> ExprList;
    
    struct Function : public HIRExpr {
        std::string name;
        std::string type;
        ExprList params;
        ExprList body;
    public:
        Function(const std::string &name, const std::string &type,
                    ExprList params = std::vector<Expr>(),
                    ExprList body = std::vector<Expr>())
            : name(name), type(type), params(params), body(body) {}
        
        std::string to_string() const override {
            std::string str = "Function:\n\tName: " + this->name + "\n\tType: "
                                + this->type + "\n\tParams:";
            
            for (auto &param : this->params)  {
                str += " " + param->to_string();
            }
            
            str += "\n\tBody:\n";
            
            for (auto &node : this->body)  {
                str += "\t\t" + node->to_string() + "\n";
            }

            return str;
        }
    };

    struct Return : public HIRExpr {
        Expr value;
    public:
        Return(Expr value)
            : value(value) {}

        std::string to_string() const override {
            return "Return: " + this->value->to_string();
        }
    };

    struct NumberSigned : public HIRExpr {
        int64_t value;
    public:
        NumberSigned(int64_t value)
            : value(value) {}

        std::string to_string() const override {
            return "NumberSigned(" + std::to_string(this->value) + ")";
        }
    };

    struct NumberUnsigned : public HIRExpr {
        uint64_t value;
    public:
        NumberUnsigned(int64_t value)
            : value(value) {}

        std::string to_string() const override {
            return "NumberUnsigned(" + std::to_string(this->value) + ")";
        }
    };

}