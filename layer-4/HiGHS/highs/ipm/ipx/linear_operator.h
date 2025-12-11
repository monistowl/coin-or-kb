/**
 * @file linear_operator.h
 * @brief Abstract interface for linear operators (preconditioners, matrices)
 *
 * Defines the LinearOperator base class used by iterative solvers.
 * Implementations include diagonal preconditioner, normal matrix,
 * and splitted normal matrix.
 *
 * The Apply() method computes lhs = F(rhs) and optionally returns
 * the inner product dot(rhs, lhs) for efficiency.
 *
 * @see diagonal_precond.h for diagonal preconditioner
 * @see normal_matrix.h for A·W·A' operator
 * @see splitted_normal_matrix.h for basis-preconditioned normal matrix
 */
#ifndef IPX_LINEAR_OPERATOR_H_
#define IPX_LINEAR_OPERATOR_H_

#include "ipm/ipx/ipx_internal.h"

namespace ipx {

class LinearOperator {
public:
    LinearOperator& operator=(const LinearOperator&) = delete;
    LinearOperator& operator=(LinearOperator&&) = delete;
    virtual ~LinearOperator() {}

    // Computes lhs = F(rhs), where F is a linear function. If rhs_dot_lhs is
    // not NULL, then the argument returns dot(rhs,lhs). The implementation can
    // assume that rhs and lhs do not refer to the same object.
    void Apply(const Vector& rhs, Vector& lhs, double* rhs_dot_lhs);

private:
    virtual void _Apply(const Vector& rhs, Vector& lhs, double* rhs_dot_lhs)
        = 0;
};

}  // namespace ipx

#endif  // IPX_LINEAR_OPERATOR_H_
