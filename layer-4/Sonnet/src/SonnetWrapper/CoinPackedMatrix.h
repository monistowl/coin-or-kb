// Copyright (C) Jan-Willem Goossens
// All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).
/**
 * @file SonnetWrapper/CoinPackedMatrix.h
 * @brief .NET wrapper for CoinPackedMatrix (sparse matrix)
 *
 * C++/CLI wrapper exposing CoinUtils sparse matrix to .NET languages.
 *
 * @algorithm Sparse Matrix Storage (via CoinPackedMatrix wrapper)
 * @math Compressed sparse column/row format: values[], indices[], starts[].
 *       getVector(i) returns i-th column/row as shallow view (no copy).
 *       O(nnz) storage, O(1) column access, O(nnz_col) element iteration.
 * @see CoinShallowPackedVector.h for vector wrapper
 */

#pragma once

#include "CoinShallowPackedVector.h"
#include "Helpers.h"

#include <CoinPackedMatrix.hpp>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace COIN
{
	//////////////////////////////////////////////////////
	///// CoinPackedMatrix
	public ref class CoinPackedMatrix : WrapperBase<::CoinPackedMatrix>
	{
	public:
		CoinPackedMatrix() {}

#ifndef CLP_NO_VECTOR  
		/** Return the i'th vector in matrix. */
		CoinShallowPackedVector ^ getVector(int i)
		{
			::CoinShallowPackedVector *tmp = new ::CoinShallowPackedVector(Base->getVector(i));
			CoinShallowPackedVector ^result = gcnew CoinShallowPackedVector(tmp);
			result->deleteBase = true;
			return result;
		}
#endif

	internal:
		CoinPackedMatrix(const ::CoinPackedMatrix *obj)
			: WrapperBase(obj)
		{
		}
	};
}