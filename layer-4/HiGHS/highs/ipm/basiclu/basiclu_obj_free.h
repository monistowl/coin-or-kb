/**
 * @file basiclu_obj_free.h
 * @brief Free memory allocated for a BasicLU object
 *
 * Releases all dynamically allocated arrays in the BasicLU object.
 * Safe to call on NULL or already-freed objects (no-op).
 * After freeing, the object can be reinitialized with basiclu_obj_initialize().
 *
 * @see basiclu_obj_initialize.h for allocation
 * @see basiclu_object.h for the object structure
 */
void basiclu_obj_free
(
    struct basiclu_object *obj
);

/*
Purpose:

    Free memory allocated from a BASICLU object. The object must have been
    initialized before by basiclu_obj_initialize(). Subsequent calls to
    basiclu_obj_free() will do nothing.

Arguments:

    struct basiclu_object *obj

        Pointer to the object which memory is to be freed. When obj is NULL,
        then the routine does nothing.
*/
