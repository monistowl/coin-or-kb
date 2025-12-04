/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     checkpointing.h
 Revision: $Id$
 Contents: Provides all checkointing interfaces.

 Copyright (c) Andreas Kowarz

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

/**
 * @file checkpointing.h
 * @brief Checkpointing support for memory-efficient reverse mode AD
 *
 * Implements checkpointing (also known as "time-stepping" or "revolve")
 * for computing adjoints of long time-stepping computations with bounded
 * memory. Instead of storing all intermediate states, only selected
 * "checkpoints" are stored, and segments are recomputed as needed.
 *
 * @algorithm Binomial Checkpointing for Reverse Mode AD:
 * Enables reverse-mode differentiation of N-step computations with only
 * s checkpoints (where s << N) by intelligently scheduling recomputation.
 *
 * PROBLEM:
 * Reverse mode AD of y = F_N(F_{N-1}(...F_1(x)...)) requires storing all
 * intermediate states x_1, x_2, ..., x_N to compute adjoints. For long
 * time-stepping simulations with N = 10^6+ steps, this is infeasible.
 *
 * SOLUTION (Optimal Binomial Schedule):
 * 1. Divide N steps into segments using s checkpoint slots
 * 2. Store state at strategically chosen checkpoints
 * 3. During reverse sweep:
 *    a. Restore from nearest checkpoint before current position
 *    b. Recompute forward to current position
 *    c. Perform single reverse step
 *    d. Repeat with optimal checkpoint repositioning
 *
 * The binomial schedule is provably optimal: with s checkpoints and
 * allowing r repetitions of each step, exactly C(s+r, r) steps can
 * be differentiated (where C is the binomial coefficient).
 *
 * @math Memory-computation trade-off:
 * - Without checkpointing: Memory O(N), Recomputation O(1)
 * - With s checkpoints: Memory O(s), Recomputation O(log(N)·N/s)
 * - Optimal s ≈ √(N/c) where c = ratio of checkpoint to compute cost
 *
 * For N steps with s checkpoints allowing r=1 repetition:
 * Maximum steps: C(s+1,1) = s+1 (linear)
 * Maximum steps with r repetitions: C(s+r,r) (grows super-linearly)
 *
 * @complexity O(N·log(N)) total forward evaluations for N steps with
 * O(√N) checkpoints. Per-step reverse cost remains O(1).
 *
 * @ref Griewank & Walther (2000). "Algorithm 799: Revolve: An
 *   Implementation of Checkpointing for the Reverse or Adjoint Mode
 *   of Computational Differentiation". ACM TOMS 26(1):19-45.
 * @ref Griewank & Walther (2008). "Evaluating Derivatives", Ch. 12.
 *
 * Use cases:
 * - Time-stepping ODEs/PDEs where storing all steps would exhaust memory
 * - Long computational chains with limited storage budget
 * - Trade-off between memory usage and recomputation cost
 *
 * @see revolve.h for the underlying scheduling algorithm
 * @see externfcts.h for external function differentiation
 */

#ifndef ADOLC_CHECKPOINTING_H
#define ADOLC_CHECKPOINTING_H

#include <adolc/adolcexport.h>
#include <adolc/internal/common.h>

class adouble;

using ADOLC_TimeStepFuncion = int(size_t dim_x, adouble *x);
using ADOLC_TimeStepFuncion_double = int(size_t dim_x, double *x);
using ADOLC_saveFct = void *(void);
using ADOLC_restoreFct = void(void *);

struct ADOLC_API CpInfos {
  // id of the outer tape, used to get checkpoint in the cp_fos_forward... and
  // reverse methods later
  size_t tapeId{0};
  ADOLC_TimeStepFuncion *function{nullptr};
  ADOLC_TimeStepFuncion_double *function_double{nullptr};
  ADOLC_saveFct *saveNonAdoubles{nullptr};
  ADOLC_restoreFct *restoreNonAdoubles{nullptr};
  size_t steps{0};
  size_t checkpoints{0};

  // This is the id of the tape that stores the checkpointing steps. This id
  // should not be confused with the id of the tape that calls
  // the checkpointing process later
  size_t cp_tape_id{0};
  int retaping{0}; /* != 0 forces retaping before every reverse step */

  size_t dim{0};           /* number of variables in input and output (n=m) */
  adouble *adp_x{nullptr}; /* input of the first step */
  adouble *adp_y{nullptr}; /* output of the last step; will be set by ADOLC */

  /* these are internal checkpointing variables => do not use */
  int check{0};
  int capo{0};
  int fine{0};
  int info{0};
  int currentCP{0};
  double *dp_internal_for{nullptr};
  double *dp_internal_rev{nullptr};
  double **dpp_internal_rev{nullptr};
  size_t index{0}; /* please do not change */
  char modeForward{0};
  char modeReverse{0};
  char *allmem{nullptr}; /* this is dummy to get externfcts and checkpointing
                   both use buffer_temp without a problem */
};

ADOLC_API
CpInfos *reg_timestep_fct(short tapeId, short cp_tape_id,
                          ADOLC_TimeStepFuncion timeStepFunction);

ADOLC_API int checkpointing(short tapeId, CpInfos *cpInfos);

class ADOLC_API CP_Context {
public:
  CP_Context(short tapeId, short cp_tape_id, ADOLC_TimeStepFuncion tsf) {
    cpInfos = reg_timestep_fct(tapeId, cp_tape_id, tsf);
  }
  ~CP_Context() = default;
  void setDoubleFct(ADOLC_TimeStepFuncion_double tsf) {
    cpInfos->function_double = tsf;
  }
  void setSaveFct(ADOLC_saveFct sf) { cpInfos->saveNonAdoubles = sf; }
  void setRestoreFct(ADOLC_restoreFct rf) { cpInfos->restoreNonAdoubles = rf; }
  void setNumberOfSteps(size_t number) { cpInfos->steps = number; }
  void setNumberOfCheckpoints(size_t number) { cpInfos->checkpoints = number; }
  void setDimensionXY(size_t dim) { cpInfos->dim = dim; }
  void setInput(adouble *x) { cpInfos->adp_x = x; }
  void setOutput(adouble *y) { cpInfos->adp_y = y; }
  void setAlwaysRetaping(bool state) {
    if (state)
      cpInfos->retaping = 1;
    else
      cpInfos->retaping = 0;
  }
  int checkpointing(short tapeId) { return ::checkpointing(tapeId, cpInfos); }

private:
  inline CP_Context() {}

  CpInfos *cpInfos;
};

/****************************************************************************/
#endif /* ADOLC_CHECKPOINTING_H */
