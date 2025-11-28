# Library Context: CoinUtils

## Purpose

CoinUtils provides basic utilities and data structures used throughout the COIN-OR ecosystem. It includes sparse matrix/vector classes, message handling, parameter management, and various helper functions. Almost every COIN-OR project depends on CoinUtils.

## Position in Ecosystem

- **Layer:** 0 (Foundation)
- **Dependencies:** None (standalone)
- **Dependents:** Osi, Clp, Cbc, Cgl, and virtually all other COIN-OR projects

## Key Classes/Modules

| Class/Module | Purpose |
|--------------|---------|
| `CoinPackedMatrix` | Sparse matrix in compressed column (CSC) or row (CSR) format |
| `CoinPackedVector` | Sparse vector with index-value pairs |
| `CoinIndexedVector` | Sparse vector with dense backing array for fast access |
| `CoinShallowPackedVector` | Non-owning view into packed vector data |
| `CoinMessageHandler` | Logging and message output system |
| `CoinParam` | Parameter handling (int, double, string, keyword params) |
| `CoinModel` | Simple model builder for LP/MIP problems |
| `CoinMpsIO` | MPS file format reader/writer |
| `CoinLpIO` | LP file format reader/writer |
| `CoinPresolveMatrix` | Matrix representation for presolve operations |
| `CoinFactorization` | LU factorization for basis matrices |
| `CoinWarmStart` | Abstract interface for warm-start information |

## Common Patterns

### Sparse Matrix Storage
CoinPackedMatrix uses compressed sparse column (CSC) format by default:
- `elements_[]` - non-zero values
- `indices_[]` - row indices for each element
- `starts_[]` - starting position of each column in elements/indices
- `lengths_[]` - number of non-zeros in each column

Can also store in row-major (CSR) format via `reverseOrdering()`.

### Vector Operations
Three vector types serve different use cases:
- `CoinPackedVector` - owns data, general purpose, can modify
- `CoinShallowPackedVector` - non-owning view, for function parameters
- `CoinIndexedVector` - sparse storage + dense array, for accumulation operations

### Memory Management
Classes use internal memory management with:
- `reserve()` to preallocate
- Automatic growth with doubling strategy
- `clear()` vs `setVector()` semantics

### Naming Conventions
- `get*()` / `set*()` - accessors
- `*ByRow` / `*ByColumn` - row-major vs column-major operations
- `Coin*` prefix on all classes

## Mathematical Background

### Sparse Linear Algebra
- Compressed sparse formats (CSC/CSR)
- Matrix-vector multiplication with sparse matrices
- Fill-in during factorization

### LP Factorization
CoinFactorization maintains LU factorization of the basis matrix B:
- B = L * U where L is lower triangular, U is upper triangular
- FTRAN: solve Bx = b via forward/backward substitution
- BTRAN: solve B^T x = b
- Update after basis change (Forrest-Tomlin or other)

### Presolve
CoinPresolve* classes implement LP presolve techniques:
- Fixed variables, free variables
- Singleton rows/columns
- Dominated rows/columns
- Duplicate rows/columns

## Primary References

- Maros, I. (2003). "Computational Techniques of the Simplex Method". Springer.
  - Chapters on sparse data structures and factorization
- Duff, Erisman, Reid (1986). "Direct Methods for Sparse Matrices". Oxford.
  - Comprehensive treatment of sparse matrix algorithms
- Original COIN-OR documentation at https://github.com/coin-or/CoinUtils

## Known Gotchas

1. **Row-major vs Column-major:** CoinPackedMatrix can be in either orientation. Check `isColOrdered()` before assuming column-major.

2. **Shallow vs Deep Copy:** CoinShallowPackedVector does NOT own its data. Lifetime management is caller's responsibility.

3. **Index Base:** Indices are 0-based internally but MPS files use 1-based naming.

4. **Factorization vs Factorize:** `CoinFactorization` is the class; `factorize()` creates the factorization; `updateColumn()` updates it.

5. **Message Handler Levels:** Messages have priorities (0-3). Level 0 is always shown, higher levels are increasingly verbose.
