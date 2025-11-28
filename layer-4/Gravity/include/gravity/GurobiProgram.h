/**
 * @file gravity/GurobiProgram.h
 * @brief Gurobi solver interface for LP/MIP/QP problems
 *
 * Adapts Gravity models to the Gurobi C++ API.
 *
 * **GurobiProgram Class:**
 * - grb_env: Gurobi environment
 * - grb_mod: Gurobi model
 * - _grb_vars: Mapping from Gravity vars to GRBVar
 * - _model: Pointer to Gravity Model
 *
 * **Model Building:**
 * - prepare_model(): Initial conversion from Gravity
 * - fill_in_grb_vmap(): Create GRBVar for each variable
 * - create_grb_constraints(): Add constraints (linear/quadratic)
 * - set_grb_objective(): Set objective function
 *
 * **Solving:**
 * - solve(relax, mipgap): Optimize with optional LP relaxation
 * - relax_model(): Remove integrality constraints
 * - update_solution(): Copy solution back to Gravity model
 *
 * **Supported Problem Types:**
 * - LP: Linear programming
 * - MIP: Mixed-integer programming
 * - QP: Quadratic programming (convex)
 * - MIQP: Mixed-integer QP
 *
 * @see gravity/solver.h for unified solver dispatch
 * @see gravity/model.h for Gravity model definition
 */
#ifndef __Gravity____GurobiProgram
#define __Gravity____GurobiProgram

#ifdef USE_GUROBI
#include <gurobi_c++.h>
#endif
#include <gravity/model.h>
using namespace gravity;


class GurobiProgram: public Program<>{
private:

    GRBModel* grb_mod;
    GRBEnv* grb_env;
    vector<GRBVar> _grb_vars; /** Mapping variables to Gurobi variables */
public:
    Model<>*    _model;
    int         _output;
    GurobiProgram();
    GurobiProgram(Model<>* m);
    GurobiProgram(const shared_ptr<Model<>>& m);
    ~GurobiProgram();
    void reset_model();

    bool solve(bool relax = false, double mipgap = 0.01);
    void prepare_model();
    void update_model();
    void update_solution();
    void relax_model();

    void fill_in_grb_vmap();
    void create_grb_constraints();
    void set_grb_objective();

    void print_constraints();
};


#endif /* defined(__Gravity____GurobiProgram) */
