/**
 * @file CoinWarmStart.h
 * @brief .NET wrapper for solver warm start information
 *
 * Wraps ::CoinWarmStart for persisting and restoring solver
 * state (basis information). Enables efficient re-optimization
 * after small problem modifications without restarting from scratch.
 *
 * @algorithm Simplex Warm Starting (via CoinWarmStart wrapper)
 * @math Stores basis status (basic/nonbasic) for each variable/constraint.
 *       Warm start: given optimal basis B for Ax=b, if A'x=b' differs
 *       slightly, use B as starting point for dual simplex to restore
 *       optimality in O(changed_rows) pivots vs O(m) from scratch.
 * @see OsiSolverInterface for getWarmStart/setWarmStart methods
 */
// Copyright (C) Jan-Willem Goossens
// This code is licensed under the terms of the Eclipse Public License (EPL).

#pragma once

#include <CoinWarmStart.hpp>
#include "Helpers.h"

namespace COIN
{
	public ref class CoinWarmStart : WrapperBase<::CoinWarmStart>
	{
	internal:
		CoinWarmStart(::CoinWarmStart *warmStart)
			:WrapperBase(warmStart)
		{
		}
	};
}