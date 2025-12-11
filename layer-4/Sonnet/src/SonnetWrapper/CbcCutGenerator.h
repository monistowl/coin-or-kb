/**
 * @file CbcCutGenerator.h
 * @brief .NET wrapper for Cbc cut generator management
 *
 * Provides managed CbcCutGenerator class that wraps the native
 * ::CbcCutGenerator. Controls when and how CGL cutting planes
 * are generated during branch-and-cut search (frequency, depth,
 * at solution, etc.).
 *
 * @algorithm Cut Generator Scheduling in Branch-and-Cut (via CBC wrapper)
 * @math Controls cut generation policy during B&C:
 *       - howOften: Frequency (every n nodes, -1=root only, -100=off)
 *       - whatDepth: Maximum tree depth for cut generation
 *       - atSolution: Generate cuts when integer feasible found
 *       - normal/infeasible: When to invoke based on LP status
 *       Balances cut strength vs computational overhead.
 * @see CglCutGenerator.h for wrapped cut generator algorithms
 * @see CbcModel for branch-and-cut model using these generators
 */
// Copyright (C) Jan-Willem Goossens
// This code is licensed under the terms of the Eclipse Public License (EPL).

#pragma once

#include <CbcCutGenerator.hpp>

#include "CglCutGenerator.h"
#include "Helpers.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace COIN
{
	public ref class CbcCutGenerator : WrapperBase<::CbcCutGenerator>
	{
	internal:
		CbcCutGenerator(::CbcCutGenerator *copy)
			:WrapperBase(copy)
		{
		}

	public:
		CbcCutGenerator() { }
	
		/// Normal constructor
		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name,
            bool normal, bool atSolution,
            bool infeasible, int howOftenInsub,
            int whatDepth, int whatDepthInSub, int switchOffIfLessThan);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name,
            bool normal, bool atSolution,
            bool infeasible, int howOftenInsub,
            int whatDepth, int whatDepthInSub);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name,
            bool normal, bool atSolution,
            bool infeasible, int howOftenInsub,
            int whatDepth);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name,
            bool normal, bool atSolution,
            bool infeasible, int howOftenInsub);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name,
            bool normal, bool atSolution,
            bool infeasible);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name,
            bool normal, bool atSolution);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name,
            bool normal);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften, String ^ name);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator,
            int howOften);

		CbcCutGenerator(CbcModel ^ model, CglCutGenerator ^ generator);

		/// Get the \c CglCutGenerator corresponding to this \c CbcCutGenerator.
		CglCutGenerator ^ generator() 
		{
			return CglCutGenerator::CreateDerived(Base->generator());
		}
	};
}
