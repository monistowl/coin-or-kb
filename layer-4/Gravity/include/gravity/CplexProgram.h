//
//  CplexProgram.h
//  Gravity
//
//  Created by Hassan Hijazi on 06/06/2017.
//
//
/**
 * @file gravity/CplexProgram.h
 * @brief IBM CPLEX solver interface for LP/MIP/QP problems
 *
 * Adapts Gravity models to the IBM ILOG CPLEX C++ API.
 *
 * **CplexProgram Class:**
 * - _cplex_env: IloEnv (CPLEX environment)
 * - _cplex_model: IloModel (CPLEX model)
 * - _cplex_vars: Mapping from Gravity vars to IloNumVarArray
 *
 * **Model Building:**
 * - prepare_model(): Initial conversion from Gravity
 * - fill_in_cplex_vars(): Create IloNumVar for each variable
 * - create_cplex_constraints(): Add constraints
 * - set_cplex_objective(): Set objective function
 *
 * **Solving:**
 * - solve(relax, mipgap): Optimize with optional LP relaxation
 * - warm_start(): Initialize from current solution
 * - relax_model(): Remove integrality constraints
 *
 * **Callback Support:**
 * - _cplex_contextmask: Context for callback location
 * - create_callback(): Set up user callbacks
 *
 * @see gravity/solver.h for unified solver dispatch
 * @see gravity/model.h for Gravity model definition
 */
#ifndef CplexProgram_h
#define CplexProgram_h

#include <stdio.h>

#ifndef __Gravity____CplexProgram
#define __Gravity____CplexProgram

#ifdef USE_CPLEX
#include <ilcplex/ilocplex.h>
#endif
#include <gravity/model.h>
//#include <gravity/CplexCallback.h>

using namespace gravity;   

class CplexProgram: public Program<>{
private:
    
    shared_ptr<IloModel> _cplex_model;
    shared_ptr<IloEnv> _cplex_env;
    vector<IloNumVarArray>   _cplex_vars; /** Mapping variables to Cplex variables */
    IloObjective        _cplex_obj;
    
    CPXLONG _cplex_contextmask = 0; /** Context mask for the callback location */
//    CplexCallback _cplex_callback; /** instantiating a callback object */
    
public:
    Model<>* _model;
    int _output;
    CplexProgram();
    CplexProgram(Model<>* m);    
    void update_model();
    void reset_model();
    
    IloModel& get_cplex_model() const{
        return *_cplex_model;
    }
    
    bool solve(bool relax=false, double mipgap = 0.01);
    void prepare_model();
    void relax_model();
    void warm_start();
    void fill_in_cplex_vars();
    void create_cplex_constraints();
    void set_cplex_objective();
    void create_callback();
    
    void print_constraints();
};


#endif /* defined(__Gravity____CplexProgram) */
#endif /* CplexProgram_hpp */
