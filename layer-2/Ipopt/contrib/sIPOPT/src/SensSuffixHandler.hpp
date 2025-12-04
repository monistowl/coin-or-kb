// Copyright 2009, 2011 Hans Pirnay
// All Rights Reserved.
// This code is published under the Eclipse Public License.
/**
 * @file SensSuffixHandler.hpp
 * @brief sIPOPT AMPL suffix handler
 *
 * SensSuffixHandler: processes AMPL suffixes for sensitivity analysis.
 * Reads parameter indices and perturbation values from .row/.col suffixes.
 * Enables AMPL-based sensitivity specification.
 */
//
// Date   : 2009-08-01

#ifndef __SENS_ASSUFFIXHANDLER_HPP__
#define __SENS_ASSUFFIXHANDLER_HPP__

#include "IpReferenced.hpp"
#include <vector>
#include <string>

namespace Ipopt
{

/** This class is the interface for all classes that can return indices.
 *
 *  The implementation for Ampl is done in the MetadataMeasurement class.
 */
class SuffixHandler: public ReferencedObject
{
public:
   SuffixHandler()
   { }

   virtual ~SuffixHandler()
   { }

   virtual std::vector<Index> GetIntegerSuffix(
      std::string suffix_string
   ) = 0;
};

}

#endif
