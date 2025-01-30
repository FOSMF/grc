#pragma once

#include <string>
#include <vector>
#include <memory>

namespace GRC {

    struct ASTNode {
        virtual ~ASTNode() = default;
        virtual std::string to_string() const = 0;
    };

    typedef std::shared_ptr<ASTNode> Node;
    typedef std::vector<Node> NodeList;

    struct Function : public ASTNode {
        std::string name;
        std::string type;
        NodeList params;
        NodeList body;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Function(const std::string &name, const std::string &type,
                    NodeList params = std::vector<Node>(),
                    NodeList body = std::vector<Node>(),
                    size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : name(name), type(type), params(std::move(params)), body(std::move(body)),
                line(line), start_col(start_col), end_col(end_col) {}

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

    struct Return : public ASTNode {
        Node value;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Return(Node value, size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : value(value), line(line), start_col(start_col), end_col(end_col) {}

        std::string to_string() const override {
            return "Return: " + this->value->to_string();
        }
    };

    struct Number : public ASTNode {
        std::string value;

        size_t line;
        size_t start_col;
        size_t end_col;
    public:
        Number(const std::string &value, size_t line = 0, size_t start_col = 0, size_t end_col = 0)
            : value(value), line(line), start_col(start_col), end_col(end_col) {}

        std::string to_string() const override {
            return "Number(" + this->value + ")"; 
        }
    };

}