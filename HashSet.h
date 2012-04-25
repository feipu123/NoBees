/** @file */
#ifndef __HASHSET_H
#define __HASHSET_H

#include "Utility.h"

/**
 * A HashSet holds elements using a hash table, providing facilities
 * to insert, remove an element into the container and search an
 * element within the container efficiently.
 *
 * We don't require an order in the iteration, but you should
 * guarantee all elements will be iterated.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashcode'',
 * which takes a parameter of type T and returns a value of type int.
 * For example, the following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashcode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashSet<int, Hashint> hash;
 * @endcode
 */
template <class T, class H>
class HashSet {
    struct node{
        T data;
        node *next;
        node() {
            next = NULL;
        }
        node(const T &x) {
            data = x;
            next = NULL;
        }
    }
    node **array;
    int length;
    int siz;
    int (*key) (const T &x);
public:
    class ConstIterator {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container
         */
        bool hasNext() {}

        /**
         * Returns the next element in the iteration.
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        const T& next() {}
    };

    class Iterator {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container.
         */
        bool hasNext() {}

        /**
         * Returns the next element in the iteration.
         * O(n) for iterating through the container
         * @throw ElementNotExist
         */
        const T& next() {}

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator.
         * O(1)
         * @throw ElementNotExist
         */
        void remove() {}
    };

    /**
     * Constructs a empty set with your own default capacity
     */
    HashSet() {
        length = 11;
        siz = 0;
        key = H::hashcode;
        array = new node* [length];
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
    }

    /**
     * Destructor
     */
    ~HashSet() {
        node *p, *q;
        for (int i = 0; i < length; ++i) {
            p = array[i];
            while (p != NULL) {
                q = p->next;
                delete p;
                p = q;
            }
        }
        delete []array;
    }

    /**
     * Copy constructor
     */
    HashSet(const HashSet &c) {
        /*array = new node* [c.length];
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
            node *p = array[i];
            node *q = c.a
            while (p != NULL) {

            }
        }*/
    }

    /**
     * Assignment operator
     */
    HashSet& operator=(const HashSet &c) {}

    /**
     * Constructs a new set containing the elements in the specified
     * collection.
     */
    template<class C> explicit HashSet(const C& c) {}

    /**
     * Constructs a new, empty set; the backing HashMap instance has the
     * specified capacity
     */
    HashSet(int capacity) {
        siz = 0;
        key = H::hashcode;
        length = capacity;
        array = new node* [length];
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
    }

    /**
     * Adds the specified element to this set if it is not already present.
     * Returns false if element is previously in the set.
     * O(1) for average
     */
    bool add(const T& elem) {
        int pos = key(elem);
        node *p = array[pos]->next;
        while (p != NULL && p->data != elem) p = p->next;
        if (p == NULL) {
            p = new node(elem);
            p->next = array[pos]->next;
            array[pos]->next = p;
            ++siz;
            return true;
        }
        return false;
    }

    /**
     * Removes all of the elements from this set.
     */
    void clear() {
        node *p, *q;
        for (int i = 0; i < length; ++i) {
            p = array[i];
            while (p != NULL) {
                q = p->next;
                delete p;
                p = q;
            }
        }
        siz = 0;
    }

    /**
     * Returns true if this set contains the specified element.
     * O(1) for average
     */
    bool contains(const T& elem) const {
        int pos = key(elem) % length;
        node *p = array[pos];
        while (p->next != NULL && p->next->data != elem) p = p->next;
        if (p->next != NULL) return true;
        return false;
    }

    /**
     * Returns true if this set contains no elements.
     * O(1)
     */
    bool isEmpty() const {
        return (siz == 0);
    }

    /**
     * Returns an iterator over the elements in this set.
     */
    Iterator iterator() {}

    /**
     * Returns an const iterator over the elements in this set.
     */
    ConstIterator constIterator() const {}

    /**
     * Removes the specified element from this set if it is present.
     * O(1) for average
     */
    bool remove(const T& elem) {
        int pos = key(elem) % length;
        node *p = array[pos];
        while (p->next != NULL && p->next->data != elem) p = p->next;
        if (p->next != NULL) {
            --siz;
            node *q = p->next;
            p->next = q->next;
            delete q;
            return true;
        }
        return false;
    }

    /**
     * Returns the number of elements in this set (its cardinality).
     * O(1)
     */
    int size() const {
        return siz;
    }
};

#endif

