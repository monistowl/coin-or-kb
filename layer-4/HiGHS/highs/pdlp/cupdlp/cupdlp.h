/**
 * @file cupdlp.h
 * @brief Master include for CUPDLP (CUDA/CPU PDLP) solver
 *
 * Aggregates all CUPDLP headers for the Primal-Dual Linear Programming
 * solver. CUPDLP implements the PDHG (Primal-Dual Hybrid Gradient)
 * algorithm for solving large-scale LPs using first-order methods.
 *
 * @see cupdlp_solver.h for main algorithm
 * @see cupdlp_defs.h for data structures
 */
#ifndef CUPDLP_H
#define CUPDLP_H

#include "pdlp/cupdlp/cupdlp_cs.h"
#include "pdlp/cupdlp/cupdlp_defs.h"
#include "pdlp/cupdlp/cupdlp_linalg.h"
#include "pdlp/cupdlp/cupdlp_proj.h"
#include "pdlp/cupdlp/cupdlp_restart.h"
#include "pdlp/cupdlp/cupdlp_scaling.h"
#include "pdlp/cupdlp/cupdlp_solver.h"
#include "pdlp/cupdlp/cupdlp_step.h"
#include "pdlp/cupdlp/cupdlp_utils.h"
#include "pdlp/cupdlp/glbopts.h"

#endif
