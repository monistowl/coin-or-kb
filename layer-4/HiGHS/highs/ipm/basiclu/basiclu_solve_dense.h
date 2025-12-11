/**
 * @file basiclu_solve_dense.h
 * @brief Solve linear system with dense right-hand side
 *
 * Solves B·x = b (trans='N') or B'·y = c (trans='T') given dense vectors.
 * The solution overwrites or is written to lhs; rhs and lhs may alias.
 *
 * **Algorithm:**
 * - Forward system: x = U⁻¹(L⁻¹(P·b)), then permute by Q
 * - Transpose system: y = P'(L⁻ᵀ(U⁻ᵀ(Q'·c)))
 *
 * For sparse right-hand sides, prefer basiclu_solve_sparse() which
 * exploits sparsity via Gilbert-Peierls symbolic analysis.
 *
 * @see basiclu_solve_sparse.h for sparse RHS (more efficient for sparse b)
 * @see basiclu_solve_for_update.h for solves that prepare basis updates
 */
lu_int basiclu_solve_dense
(
    lu_int istore[],
    double xstore[],
    lu_int Li[],
    double Lx[],
    lu_int Ui[],
    double Ux[],
    lu_int Wi[],
    double Wx[],
    const double rhs[],
    double lhs[],
    char trans
);

/*
Purpose:

    Given the factorization computed by basiclu_factorize() or basiclu_update()
    and the dense right-hand side, rhs, solve a linear system for the solution
    lhs.

Return:

    BASICLU_ERROR_invalid_store if istore, xstore do not hold a BASICLU
    instance. In this case xstore[BASICLU_STATUS] is not set.

    Otherwise return the status code. See xstore[BASICLU_STATUS] below.

Arguments:

    lu_int istore[]
    double xstore[]
    lu_int Li[]
    double Lx[]
    lu_int Ui[]
    double Ux[]
    lu_int Wi[]
    double Wx[]

        Factorization computed by basiclu_factorize() or basiclu_update().

    const double rhs[m]

        The right-hand side vector.

    double lhs[m]

        Uninitialized on entry. On return lhs holds the solution to the linear
        system.

        lhs and rhs are allowed to overlap. To overwrite rhs with the solution
        pass pointers to the same array.

    char trans

        Defines which system to solve. 't' or 'T' for the transposed system, any
        other character for the forward system.

Info:

    xstore[BASICLU_STATUS]: status code.

        BASICLU_OK

            The linear system has been successfully solved.

        BASICLU_ERROR_argument_missing

            One or more of the pointer/array arguments are NULL.

        BASICLU_ERROR_invalid_call

            The factorization is invalid.
*/
