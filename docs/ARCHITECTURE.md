# ChronoMemDB Architecture

## Overview
ChronoMemDB separates concerns into four subsystems:

1) **Storage Engine** — owns tables and in‑memory row vectors (MVP uses a simple row store).
2) **Indexing** — B+Tree skeleton provided; wiring via `Index` interface (future).
3) **Transaction Manager** — stubs for begin/commit/rollback; future WAL and locks.
4) **Query Processor** — parses tiny commands and calls storage APIs.

```
          +-----------------------+
          |     Query Parser      |
          +-----------+-----------+
                      |
                      v
+---------+   +-------+--------+   +----------------+
| Storage |<->|  Transaction  |<->|  Logging/WAL   |
+----+----+   +-------+--------+   +----------------+
     ^                |
     |                v
     |          +-----+-----+
     |          |  Indexes  |
     |          | (B+Tree)  |
     |          +-----------+
     v
  In‑Memory Tables
```

## Data Model (MVP)
- Demonstration table: `users(id:int, name:string, age:int)`
- Stored as `std::vector<Row>`; id acts as logical primary key.
- Lookup is O(n) in MVP (replace with B+Tree for O(log n)).

## Parsing
A minimal, whitespace‑split parser handles:
- `CREATE TABLE users`
- `INSERT INTO users VALUES (id, name, age)`
- `SELECT * FROM users`
- `SELECT BY ID <id>`

## Extending
- Replace linear scans with B+Tree
- Add schema catalog and multiple tables
- Introduce WAL + snapshots for durability
- Add MVCC or 2PL for isolation
