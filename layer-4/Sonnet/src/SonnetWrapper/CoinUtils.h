/**
 * @file CoinUtils.h
 * @brief .NET wrapper for CoinUtils helper functions
 *
 * Provides managed access to low-level COIN-OR utilities:
 * array allocation/deallocation, bulk copy/zero operations,
 * and CPU time measurement. Useful for .NET code that needs
 * to work directly with native memory buffers.
 *
 * @see array_handler.h for related array utilities
 */
// Copyright (C) Jan-Willem Goossens
// This code is licensed under the terms of the Eclipse Public License (EPL).

#pragma once

#include <CoinHelperFunctions.hpp>
#include <CoinTime.hpp>

namespace COIN
{
	public ref class CoinUtils
	{
	private:
		CoinUtils(void);

	public:
		static double* NewDoubleArray(const int size);
		static int* NewIntArray(const int size);

		static void DeleteArray(double *to);
		static void DeleteArray(int *to);

		static void CoinDisjointCopyN(const double * from, const int size, double * to);
		static void CoinZeroN(double * to, const int size);

		static void CoinDisjointCopyN(array<double>^ from, const int size, array<double> ^to);
		static void CoinZeroN(array<double>^ to, const int size);

		static double CoinCpuTime();
	};
}