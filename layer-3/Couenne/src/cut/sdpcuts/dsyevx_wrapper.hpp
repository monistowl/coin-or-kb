/*
 *
 * Name:    dsyevx_wrapper.hpp
 * Authors: Andrea Qualizza
 *          Pietro Belotti
 * Purpose:
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file dsyevx_wrapper.hpp
 * @brief LAPACK dsyevx wrapper for symmetric eigenvalue computation
 *
 * C++ interface to LAPACK's dsyevx routine for computing selected
 * eigenvalues and eigenvectors of a real symmetric matrix.
 *
 * **dsyevx_interface parameters:**
 * - n: Matrix dimension
 * - A: Input symmetric matrix (upper or lower triangle)
 * - m: [out] Number of eigenvalues found
 * - w: [out] Eigenvalues in ascending order
 * - z: [out] Eigenvectors (column-wise)
 * - tolerance: Relative accuracy for eigenvalues
 * - lb_ev, ub_ev: Eigenvalue range to compute (RANGE='V')
 * - firstidx, lastidx: Index range to compute (RANGE='I')
 *
 * **Usage in Couenne:**
 * Used by CouenneSdpCuts to compute negative eigenvalues of the
 * lifted matrix X - xxᵀ, where violations indicate cuts.
 *
 * **Algorithm:**
 * DSYEVX uses bisection followed by inverse iteration for
 * selected eigenvalues, more efficient than full diagonalization.
 *
 * @see CouenneSdpCuts which uses this for semidefinite cuts
 */
#ifndef DSYEVX_HPP
#define DSYEVX_HPP

int dsyevx_interface (int n, double *A, int &m,
		       double * &w, double * &z, // output values
		       double tolerance,
		       double lb_ev,
		       double ub_ev,
		       int firstidx,
		       int lastidx);

#endif
