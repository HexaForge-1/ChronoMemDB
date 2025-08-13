#include <cassert>
#include <iostream>
#include "storage.h"
#include "query_parser.h"

int main() {
    StorageEngine engine;
    QueryParser parser;

    auto r1 = parser.dispatch("CREATE TABLE users", engine);
    assert(r1.ok && "table create failed");

    auto r2 = parser.dispatch("INSERT INTO USERS VALUES (1, "Alice", 30)", engine);
    assert(r2.ok && "insert failed");

    auto r3 = parser.dispatch("SELECT BY ID 1", engine);
    assert(r3.ok && r3.output.find("Alice") != std::string::npos);

    auto r4 = parser.dispatch("SELECT * FROM users", engine);
    assert(r4.ok && r4.output.size() > 0);

    std::cout << "Basic tests passed.\n";
    return 0;
}
