# Victim Cache Analysis in gem5

A **Victim Cache** is a cache optimization that reduces the conflict miss penalty incurred by the L1 cache by storing and serving recently evicted blocks.  
In this project, I evaluated this property of the victim cache through a series of experiments using the **gem5** simulator.

---

## Table of Contents
1. [Introduction to Victim Cache](#introduction-to-victim-cache)   
2. [Experiments](#experiments)  
   - [Experiment 1 : Configuration and Custom Statistic](#experiment-1)  
   - [Experiment 2](#experiment-2)  
   - [Experiment 3](#experiment-3)  
   - [Experiment 4](#experiment-4)  
   - [Experiment 5](#experiment-5)  
3. [Implementation Details](#implementation-details)
4. [Future Work](#future-work)  
5. [Reference](#reference)  

---

## Introduction to Victim Cache
A **Victim Cache** is a small, fully-associative cache placed between the L1 cache and the next level of memory hierarchy. It temporarily stores cache lines evicted from the L1 cache, providing another chance to hit before going to L2 or main memory.  

This design helps reduce **miss penalty** while keeping the L1 cache simple and fast.  

Below is a high-level schematic of where the Victim Cache is placed in the hierarchy:

<p align="left">
  <img src="assets/vc.png">
</p>

---

## Experiments

### Experiment 1: Configuration Test with Custom Statistic

#### Task
The only objective of this experiment was to correctly add and verify a custom statistic (`m_count_hits`) to the Ruby memory system in gem5.This counter tracked **L1-D cache hits** and was compared against the predefined `m_demand_hits` counter for verification.

#### Configuration

| Component             | Configuration                |
|-----------------------|------------------------------|
| CPU                   | TIMING, 1 core (ARM ISA)     |
| L1 Data Cache         | 16 KiB, 8-way associative    |
| L1 Instruction Cache  | 16 KiB, 8-way associative    |
| L2 Cache              | 256 KiB, 16-way associative  |
| Memory                | SingleChannelDDR4_2400       |
| Clock Frequency       | 3 GHz                        |
| Workload              | GAPBS BFS (ARM binary)       |

#### Result
- The custom statistic `m_count_hits` appeared in `stats.txt`.  
- Its value exactly matched gem5’s built-in counter `m_demand_hits` for the L1-D cache.  
- This verified that the counter was correctly integrated into the Ruby subsystem.

---

### Experiment 2
- **Task:**  
- **Setup/Config:**  
- **Result:**  
- **Key Takeaway:**  

### Experiment 3
- **Task:**  
- **Setup/Config:**  
- **Result:**  
- **Key Takeaway:**  

### Experiment 4
- **Task:**  
- **Setup/Config:**  
- **Result:**  
- **Key Takeaway:**  

### Experiment 5
- **Task:**  
- **Setup/Config:**  
- **Result:**  
- **Key Takeaway:**  

---

## Implementation Details
The implementation steps, file modifications, and code snippets are documented in [IMPLEMENTATION.md](IMPLEMENTATION.md).

## Future Work
The following extensions and optimizations can be explored as part of future work:
- **Way Prediction** – predicting the matching way in set-associative caches to reduce access latency.  
- **Prefetching** – preloading likely-to-be-used cache lines.  
- **Critical Word First / Early Restart** – prioritizing the word requested by the CPU to reduce stall time.  
- **NoC-based Cache Coherence Protocol Analysis** – exploring victim cache impact in multi-core and network-on-chip scenarios.  

---

## Reference
For details about the base gem5 simulator, please refer to [README_gem5.md](README_gem5.md) included in this repository.
