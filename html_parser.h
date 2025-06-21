#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <string>
#include <vector>

class HTMLParser {
public:
    HTMLParser(const std::string& html);
    std::vector<std::string> get_scripts();
    std::vector<std::string> get_paragraphs();
private:
    std::string html_;
};

#endif // HTML_PARSER_H
