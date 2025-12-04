/**
 * @file BonOAMessages.hpp
 * @brief Message definitions for Outer Approximation algorithms
 * Copyright (C) Carnegie Mellon University 2006. All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * Defines message IDs and OaMessages class for output during
 * Outer Approximation cutting plane algorithms. Messages include
 * NLP solve status, bound updates, and iteration statistics.
 *
 * Authors: Pierre Bonami, Carnegie Mellon University
 * Date: July 15, 2005
 *
 * @see CoinMessages for COIN message framework
 * @see OaDecompositionBase for OA algorithm using these messages
 */

#ifndef OaMessages_H
#define OaMessages_H
#include "BonminConfig.h"
#include "CoinMessage.hpp"

namespace Bonmin
{
  enum OA_Message{
    FEASIBLE_NLP,
    INFEASIBLE_NLP,
    UPDATE_UB,
    SOLVED_LOCAL_SEARCH,
    LOCAL_SEARCH_ABORT,
    UPDATE_LB,
    ABORT,
    OASUCCESS,
    OAABORT,
    OA_STATS,
    LP_ERROR,
    PERIODIC_MSG,
    FP_DISTANCE,
    FP_MILP_VAL,
    FP_MAJOR_ITERATION,
    FP_MINOR_ITERATION,
    DUMMY_END
  };

  /** Output messages for Outer approximation cutting planes */
  class BONMINLIB_EXPORT OaMessages : public CoinMessages
  {
  public:
    OaMessages();
  };

} //end namespace Bonmin
#endif
