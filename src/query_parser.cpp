#include "query_parser.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

static std::vector<std::string> split_ws(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> toks;
    std::string t;
    while (iss >> t) toks.push_back(t);
    return toks;
}

std::string QueryParser::trim(const std::string& s) {
    size_t a = 0, b = s.size();
    while (a < b && std::isspace(static_cast<unsigned char>(s[a]))) ++a;
    while (b > a && std::isspace(static_cast<unsigned char>(s[b-1]))) --b;
    return s.substr(a, b-a);
}

std::string QueryParser::normalize(const std::string& in) const {
    std::string s = in;
    // uppercase
    for (char& c : s) if (std::islower(static_cast<unsigned char>(c))) c = std::toupper(static_cast<unsigned char>(c));
    // remove trailing semicolon
    if (!s.empty() && s.back() == ';') s.pop_back();
    return trim(s);
}

ExecResult QueryParser::dispatch(const std::string& cmd, StorageEngine& engine) const {
    auto toks = split_ws(cmd);
    ExecResult res;
    if (toks.empty()) { res.ok = true; return res; }

    if (cmd == "CREATE TABLE USERS" || (toks.size()>=3 && toks[0]=="CREATE" && toks[1]=="TABLE")) {
        res.ok = engine.createUsersTable();
        res.message = res.ok ? "Table 'users' created." : "Failed to create table.";
        res.output = res.message;
        return res;
    }

    if (toks.size() >= 6 && toks[0]=="INSERT" && toks[1]=="INTO" && toks[2]=="USERS") {
        // Expect: INSERT INTO USERS VALUES (id, name, age)
        auto pos = cmd.find("VALUES");
        if (pos == std::string::npos) { res.message="Syntax error: missing VALUES"; return res; }
        auto tuple = cmd.substr(pos + 6);
        std::string buf;
        for (char c : tuple) {
            if (std::isdigit(static_cast<unsigned char>(c)) || std::isalpha(static_cast<unsigned char>(c)) || c==' ' ) buf.push_back(c);
            if (c==',' ) buf.push_back(' ');
        }
        auto vals = split_ws(buf);
        if (vals.size() < 3) { res.message="Syntax error: need id name age"; return res; }
        int id = std::stoi(vals[0]);
        std::string name = vals[1];
        int age = std::stoi(vals[2]);
        bool ok = engine.insertUser(id, name, age);
        if (!ok) { res.message="Insert failed (duplicate id or table missing)"; return res; }
        res.ok = true; res.output = "Inserted 1 row.";
        return res;
    }

    if (toks.size() >= 4 && toks[0]=="SELECT" && toks[1]=="BY" && toks[2]=="ID") {
        int id = std::stoi(toks[3]);
        auto row = engine.selectUserById(id);
        if (!row) { res.message="Not found"; return res; }
        std::ostringstream oss; oss << "id="<<row->id<<", name="<<row->name<<", age="<<row->age;
        res.ok = true; res.output = oss.str(); return res;
    }

    if (cmd == "SELECT * FROM USERS" || (toks.size()>=4 && toks[0]=="SELECT" && toks[1]=="*" && toks[2]=="FROM")) {
        auto rows = engine.selectAllUsers();
        std::ostringstream oss;
        for (const auto& r : rows) oss << r.id << " " << r.name << " " << r.age << "\n";
        res.ok = true; res.output = oss.str(); return res;
    }

    res.message = "Unknown command. Type HELP.";
    return res;
}
