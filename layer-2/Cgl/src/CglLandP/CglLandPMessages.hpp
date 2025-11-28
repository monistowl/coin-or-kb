/**
 * @file CglLandPMessages.hpp
 * @brief Message handler for Lift-and-Project simplex
 * @author Pierre Bonami (CNRS, Aix-Marseille Universites)
 *
 * Defines LAP_messages enum for L&P algorithm status reporting:
 * - Separating, FoundImprovingRow, FoundBestImprovingCol
 * - PivotLog, FinishedOptimal, HitLimit
 * - Warning messages for numerical issues
 *
 * LandPMessages class extends CoinMessages for log formatting.
 *
 * @see CglLandPSimplex for the algorithm using these messages
 * @see CglLandP for the main cut generator
 * @see CoinMessageHandler for message infrastructure
 *
 * Date:     02/23/08
 *
 * Copyright (C) 2005-2009, Pierre Bonami and others.  All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 */
//---------------------------------------------------------------------------
#ifndef CglLandPMessages_H
#define CglLandPMessages_H

#include "CoinMessage.hpp"
#include "CoinMessageHandler.hpp"

namespace LAP
{
/** Forward declaration of class to store extra debug data.*/
class DebugData;
/** Types of messages for lift-and-project simplex.*/
enum LAP_messages
{
    Separating,
    FoundImprovingRow,
    FoundBestImprovingCol,
    WarnFailedBestImprovingCol,
    LogHead,
    PivotLog,
    FinishedOptimal,
    HitLimit,
    NumberNegRc,
    NumberZeroRc,
    NumberPosRc,
    WeightsStats,
    WarnBadSigmaComputation,
    WarnBadRowComputation,
    WarnGiveUpRow,
    PivotFailedSigmaUnchanged,
    PivotFailedSigmaIncreased,
    FailedSigmaIncreased,
    WarnBadRhsComputation,
    WarnFailedPivotTol,
    WarnFailedPivotIIf,
    RoundStats,
    CutStat,
    DUMMY_END
};
/** Message handler for lift-and-project simplex. */
class LandPMessages : public CoinMessages
{
public:

    /** Constructor */
    LandPMessages();
};
}
#endif
