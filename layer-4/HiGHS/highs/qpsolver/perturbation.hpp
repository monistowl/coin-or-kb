/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file perturbation.hpp
 * @brief HiGHS QP perturbation
 *
 * Perturbation for handling degeneracy in QP.
 * Adds small shifts to ensure unique optima.
 */
#ifndef __SRC_LIB_PERTURBATION_HPP__
#define __SRC_LIB_PERTURBATION_HPP__

#include "runtime.hpp"

void perturb(Runtime& rt);

#endif
