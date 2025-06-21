#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept> 
#include "lexer.h"
#include "perser.h"

// グローバルなシンボルテーブルをここで定義
std::unordered_map<std::string, double> symbol_table;

int main() {
    std::cout << "if-else/比較対応インタプリタ (exitで終了)" << std::endl;
    std::cout << "例: var x = 10; if (x > 5) { 100 } else { 200 }" << std::endl;

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
