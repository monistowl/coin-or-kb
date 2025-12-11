/**
 * @file basiclu_obj_solve_sparse.h
 * @brief Solve linear system with sparse RHS using BasicLU object
 *
 * Object-oriented wrapper for basiclu_solve_sparse().
 * Solution stored in obj->lhs with pattern in obj->ilhs[0..obj->nzlhs-1].
 *
 * @see basiclu_solve_sparse.h for Gilbert-Peierls algorithm
 * @see basiclu_object.h for accessing solution
 */
lu_int basiclu_obj_solve_sparse
(
    struct basiclu_object *obj,
    lu_int nzrhs,
    const lu_int irhs[],
    const double xrhs[],
    char trans
);

/*
Purpose:

    Call basiclu_solve_sparse() on a BASICLU object. On success, the solution
    is provided in obj->lhs and the nonzero pattern is stored in
    obj->ilhs[0..obj->nzlhs-1].

Return:

    BASICLU_ERROR_invalid_object

        obj is NULL or initialized to a null object.

    Other return codes are passed through from basiclu_solve_sparse().

Arguments:

    struct basiclu_object *obj

        Pointer to an initialized BASICLU object.

    The other arguments are passed through to basiclu_solve_sparse().
*/
