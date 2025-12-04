/*
 *
 * Name:    CouenneSdpCuts.hpp
 * Authors: Pietro Belotti
 *          Andrea Qualizza
 * Purpose: wrapper for Couenne to insert sdpcuts
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneSdpCuts.hpp
 * @brief SDP-based cutting planes using matrix positive semidefiniteness
 *
 * Generates cuts exploiting that product matrices X = (x_ij) where x_ij = x_i*x_j
 * must be positive semidefinite. These cuts strengthen the LP relaxation beyond
 * what McCormick envelopes provide.
 *
 * @algorithm SDP Cut Generation (Qualizza-Belotti-Margot):
 *   Eigenvalue-based separation for PSD constraint X ⪰ 0:
 *   1. **Matrix construction:** Build X* from current LP (x_ij = w_ij values)
 *   2. **Eigendecomposition:** Compute X* = VΛV' (symmetric EVD)
 *   3. **Violation detection:** Find λ_min < 0 (X* not PSD)
 *   4. **Cut generation:** For eigenvector v with λ < 0:
 *      - Cut: v'Xv ≥ 0 (linear in original variables)
 *      - Translates to: Σ v_i·v_j·x_ij ≥ 0
 *   5. **Sparsification:** Remove small coefficients for stability
 *   6. Add cuts to LP, iterate
 *
 * @math PSD relaxation theory:
 *   For X ⪰ 0: v'Xv ≥ 0 for all v (infinite constraints)
 *   Current X* violates PSD if min eigenvalue λ < 0
 *   Corresponding v gives most violated constraint v'Xv ≥ 0
 *   These cuts are valid because X ⪰ 0 implies all v'Xv ≥ 0
 *
 * @complexity O(n³) per eigendecomposition (n = matrix dimension)
 *   Each minor generates up to numEigVec_ cuts
 *   Sparsification is O(n²) but improves cut quality
 *
 * @ref Qualizza, Belotti, Margot (2012). "Linear Programming Relaxations
 *      of Quadratically Constrained Quadratic Programs". Mixed Integer
 *      Nonlinear Programming, Springer.
 *
 * **Parameters:**
 * - numEigVec_: Number of eigenvectors to use (default: all)
 * - onlyNegEV_: Only use negative eigenvalues (default: yes)
 * - useSparsity_: Sparsify eigenvalues (default: no)
 * - fillMissingTerms_: Add fictitious aux vars for denser minors
 *
 * @see CouennePSDcon for explicit PSD constraints
 * @see CouenneExprMatrix for sparse matrix representation
 */
#ifndef CouenneSdpCuts_hpp
#define CouenneSdpCuts_hpp

#include "CglConfig.h"
#include "CglCutGenerator.hpp"
#include "BonRegisteredOptions.hpp"
#include "IpOptionsList.hpp"
#include "CouenneConfig.h"
#include "CouenneJournalist.hpp"

namespace Couenne {

  class CouenneProblem;
  class CouenneExprMatrix;

  ///
  /// These are cuts of the form
  ///
  /// a' X a >= 0
  ///
  /// where X is a matrix constrained to be PSD.
  ///
  /// Typical application is in problems with products forming a
  /// matrix of auxiliary variables X0 = (x_ij)_{i,j in N}, and x_ij
  /// is the auxiliary variable for x_i * x_j. After reformulation,
  /// matrices like X0 arise naturally and can be used to separate
  /// cuts that help strengthen the lower bound. See Sherali and
  /// Fraticelli for the base idea, and Qualizza, Belotti and Margot
  /// for an efficient rework and its implementation. Andrea
  /// Qualizza's code has been made open source and is used here
  /// (thanks Andrea!).
  ///

  class COUENNELIB_EXPORT CouenneSdpCuts: public CglCutGenerator {

  protected:

    CouenneProblem *problem_; ///< pointer to problem info

    bool doNotUse_; ///< after construction, true if there are enough
		    ///< product terms to justify application. If not,
		    ///< do not add this cut generator

    std::vector <CouenneExprMatrix *> minors_; ///< minors on which to apply cuts

    int numEigVec_; ///< number of eigenvectors to be used (default: n)

    bool onlyNegEV_; ///< only use negative eigenvalues (default: yes)

    bool useSparsity_; ///< Sparsify eigenvalues before writing inequality (default: no)

    bool fillMissingTerms_; ///< If minor not fully dense, create
			    ///< fictitious auxiliary variables that
			    ///< will be used in sdp cuts only (tighter
			    ///< than sdp cuts without)

  public:

    CouenneSdpCuts  (CouenneProblem *, JnlstPtr,
		     const Ipopt::SmartPtr <Ipopt::OptionsList>); ///< Constructor

    ~CouenneSdpCuts ();                                           ///< Destructor
    CouenneSdpCuts  &operator= (const CouenneSdpCuts &);          ///< Assignment
    CouenneSdpCuts             (const CouenneSdpCuts &);          ///< Copy constructor
    virtual CglCutGenerator *clone () const;                      ///< Cloning constructor

    const bool doNotUse () const {return doNotUse_;}

    /// The main CglCutGenerator
    virtual void generateCuts (const OsiSolverInterface &,
			       OsiCuts &,
			       const CglTreeInfo = CglTreeInfo ())
#if CGL_VERSION_MAJOR == 0 && CGL_VERSION_MINOR <= 57
    const
#endif
    ;

    /// Add list of options to be read from file
    static void registerOptions (Ipopt::SmartPtr <Bonmin::RegisteredOptions> roptions);

    // -----------------------------------------------------------------------------------------------------

    void updateSol();

  private:

    void genCutSingle (CouenneExprMatrix * const &,
		       const OsiSolverInterface &, OsiCuts &,
		       const CglTreeInfo = CglTreeInfo ()) const;

    void compareSparsify (const OsiSolverInterface &si,
			  int n, int m, const double *sol,
			  double *z, double *w,FILE *out) const;


    void sparsify2 (const int n,
		    const double *A, double **sparse_v_mat,
		    int *card_v_mat, int min_nz, int *evdec_num) const;

    void genSDPcut (const OsiSolverInterface &si,
		    OsiCuts &cs,
		    CouenneExprMatrix *XX,
		    double *v1, double *v2,
		    int **) const; // contains indices

    void additionalSDPcuts (const OsiSolverInterface &si,
			    OsiCuts &cs,
			    CouenneExprMatrix *minor,
			    int np, const double *A,
			    const double *vector, int **) const; // indices of matrix X'

    enum zero_type {POS_DELTA, SELECTED, VALID_DELTA};

    void zero_comp (const int ind_i, const double delta,
		    const int np, const int *selected,
		    int *loc_selected,
		    int *ploc_card_selected, int *ploc_card_new_selected,
		    double *ploc_lhs,
		    double *locmargin, double *locmat,
		    double *locv,
		    const int evidx, bool wise,
		    int *evdec_num,
		    double *recomp_gap,
		    double *threshold) const;

    void zero_unified (enum zero_type type,
		       const int np, const int *order,
		       const int * selected,
		       const int min_card_new_selected,
		       const double min_delta, const int start_point,
		       const int curr_i,
		       int *loc_selected,
		       int *ploc_card_selected,
		       int *ploc_card_new_selected,
		       double *ploc_lhs,
		       double *locmargin, double *locmat,
		       int *pnchanged,
		       double *locv,
		       const int evidx, bool wise,double *recomp_gap, double *threshold,
		       int *evdec_num) const;

    void add_v_cut(const int np,
		   const int *loc_selected,
		   const int loc_card_selected,
		   const double *locv,
		   const int init_card_selected, int *has_init_vect,
		   int *selected, int *pcard_selected,
		   int *pnew_selected,
		   double **sparse_v_mat,
		   int *pcard_v_mat) const;

    void update_sparsify_structures(const int np,
				    double *v, double* margin,
				    double *A, double *lhs, const int *zeroed,
				    int evidx, bool decompose, int *evdec_num) const;

    void sparsify (bool sparsify_new,
		   const int evidx, const double eigen_val,
		   const double *v, const int n,
		   const double *sol, double **sparse_v_mat,
		   int *card_v_mat,
		   int *evdec_num) const;
  };
}

#endif
