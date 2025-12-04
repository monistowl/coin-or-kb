/**
 * @file BonMsgUtils.hpp
 * @brief Message utilities and macros for Bonmin
 * This code is published under the Eclipse Public License.
 *
 * Provides ADD_MSG macro and message ID functions for standard,
 * warning, and error messages in the COIN message system.
 *
 * @see CoinMessages for the COIN messaging framework
 */

#ifndef BonMsgUtils_H
#define BonMsgUtils_H

#ifdef ADD_MSG
#error "Macro ADD_MSG already defined"    
#endif    
#define ADD_MSG(Id,Type,Level,MSG) addMessage(Id, CoinOneMessage( Type(Id), Level, MSG))

namespace Bonmin{
  inline int std_m(int n){return 1 + n;}
  inline int warn_m(int n) {return  3000 + n;}
  inline int err_m(int n) {return n + 6000;}
}
#endif

