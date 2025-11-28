// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinPackedVectorBase.hpp
 * @brief Abstract base class for read-only sparse vector access
 *
 * Provides the read-only interface for sparse vectors stored as parallel
 * index/value arrays. This is the base class for CoinPackedVector (owning)
 * and CoinShallowPackedVector (non-owning reference).
 *
 * @see CoinPackedVector for a modifiable sparse vector
 * @see CoinShallowPackedVector for a lightweight view
 */

#ifndef CoinPackedVectorBase_H
#define CoinPackedVectorBase_H

#include <set>
#include <map>
#include "CoinPragma.hpp"
#include "CoinError.hpp"

class COINUTILSLIB_EXPORT CoinPackedVector;

/**
 * @brief Abstract base class providing read-only access to sparse vectors
 *
 * Since this class is abstract, no object of this type can be created.
 * The sole purpose is to provide const access to sparse vector data.
 * Sparse vectors store only non-zero elements as parallel arrays of
 * indices and values.
 *
 * @invariant All methods are const; derived classes manage actual storage
 */
class COINUTILSLIB_EXPORT CoinPackedVectorBase {
  
public:
  /**@name Virtual methods that the derived classes must provide */
  //@{
  /**
   * @brief Get the number of stored (non-zero) elements
   * @return Count of index/value pairs
   */
  virtual int getNumElements() const = 0;
  /**
   * @brief Get pointer to array of element indices
   * @return Pointer to indices array (may be null if empty)
   */
  virtual const int *getIndices() const = 0;
  /**
   * @brief Get pointer to array of element values
   * @return Pointer to values array (may be null if empty)
   */
  virtual const double *getElements() const = 0;
  //@}

  /**@name Methods related to whether duplicate-index checking is performed.

       If the checking for duplicate indices is turned off, then
       some CoinPackedVector methods may not work correctly if there
       are duplicate indices.
       Turning off the checking for duplicate indices may result in
       better run time performance.
      */
  //@{
  /** \brief Set to the argument value whether to test for duplicate indices
	      in the vector whenever they can occur.
       
       Calling this method with \p test set to true will trigger an immediate
       check for duplicate indices.
   */
  void setTestForDuplicateIndex(bool test) const;
  /** \brief Set to the argument value whether to test for duplicate indices
	      in the vector whenever they can occur BUT we know that right
	      now the vector has no duplicate indices.

       Calling this method with \p test set to true will <em>not</em> trigger
       an immediate check for duplicate indices; instead, it's assumed that
       the result of the test will be true.
   */
  void setTestForDuplicateIndexWhenTrue(bool test) const;
  /**
   * @brief Check if duplicate index testing is enabled
   * @return true if vector will be tested for duplicates when they can occur
   */
  bool testForDuplicateIndex() const { return testForDuplicateIndex_; }
  /**
   * @brief Disable all duplicate checking without exception handling
   */
  inline void setTestsOff() const
  {
    testForDuplicateIndex_ = false;
    testedDuplicateIndex_ = false;
  }
  //@}

  /**@name Methods for getting info on the packed vector as a full vector */
  //@{
  /**
   * @brief Convert sparse vector to dense format
   * @param denseSize Length of the dense vector to create
   * @return Newly allocated dense array (caller must delete[])
   * @note Indices beyond denseSize are ignored
   */
  double *denseVector(int denseSize) const;
  /**
   * @brief Access element by dense index
   * @param i Index in the conceptual dense vector
   * @return Value at index i, or zero if not stored
   * @note Very expensive; prefer denseVector() for multiple accesses
   */
  double operator[](int i) const;
  //@}

  /**@name Index methods */
  //@{
  /**
   * @brief Get the largest index in the sparse vector
   * @return Maximum index value, or -infinity if empty
   */
  int getMaxIndex() const;
  /**
   * @brief Get the smallest index in the sparse vector
   * @return Minimum index value, or +infinity if empty
   */
  int getMinIndex() const;

  /**
   * @brief Throw CoinError if duplicate indices exist
   * @param methodName Name of calling method (for error message)
   * @param className Name of calling class (for error message)
   */
  void duplicateIndex(const char *methodName = NULL,
    const char *className = NULL) const;

  /**
   * @brief Check if an index exists in the sparse vector
   * @param i Index to search for
   * @return true if index i is stored
   */
  bool isExistingIndex(int i) const;

  /**
   * @brief Find position of an index in the sparse storage
   * @param i Index to search for
   * @return Position in indices/elements arrays, or -1 if not found
   */
  int findIndex(int i) const;

  //@}

  /**@name Comparison operators on two packed vectors */
  //@{
  /** Equal. Returns true if vectors have same length and corresponding
       element of each vector is equal. */
  bool operator==(const CoinPackedVectorBase &rhs) const;
  /// Not equal
  bool operator!=(const CoinPackedVectorBase &rhs) const;

#if 0
   // LL: This should be implemented eventually. It is useful to have.
   /** Lexicographic comparisons of two packed vectors. Returns
       negative/0/positive depending on whether \c this is
       smaller/equal.greater than \c rhs */
   int lexCompare(const CoinPackedVectorBase& rhs);
#endif

  /** This method establishes an ordering on packed vectors. It is complete
       ordering, but not the same as lexicographic ordering. However, it is
       quick and dirty to compute and thus it is useful to keep packed vectors
       in a heap when all we care is to quickly check whether a particular
       vector is already in the heap or not. Returns negative/0/positive
       depending on whether \c this is smaller/equal.greater than \c rhs. */
  int compare(const CoinPackedVectorBase &rhs) const;

  /** equivalent - If shallow packed vector A & B are equivalent, then they
       are still equivalent no matter how they are sorted.
       In this method the FloatEqual function operator can be specified. The
       default equivalence test is that the entries are relatively equal.<br> 
       <strong>NOTE</strong>: This is a relatively expensive method as it
       sorts the two shallow packed vectors.
   */
  template < class FloatEqual >
  bool
  isEquivalent(const CoinPackedVectorBase &rhs, const FloatEqual &eq) const
  {
    if (getNumElements() != rhs.getNumElements())
      return false;

    duplicateIndex("equivalent", "CoinPackedVector");
    rhs.duplicateIndex("equivalent", "CoinPackedVector");

    std::map< int, double > mv;
    const int *inds = getIndices();
    const double *elems = getElements();
    int i;
    for (i = getNumElements() - 1; i >= 0; --i) {
      mv.insert(std::make_pair(inds[i], elems[i]));
    }

    std::map< int, double > mvRhs;
    inds = rhs.getIndices();
    elems = rhs.getElements();
    for (i = getNumElements() - 1; i >= 0; --i) {
      mvRhs.insert(std::make_pair(inds[i], elems[i]));
    }

    std::map< int, double >::const_iterator mvI = mv.begin();
    std::map< int, double >::const_iterator mvIlast = mv.end();
    std::map< int, double >::const_iterator mvIrhs = mvRhs.begin();
    while (mvI != mvIlast) {
      if (mvI->first != mvIrhs->first || !eq(mvI->second, mvIrhs->second))
        return false;
      ++mvI;
      ++mvIrhs;
    }
    return true;
  }

  bool isEquivalent(const CoinPackedVectorBase &rhs) const;
  //@}

  /**@name Arithmetic operators. */
  //@{
  /**
   * @brief Compute dot product with a dense vector
   * @param dense Pointer to dense vector (must have length >= max index + 1)
   * @return Sum of element[i] * dense[index[i]] for all stored elements
   */
  double dotProduct(const double *dense) const;

  /**
   * @brief Compute the 1-norm (sum of absolute values)
   * @return Sum of |element[i]| for all stored elements
   */
  double oneNorm() const;

  /**
   * @brief Compute the squared 2-norm
   * @return Sum of element[i]^2 for all stored elements
   */
  double normSquare() const;

  /**
   * @brief Compute the 2-norm (Euclidean length)
   * @return Square root of normSquare()
   */
  double twoNorm() const;

  /**
   * @brief Compute the infinity-norm (maximum absolute value)
   * @return Maximum |element[i]| across all stored elements
   */
  double infNorm() const;

  /**
   * @brief Compute the sum of all elements
   * @return Sum of element[i] for all stored elements
   */
  double sum() const;
  //@}

protected:
  /**@name Constructors, destructor
      <strong>NOTE</strong>: All constructors are protected. There's no need
      to expose them, after all, this is an abstract class. */
  //@{
  /** Default constructor. */
  CoinPackedVectorBase();

public:
  /** Destructor */
  virtual ~CoinPackedVectorBase();
  //@}

private:
  /**@name Disabled methods */
  //@{
  /** The copy constructor. <br>
       This must be at least protected, but we make it private. The reason is
       that when, say, a shallow packed vector is created, first the
       underlying class, it this one is constructed. However, at that point we
       don't know how much of the data members of this class we need to copy
       over. Therefore the copy constructor is not used. */
  CoinPackedVectorBase(const CoinPackedVectorBase &);
  /** This class provides <em>const</em> access to packed vectors, so there's
       no need to provide an assignment operator. */
  CoinPackedVectorBase &operator=(const CoinPackedVectorBase &);
  //@}

protected:
  /**@name Protected methods */
  //@{
  /// Find Maximum and Minimum Indices
  void findMaxMinIndices() const;

  /// Return indexSetPtr_ (create it if necessary).
  std::set< int > *indexSet(const char *methodName = NULL,
    const char *className = NULL) const;

  /// Delete the indexSet
  void clearIndexSet() const;
  void clearBase() const;
  void copyMaxMinIndex(const CoinPackedVectorBase &x) const
  {
    maxIndex_ = x.maxIndex_;
    minIndex_ = x.minIndex_;
  }
  //@}

private:
  /**@name Protected member data */
  //@{
  /// Contains max index value or -infinity
  mutable int maxIndex_;
  /// Contains minimum index value or infinity
  mutable int minIndex_;
  /** Store the indices in a set. This set is only created if it is needed.
       Its primary use is testing for duplicate indices.
    */
  mutable std::set< int > *indexSetPtr_;
  /** True if the vector should be tested for duplicate indices when they can
       occur. */
  mutable bool testForDuplicateIndex_;
  /** True if the vector has already been tested for duplicate indices. Most
       of the operations in CoinPackedVector preserves this flag. */
  mutable bool testedDuplicateIndex_;
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
