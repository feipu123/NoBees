/** @file */

#ifndef __TREESET_H
#define __TREESET_H

#include "Utility.h"

/**
 * A set implemented by balanced tree,
 * the elements being putted must guarantee operator'<'
 *
 * The iterator must iterates in the order defined by the operator'<' (from the smallest to the biggest)
 */

template <class E>
class TreeSet
{
public:
    class ConstIterator
    {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
        bool hasNext() { }

        /**
         * Returns a const reference to the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next() { }
    };

    class Iterator
    {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
        bool hasNext() { }

        /**
         * Returns a const reference the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next() { }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(logn)
         * @throw ElementNotExist
         */
        void remove() { }
    };

    /**
     * Constructs a new, empty tree set, sorted according to the natural ordering of its elements.
     */
    TreeSet() { }

    /**
     * Constructs a set containing the elements of the specified collection, in
     * the order they are returned by the collection's iterator.
     */
    template <class E2>
    explicit TreeSet(const E2& x) { }

    /**
     * Destructor
     */
    ~TreeSet() { }

    /**
     * Assignment operator
     */
    TreeSet& operator=(const TreeSet& x) { }

    /**
     * Copy-constructor
     */
    TreeSet(const TreeSet& x) { }

    /**
     * Returns an iterator over the elements in this set in proper sequence.
     */
    Iterator iterator() { }

    /**
     * Returns an CONST iterator over the elements in this set in proper sequence.
     */
    ConstIterator constIterator() const { }

    /**
     * Adds the specified element to this set if it is not already present.
     * Returns true if this set did not already contain the specified element.
     * O(logn)
     */
    bool add(const E& e) { }

    /**
     * Removes all of the elements from this set.
     */
    void clear() { }

    /**
     * Returns true if this set contains the specified element.
     * O(logn)
     */
    bool contains(const E& e) const { }

    /**
     * Returns a const reference to the first (lowest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& first() const { }

    /**
     * Returns true if this set contains no elements.
     * O(1)
     */
    bool isEmpty() const { }

    /**
     * Returns a const reference to the last (highest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& last() const { }

    /**
     * Removes the specified element from this set if it is present.
     * O(logn)
     */
    bool remove(const E& e) { }

    /**
     * Returns the number of elements in this set (its cardinality).
     * O(1)
     */
    int size() const { }
};
#endif
