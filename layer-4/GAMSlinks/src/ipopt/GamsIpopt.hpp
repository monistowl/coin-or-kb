// Copyright (C) GAMS Development and others
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Author: Stefan Vigerske
/**
 * @file ipopt/GamsIpopt.hpp
 * @brief GAMS interface to Ipopt NLP solver
 *
 * Connects GAMS modeling environment to COIN-OR Ipopt.
 *
 * **GamsIpopt Class:**
 * - ipopt: SmartPtr to IpoptApplication
 * - nlp: GamsNLP problem representation
 * - Warmstart support for sequential solves
 *
 * @see GamsNLP.hpp for NLP problem representation
 * @see GamsJournal.hpp for message handling
 */

#ifndef GAMSIPOPT_HPP_
#define GAMSIPOPT_HPP_

typedef struct gmoRec* gmoHandle_t;
typedef struct gevRec* gevHandle_t;

#include "IpTNLP.hpp"
#include "IpIpoptApplication.hpp"
#include "GamsLinksConfig.h"
#include "GamsNLP.hpp"

#include <cstdint>

/** GAMS interface to Ipopt */
class DllExport GamsIpopt
{
   friend int main(int, char**);
private:
   struct gmoRec*         gmo;                /**< GAMS modeling object */
   struct gevRec*         gev;                /**< GAMS environment */

   /// whether we are IpoptH or Ipopt
   bool ipoptlicensed;
   /// Ipopt environment
   Ipopt::SmartPtr<Ipopt::IpoptApplication> ipopt;
   /// NLP to be solved
   Ipopt::SmartPtr<GamsNLP> nlp;

   /// whether next solve should be a warmstart (use ReOptimizeTNLP)
   bool warmstart;
   /// information which variable lower and upper bounds are present (bitflags)
   uint8_t* boundtype;

   /// sets up ipopt, allows for gev==NULL
   void setupIpopt();

public:
   GamsIpopt()
   : gmo(NULL),
     gev(NULL),
     ipoptlicensed(false),
     warmstart(false),
     boundtype(NULL)
   { }

   ~GamsIpopt()
   {
      delete[] boundtype;
   }

   int readyAPI(
      struct gmoRec*     gmo_
   );

   int callSolver();

   int modifyProblem();
};

extern "C" {

DllExport
int ipoCreate(
   void** Cptr,
   char*  msgBuf,
   int    msgBufLen
   );

DllExport
void ipoFree(
   void** Cptr
   );

DllExport
int ipoCallSolver(
   void* Cptr
   );

DllExport
int ipoReadyAPI(
   void*       Cptr,
   gmoHandle_t Gptr
   );

DllExport
int ipoHaveModifyProblem(
   void* Cptr
   );

DllExport
int ipoModifyProblem(
   void* Cptr
   );

} // extern "C"

#endif
