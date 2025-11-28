// (C) Copyright International Business Machines Corporation 2007
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors :
// Pierre Bonami, International Business Machines Corporation
//
// Date : 04/23/2007

/**
 * @file BonBabInfos.hpp
 * @brief Information passing between Bonmin B&B components
 *
 * Extends OsiAuxInfo to pass Bonmin-specific information between components
 * during branch-and-cut. Provides access to the Bab solver and solution info.
 *
 * **Key functionality:**
 * - babPtr_: Access to the Bab object (and via it, CbcModel)
 * - hasSolution(): Check if incumbent exists
 * - bestSolution_: Current best known solution (from AuxInfo)
 *
 * Used by cut generators and heuristics to query current B&B state.
 *
 * @see AuxInfo for the base class
 * @see Bab for the branch-and-bound driver
 */
#ifndef BonBabInfos_H
#define BonBabInfos_H
#include <stdlib.h>
#include "BonminConfig.h"
#include "BonAuxInfos.hpp"

namespace Bonmin
{
  class Bab;
  /** Bonmin class for passing info between components of branch-and-cuts.*/
  class BONMINLIB_EXPORT BabInfo : public Bonmin::AuxInfo
  {
  public:
    /** Default constructor.*/
    BabInfo(int type);

    /** Constructor from OsiBabSolver.*/
    BabInfo(const OsiBabSolver &other);

    /** Copy constructor.*/
    BabInfo(const BabInfo &other);

    /** Destructor.*/
    virtual ~BabInfo();

    /** Virtual copy constructor.*/
    virtual OsiAuxInfo * clone() const;

    /** Set pointer to the branch-and-bound algorithm (to access CbcModel).*/
    void setBabPtr(Bab * babPtr)
    {
      babPtr_ = babPtr;
    }

    /** Pointer to the branch-and-bound algorithm (to access CbcModel).*/
    Bab * babPtr()
    {
      return babPtr_;
    }

    bool hasSolution() const{
      return bestSolution_ != NULL;}
  protected:
    /** Pointer to branch-and-bound algorithm.*/
    Bab * babPtr_;
  };
}/* End namespace.*/

#endif
