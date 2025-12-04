/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     adolc.h
 Revision: $Id$
 Contents: Provides all C/C++ interfaces of ADOL-C.
           NOTICE: ALL C/C++ headers will be included DEPENDING ON
           whether the source code is plain C or C/C++ code.

 Copyright (c) Andrea Walther, Andreas Griewank, Andreas Kowarz,
               Hristo Mitev, Sebastian Schlenkrich, Jean Utke, Olaf Vogel

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

/**
 * @file adolc.h
 * @brief Master include file for ADOL-C automatic differentiation library
 *
 * ADOL-C (Automatic Differentiation by Overloading in C++) computes derivatives
 * of mathematical functions via operator overloading and tape-based recording.
 * Records computation as a "tape" then replays in forward/reverse mode.
 *
 * @algorithm Tape-Based Automatic Differentiation:
 * Computes exact derivatives using operator overloading and tape replay:
 *
 * RECORDING PHASE:
 * 1. trace_on(tag) - Begin recording to tape with identifier 'tag'
 * 2. Use adouble type - Operations recorded as instruction sequence
 * 3. trace_off() - Finalize tape, optionally write to disk
 *
 * FORWARD MODE (compute directional derivatives):
 * - Propagate derivatives from inputs to outputs: ẏ = J·ẋ
 * - Cost: O(p·ops) for p directions, 'ops' = tape operations
 * - Modes: zos (0th order), fos (1st order scalar), hos (higher order)
 *
 * REVERSE MODE (compute gradients/adjoints):
 * - Propagate adjoints from outputs to inputs: x̄ = Jᵀ·ȳ
 * - Cost: O(q·ops) for q adjoints, independent of input dimension!
 * - Modes: fos_reverse, hos_reverse, hov_reverse
 *
 * @math Forward vs Reverse complexity:
 * For f: ℝⁿ → ℝᵐ, computing full Jacobian J ∈ ℝᵐˣⁿ:
 * - Forward mode: O(n) tape evaluations (one per input direction)
 * - Reverse mode: O(m) tape evaluations (one per output adjoint)
 * Reverse is O(n/m) faster for m << n (e.g., scalar objective functions).
 *
 * Higher-order Taylor coefficients computed via univariate Taylor propagation.
 *
 * @complexity O(ops) per tape evaluation, where ops = number of recorded operations.
 * Memory: O(ops) for tape storage + O(ops) for reverse mode intermediates.
 *
 * @ref Griewank & Walther (2008). "Evaluating Derivatives: Principles and
 *   Techniques of Algorithmic Differentiation", 2nd ed. SIAM.
 * @ref Walther & Griewank (2012). "Getting Started with ADOL-C".
 *   Combinatorial Scientific Computing, Chapman & Hall/CRC.
 *
 * @see adtb_types.h for adouble/pdouble class definitions
 * @see interfaces.h for low-level forward/reverse mode calls
 * @see drivers/drivers.h for high-level derivative computation
 * @see tape_interface.h for tape management functions
 * @see Ipopt for NLP optimization using ADOL-C derivatives
 */

#if !defined(ADOLC_ADOLC_H)
#define ADOLC_ADOLC_H 1

#include <adolc/internal/common.h>

/****************************************************************************/
/*                                                  Now the pure C++ THINGS */
#if defined(__cplusplus)
/*--------------------------------------------------------------------------*/
/* Operator overloading things (active doubles & vectors) */
#include <adolc/adtb_types.h>
#include <adolc/checkpointing.h>
#include <adolc/edfclasses.h>
#include <adolc/externfcts.h>
#include <adolc/externfcts2.h>
#include <adolc/fixpoint.h>
#include <adolc/tape_interface.h>
#endif

/****************************************************************************/
/*                                                     Now the C/C++ THINGS */

/*--------------------------------------------------------------------------*/
/* interfaces to basic forward/reverse routines */
#include <adolc/interfaces.h>

/*--------------------------------------------------------------------------*/
/* interfaces to "Easy To Use" driver routines for ... */
#include <adolc/drivers/drivers.h>    /* optimization & nonlinear equations */
#include <adolc/drivers/odedrivers.h> /* ordinary differential equations */
#include <adolc/drivers/psdrivers.h>  /* piecewise smooth functions */
#include <adolc/drivers/taylor.h> /* higher order tensors & inverse/implicit functions */

/*--------------------------------------------------------------------------*/
/* interfaces to TAPEDOC package */
#include <adolc/tapedoc/tapedoc.h>

/*--------------------------------------------------------------------------*/
/* interfaces to SPARSE package */
#if defined(SPARSE_DRIVERS)
#include <adolc/sparse/sparse_fo_rev.h>
#include <adolc/sparse/sparsedrivers.h>
#endif

/*--------------------------------------------------------------------------*/
/* allocation utilities */
#include <adolc/adalloc.h>

/****************************************************************************/
#endif
