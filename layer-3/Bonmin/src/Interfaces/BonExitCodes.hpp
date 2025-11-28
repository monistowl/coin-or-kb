/**
 * @file BonExitCodes.hpp
 * @brief Error codes for uncatchable errors in Bonmin
 *
 * Defines error codes for fatal errors that cannot be handled via exceptions.
 *
 * **Error codes:**
 * - ERROR_IN_AMPL_SUFFIXES (111): Invalid AMPL suffix specification
 * - UNSUPPORTED_CBC_OBJECT: CbcObject type not supported by Bonmin
 */
#ifndef BonExitCodes_H
#define BonExitCodes_H


namespace Bonmin{
 /** Some error codes for uncatachable errors.*/
enum ErrorCodes{
 ERROR_IN_AMPL_SUFFIXES = 111,
 UNSUPPORTED_CBC_OBJECT/** There is a CbcObject in the model which is not understood by Bonmin.*/
};
}
#endif
