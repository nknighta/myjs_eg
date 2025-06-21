#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include "lexer.h"
#include "parser.h"

// Global symbol table
std::unordered_map<std::string, double> symbol_table;

int main() {
    std::cout << "Interpreter with assignment and 'while' support (type 'exit' to quit)" << std::endl;
    std::cout << "Example: var i = 0; while (i < 3) { i = i + 1; }; i;" << std::endl;

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") break;
        if (input.empty()) continue;

        try {
            Lexer lexer(input);
            Parser parser(lexer);
            std::unique_ptr<ASTNode> ast = parser.parse();
            double result = ast->evaluate();
            std::cout << "=> " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
