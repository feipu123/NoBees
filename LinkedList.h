/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "Utility.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T> class LinkedList {
public:
    class ConstIterator {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(1).
         */
        bool hasNext() {}

        /**
         * Returns the next element in the iteration.
         * O(1).
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T& next() {}
    };

    class Iterator {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(1).
         */
        bool hasNext() {}

        /**
         * Returns the next element in the iteration.
         * O(1).
         * @throw ElementNotExist exception when hasNext() == false
         */
        T& next() {}

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator
         * O(1).
         * @throw ElementNotExist
         */
        void remove() {}
    };

    /**
     * Constructs an empty list
     */
    LinkedList() {}

    /**
     * Copy constructor
     * You may utilize the ``addAll'' function from Utility.h
     */
    LinkedList(const LinkedList<T> &c) {}

    /**
     * Assignment operator
     * You may utilize the ``addAll'' function from Utility.h
     */
    LinkedList<T>& operator=(const LinkedList<T> &c) {}

    /**
     * Constructs a list containing the elements of the specified
     * collection, in the order they are returned by the collection's
     * const iterator.
     * You may utilize the ``addAll'' function from Utility.h
     */
    template <class C> LinkedList(const C& c) {}

    /**
     * Desturctor
     */
    ~LinkedList() {}

    /**
     * Inserts the specified element at the specified position in
     * this list.
     * O(n)
     * @throw IndexOutOfBound exception when index is out of bound
     */
    void add(int index, const T& elem) {}

    /**
     * Appends the specified element to the end of this list.
     * O(1).
     * Always returns true;
     */
    bool add(const T& elem) {}

    /**
     * Inserts the specified element at the beginning of this list.
     * O(1).
     */
    void addFirst(const T& elem) {}

    /**
     * Removes all of the elements from this list.
     * O(n).
     */
    void clear() {}

    /**
     * Returns true if this list contains the specified element.
     * O(n).
     */
    bool contains(const T& elem) const {}

    /**
     * Returns a reference to the element at the specified position.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T& get(int index) {}

    /**
     * Returns a const reference to the element at the specified position.
     * O(n).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const {}

    /**
     * Returns a reference to the first element.
     * O(1).
     * @throw ElementNotExist
     */
    T& getFirst() {}

    /**
     * Returns a const reference to the first element.
     * O(1).
     * @throw ElementNotExist
     */
    const T& getFirst() const {}

    /**
     * Returns a reference to the last element.
     * O(1).
     * @throw ElementNotExist
     */
    T& getLast() {}

    /**
     * Returns a const reference to the last element.
     * O(1).
     * @throw ElementNotExist
     */
    const T& getLast() const {}

    /**
     * Returns the index of the first occurrence of the specified element
     * O(1).
     * in this list, or -1 if this list does not contain the element.
     */
    int indexOf(const T& elem) const {}

    /**
     * Returns true if this list contains no elements.
     * O(1).
     */
    bool isEmpty() const {}

    /**
     * Returns an iterator
     * O(1).
     */
    Iterator iterator() {}

    /**
     * Returns an const iterator
     * O(1).
     */
    ConstIterator constIterator() const {}

    /**
     * Removes the element at the specified position in this list.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T removeIndex(int index) {}

    /**
     * Removes the first occurrence of the specified element from this
     * O(n).
     * list, if it is present.
     */
    bool remove(const T& elem) {}

    /**
     * Removes and returns the first element from this list.
     * O(1).
     * @throw ElementNotExist
     */
    T removeFirst() { }

    /**
     * Removes and returns the last element from this list.
     * O(1).
     * @throw ElementNotExist
     */
    T removeLast() {}

    /**
     * Replaces the element at the specified position in this list with
     * the specified element.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T set(int index, const T& elem) {}

    /**
     * Returns the number of elements in this list.
     */
    int size() const {}

    /**
     * Returns a view of the portion of this list between the specified
     * fromIndex, inclusive, and toIndex, exclusive.
     * O(n).
     * @throw IndexOutOfBound
     */
    LinkedList<T> subList(int fromIndex, int toIndex);
};
#endif

