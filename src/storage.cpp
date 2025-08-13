#include "storage.h"
#include <algorithm>

bool Table::insert(const Row& row) {
    if (id_index_.count(row.id)) return false;
    id_index_[row.id] = rows_.size();
    rows_.push_back(row);
    return true;
}

std::optional<Row> Table::findById(int id) const {
    auto it = id_index_.find(id);
    if (it == id_index_.end()) return std::nullopt;
    return rows_[it->second];
}

bool StorageEngine::createUsersTable() {
    users_created_ = true; // single demo table
    return true;
}

bool StorageEngine::insertUser(int id, const std::string& name, int age) {
    if (!users_created_) return false;
    return users_.insert(Row{id, name, age});
}

std::optional<Row> StorageEngine::selectUserById(int id) const {
    if (!users_created_) return std::nullopt;
    return users_.findById(id);
}

std::vector<Row> StorageEngine::selectAllUsers() const {
    if (!users_created_) return {};
    return users_.all();
}
