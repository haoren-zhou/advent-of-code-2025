# Day 11: Reactor

[Original Prompt](https://adventofcode.com/2025/day/11)

## Part 1

Topological sort + Count total ways from source to node

**Time Complexity**: $O(v + e)$ where $v$ is the number of nodes and $e$ is the number of connections/edges.

## Part 2

WLOG `fft` before `dac` (after topological sort).

Number of ways from `svr` to `fft` $\times$ Number of ways from `fft` to `dac` $\times$ Number of ways from `dac` to `out`

**Time Complexity**: $O(v+e)$
