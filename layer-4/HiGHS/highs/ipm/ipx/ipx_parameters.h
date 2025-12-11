/**
 * @file ipx_parameters.h
 * @brief Solver parameters and configuration options
 *
 * C-compatible structure for all IPX solver parameters:
 *
 * **Control:** display, logfile, time_limit
 * **Preprocessing:** dualize (-1=auto), scale
 * **IPM:** ipm_maxiter, tolerances (feasibility, optimality, drop)
 * **KKT Solver:** kkt_tol
 * **Basis:** crash_basis, dependency_tol, volume_tol, rows_per_slice
 * **LU:** lu_kernel, lu_pivottol
 * **Crossover:** run_crossover, tolerances
 * **Centring:** run_centring, max_centring_steps, ratio parameters
 *
 * @see ipx_internal.h for default values (Parameters struct)
 * @see control.h for parameter access during solve
 */
#ifndef IPX_PARAMETERS_H_
#define IPX_PARAMETERS_H_

#include "io/HighsIO.h"
#include "ipm/ipx/ipx_config.h"
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
struct ipx_parameters {
    /* Solver control */
    ipxint display;
    const char* logfile;
    double print_interval;
    double time_limit;
    bool analyse_basis_data;

    /* Preprocessing */
    ipxint dualize;
    ipxint scale;

    /* Interior point method */
    ipxint ipm_maxiter;
    double ipm_feasibility_tol;
    double ipm_optimality_tol;
    double ipm_drop_primal;
    double ipm_drop_dual;

    /* Linear solver */
    double kkt_tol;

    /* Basis construction in IPM */
    ipxint crash_basis;
    double dependency_tol;
    double volume_tol;
    ipxint rows_per_slice;
    ipxint maxskip_updates;

    /* LU factorization */
    ipxint lu_kernel;
    double lu_pivottol;

    /* Crossover */
    ipxint run_crossover;
    double start_crossover_tol;
    double pfeasibility_tol;
    double dfeasibility_tol;

    /* Debugging */
    ipxint debug;
    ipxint switchiter;
    ipxint stop_at_switch;
    ipxint update_heuristic;
    ipxint maxpasses;

    /* Centring */
    ipxint run_centring;
    ipxint max_centring_steps;
    double centring_ratio_tolerance;
    double centring_ratio_reduction;
    double centring_alpha_scaling;
    ipxint bad_products_tolerance;

    /* HiGHS logging parameters */
    bool highs_logging;
    bool timeless_log;
    const HighsLogOptions* log_options;
  
};

#ifdef __cplusplus
}
#endif

#endif  /* IPX_PARAMETERS_H_ */
