# IvyDB Database Management System

This project aims to get my hands dirtier in database management systems development in C++.

## Description

The project is divided into several stages, each covering a critical aspect of database development:

1. **Basic In-Memory Key/Value Store:** Creation of a simple, in-memory key/value store with experimentation on concurrent data reading and writing mechanisms.

2. **Disk-Based Storage Engine for Read-Only Key/Value Data:** Development of a persistent storage engine for random reads of key/value data, addressing challenges associated with disk-based storage. (My biggest focus)

3. **Log-Structured Merge-Tree for Persistent Reads and Writes:** Extension of the read-only storage engine to support persistent reads and writes using a log-structured merge-tree, optimizing data storage and retrieval.

4. **Partitioned Storage Engine for Enhanced Concurrent Performance:** Application of partitioning techniques to enhance concurrent write performance and reduce lock contention, thereby improving scalability.

5. **Write-Ahead Logging for Durable Key/Value Persistence:** Implementation of write-ahead logging to ensure durable persistence of key/value data, along with evaluation of its impact on performance.

6. **Document Storage Engine for Semi-Structured Data:** Extension of the key/value storage engine to support semi-structured data like JSON documents, enhancing the database's versatility.

## Checklist

- [ ] Basic In-Memory Key/Value Store
- [ ] Disk-Based Storage Engine for Read-Only Key/Value Data
- [ ] Log-Structured Merge-Tree for Persistent Reads and Writes
- [ ] Partitioned Storage Engine for Enhanced Concurrent Performance
- [ ] Write-Ahead Logging for Durable Key/Value Persistence
- [ ] Document Storage Engine for Semi-Structured Data

If things go well, i'll add Transactions, Query Planning and Execution, Query Language and everything else !!!
