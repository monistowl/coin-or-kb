# ifndef CPPAD_CPPAD_HPP
# define CPPAD_CPPAD_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-24 Bradley M. Bell
// ----------------------------------------------------------------------------
/**
 * @file cppad.hpp
 * @brief Main include file for CppAD automatic differentiation library
 *
 * CppAD (C++ Algorithmic Differentiation) computes derivatives of
 * mathematical functions defined by C++ code using operator overloading.
 *
 * Key concepts:
 * - **AD<Base>**: Scalar type that records operations for later differentiation
 * - **ADFun**: Function object created from taped operations
 * - **Forward/Reverse**: Two modes of automatic differentiation
 *
 * Typical workflow:
 * 1. Declare independent variables: Independent(x)
 * 2. Compute dependent variables using AD<double> arithmetic
 * 3. Create function object: ADFun<double> f(x, y)
 * 4. Evaluate derivatives: f.Jacobian(x), f.Hessian(x, w)
 *
 * @algorithm Operator overloading records a "tape" of operations.
 *            Forward mode: propagates derivatives from inputs to outputs.
 *            Reverse mode: propagates derivatives from outputs to inputs.
 *            Reverse mode is more efficient for many inputs, few outputs.
 *
 * @ref Griewank, Walther (2008). "Evaluating Derivatives: Principles and
 *      Techniques of Algorithmic Differentiation", 2nd ed. SIAM.
 *
 * @see AD for the automatic differentiation scalar type
 * @see ADFun for the recorded function object
 * @see Ipopt for nonlinear optimization using CppAD derivatives
 *
 * @namespace CppAD
 * @brief Contains all variables and functions defined by CppAD package
 */

# include <cppad/base_require.hpp> // all base type requirements
// ---------------------------------------------------------------------------
// CppAD general purpose library routines (can be included separately)
# include <cppad/utility.hpp>
// --------------------------------------------------------------------------
// System routines that can be used by rest of CppAD with out including

# include <cstddef>
# include <iostream>
# include <complex>
# include <cmath>

// ---------------------------------------------------------------------------
// definitions needed by rest of includes

// definitions that come from the installation
# include <cppad/configure.hpp>

// definitions that are local to the CppAD include files
# include <cppad/local/define.hpp>

// vectors used with CppAD
# include <cppad/core/testvector.hpp>

// Declare classes and functions that are used before defined
# include <cppad/local/declare_ad.hpp>

// ---------------------------------------------------------------------------
// declare the AD<Base> template class

# include <cppad/core/ad.hpp>

// ---------------------------------------------------------------------------

# include <cppad/core/user_ad.hpp>  // AD class methods available to the user
// tape that tape for AD<Base> acts as a user of Base operations
// so user_ad.hpp must come before op.hpp
# include <cppad/local/var_op/var_op.hpp>       // executes taped operations
# include <cppad/core/ad_fun.hpp>   // ADFun objects
//
// Putting these includes in ad_fun.hpp leads to circular including; i.e,
// a file needs to include itself and the include guard stops it.
# include <cppad/local/val_graph/fun2val.hpp>
# include <cppad/local/val_graph/val2fun.hpp>

// ---------------------------------------------------------------------------
// library routines that require the rest of CppAD
# include <cppad/core/lu_ratio.hpp>
# include <cppad/core/bender_quad.hpp>
# include <cppad/core/opt_val_hes.hpp>
# include <cppad/local/graph/cpp_graph_op.hpp>
# include <cppad/local/graph/json_lexer.hpp>
# if CPPAD_HAS_IPOPT
# include <cppad/ipopt/solve.hpp>
# endif

// undo definitions in Define.h
# include <cppad/core/undef.hpp>

# endif
