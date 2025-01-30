#pragma once

#include <memory>
#include <string>
#include <vector>

namespace HIR {

    struct HIRExpr {
        virtual ~HIRExpr() = default;
        virtual std::string to_string() const = 0;
        virtual size_t get_line() const = 0;
        virtual size_t get_start_col() const = 0;
        virtual size_t get_end_col() const = 0;
    };
    
    typedef std::shared_ptr<HIRExpr> Expr;
    typedef std::vector<Expr> ExprList;
    
    struct Function : public HIRExpr {
        std::string name;
        std::string type;
        ExprList params;
        ExprList body;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Function(const std::string &name, const std::string &type,
                    ExprList params = std::vector<Expr>(),
                    ExprList body = std::vector<Expr>(),
                    size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : name(name), type(type), params(params), body(body), line(line),
                start_col(start_col), end_col(end_col) {}

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

        size_t get_line() const override { return this->line; }
        size_t get_start_col() const override { return this->start_col; }
        size_t get_end_col() const override { return this->end_col; }
    };

    struct Return : public HIRExpr {
        Expr value;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Return(Expr value, size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : value(value), line(line), start_col(start_col), end_col(end_col) {}

        std::string to_string() const override {
            return "Return: " + this->value->to_string();
        }

        size_t get_line() const override { return this->line; }
        size_t get_start_col() const override { return this->start_col; }
        size_t get_end_col() const override { return this->end_col; }
    };

    struct NumberSigned : public HIRExpr {
        int64_t value;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        NumberSigned(int64_t value, size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : value(value), line(line), start_col(start_col), end_col(end_col) {}

        std::string to_string() const override {
            return "NumberSigned(" + std::to_string(this->value) + ")";
        }

        size_t get_line() const override { return this->line; }
        size_t get_start_col() const override { return this->start_col; }
        size_t get_end_col() const override { return this->end_col; }
    };

    struct NumberUnsigned : public HIRExpr {
        uint64_t value;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        NumberUnsigned(int64_t value, size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : value(value), line(line), start_col(start_col), end_col(end_col) {}

        std::string to_string() const override {
            return "NumberUnsigned(" + std::to_string(this->value) + ")";
        }

        size_t get_line() const override { return this->line; }
        size_t get_start_col() const override { return this->start_col; }
        size_t get_end_col() const override { return this->end_col; }
    };

}