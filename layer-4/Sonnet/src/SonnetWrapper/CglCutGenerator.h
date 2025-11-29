// Copyright (C) Jan-Willem Goossens
// This code is licensed under the terms of the Eclipse Public License (EPL).
/**
 * @file SonnetWrapper/CglCutGenerator.h
 * @brief .NET wrapper for CglCutGenerator (cut generator base class)
 *
 * C++/CLI wrapper exposing CGL cut generators to .NET languages.
 * Generic template CglCutGeneratorGeneric<T> for derived generators.
 *
 * @see CglProbing.h for probing cut generator
 * @see CbcCutGenerator.h for CBC integration
 */

#pragma once


#include <CglCutGenerator.hpp>
#include "Helpers.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace COIN
{	
	public ref class CglCutGenerator : WrapperAbstractBase<::CglCutGenerator>
	{
	public:
		static CglCutGenerator ^ CreateDerived(::CglCutGenerator *derived);
	};

	template<class T>
	public ref class CglCutGeneratorGeneric : CglCutGenerator
	{
	public:
		CglCutGeneratorGeneric()
		{
			Base = new T();
		}

	protected:
		property T * Base 
		{
			T * get() 
			{ 
				return dynamic_cast<T*>(CglCutGenerator::Base); 
			} 
		}
	};
}