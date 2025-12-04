/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     revolve.h
 Revision: $Id$
 Contents: optimal binomial checkpointing adapted for ADOL-C

 Copyright (c) Andrea Walther, Andreas Griewank, Andreas Kowarz

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

---------------------------------------------------------------------------*/

/**
 * @file revolve.h
 * @brief Optimal binomial checkpointing for memory-efficient reverse mode
 *
 * Implements the revolve algorithm (Griewank & Walther) for optimal
 * checkpoint placement in reverse mode automatic differentiation.
 *
 * @algorithm Revolve - Optimal Checkpointing Schedule:
 * Computes the provably optimal sequence of checkpoint operations to
 * minimize total recomputation while staying within memory budget.
 *
 * STATE MACHINE:
 * The revolve() function returns action codes that drive the outer loop:
 *
 *   revolve_advance   → Run forward computation from 'capo' to new position
 *   revolve_takeshot  → Save current state to checkpoint slot 'check'
 *   revolve_restore   → Restore state from checkpoint slot 'check'
 *   revolve_firsturn  → Begin reverse sweep (first reverse step)
 *   revolve_youturn   → Continue reverse sweep (subsequent steps)
 *   revolve_terminate → Adjoint computation complete
 *
 * TYPICAL USAGE PATTERN:
 * ```
 * while ((action = revolve(&check, &capo, &fine, snaps, &info)) != terminate) {
 *   switch(action) {
 *     case advance:   forward_sweep(capo, fine); break;
 *     case takeshot:  save_checkpoint(check); break;
 *     case restore:   load_checkpoint(check); break;
 *     case firsturn:
 *     case youturn:   reverse_step(); fine--; break;
 *   }
 * }
 * ```
 *
 * @math Binomial Bound:
 * With s checkpoint slots and r repetitions allowed, revolve handles exactly:
 *   N_max = C(s+r, r) = (s+r)! / (s! · r!)
 * steps optimally.
 *
 * For r=1: N_max = s+1 (minimal repetition)
 * For large r: N_max grows super-exponentially in s
 *
 * The schedule minimizes total forward evaluations subject to checkpoint
 * budget constraint. This is achieved by placing checkpoints at binomial
 * coefficients: if you have s checkpoints for N steps, place first checkpoint
 * at position C(s-1+r,r)/C(s+r,r) · N.
 *
 * @complexity Total forward evaluations: O(r·N) for N steps with r repetitions.
 * With s = O(log N) checkpoints and r = O(log N), achieves O(N log N) work.
 * Space: O(s · state_size) for checkpoint storage.
 *
 * @ref Griewank & Walther (2000). "Algorithm 799: Revolve". ACM TOMS.
 * @ref Stumm & Walther (2010). "New Algorithms for Optimal Online
 *   Checkpointing". SIAM J. Sci. Comput.
 *
 * @see checkpointing.h for ADOL-C checkpointing interface
 */
#ifndef ADOLC_REVOLVE_H
#define ADOLC_REVOLVE_H

#include <adolc/internal/common.h>

struct revolve_nums {
  int advances{0};
  int takeshots{0};
  int commands{0};
  int turn{0};
  int reps{0};
  int range{0};
  int ch[ADOLC_CHECKUP] = {0};
  int oldsnaps{0};
  int oldfine{0};
};

inline revolve_nums revolve_numbers;

inline revolve_nums &get_revolve_numbers() { return revolve_numbers; }

enum revolve_action {
  revolve_advance,
  revolve_takeshot,
  revolve_restore,
  revolve_firsturn,
  revolve_youturn,
  revolve_terminate,
  revolve_error
};

int maxrange(int ss, int tt);

int adjustsize(int *steps, int *snaps, int *reps);

enum revolve_action revolve(int *check, int *capo, int *fine, int snaps,
                            int *info);

#endif // ADOLC_REVOLVE_H
