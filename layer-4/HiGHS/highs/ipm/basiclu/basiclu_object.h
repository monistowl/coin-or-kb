/**
 * @file basiclu_object.h
 * @brief Object-oriented wrapper for BasicLU with automatic memory management
 *
 * Provides a simplified interface that manages internal arrays automatically.
 * The basiclu_obj_* functions handle allocation, reallocation, and deallocation
 * of the istore, xstore, Li, Lx, Ui, Ux, Wi, Wx arrays.
 *
 * **User-Accessible Members:**
 * - xstore: Read/write parameters and statistics
 * - lhs, ilhs, nzlhs: Solution after solve_sparse/solve_for_update (read-only)
 * - realloc_factor: Growth multiplier for reallocations (default 1.5)
 *
 * **Usage Pattern:**
 * ```c
 * struct basiclu_object obj;
 * basiclu_obj_initialize(&obj, m);
 * basiclu_obj_factorize(&obj, Bbegin, Bend, Bi, Bx);
 * basiclu_obj_solve_sparse(&obj, nzrhs, irhs, xrhs, 'N');
 * // Solution in obj.lhs[obj.ilhs[0..obj.nzlhs-1]]
 * basiclu_obj_free(&obj);
 * ```
 *
 * @see basiclu.h for the low-level array-based interface
 * @see basiclu_obj_initialize.h for initialization
 * @see basiclu_obj_free.h for cleanup
 */
struct basiclu_object
{
    lu_int *istore;
    double *xstore;
    lu_int *Li, *Ui, *Wi;
    double *Lx, *Ux, *Wx;
    double *lhs;
    lu_int *ilhs;
    lu_int nzlhs;
    double realloc_factor;
};

/*
A variable of type struct basiclu_object must be defined in user code. Its
members are set and maintained by basiclu_obj_* routines. User code should only
access the following members:

    xstore (read/write)

        set parameters and get info values

    lhs, ilhs, nzlhs (read only)

        holds solution after solve_sparse() and solve_for_update()

    realloc_factor (read/write)

        Arrays are reallocated for max(realloc_factor, 1.0) times the
        required size. Default: 1.5
*/
