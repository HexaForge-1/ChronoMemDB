#pragma once
#include <vector>
#include <string>
#include <optional>
#include <unordered_map>

struct Row {
    int id{};
    std::string name;
    int age{};
};

class Table {
public:
    bool insert(const Row& row);
    std::optional<Row> findById(int id) const;
    const std::vector<Row>& all() const { return rows_; }

private:
    std::vector<Row> rows_;
    std::unordered_map<int, size_t> id_index_; // simple O(1) lookup
};

class StorageEngine {
public:
    bool createUsersTable();
    bool insertUser(int id, const std::string& name, int age);
    std::optional<Row> selectUserById(int id) const;
    std::vector<Row> selectAllUsers() const;

private:
    bool users_created_ = false;
    Table users_;
};
