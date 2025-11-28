---
name: annotation-tags-reference
description: Quick reference for all annotation tags used in the solver knowledge base. Consult when unsure which tag to use.
---

# Annotation Tags Quick Reference

## Pass 1: Structural Tags

| Tag | Usage | Example |
|-----|-------|---------|
| `@file` | File-level documentation | `@file CoinPackedVector.hpp` |
| `@brief` | One-line summary | `@brief Sparse vector using index-value pairs` |
| `@param` | Function parameter | `@param index Position in dense vector` |
| `@param[in]` | Input parameter | `@param[in] data Source array` |
| `@param[out]` | Output parameter | `@param[out] result Computed value` |
| `@param[in,out]` | Modified parameter | `@param[in,out] vec Vector to update` |
| `@return` | Return value | `@return Number of elements` |
| `@tparam` | Template parameter | `@tparam T Element type` |
| `@see` | Cross-reference | `@see CoinPackedMatrix` |
| `@note` | Important note | `@note Not thread-safe` |
| `@warning` | Warning | `@warning Modifies input` |
| `@deprecated` | Deprecated API | `@deprecated Use newMethod() instead` |

## Pass 2: Semantic Tags

| Tag | Usage | Example |
|-----|-------|---------|
| `@algorithm` | Algorithm name + info | `@algorithm Dantzig's simplex method` |
| `@math` | Mathematical foundation | `@math Solves Ax = b using LU factorization` |
| `@complexity` | Time/space complexity | `@complexity O(n log n) time, O(n) space` |
| `@invariant` | Class/loop invariant | `@invariant Elements always sorted by index` |
| `@pre` | Precondition | `@pre Matrix must be non-singular` |
| `@post` | Postcondition | `@post Solution vector contains result` |
| `@ref` | Citation | `@ref Dantzig (1963), Linear Programming` |

## Deferred Work Tags

| Tag | Usage | Example |
|-----|-------|---------|
| `@todo` | Future work needed | `@todo Add bounds checking` |
| `@todo PASS2:` | Needs semantic review | `@todo PASS2: Identify algorithm` |

## Inline Documentation

For private members and inline comments:
```cpp
int count_;  ///< Number of elements stored
```

## File Header Template

```cpp
/**
 * @file FileName.hpp
 * @brief One-line description of file purpose
 *
 * Longer description explaining the main classes/functions
 * in this file and their relationships.
 *
 * @see RelatedFile.hpp
 */
```

## Function Documentation Template

```cpp
/**
 * @brief One-line description of what function does
 *
 * Longer description if needed, explaining behavior,
 * edge cases, and usage patterns.
 *
 * @param paramName Description of parameter
 * @return Description of return value
 *
 * @algorithm Name of algorithm if non-trivial
 * @complexity O(?) time, O(?) space
 *
 * @pre Any preconditions
 * @post Any postconditions
 *
 * @see relatedFunction()
 */
```

## Class Documentation Template

```cpp
/**
 * @brief One-line description of class purpose
 *
 * Longer description explaining the class's role,
 * typical usage, and relationship to other classes.
 *
 * @tparam T Description of template parameter (if applicable)
 *
 * @invariant Key invariants the class maintains
 *
 * @see RelatedClass
 */
```

## Common Patterns in Solver Code

### Sparse Matrix Operations
```cpp
/**
 * @brief Multiply sparse matrix by dense vector
 * @param x Input vector (dense)
 * @param[out] y Output vector (dense), computed as y = A*x
 * @algorithm Compressed sparse row (CSR) matrix-vector product
 * @complexity O(nnz) where nnz is number of nonzeros
 */
```

### Optimization Algorithms
```cpp
/**
 * @brief Perform one iteration of the simplex method
 * @return true if optimal or infeasible, false if more iterations needed
 * @algorithm Revised simplex with steepest edge pricing
 * @math Pivots to adjacent basic feasible solution
 * @complexity O(m*n) per iteration for m constraints, n variables
 */
```

### Numerical Utilities
```cpp
/**
 * @brief Check if value is effectively zero
 * @param value Number to check
 * @param tolerance Threshold for zero (default 1e-10)
 * @return true if |value| < tolerance
 * @note Uses absolute tolerance, not relative
 */
```
