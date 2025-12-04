// Copyright (C) 2005, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
/**
 * @file RegisteredTNLP.hpp
 * @brief Registration system for scalable test problems
 *
 * RegisteredTNLP: factory pattern for creating test problem instances.
 * Allows selecting test problems by name with configurable size.
 * Manages Luksan-Vlcek and Mittelmann problem instantiation.
 */
//
// Authors:  Andreas Waechter            IBM    2005-10-20

#ifndef __REGISTEREDTNLPS_HPP__
#define __REGISTEREDTNLPS_HPP__

#include "IpTNLP.hpp"
#include <map>

using namespace Ipopt;

class RegisteredTNLP: public TNLP
{
public:
   RegisteredTNLP()
      : interrupted_(false)
   { }

   /** Initialize internal parameters.
    *
    *  @return false, if N has an invalid value
    */
   virtual bool InitializeProblem(
      Index N  /**< determines problems size */
   ) = 0;

   bool intermediate_callback(
      AlgorithmMode              /*mode*/,
      Index                      /*iter*/,
      Number                     /*obj_value*/,
      Number                     /*inf_pr*/,
      Number                     /*inf_du*/,
      Number                     /*mu*/,
      Number                     /*d_norm*/,
      Number                     /*regularization_size*/,
      Number                     /*alpha_du*/,
      Number                     /*alpha_pr*/,
      Index                      /*ls_trials*/,
      const IpoptData*           /*ip_data*/,
      IpoptCalculatedQuantities* /*ip_cq*/
   )
   {
      /* returning false makes Ipopt stop */
      return !interrupted_;
   }

   bool interrupted_;
};

class RegisteredTNLPs
{
public:
   RegisteredTNLPs(
      const SmartPtr<RegisteredTNLP>& tnlp,
      const std::string&              name
   )
   {
      RegisterTNLP(tnlp, name);
   }

   virtual ~RegisteredTNLPs()
   { }

   static SmartPtr<RegisteredTNLP> GetTNLP(
      const std::string& name
   );

   static void PrintRegisteredProblems();

private:
   void RegisterTNLP(
      const SmartPtr<RegisteredTNLP>& tnlp,
      const std::string&              name
   );

   SmartPtr<RegisteredTNLP> tnlp_;
};

#define REGISTER_TNLP(class_constructor, name) \
class RegisteredTNLP_Setup_ ## name : public RegisteredTNLPs \
{ \
public: \
  RegisteredTNLP_Setup_ ## name() \
    : \
    RegisteredTNLPs(new class_constructor, #name) \
  { } \
  RegisteredTNLP_Setup_ ## name* KeepCompilerFromRemovingThis(); \
}; \
 \
RegisteredTNLP_Setup_ ## name RegisteredTNLP_Setup_ ## name ## instance_; \
RegisteredTNLP_Setup_ ## name* \
RegisteredTNLP_Setup_ ## name::KeepCompilerFromRemovingThis() \
{ return &RegisteredTNLP_Setup_ ## name ## instance_; }

//static RegisteredTNLP_Setup_ ## name RegisteredTNLP_Setup_ ## name ## instance
#endif
