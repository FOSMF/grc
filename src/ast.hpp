#pragma once

#include <string>
#include <vector>
#include <memory>

namespace GRC {

    struct ASTNode {
        virtual ~ASTNode() = default;
        virtual std::string to_string() const = 0;
    };

    typedef std::unique_ptr<ASTNode> Node;
    typedef std::vector<Node> NodeList;

    struct Function : public ASTNode {
        std::string name;
        std::string type;
        NodeList params;
        NodeList body;
    public:
        std::string to_string() const override {
            std::string str = "Function:\n\tName: " + this->name + "\n\tType: "
                                + this->type + "\n\tParams:";

            for (auto &param : this->params)  {
                str += " " + param->to_string();
            }
            
            str += "\n\tBody:\n";

            for (auto &node : this->body)  {
                str += "\t" + node->to_string() + "\n";
            }

            return str;
        }
    };

    struct Return : public ASTNode {
        Node value;
    public:
        std::string to_string() const override {
            return "Return: " + this->value->to_string();
        }
    };

}