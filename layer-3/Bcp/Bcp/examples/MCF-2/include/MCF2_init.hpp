/**
 * @file MCF2_init.hpp
 * @brief MCF BCP initialization
 *
 * @algorithm MCF2 Init: Process Factory
 *
 * USER_initialize creating MCF2_tm, MCF2_lp, and MCF2_packer.
 */
#ifndef MCF2_init_hpp
#define MCF2_init_hpp

#include "BCP_USER.hpp"

class MCF2_init : public USER_initialize {
public:
  virtual BCP_user_pack* packer_init(BCP_user_class* p);
  virtual BCP_tm_user* tm_init(BCP_tm_prob& p,
			       const int argnum, const char * const * arglist);
  virtual BCP_lp_user* lp_init(BCP_lp_prob& p);
};

#endif
