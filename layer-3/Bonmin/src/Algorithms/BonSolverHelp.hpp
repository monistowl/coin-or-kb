/**
 * @file BonSolverHelp.hpp
 * @brief Utility functions for OA and Feasibility Pump algorithms
 * Copyright (C) International Business Machines (IBM) 2006.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * Helper functions for manipulating solver state during OA decomposition
 * and Feasibility Pump: checking integer feasibility, fixing/relaxing
 * integer variables, comparing solutions, and installing cuts.
 *
 * Authors: Pierre Bonami, IBM
 * Date: December 7, 2006
 *
 * @see OaDecompositionBase for main OA algorithm
 * @see MinlpFeasPump for Feasibility Pump using these utilities
 */

#ifndef BonSolverHelp_H
#define BonSolverHelp_H

class OsiSolverInterface;
class OsiBranchingInformation;
class OsiObject;
class OsiCuts;

namespace Bonmin {
   /** Check for integer feasibility of a solution return true if it is feasible.*/
   bool integerFeasible(OsiSolverInterface & si, const OsiBranchingInformation & info,
                        double integer_tolerance,
                        OsiObject ** objects = 0, int nObjects = -1);

   /** Fix integer variables in si to their values in colsol.
       \remark colsol is assumed to be integer on the integer constrained variables.
    */
   void fixIntegers(OsiSolverInterface & si, const OsiBranchingInformation & info,
                    double integer_tolerance,
                    OsiObject ** objects = 0, int nObjects = -1);
   /** Relax integer variables in si.
    */
   void relaxIntegers(OsiSolverInterface & si, const OsiBranchingInformation & info,
                    double integer_tolerance,
                    OsiObject ** objects = 0, int nObjects = -1);
   /** Check if two solutions are the same on integer variables. */
   bool isDifferentOnIntegers(OsiSolverInterface &si,
                              OsiObject ** objects, int nObjects,
                              double integer_tolerance,
                              const double * colsol, const double * other);

   /** Install cuts in solver. */
   void installCuts(OsiSolverInterface &si,
                    const OsiCuts& cs, int numberCuts);

}
#endif

