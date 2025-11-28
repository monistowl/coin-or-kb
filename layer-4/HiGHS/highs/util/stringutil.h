/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file util/stringutil.h
 * @brief String manipulation utilities for file parsing
 *
 * Helper functions for trimming, case conversion, and tokenization.
 *
 * **Case Conversion:**
 * - tolower(): Convert string to lowercase in-place
 * - toupper(): Convert string to uppercase in-place
 *
 * **Trimming:**
 * - ltrim(): Remove leading whitespace
 * - rtrim(): Remove trailing whitespace
 * - trim(): Remove leading and trailing whitespace
 * - default_non_chars: Standard whitespace characters
 *
 * **Predicates:**
 * - is_empty(): Check if string contains only whitespace
 * - is_end(): Check if position is at end of content
 *
 * **Tokenization:**
 * - first_word(): Extract first word from position
 * - first_word_end(): Find end position of first word
 *
 * **Usage:**
 * Used by MPS/LP parsers for section and field extraction.
 *
 * @see io/HMpsFF.h for MPS parsing
 * @see io/FilereaderLp.h for LP parsing
 */
#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <ctype.h>

#include <cstring>
#include <string>

/*
void strRemoveWhitespace(char* str);
char* strClone(const char* str);
int strIsWhitespace(const char* str);
void strToLower(char* str);
void strTrim(char* str);
*/
// std::string& str_tolower(std::string s);

void tolower(std::string& str);
void toupper(std::string& str);

const std::string default_non_chars = "\t\n\v\f\r ";
std::string& ltrim(std::string& str,
                   const std::string& chars = default_non_chars);
std::string& rtrim(std::string& str,
                   const std::string& chars = default_non_chars);
std::string& trim(std::string& str,
                  const std::string& chars = default_non_chars);

bool is_empty(std::string& str, const std::string& chars = default_non_chars);
bool is_empty(char c, const std::string& chars = default_non_chars);
bool is_end(std::string& str, size_t end,
            const std::string& chars = default_non_chars);

// todo: replace with pair of references rather than string ret value to avoid
// copy and also using function below. or do it properly with iterators.
std::string first_word(std::string& str, size_t start);
size_t first_word_end(std::string& str, size_t start);

#endif
