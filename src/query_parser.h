#pragma once
#include <string>
#include "storage.h"

struct ExecResult {
    bool ok{false};
    std::string message;
    std::string output;
};

class QueryParser {
public:
    std::string normalize(const std::string& in) const;
    ExecResult dispatch(const std::string& cmd, StorageEngine& engine) const;

private:
    static std::string trim(const std::string& s);
};
