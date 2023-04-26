#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class ASTNode {
public:
    virtual int evaluate() const = 0;
};

/// BinarOperationNode is a subclass of ASTNode
class BinaryOperationNode : public ASTNode {
public:
    BinaryOperationNode(char op, ASTNode* left, ASTNode* right) : op(op), left(left), right(right) {}
    int evaluate() const override {
        int leftVal = left->evaluate();
        int rightVal = right->evaluate();
        switch (op) {
            case '+':
                return leftVal + rightVal;
            case '-':
                return leftVal - rightVal;
            case '*':
                return leftVal * rightVal;
            case '/':
                return leftVal / rightVal;
            default:
                throw runtime_error("Invalid operator");
        }
    }
private:
    char op;
    ASTNode* left;
    ASTNode* right;
};

class NumberNode : public ASTNode {
public:
    NumberNode(int value) : value(value) {}
    int evaluate() const override {
        return value;
    }
private:
    int value;
};

class Parser {
public:
    Parser(const string& input) : input(input) {}
    ASTNode* parse() {
        pos = 0;
        ASTNode* node = parseExpression();
        if (pos != input.length()) {
            throw runtime_error("Unexpected end of input");
        }
        return node;
    }
private:
    ASTNode* parseExpression() {
        ASTNode* left = parseTerm();
        while (pos < input.length() && (input[pos] == '+' || input[pos] == '-')) {
            char op = input[pos++];
            ASTNode* right = parseTerm();
            left = new BinaryOperationNode(op, left, right);
        }
        return left;
    }
    ASTNode* parseTerm() {
        ASTNode* left = parseFactor();
        while (pos < input.length() && (input[pos] == '*' || input[pos] == '/')) {
            char op = input[pos++];
            ASTNode* right = parseFactor();
            left = new BinaryOperationNode(op, left, right);
        }
        return left;
    }
    ASTNode* parseFactor() {
        if (pos >= input.length()) {
            throw runtime_error("Unexpected end of input");
        }
        if (isdigit(input[pos])) {
            int value = input[pos++] - '0';
            while (pos < input.length() && isdigit(input[pos])) {
                value = value * 10 + (input[pos++] - '0');
            }
            return new NumberNode(value);
        }
        else if (input[pos] == '(') {
            pos++;
            ASTNode* node = parseExpression();
            if (pos >= input.length() || input[pos] != ')') {
                throw runtime_error("Expected ')'");
            }
            pos++;
            return node;
        }
        else {
            throw runtime_error("Expected number or '('");
        }
    }
    string input;
    int pos;
};

int main() {
    string input = "2+3*(3-1)";
    Parser parser(input);
    ASTNode* ast = parser.parse();
    cout << ast->evaluate() << endl;
    delete ast;
    return 0;
}
