//
//  Utils.h
//  Gravity
//
//  Created by Hassan on Oct 1st 2017
//
/**
 * @file gravity/utils.h
 * @brief Utility functions for timing, printing, and sign operations
 *
 * General utilities used throughout the Gravity library.
 *
 * **Timing:**
 * - get_wall_time(): Wall clock time in seconds
 * - get_cpu_time(): CPU time in seconds
 *
 * **Printing:**
 * - clean_print(): Format value with sign for display
 * - RESET macro: Terminal color reset code
 *
 * **Parallelism:**
 * - bounds(parts, mem): Split memory/indices into chunks
 *   for parallel processing
 *
 * **Sign Arithmetic:**
 * - reverse(Sign): Negate sign
 * - sign_add(s1, s2): Result sign of sum
 * - sign_product(s1, s2): Result sign of product
 *
 * **Time Indexing:**
 * - time(p1, p2): Create time-indexed set [p1, p2]
 * - time(idx1, ...): Variadic time index construction
 *
 * **Complex Number Support:**
 * - Comparison operators for Cpx type
 *
 * @see gravity/types.h for Sign enum
 */
#ifndef Gravity___Utils_h
#define Gravity___Utils_h
//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#ifdef USE_OPT_PARSER
#include <optionParser.hpp>
#endif
#include <vector>
#include <gravity/types.h>
#include <gravity/GravityConfig.h>
double get_wall_time();
double get_cpu_time();

std::string clean_print(bool pos, const std::string& v, bool brackets = false);



#ifdef USE_OPT_PARSER
op::OptionParser readOptions(int argc, char * argv[]);
#endif


//Split "mem" into "parts", e.g. if mem = 10 and parts = 4 you will have: 0,2,4,6,10
//if possible the function will split mem into equal chuncks, if not
//the last chunck will be slightly larger
std::vector<size_t> bounds(unsigned parts, size_t mem);


gravity::Sign reverse(gravity::Sign s);

gravity::Sign sign_add(gravity::Sign s1, gravity::Sign s2);

gravity::Sign sign_product(gravity::Sign s1, gravity::Sign s2);

gravity::indices time(unsigned p1 ,unsigned p2);

template<typename... Args>
gravity::indices time(std::string idx1, Args&&... args) {
    gravity::indices res("time");
    res.init(idx1,args...);
    res._time_extended = true;
    return res;
}


bool operator <(const gravity::Cpx& lhs, const gravity::Cpx& rhs);

bool operator >(const gravity::Cpx& lhs, const gravity::Cpx& rhs);

bool operator <=(const gravity::Cpx& lhs, const gravity::Cpx& rhs);

bool operator >=(const gravity::Cpx& lhs, const gravity::Cpx& rhs);

namespace gravity{
    
//    int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
    
    set<int> get_phases(string phases);
//    Cpx min (const Cpx& a, const Cpx& b);
//    Cpx max (const Cpx& a, const Cpx& b);
    
    template<class T, typename enable_if<is_same<T,gravity::Cpx>::value>::type* = nullptr>
    T min (const T& a, const T& b){
        gravity::Cpx res(a);
        if (res.real()>b.real()) {
            res.real(b.real());
        }
        if (res.imag()>b.imag()) {
            res.imag(b.imag());
        }
        return res;
    }
    
    template<class T, typename enable_if<is_same<T,gravity::Cpx>::value>::type* = nullptr>
    T max(const T& a, const T& b){
        gravity::Cpx res(a);
        if (res.real()<b.real()) {
            res.real(b.real());
        }
        if (res.imag()<b.imag()) {
            res.imag(b.imag());
        }
        return res;
    }
    
//    template<class T, typename enable_if<is_arithmetic<T>::value>::type* = nullptr>
//    T min (const T& a, const T& b){
//        return std::min(a,b);
//    }
//    
//    
//    template<class T, typename enable_if<is_arithmetic<T>::value>::type* = nullptr>
//    T max(const T& a, const T& b){
//        return std::max(a,b);
//    }
}

#endif
