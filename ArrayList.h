/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "Utility.h"

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, it means
 * the length of the array of your inner implemention
 * For example, even if the capacity is 10, the method "isEmpty()" may still return true.
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class E>
class ArrayList
{
public:
    class ConstIterator
    {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(1)
         */
        bool hasNext() { }

        /**
         * Returns the next element in the iteration.
         * O(1)
         * @throw ElementNotExist
         */
        const E& next() { }
    };

    class Iterator
    {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(1)
         */
        bool hasNext() { }

        /**
         * Returns the next element in the iteration.
         * O(1)
         * @throw ElementNotExist
         */
        E& next() { }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(n)
         * @throw ElementNotExist
         */
        void remove() { }
    };

    /**
     * Constructs an empty list with an initial capacity of ten.
     */
    ArrayList() { }

    /**
     * Constructs a list containing the elements of the specified collection, in
     * the order they are returned by the collection's iterator.
     */
    template <class E2>
    explicit ArrayList(const E2& x) { }

    /**
     * Constructs an empty list with the specified initial capacity.
     */
    ArrayList(int initialCapacity) { }

    /**
     * Destructor
     */
    ~ArrayList() { }

    /**
     * Assignment operator
     */
    ArrayList& operator=(const ArrayList& x) { }

    /**
     * Copy-constructor
     */
    ArrayList(const ArrayList& x) { }

    /**
     * Returns an iterator over the elements in this list in proper sequence.
     */
    Iterator iterator() { }

    /**
     * Returns an CONST iterator over the elements in this list in proper sequence.
     */
    ConstIterator constIterator() const { }

    /**
     * Appends the specified element to the end of this list.
     * O(1)
     */
    bool add(const E& e) { }

    /**
     * Inserts the specified element at the specified position in this list.
     * The range of index is [0, size].
     * O(n)
     * @throw IndexOutOfBound
     */
    void add(int index, const E& element) { }

    /**
     * Removes all of the elements from this list.
     */
    void clear() { }

    /**
     * Returns true if this list contains the specified element.
     * O(n)
     */
    bool contains(const E& e) const { }

    /**
     * Increases the capacity of this ArrayList instance, if necessary, to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
     */
    void ensureCapacity(int minCapacity) { }

    /**
     * Returns a reference to the element at the specified position in this list.
     * O(1)
     * @throw IndexOutOfBound
     */
    E& get(int index) { }

    /**
     * Returns a const reference to the element at the specified position in this list.
     * O(1)
     * @throw IndexOutOfBound
     */
    const E& get(int index) const { }

    /**
     * Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * O(n)
     */
    int indexOf(const E& e) const { }

    /**
     * Returns true if this list contains no elements.
     * O(1)
     */
    bool isEmpty() const { }

    /**
     * Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * O(n)
     */
    int lastIndexOf(const E& e) const { }

    /**
     * Removes the element at the specified position in this list.
     * Returns the element that was removed from the list.
     * O(n)
     * @throw IndexOutOfBound
     */
    E removeIndex(int index) { }

    /**
     * Removes the first occurrence of the specified element from this list, if it is present.
     * O(n)
     */
    bool remove(const E& e) { }

    /**
     * Removes from this list all of the elements whose index is between fromIndex, inclusive, and toIndex, exclusive.
     * O(n)
     * @throw IndexOutOfBound
     */
    void removeRange(int fromIndex, int toIndex) { }

    /**
     * Replaces the element at the specified position in this list with the specified element.
     * Returns the element previously at the specified position.
     * O(1)
     * @throw IndexOutOfBound
     */
    E set(int index, const E& element) { }

    /**
     * Returns the number of elements in this list.
     * O(1)
     */
    int size() const { }

    /**
     * Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
     * O(n)
     * @throw IndexOutOfBound
     */
    ArrayList subList(int fromIndex, int toIndex) const { }
};
#endif

