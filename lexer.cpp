#include <iostream>
#include <string>

using namespace std;

enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LEFT_PAREN,
    RIGHT_PAREN,
    END_OF_FILE
};

// a lexeme represents a token as a pattern of symbols
class Token {
public:
    Token(TokenType type, string lexeme) : type(type), lexeme(lexeme) {}

    TokenType type;
    string lexeme;
};

class Lexer {
public:
    // constructor initializer list
    Lexer(string input) : input(input), position(0) {}

    Token getNextToken() {
        while (position < input.size()) {
            switch (input[position]) {
                case '+':
                    position++;
                    return Token(PLUS, "+");
                case '-':
                    position++;
                    return Token(MINUS, "-");
                case '*':
                    position++;
                    return Token(MULTIPLY, "*");
                case '/':
                    position++;
                    return Token(DIVIDE, "/");
                case '(':
                    position++;
                    return Token(LEFT_PAREN, "(");
                case ')':
                    position++;
                    return Token(RIGHT_PAREN, ")");
                default:
                    if (isdigit(input[position])) {
                        string lexeme;
                        while (position < input.size() && isdigit(input[position])) {
                            lexeme.push_back(input[position]);
                            position++;
                        }
                        return Token(NUMBER, lexeme);
                    } else {
                        // Invalid character
                        throw runtime_error("Invalid character: " + string(1, input[position]));
                    }
            }
        }

        return Token(END_OF_FILE, "");
    }

private:
    string input;
    size_t position; // size_t is unsigned int guaranteed to be big enough to hold the size of any object in bytes
};

int main() {
    string input = "2+3*(4-1)";
    Lexer lexer(input);

    try {
        while (true) {
            Token token = lexer.getNextToken();
            cout << token.lexeme << endl;
            if (token.type == END_OF_FILE) {
                break;
            }
        }
    } catch (exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
