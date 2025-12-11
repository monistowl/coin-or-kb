/**
 * @file basiclu_obj_update.h
 * @brief Apply Forrest-Tomlin update using BasicLU object
 *
 * Object-oriented wrapper for basiclu_update() with automatic
 * memory reallocation for Wi/Wx arrays if needed.
 *
 * @see basiclu_update.h for Forrest-Tomlin algorithm
 * @see basiclu_obj_solve_for_update.h for required preparation
 */
lu_int basiclu_obj_update
(
    struct basiclu_object *obj,
    double xtbl
);

/*
Purpose:

    Call basiclu_update() on a BASICLU object.

Return:

    BASICLU_ERROR_invalid_object

        obj is NULL or initialized to a null object.

    BASICLU_ERROR_out_of_memory

        reallocation failed because of insufficient memory.

    Other return codes are passed through from basiclu_update().

Arguments:

    struct basiclu_object *obj

        Pointer to an initialized BASICLU object.

    The other arguments are passed through to basiclu_update().
*/
