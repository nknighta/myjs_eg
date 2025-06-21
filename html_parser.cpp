#include "html_parser.h"

HTMLParser::HTMLParser(const std::string& html) : html_(html) {}

std::vector<std::string> HTMLParser::get_scripts() {
    std::vector<std::string> scripts;
    std::string::size_type pos = 0;
    while ((pos = html_.find("<script>", pos)) != std::string::npos) {
        pos += 8; // length of "<script>"
        std::string::size_type end_pos = html_.find("</script>", pos);
        if (end_pos != std::string::npos) {
            scripts.push_back(html_.substr(pos, end_pos - pos));
            pos = end_pos + 9; // length of "</script>"
        } else {
            break; // No closing tag found
        }
    }
    return scripts;
}

std::vector<std::string> HTMLParser::get_paragraphs() {
    std::vector<std::string> paragraphs;
    std::string::size_type pos = 0;
    while ((pos = html_.find("<p>", pos)) != std::string::npos) {
        pos += 3; // length of "<p>"
        std::string::size_type end_pos = html_.find("</p>", pos);
        if (end_pos != std::string::npos) {
            paragraphs.push_back(html_.substr(pos, end_pos - pos));
            pos = end_pos + 4; // length of "</p>"
        } else {
            break; // No closing tag found
        }
    }
    return paragraphs;
}
