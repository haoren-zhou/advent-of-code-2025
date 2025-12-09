# Day 9: Movie Theater

![Original Prompt](https://adventofcode.com/2025/day/9)

## Part 1

Brute force approach: Calculate the area enclosed by every pair of tiles

**Time Complexity**: $O(n^2)$

## Part 2

Tiles enclosed within pair of tiles must all be enclosed in the overall shape.

- Store all **edges** (adjacent tiles)
- For each **pair of tiles** $(a, b)$:
  - For each **edge**(_start_, _end_):
    - if the **edge** invalidates the rectangle:
      - pair is invalid, continue to next pair of tiles
    - else:
      - calculate area

To check if an **edge**(_start_, _end_) invalidates a rectangle:

- if either _start_ or _end_ lie within the rectangle, the rectangle is invalid
- if the **edge** divides/cuts the rectangle, the rectangle is invalid

```
......C....... ......C.......
.............. ......X.......
..AOOOOOOOOO.. ..AOOOXOOOOO..
..OOOOOOOOOO.. ..OOOOXOOOOO..
..OOOOOOOOOO.. ..OOOOXOOOOO..
..OOOOOOOOOO.. ..OOOOXOOOOO..
..OOOOOOOOOB.. ..OOOOXOOOOB..
.............. ......X.......
......D....... ......D.......
.............. ..............

```

e.g. **edge**(_C_, _D_) cuts the rectangle formed by _A_ and _B_

**Time Complexity**: For $n$ tiles, there are ${n\choose 2}$ pairs and $n$ edges $\implies O(n^3)$

Since $n$ is small ($n<500$), solution runs quickly.
