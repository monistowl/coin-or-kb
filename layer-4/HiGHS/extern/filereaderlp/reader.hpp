/**
 * @file reader.hpp
 * @brief HiGHS QP solver component
 *
 * Part of HiGHS quadratic programming active set solver.
 */
#ifndef __READERLP_READER_HPP__
#define __READERLP_READER_HPP__

#include <string>

#include "model.hpp"

Model readinstance(std::string filename);

#endif
