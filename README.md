# ChronoMemDB ⏱️💾
*A lightweight, high‑performance in‑memory database engine written in modern C++.*

ChronoMemDB is a teaching/portfolio‑grade engine that focuses on clear architecture and extendability.
It ships with a minimal storage layer, skeleton B+Tree index, a tiny SQL‑like REPL, and hooks for
transactions and logging.

> Status: **Starter template** — compile‑ready, unit‑tested stubs, and room to grow.

---

## ✨ Features (MVP)
- In‑memory row store (example `users` table)  
- Clean interfaces for Storage, Index, Transactions, and Query Processor  
- Tiny SQL‑like commands (subset): `CREATE`, `INSERT`, `SELECT` (very limited)  
- C++17 codebase with CMake build

## 🧭 Roadmap (Next Steps)
- Implement B+Tree index for primary key
- Add WHERE filters, range scans, and projections
- Introduce TransactionManager with WAL (Write‑Ahead Logging)
- Add persistence layer (snapshot + redo log)
- MVCC for concurrent readers/writers
- Proper parser (e.g., PEGTL) — currently a hand‑rolled minimal parser

---

## 🔧 Build
```bash
mkdir build && cd build
cmake ..
cmake --build . -j
./chrono_mem_db
```

### Requirements
- C++17 compatible compiler (GCC 9+/Clang 10+/MSVC 2019+)
- CMake 3.15+

---

## 🖥️ Usage (REPL)
Run the executable and enter commands (semicolon optional for simple commands):

```
CREATE TABLE users;
INSERT INTO users VALUES (1, Alice, 30);
SELECT * FROM users;
SELECT BY ID 1;
QUIT
```

> Note: This is a learning scaffold; the parser is intentionally simple.
Strings without spaces work out‑of‑the‑box; quote handling is left as an exercise.

---

## 🗂️ Project Structure
```
ChronoMemDB/
  ├─ src/
  │   ├─ main.cpp
  │   ├─ storage.h / storage.cpp
  │   ├─ bptree.h  / bptree.cpp       (skeleton)
  │   ├─ transaction_manager.h / transaction_manager.cpp (skeleton)
  │   └─ query_parser.h / query_parser.cpp
  ├─ tests/
  │   └─ basic_tests.cpp
  ├─ docs/
  │   └─ ARCHITECTURE.md
  ├─ CMakeLists.txt
  ├─ .gitignore
  └─ LICENSE
```

---

## 📚 License
MIT — see `LICENSE`.

## 🙌 Contributions
PRs are welcome. This repo is purposefully small and approachable; design notes in `docs/` highlight
how to extend each subsystem.
