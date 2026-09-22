# The Sacred STCs: Data Structures & Litanies of Algorithms in C


*“Toll the Great Bell Once! Pull the Lever forward to engage the Lexmechanic. Toll the Great Bell Twice! With push of Button wake the Cogitator. Toll the Great Bell Thrice! Praise the Omnissiah and the ancient code of C.”*


An illuminated archive of fundamental structural STCs (Standard Template Constructs) and algorithmic litanies, transcribed in the ancient and unforgiving memory-management of C. 


---


## Vaults of Structure (Data Structures)


### Linear Formations (Trench Lines & Servitor Queues)

- [x] **Array List** — Sequential cogitator memory implementation (`O(1)` access, `O(N)` deployment/extraction)

- [x] **Linked List** — Pointer-based chainsword links (`O(N)` access, `O(1)` head insert/delete)

- [x] **Cursor List** — Array-based servitor-pointer linked list (`O(N)` access)

- [x] **Array Stack** — LIFO array-backed drop pod stack (`O(1)` push/pop)

- [x] **Linked Stack** — LIFO pointer-backed stack (`O(1)` push/pop)

- [x] **Cursor Stack** — LIFO cursor-backed stack (`O(1)` push/pop)

- [x] **Array Queue** — FIFO circular trench queue (`O(1)` enqueue/dequeue)

- [x] **Linked Queue** — FIFO pointer-backed Munitorum supply line (`O(1)` enqueue/dequeue)

- [x] **Cursor Queue** — FIFO cursor-backed supply line (`O(1)` enqueue/dequeue)


### Inquisitorial Databanks (Sets & Dictionaries)

- [x] **Bit Vector Set** — Fast auspex scanning via bitwise operations (`O(1)` lookups)

- [x] **Computer Word Set** — Set encoding in standard machine spirit word formats

- [x] **Open Hashing Dictionary** — Separate chaining hash table for Administratum records (`O(1)` avg lookup)

- [x] **Closed Hashing Dictionary** — Open addressing / linear or quadratic probing (`O(1)` avg lookup)


### Branching Paths of the Webway (Trees & Priority Queues)

- [x] **Binary Search Tree (BST)** — Search tree with Pre/In/Post-order astropathic traversals (`O(log N)` avg search/insert/delete)

- [x] **Max Heap** — Array-based Max Priority Queue for targeting hierarchies (`O(log N)` insert/deleteMax, `O(N)` heapify)

- [x] **Min Heap** — Array-based Min Priority Queue (`O(log N)` insert/deleteMin)

- [ ] **AVL Tree** — Self-balancing BST with LL/RR/LR/RL tactical rotations (`O(log N)` worst-case search)

- [ ] **Trie (Prefix Tree)** — Fast retrieval for xenos cypher cracking (`O(L)` lookup where L = key length)

- [ ] **Disjoint Set Union (DSU)** — United planetary systems with warp-path compression (`O(α(N))` operations)


### Astropathic Choirs & Networks (Graphs)

- [x] **Adjacency Matrix** — Dense sector grid representation (`O(1)` warp route lookup, `O(V²)` space)

- [x] **Adjacency List** — Sparse spatial route representation (`O(V + E)` space)


### Deep Vault Storage Litanies (B-Trees)

- [ ] **B-Tree** — Self-balancing $m$-way tree for massive data-tome disk storage (`O(log N)` search/insert)

- [ ] **B+ Tree** — Data-in-leaves variant with linked leaf nodes for pict-feed range scans (`O(log N)` search, fast range scan)

- [ ] **B\* Tree** — High-density variant requiring 2/3 cogitator fill factor (`O(log N)` search, higher space efficiency)


---


## The Holy Rites of Computation (Algorithms)


### Rites of Organization (Sorting Algorithms)

#### The Standard Templates

- [ ] **Bubble Sort** — `O(N²)` time | `O(1)` space *(Frowned upon by the Tech-Priests)*

- [ ] **Insertion Sort** — `O(N²)` time | `O(1)` space

- [ ] **Selection Sort** — `O(N²)` time | `O(1)` space

- [ ] **Merge Sort** — `O(N log N)` time | `O(N)` space *(Regimented splitting and merging)*

- [ ] **Quick Sort** — `O(N log N)` avg time | `O(log N)` space *(The Emperor's Swift Judgement)*

- [ ] **Heap Sort** — `O(N log N)` time | `O(1)` space

- [ ] **Counting Sort** — `O(N + K)` non-comparison sort *(Munitorum tallying)*

- [ ] **Radix Sort** — `O(N · K)` digit-by-digit distribution sort


#### Apocryphal & Niche Rites

- [ ] **Shell Sort** — `O(N^1.5)` gap sequence optimization

- [ ] **Bucket Sort** — `O(N + K)` uniform distribution sort

- [ ] **Comb Sort** — Variant of bubble sort using variable gaps

- [ ] **Gnome Sort** — Single-loop sorting algorithm *(Approved by the Leagues of Votann)*

- [ ] **Strand Sort** — Linked-list sublist merging sort

- [ ] **Tournament Sort** — Tree-selection based gladiatorial sort


### Inquisitorial Sweeps (Searching & Matching)

- [ ] **Linear Search** — Unsorted planetary sweep (`O(N)`)

- [ ] **Binary Search** — Iterative & recursive divide-and-conquer strategy (`O(log N)`)

- [ ] **Interpolation Search** — Uniformly distributed sorted auspex ping (`O(log log N)`)

- [ ] **KMP Algorithm** — Knuth-Morris-Pratt pattern matching for detecting heretical texts (`O(N + M)`)


### Navigating the Immaterium (Graph Algorithms)

- [ ] **Breadth-First Search (BFS)** — Queue-based system-by-system expansion (`O(V + E)`)

- [ ] **Depth-First Search (DFS)** — Stack/recursive deep warp dive (`O(V + E)`)

- [ ] **Dijkstra’s Algorithm** — Single-source safest warp route with Min-Heap (`O((V + E) log V)`)

- [ ] **Bellman-Ford Algorithm** — Shortest path handling warp storm (negative weight) edges (`O(V · E)`)

- [ ] **Floyd-Warshall Algorithm** — All-pairs route calculation dynamic programming (`O(V³)`)

- [ ] **Kruskal’s Algorithm** — Minimum Spanning Network using DSU (`O(E log E)`)

- [ ] **Prim’s Algorithm** — Minimum Spanning Network using Priority Queue (`O(E log V)`)

- [ ] **Topological Sort** — Directed Acyclic Graph (DAG) campaign sequencing (`O(V + E)`)


### Tactical Cogitation (Dynamic Programming & Greedy)

- [ ] **0/1 Knapsack Problem** — Dropship loadout state space optimization

- [ ] **Longest Common Subsequence (LCS)** — Genetic sequence matching for Genestealer cults

- [ ] **Huffman Coding** — Greedy-choice astropathic cipher compression tree construction