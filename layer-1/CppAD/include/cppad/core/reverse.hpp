# ifndef CPPAD_CORE_REVERSE_HPP
# define CPPAD_CORE_REVERSE_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-25 Bradley M. Bell
// ----------------------------------------------------------------------------

/**
 * @file core/reverse.hpp
 * @brief Reverse mode automatic differentiation
 *
 * @algorithm Reverse Mode AD (Backpropagation):
 * Computes gradients by traversing the computation graph backwards.
 * Key advantage: gradient of scalar function w.r.t. all inputs in O(ops).
 *
 * FORWARD SWEEP (already done):
 *   Compute y = f(x) while recording operation tape
 *   Store intermediate values at each node
 *
 * REVERSE SWEEP:
 *   Initialize: ȳ = 1 (adjoint of output)
 *   For each operation v = op(u₁, u₂, ...) in reverse order:
 *     Compute: ūᵢ += ȳ · ∂v/∂uᵢ (chain rule)
 *   Final: x̄ = gradient ∂y/∂x
 *
 * HIGHER ORDER REVERSE:
 *   With q-th order forward coefficients stored:
 *   Computes ∂W/∂x where W = Σₖ wₖ · yₖ
 *   Returns q Taylor coefficient derivatives per variable
 *
 * ADJOINT EQUATIONS:
 *   For v = u₁ + u₂:  ū₁ += v̄, ū₂ += v̄
 *   For v = u₁ · u₂:  ū₁ += v̄·u₂, ū₂ += v̄·u₁
 *   For v = sin(u):   ū += v̄·cos(u)
 *   For v = exp(u):   ū += v̄·v
 *
 * @math Complexity comparison for f: Rⁿ → Rᵐ:
 *   Forward mode: O(n·ops) for full Jacobian (n forward sweeps)
 *   Reverse mode: O(m·ops) for full Jacobian (m reverse sweeps)
 *   For gradient (m=1): reverse is O(ops), forward is O(n·ops)
 *
 * Memory: O(ops) to store forward sweep values for reverse
 *
 * @complexity
 * - Single reverse sweep: O(ops) time, O(ops) space
 * - Gradient of scalar function: O(ops) regardless of input dimension
 * - Full Jacobian: O(min(n,m)·ops) using appropriate mode
 *
 * @ref Griewank & Walther (2008). "Evaluating Derivatives: Principles and
 *   Techniques of Algorithmic Differentiation". 2nd ed., SIAM.
 *
 * @see cppad/core/forward.hpp for forward mode
 * @see cppad/core/sparse_hes.hpp for sparse Hessian via reverse-on-forward
 */

# include <algorithm>
# include <cppad/local/pod_vector.hpp>
# include <cppad/local/play/sequential_iterator.hpp>

namespace CppAD { // BEGIN_CPPAD_NAMESPACE
/*!
\file core/reverse.hpp
Compute derivatives using reverse mode.
*/


/*!
Use reverse mode to compute derivative of forward mode Taylor coefficients.

The function
\f$ X : {\bf R} \times {\bf R}^{n \times q} \rightarrow {\bf R} \f$
is defined by
\f[
X(t , u) = \sum_{k=0}^{q-1} u^{(k)} t^k
\f]
The function
\f$ Y : {\bf R} \times {\bf R}^{n \times q} \rightarrow {\bf R} \f$
is defined by
\f[
Y(t , u) = F[ X(t, u) ]
\f]
The function
\f$ W : {\bf R}^{n \times q} \rightarrow {\bf R} \f$ is defined by
\f[
W(u) = \sum_{k=0}^{q-1} ( w^{(k)} )^{\rm T}
\frac{1}{k !} \frac{ \partial^k } { t^k } Y(0, u)
\f]

\tparam Base
base type for the operator; i.e., this operation sequence was recorded
using AD< Base > and computations by this routine are done using type
 Base.

\tparam BaseVector
is a Simple Vector class with elements of type Base.

\param q
is the number of the number of Taylor coefficients that are being
differentiated (per variable).

\param w
is the weighting for each of the Taylor coefficients corresponding
to dependent variables.
If the argument w has size <tt>m * q </tt>,
for \f$ k = 0 , \ldots , q-1 \f$ and \f$ i = 0, \ldots , m-1 \f$,
\f[
   w_i^{(k)} = w [ i * q + k ]
\f]
If the argument w has size m ,
for \f$ k = 0 , \ldots , q-1 \f$ and \f$ i = 0, \ldots , m-1 \f$,
\f[
w_i^{(k)} = \left\{ \begin{array}{ll}
   w [ i ] & {\rm if} \; k = q-1
   \\
   0       & {\rm otherwise}
\end{array} \right.
\f]

\return
Is a vector \f$ dw \f$ such that
for \f$ j = 0 , \ldots , n-1 \f$ and
\f$ k = 0 , \ldots , q-1 \f$
\f[
   dw[ j * q + k ] = W^{(1)} ( x )_{j,k}
\f]
where the matrix \f$ x \f$ is the value for \f$ u \f$
that corresponding to the forward mode Taylor coefficients
for the independent variables as specified by previous calls to Forward.

*/
template <class Base, class RecBase>
template <class BaseVector>
BaseVector ADFun<Base,RecBase>::Reverse(size_t q, const BaseVector &w)
{  // used to identify the RecBase type in calls to sweeps
   RecBase not_used_rec_base(0.0);

   // constants
   const Base zero(0);

   // temporary indices
   size_t i, j, k;

   // number of independent variables
   size_t n = ind_taddr_.size();

   // number of dependent variables
   size_t m = dep_taddr_.size();

   // check BaseVector is Simple Vector class with Base type elements
   CheckSimpleVector<Base, BaseVector>();

   CPPAD_ASSERT_KNOWN(
      size_t(w.size()) == m || size_t(w.size()) == (m * q),
      "Argument w to Reverse does not have length equal to\n"
      "the dimension of the range or dimension of range times q."
   );
   CPPAD_ASSERT_KNOWN(
      q > 0,
      "The first argument to Reverse must be greater than zero."
   );
   CPPAD_ASSERT_KNOWN(
      num_order_taylor_ >= q,
      "Less than q Taylor coefficients are currently stored"
      " in this ADFun object."
   );
   // special case where multiple forward directions have been computed,
   // but we are only using the one direction zero order results
   if( (q == 1) && (num_direction_taylor_ > 1) )
   {  num_order_taylor_ = 1;        // number of orders to copy
      size_t c = cap_order_taylor_; // keep the same capacity setting
      size_t r = 1;                 // only keep one direction
      capacity_order(c, r);
   }
   CPPAD_ASSERT_KNOWN(
      num_direction_taylor_ == 1,
      "Reverse mode for Forward(q, r, xq) with more than one direction"
      "\n(r > 1) is not yet supported for q > 1."
   );

   // initialize entire Partial matrix to zero
   local::pod_vector_maybe<Base> Partial(num_var_tape_ * q);
   for(i = 0; i < num_var_tape_; i++)
      for(j = 0; j < q; j++)
         Partial[i * q + j] = zero;

   // set the dependent variable direction
   // (use += because two dependent variables can point to same location)
   if( size_t(w.size()) == m )
   {  for(i = 0; i < m; ++i)
      {  CPPAD_ASSERT_UNKNOWN( dep_taddr_[i] < num_var_tape_  );
         Partial[dep_taddr_[i] * q + q - 1] += w[i];
      }
   }
   else
   {  CPPAD_ASSERT_UNKNOWN( size_t(w.size()) == m * q );
      for(i = 0; i < m; i++)
      {  CPPAD_ASSERT_UNKNOWN( dep_taddr_[i] < num_var_tape_  );
         for(k = 0; k < q; k++)
            Partial[ dep_taddr_[i] * q + k ] += w[i * q + k ];
      }
   }
   // evaluate the derivatives
   CPPAD_ASSERT_UNKNOWN( cskip_op_.size() == play_.num_var_op() );
   CPPAD_ASSERT_UNKNOWN( load_op2var_.size()  == play_.num_var_load() );
   local::play::const_sequential_iterator play_itr = play_.end();
   local::sweep::reverse(
      num_var_tape_,
      &play_,
      cap_order_taylor_,
      taylor_.data(),
      q,
      Partial.data(),
      cskip_op_.data(),
      load_op2var_,
      play_itr,
      not_used_rec_base
   );

   // return the derivative values
   BaseVector value(n * q);
   for(j = 0; j < n; j++)
   {  CPPAD_ASSERT_UNKNOWN( ind_taddr_[j] < num_var_tape_  );

      // independent variable taddr equals its operator taddr
      CPPAD_ASSERT_UNKNOWN( play_.GetOp( ind_taddr_[j] ) == local::InvOp );

      // by the Reverse Identity Theorem
      // partial of y^{(k)} w.r.t. u^{(0)} is equal to
      // partial of y^{(q-1)} w.r.t. u^{(q - 1 - k)}
      if( size_t(w.size()) == m )
      {  for(k = 0; k < q; k++)
            value[j * q + k ] =
               Partial[ind_taddr_[j] * q + q - 1 - k];
      }
      else
      {  for(k = 0; k < q; k++)
            value[j * q + k ] =
               Partial[ind_taddr_[j] * q + k];
      }
   }
   CPPAD_ASSERT_KNOWN( ! ( hasnan(value) && check_for_nan_ ) ,
      "dw = f.Reverse(q, w): has a nan,\n"
      "but none of its Taylor coefficents are nan."
   );

   return value;
}


} // END_CPPAD_NAMESPACE
# endif
