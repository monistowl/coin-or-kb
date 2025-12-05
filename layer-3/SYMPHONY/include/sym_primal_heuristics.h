/*===========================================================================*/
/*                                                                           */
/* This file is part of the SYMPHONY MILP Solver Framework.                  */
/*                                                                           */
/* SYMPHONY was jointly developed by Ted Ralphs (ted@lehigh.edu) and         */
/* Laci Ladanyi (ladanyi@us.ibm.com).                                        */
/*                                                                           */
/* The author of this file is Ashutosh Mahajan                               */
/*                                                                           */
/* (c) Copyright 2006-2022 Lehigh University. All Rights Reserved.           */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

/**
 * @file sym_primal_heuristics.h
 * @brief Primal heuristics for finding feasible solutions
 *
 * Collection of heuristics to find feasible MIP solutions quickly.
 * Called during B&C to improve incumbent and provide bounds.
 *
 * @algorithm Feasibility Pump (Fischetti, Glover, Lodi 2005):
 * Alternate between LP and rounding to find feasible integer point.
 *
 * ALGORITHM:
 *   1. Solve LP relaxation → x_LP
 *   2. Round to nearest integer: x̃ = round(x_LP)
 *   3. If x̃ feasible: DONE
 *   4. Solve: min ||x - x̃|| s.t. Ax ≥ b (pump LP)
 *   5. Goto 2 until feasible or iteration limit
 *
 * @math Pump LP objective:
 *   min Σ_i∈B |x_i - x̃_i| + Σ_i∈I |x_i - x̃_i|
 *   Linearized via auxiliary x+, x-: |x-x̃| = x+ + x-
 *
 * ANTI-CYCLING:
 *   - alpha parameter blends distance with original obj
 *   - Track previous x̃ to detect cycles
 *   - Random perturbation if cycling detected
 *
 * @algorithm Diving Heuristics (ds_*):
 * Iteratively fix variables and solve LP.
 *
 * TYPES:
 *   - Fractional: Fix most fractional variable
 *   - Guided: Fix toward incumbent solution
 *   - Euclidean: Fix to minimize distance to integer
 *   - Rank-based: Use variable ranking for fixing order
 *
 * ALGORITHM:
 *   1. Solve LP → identify fractional variables
 *   2. Select variable x_k by diving strategy
 *   3. Fix x_k to floor or ceil
 *   4. Resolve LP, repeat until integer or infeasible
 *   5. If infeasible, backtrack and try opposite fixing
 *
 * @algorithm Local Branching (Fischetti & Lodi 2003):
 * Search neighborhood around incumbent.
 *
 * @math Local branching cut:
 *   Σ_{i: x*_i=0} x_i + Σ_{i: x*_i=1} (1-x_i) ≤ k
 *   Hamming distance from x* at most k
 *
 * Add cut to MIP and solve restricted sub-problem.
 *
 * @algorithm RINS (Danna, Rothberg, Le Pape 2005):
 * Relaxation Induced Neighborhood Search.
 *
 * restricted_search() with fr_force_feasible():
 *   Fix variables where LP = incumbent
 *   Free variables where LP ≠ incumbent
 *   Solve resulting smaller MIP
 *
 * @complexity
 *   Feasibility pump: O(iterations × LP_solve)
 *   Diving: O(n × LP_solve) worst case
 *   Local branching: O(sub-MIP solve)
 *
 * @ref Fischetti, M., Glover, F., & Lodi, A. (2005).
 *   "The feasibility pump". Math Programming 104:91-104.
 *
 * @see sym_lp_params.h for heuristic parameters (fp_*, fr_*, rs_*, lb_*, ds_*)
 * @see sym_lp.h for LP process calling heuristics
 */
/*
 * TODO:
 * change ifdef _FEASI.. to ifdef _HEURISTICS
 */

#ifndef _PRIMAL_HEURISTICS_H
#define _PRIMAL_HEURISTICS_H
#include "sym_lp_solver.h"
#include "sym_lp.h"
#include "sym_types.h"

/* feasibility pump */
typedef struct FP_VARS {
   char          is_bin;
   char          is_int;
   int           xplus;
   int           xminus;
}FPvars;

typedef struct FP_DATA {
   FPvars      **fp_vars;       /* an array of fp_vars */
   int           n0;            /* no. of vars in orignial lp */
   int           m0;
   int           n;             /* no. of vars in pumping lp */
   int           m;             /* no. of constraints in pumping lp */
   int           iter;
   int           numNonBinInts;
   int           numInts;
   int          *index_list;
   int         **x_bar_ind;     /* array containing previous x_bars */
   double      **x_bar_val;     /* array containing previous x_bars */
   int          *x_bar_len;     /* rounded x_lp */
   double       *alpha_p;       /* previous alphas */
   double       *x_lp;          /* solution of pumpling lp */
   double       *x_ip;          /* rounded x_lp */
   double       *mip_obj;       /* normalized original obj */
   double       *obj;           /* obj function for pumping lp */
   char          can_check_sos; /* whether we can check sos rows while fixing bin vars */
   char         *sos_row_filled;/*to keep track of the sos variables while flipping */
   char         *sos_var_fixed_zero;/*to keep track of the sos variables while flipping */ 
   double        norm_c;        /* norm of mip_obj */
   double        alpha;
   double        alpha_decr;
   int           verbosity;
   double        flip_fraction;
   double        norm;
   int           iterd;
   int           single_iter_limit; 
   int           total_iter_limit;
}FPdata;

/*  solution pool */
int sp_add_solution PROTO((lp_prob *p, int cnt, int *indices, double *values, double obj_value, int bc_index));
int sp_delete_solution PROTO((sp_desc *sp, int position));
int sp_is_solution_in_sp PROTO((lp_prob *p, int cnt, int *indices, double *values, double obj_value));
#ifdef SYM_COMPILE_IN_LP
int sp_initialize(tm_prob *tm);
#endif
int sp_free_sp(sp_desc *sp);

/* feasibility pump */
int feasibility_pump (lp_prob *p, char *found_better_solution, double &solution_value, 
		      double *colSolution, double *betterSolution);		      
int fp_round (lp_prob *p, FPdata *fp_data, LPdata *lp_data);
int fp_is_feasible (LPdata *lp_data, const CoinPackedMatrix *matrix, const double *r_low, const double *r_up, FPdata *fp_data, char *is_feasible );
int fp_initialize_lp_solver(lp_prob *p, LPdata *new_lp_data, FPdata *fp_data, 
			    double *colSolution);
int fp_solve_lp(LPdata *lp_data, FPdata *fp_data, char *is_feasible) ;
int fp_should_call_fp(lp_prob *p, int branching, int *should_call, 
		      char is_last_iter, double t_lb);
int fp_add_obj_row(LPdata *new_lp_data, int n, const double *obj, double rhs);
int fp_can_sos_var_fix(lp_prob *p, FPdata *fp_data, int ind, int *filled_row_count);
int fp_fix_sos_var(lp_prob *p, FPdata *fp_data, int ind);

/* rounding */
int round_solution PROTO((lp_prob *p, LPdata *lp_data, double *solution_value, 
			  double *betterSolution, double t_lb));
/* shifting */
int shift_solution PROTO((lp_prob *p, LPdata *lp_data, double *solution_value, 
			  double *betterSolution, double t_lb));
/* local search */
int apply_local_search PROTO((lp_prob *p, double *solution_value, 
			      double *col_solution, double *better_solution, double *dual_gap, double t_lb));
int local_search PROTO((lp_prob *p, double *solution_value, 
			double *col_solution, double *better_solution, double t_lb));

/* diving search */
int diving_search PROTO((lp_prob *p, double *solutionValue, double *colSolution,
			 double *betterSolution, char is_last_iter, double t_lb));
int ds_fix_vars PROTO((lp_prob *p, LPdata *diving_lp, double *x, 
		       int *frac_ind, int frac_cnt, int d_fixed_cnt, int fix_incr_cnt, 
		       int d_type, double *obj, double *ip_sol, double *x_rank,
		       char *direction, int *min_ind, char *min_dir, char should_fix));

int ds_get_frac_vars PROTO((LPdata *lp_data, double *x, int *indices, 
			    int *frac_ip_cnt, int *int_ip_cnt));  

int ds_fix_common_vars PROTO((LPdata * lp_data, var_desc **vars, double *ip_sol, double *x));

/* restricted search */

int restricted_search PROTO((lp_prob *p, double *solution_value, double *colSolution,  
			     double *betterSolution, int fr_mode, double t_lb));

int fr_force_feasible(lp_prob *p, char use_base, int *sym_fixed_int_cnt, int *sym_fixed_c_cnt,
		      char *sym_fixed_type, double *sym_fixed_val, int *max_int_fix, int *max_c_fix);

/* local branching */
int lbranching_search PROTO((lp_prob *p, double *solution_value, double *colSolution,  
			     double *betterSolution, double t_lb));

int resize_tmp1_arrays(LPdata *lp_data, int new_size);

//sym_environment * lp_to_sym PROTO((lp_prob *p, LPdata *lp_data, char use_base));
sym_environment * lp_to_sym PROTO ((lp_prob *p, LPdata *lp_data, char use_base, int sym_fixed_cnt,
				    char *sym_fixed_type, double *sym_fixed_val, 
				    double *sym_fixed_offset, int *unfix_nz, int *new_ind));
#endif
