#pragma once

#include <memory>
#include <string>
#include <vector>

namespace MIR {

    struct MIRExpr {
        virtual ~MIRExpr() = default;
        virtual std::string to_string() const = 0;
        virtual size_t get_line() const = 0;
        virtual size_t get_start_col() const = 0;
        virtual size_t get_end_col() const = 0;
    };

    typedef std::shared_ptr<MIRExpr> Expr;
    typedef std::vector<Expr> ExprList;

    struct Block {
        std::string name;
        ExprList body;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Block(const std::string &name, ExprList body = std::vector<Expr>(), size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : name(name), body(body), line(line), start_col(start_col), end_col(end_col) {}

        std::string to_string() const {
            std::string str = "Block: " + this->name + " {\n";
            for (auto &node : this->body) {
                str += "\t\t\t" + node->to_string() + "\n";
            }
            str += "\t\t}";
            return str;
        }
    };
    
    struct Function : public MIRExpr {
        std::string name;
        std::string type;
        ExprList params;
        std::vector<Block> blocks;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Function(const std::string &name, const std::string &type,
                    ExprList params = std::vector<Expr>(),
                    std::vector<Block> blocks = std::vector<Block>(),
                    size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : name(name), type(type), params(params), blocks(blocks), line(line),
                start_col(start_col), end_col(end_col) {}

        std::string to_string() const override {
            std::string str = "Function:\n\tName: " + this->name + "\n\tType: "
                                + this->type + "\n\tParams:";
            
            for (auto &param : this->params)  {
                str += " " + param->to_string();
            }
            
            str += "\n\tBody:\n";
            for (auto &block : this->blocks)  {
                str += "\t\t" + block.to_string() + "\n";
            }

            return str;
        }

        size_t get_line() const override { return this->line; }
        size_t get_start_col() const override { return this->start_col; }
        size_t get_end_col() const override { return this->end_col; }
    };

    struct Return : public MIRExpr {
        Expr value;

        std::string type;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Return(const std::string &type, Expr value, size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : value(value), type(type), line(line), start_col(start_col), end_col(end_col) {}

        std::string to_string() const override {
            return "Return: " + this->type + " " + this->value->to_string();
        }

        size_t get_line() const override { return this->line; }
        size_t get_start_col() const override { return this->start_col; }
        size_t get_end_col() const override { return this->end_col; }
    };

    struct NumberSigned : public MIRExpr {
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

    struct NumberUnsigned : public MIRExpr {
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