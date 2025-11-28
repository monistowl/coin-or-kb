/**
 * @file gravity/HiGHSProgram.h
 * @brief HiGHS solver interface for LP/MIP problems
 *
 * Adapts Gravity models to the HiGHS open-source LP/MIP solver.
 *
 * **HiGHSProgram Class:**
 * - Highs_mod: HighsModel (HiGHS model container)
 * - Highs_inst: Highs solver instance
 *
 * **Model Building:**
 * - prepare_model(): Initial conversion from Gravity
 * - fill_in_var_map(): Create variable mappings
 * - create_constraints(): Add linear constraints
 * - set_objective(): Set linear objective
 *
 * **Solving:**
 * - solve(relax, mipgap): Optimize with optional LP relaxation
 * - update_solution(): Copy solution back to Gravity model
 * - relax_model(): Remove integrality constraints
 *
 * **Supported Problem Types:**
 * - LP: Linear programming
 * - MIP: Mixed-integer programming
 *
 * @note HiGHS is an open-source solver that excels at large-scale LP
 *       and MIP problems with state-of-the-art performance.
 *
 * @see gravity/solver.h for unified solver dispatch
 */
#ifndef __Gravity____HiGHSProgram
#define __Gravity____HiGHSProgram

#ifdef USE_HiGHS
#include <Highs.h>
#endif
#include <gravity/model.h>
using namespace gravity;


class HiGHSProgram: public Program<>{
private:

    HighsModel          Highs_mod;/**< Highs model */
    Highs               Highs_inst;/**< Highs instance */
    
public:
    Model<>*            _model;
    int                 _output;
    HiGHSProgram();
    HiGHSProgram(Model<>* m);
    HiGHSProgram(const shared_ptr<Model<>>& m);
    ~HiGHSProgram();
    void reset_model();

    bool solve(bool relax = false, double mipgap = 0.01);
    void prepare_model();
    void update_model();
    void update_solution();
    void relax_model();

    void fill_in_var_map();
    void create_constraints();
    void set_objective();

    void print_constraints();
};


#endif /* defined(__Gravity____HiGHSProgram) */
