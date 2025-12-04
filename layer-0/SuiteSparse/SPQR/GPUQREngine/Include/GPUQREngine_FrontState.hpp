/**
 * @file GPUQREngine_FrontState.hpp
 * @brief Finite state machine for front factorization lifecycle
 * Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
 * and Sanjay Ranka. GPL-2.0+ license.
 *
 * FrontState enum defines 9-state FSM: ALLOCATE_WAIT (0) → ASSEMBLE_S (1) →
 * CHILD_WAIT (2) → FACTORIZE (3) → FACTORIZE_COMPLETE (4) → PARENT_WAIT (5) →
 * PUSH_ASSEMBLE (6) → CLEANUP (7) → DONE (8). Transitions driven by
 * FillWorkQueue and PostProcessing. Scheduler uses states to coordinate work.
 *
 * @see GPUQREngine_Front.hpp uses FrontState
 * @see GPUQREngine_Scheduler.hpp manages state transitions
 */

// =============================================================================
// === GPUQREngine/Include/GPUQREngine_FrontState.hpp ==========================
// =============================================================================

// GPUQREngine, Copyright (c) 2013, Timothy A Davis, Sencer Nuri Yeralan,
// and Sanjay Ranka.  All Rights Reserved.
// SPDX-License-Identifier: GPL-2.0+

//------------------------------------------------------------------------------
//
// The front state refers to the finite state machine model for factorizing
// fronts using GPUQREngine.
//
// A front will progress through these fronts, as dictated by
//  FillWorkQueue and PostProcessing codes.
//
// =============================================================================

#ifndef GPUQRENGINE_FRONTSTATE_HPP
#define GPUQRENGINE_FRONTSTATE_HPP

enum FrontState
{
    ALLOCATE_WAIT = 0,      // Front not allocated yet
    ASSEMBLE_S = 1,         // Assembling rows of S
    CHILD_WAIT = 2,         // Waiting for children to be finished
    FACTORIZE = 3,          // Factorization under way
    FACTORIZE_COMPLETE = 4, // Records an event to mark the end of the
                            // factorize
    PARENT_WAIT = 5,        // Waits for the parent to be allocated
    PUSH_ASSEMBLE = 6,      // Pushes contribution blocks to the parent
    CLEANUP = 7,            // Frees the front
    DONE = 8                // Front totally finished
};

#endif
