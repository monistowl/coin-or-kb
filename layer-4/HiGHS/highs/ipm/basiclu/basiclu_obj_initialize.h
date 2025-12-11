/**
 * @file basiclu_obj_initialize.h
 * @brief Initialize a BasicLU object with automatic memory management
 *
 * Allocates and initializes all internal arrays (istore, xstore, Li, Lx,
 * Ui, Ux, Wi, Wx, lhs, ilhs) for processing m×m matrices.
 *
 * When m=0, creates a "null object" that cannot factorize but can be
 * passed to basiclu_obj_free(). Use m=0 for deferred initialization.
 *
 * @see basiclu_object.h for the object structure
 * @see basiclu_obj_free.h for cleanup
 * @see basiclu_obj_factorize.h for the next step
 */
lu_int basiclu_obj_initialize
(
    struct basiclu_object *obj,
    lu_int m
);

/*
Purpose:

    Initialize a BASICLU object. When m is positive, then *obj is initialized to
    process matrices of dimension m. When m is zero, then *obj is initialized to
    a "null" object, which cannot be used for factorization, but can be passed
    to basiclu_obj_free().

    This routine must be called once before passing obj to any other
    basiclu_obj_ routine. When obj is initialized to a null object, then the
    routine can be called again to reinitialize obj.

Return:

    BASICLU_OK

        *obj successfully initialized.

    BASICLU_ERROR_argument_missing

        obj is NULL.

    BASICLU_ERROR_invalid_argument

        m is negative.

    BASICLU_ERROR_out_of_memory

        insufficient memory to initialize object.

Arguments:

    struct basiclu_object *obj

        Pointer to the object to be initialized.

    lu_int m

        The dimension of matrices which can be processed, or 0.
*/
