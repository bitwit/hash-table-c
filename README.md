# Hash Table Implementation in C

Notes:

- This hash table is designed for storing `(char*)key`, `(char*)value` pairs

- Uses an FNV1-a hashing algorithm. Based on [this discussion](http://programmers.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed) it appears that FNV1-a has the most uniform distribution.

- This hash table uses a chaining method to handle collisions.

- Compiling and running this code will execute a small series of proofs with 2 hash tables. The first a hash table, sized for 100 items with no collisions and second a hash table sized to 1 item, where every entry will collide and form a linked list. The same series of assertions pass under both conditions. Additional information about the process and results are also printed to output.
