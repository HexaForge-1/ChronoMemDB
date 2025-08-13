#include <iostream>
#include <string>
#include <sstream>
#include "storage.h"
#include "query_parser.h"

int main() {
    std::cout << "ChronoMemDB started. Type HELP for commands.\n";
    StorageEngine engine;
    QueryParser parser;

    std::string line;
    while (true) {
        std::cout << "cmd> ";
        if (!std::getline(std::cin, line)) break;
        std::string cmd = parser.normalize(line);
        if (cmd == "QUIT" || cmd == "EXIT") {
            std::cout << "Bye.\n";
            break;
        }
        if (cmd == "HELP") {
            std::cout << "Commands:\n"
                         "  CREATE TABLE users\n"
                         "  INSERT INTO users VALUES (id, name, age)\n"
                         "  SELECT * FROM users\n"
                         "  SELECT BY ID <id>\n"
                         "  QUIT\n";
            continue;
        }
        auto res = parser.dispatch(cmd, engine);
        if (!res.ok) {
            std::cout << "Error: " << res.message << "\n";
        } else if (!res.output.empty()) {
            std::cout << res.output << "\n";
        }
    }
    return 0;
}
