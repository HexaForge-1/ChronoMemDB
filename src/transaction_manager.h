#pragma once
#include <cstdint>

class TransactionManager {
public:
    using TxnId = std::uint64_t;

    TxnId begin() { return ++last_id_; }
    void commit(TxnId) {/* TODO: WAL commit */}
    void rollback(TxnId) {/* TODO: undo changes */}

private:
    TxnId last_id_{0};
};
