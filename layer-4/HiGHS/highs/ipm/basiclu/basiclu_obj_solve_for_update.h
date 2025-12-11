/**
 * @file basiclu_obj_solve_for_update.h
 * @brief Solve and prepare for update using BasicLU object
 *
 * Object-oriented wrapper for basiclu_solve_for_update() with automatic
 * memory reallocation. The want_solution parameter controls whether the
 * full solution is computed (requires extra triangular solve).
 *
 * Solution stored in obj->lhs with pattern in obj->ilhs[0..obj->nzlhs-1].
 *
 * @see basiclu_solve_for_update.h for FTRAN/BTRAN details
 * @see basiclu_obj_update.h for completing the basis update
 */
lu_int basiclu_obj_solve_for_update
(
    struct basiclu_object *obj,
    lu_int nzrhs,
    const lu_int irhs[],
    const double xrhs[],
    char trans,
    lu_int want_solution
);

/*
Purpose:

    Call basiclu_solve_for_update() on a BASICLU object. On success, if the
    solution was requested, it is provided in obj->lhs and the nonzero pattern
    is stored in obj->ilhs[0..obj->nzlhs-1].

Return:

    BASICLU_ERROR_invalid_object

        obj is NULL or initialized to a null object.

    BASICLU_ERROR_out_of_memory

        reallocation failed because of insufficient memory.

    Other return codes are passed through from basiclu_solve_for_update().

Arguments:

    struct basiclu_object *obj

        Pointer to an initialized BASICLU object.

    lu_int want_solution

        Nonzero to compute the solution to the linear system,
        zero to only prepare the update.

    The other arguments are passed through to basiclu_solve_for_update().
*/
