// Copyright (C) 2004, 2011 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter, Carl Laird       IBM    2004-09-27

/**
 * @file IpOrigIterationOutput.hpp
 * @brief Standard iteration output for original NLP problem
 *
 * OrigIterationOutput displays the per-iteration summary line
 * for the original (non-restoration) NLP problem.
 *
 * @algorithm Iteration Summary Output:
 *   WriteOutput() at each iteration:
 *   1. Check print frequency: skip if not due (by iter or time).
 *   2. Format iteration data into fixed-width columns.
 *   3. Append info string suffix if enabled (e.g., 'r' for resto).
 *   4. Write to Journalist at J_ITERSUMMARY level.
 *   First iteration writes header line with column names.
 *
 * @math Iteration metrics displayed:
 *   inf_pr = ||c(x)||∞ or ||r||₁/n (primal feasibility measure).
 *   inf_du = ||∇L||∞ scaled (dual feasibility / optimality).
 *   lg(mu) = log₁₀(μ) (barrier parameter in log scale).
 *   lg(rg) = log₁₀(δx) (regularization for inertia control).
 *   alpha_pr, alpha_du = primal/dual step lengths ∈ (0,1].
 *
 * @complexity O(1) per iteration (just formatting and printing).
 *   Controlled by print_frequency_iter and print_frequency_time options.
 *
 * Output format (one line per iteration):
 *   iter  objective  inf_pr  inf_du  lg(mu)  ||d||  lg(rg)  alpha_du  alpha_pr  ls
 *
 * Where:
 * - iter: Iteration number
 * - objective: Current objective value (scaled)
 * - inf_pr: Primal infeasibility (see inf_pr_output_)
 * - inf_du: Dual infeasibility
 * - lg(mu): Log10 of barrier parameter
 * - ||d||: Norm of search direction
 * - lg(rg): Log10 of regularization delta_x
 * - alpha_du: Dual step size
 * - alpha_pr: Primal step size
 * - ls: Line search trials
 *
 * Configuration:
 * - print_info_string_: Append info character (e.g., 'r' for resto)
 * - inf_pr_output_: What to show in inf_pr column
 * - print_frequency_iter_: Print every N iterations
 * - print_frequency_time_: Print every T seconds
 *
 * @see IpIterationOutput.hpp for base interface
 * @see IpRestoIterationOutput.hpp for restoration phase output
 */

#ifndef __IPORIGITERATIONOUTPUT_HPP__
#define __IPORIGITERATIONOUTPUT_HPP__

#include "IpIterationOutput.hpp"

namespace Ipopt
{

/** Class for the iteration summary output for the original NLP.
 */
class OrigIterationOutput: public IterationOutput
{
public:
   /**@name Constructors / Destructor */
   ///@{
   /** Default Constructor */
   OrigIterationOutput();

   /** Destructor */
   virtual ~OrigIterationOutput();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method to do all the summary output per iteration.
    *
    *  This include the one-line summary output as well as writing the
    *  details about the iterates if desired.
    */
   virtual void WriteOutput();

   /** Methods for OptionsList */
   ///@{
   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );
   ///@}

private:
   /**@name Default Compiler Generated Methods (Hidden to avoid
    * implicit creation/calling).
    *
    * These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Copy Constructor */
   OrigIterationOutput(
      const OrigIterationOutput&
   );

   /** Overloaded Assignment Operator */
   void operator=(
      const OrigIterationOutput&
   );
   ///@}

   /** Flag indicating weather info string should be printed at end
    *  of iteration summary line.
    */
   bool print_info_string_;

   /** Option indication what should be printed in inf_pr column */
   InfPrOutput inf_pr_output_;

   /** Option indicating at which iteration frequency the summary line should be printed */
   Index print_frequency_iter_;

   /** Option indicating at which time frequency the summary line should be printed */
   Number print_frequency_time_;
};

} // namespace Ipopt

#endif
