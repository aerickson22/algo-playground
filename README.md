# algo-lab

Small C projects exploring topics from COMS 3110 (Design and Analysis of Algorithms).

## Topics

- **Running time analysis & asymptotic notation**
  - Empirical complexity plotter: time bubble/insertion/merge/quicksort on growing input sizes, export to CSV, compare against theoretical growth rates

- **Heaps and hashing**
  - Binary min-heap from scratch (array-backed); use it for a task scheduler or k-th smallest element finder
  - Hash table with chaining vs. open addressing (linear/double probing); benchmark load factor vs. lookup time
  - Word-frequency counter over a text file using the custom hash table

- **Graphs and graph exploration**
  - Maze generator (randomized DFS/Kruskal's) + solver (BFS for shortest path, DFS), printed as ASCII art
  - Six-degrees-of-separation style BFS on a small graph

- **Greedy algorithms**
  - Huffman coding compressor: build tree with a heap, encode/decode a text file, compare compressed vs. original size
  - Activity/interval scheduler: CLI that takes start/end times and prints the max non-overlapping set

- **Divide and conquer**
  - Closest pair of points in the plane (O(n log n))
  - Karatsuba big-integer multiplication vs. naive multiplication

- **Dynamic programming**
  - 0/1 knapsack solver
  - Longest common subsequence / edit distance (Levenshtein) — usable as a basic text diff tool

- **NP and computational intractability**
  - Brute-force vs. nearest-neighbor heuristic TSP (n≤ 10 exact, compare runtime/quality)
  - Brute-force SAT solver on small boolean formulas, timed to show exponential blowup

- **Public-key cryptography**
  - RSA from scratch: key generation, encryption, decryption using modular exponentiation
  - Diffie-Hellman key exchange demo between two simulated parties

## Build

```bash
gcc -o project_name project_name.c
```

## Run

```bash
./project_name
```
