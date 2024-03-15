#include <iostream>
#include "port.h"
#include "ip.h"
#include "input.h"

int main(int argc, char *argv[]) {
    String str_rule = String(argv[1]);
    str_rule.trim();
    char *rule_trimmed = str_rule.get_string();
    // Read the entire content from std::cin into a string
    if (!strncmp(rule_trimmed, "src-port", 8) || !strncmp(rule_trimmed, "dst-port", 8)) {
        const GenericField &rule = port(rule_trimmed);
        parse_input(rule);
    } else if (!strncmp(rule_trimmed, "src-ip", 6) || !strncmp(rule_trimmed, "dst-ip", 6)) {
        const GenericField &rule = ip(rule_trimmed);
        parse_input(rule);
    } else {
        // Invalid rule string
        std::cerr << "Invalid rule: " << rule_str << std::endl;
        return 1;
    }
    return 0;
}
