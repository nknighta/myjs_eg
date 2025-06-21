#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"

// Global symbol table
std::unordered_map<std::string, double> symbol_table;

void execute_code(const std::string& code) {
    try {
        Lexer lexer(code);
        Parser parser(lexer);
        std::unique_ptr<ASTNode> ast = parser.parse();
        double result = ast->evaluate();
        std::cout << "=> " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string filename = argv[1];
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return 1;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        execute_code(buffer.str());
    } else {
        std::cout << "Interpreter with assignment and 'while' support (type 'exit' to quit)" << std::endl;
        std::cout << "Example: var i = 0; while (i < 3) { i = i + 1; }; i;" << std::endl;

        std::string input;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, input);
            if (input == "exit") break;
            if (input.empty()) continue;
            execute_code(input);
        }
    }
    return 0;
}
