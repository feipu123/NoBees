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
        node *next, *prev;
        node() {
            prev = next = NULL;
        }
        node(const T &x) {
            data = x;
            prev = next = NULL;
        }
    };
    node **array;
    int length;
    int siz;
public:
    class ConstIterator {
        const HashSet* parent;
        int pos;
        int counter;
        node *npos;
    public:
        ConstIterator(const HashSet* const x){
            counter = 0;
            pos = 0;
            parent = x;
            npos = x->array[0];
        }
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container
         */
        bool hasNext() {
            if (counter < parent->size()) return true;
            return false;
        }

        /**
         * Returns the next element in the iteration.
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        const T& next() {
            while (npos->next == NULL) {
                ++pos;
                npos = parent->array[pos];
            }
            npos = npos->next;
            ++counter;
            return npos->data;
        }
    };

    class Iterator {
        HashSet *parent;
        int pos;
        int counter;
        node *npos;
    public:
        Iterator(HashSet* x){
            counter = 0;
            pos = 0;
            parent = x;
            npos = x->array[0];
        }
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container.
         */
        bool hasNext() {
            if (counter < parent->size()) return true;
            return false;
        }

        /**
         * Returns the next element in the iteration.
         * O(n) for iterating through the container
         * @throw ElementNotExist
         */
        const T& next() {
            while (npos->next == NULL) {
                ++pos;
                npos = parent->array[pos];
            }
            npos = npos->next;
            ++counter;
            return npos->data;
        }

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator.
         * O(1)
         * @throw ElementNotExist
         */
        void remove() {
            if (parent->remove(npos->data)) --counter;
        }
    };

    /**
     * Constructs a empty set with your own default capacity
     */
    HashSet() {
        length = 101;
        siz = 0;
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
        array = new node* [c.length];
        length = c.length;
        siz = 0;
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
        ConstIterator iter = c.constIterator();
        while (iter.hasNext()) {
            add(iter.next());
        }
    }

    /**
     * Assignment operator
     */
    HashSet& operator=(const HashSet &c) {
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
        array = new node* [c.length];
        addAll(*this, c);
    }

    /**
     * Constructs a new set containing the elements in the specified
     * collection.
     */
    template<class C>
    explicit HashSet(const C& c) {
        array = new node* [11];
        siz = 0;
        length = 11;
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
        addAll(*this, c);
    }

    /**
     * Constructs a new, empty set; the backing HashMap instance has the
     * specified capacity
     */
    HashSet(int capacity) {
        siz = 0;
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
        int pos = H::hashcode(elem) % length;
        node *p = array[pos]->next;
        while (p != NULL && p->data != elem) p = p->next;
        if (p == NULL) {
            p = new node(elem);
            p->next = array[pos]->next;
            if (array[pos]->next != NULL) array[pos]->next->prev = p;
            array[pos]->next = p;
            p->prev = array[pos];
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
            p = array[i]->next;
            while (p != NULL) {
                q = p->next;
                delete p;
                p = q;
            }
            array[i]->next = NULL;
        }
        siz = 0;
    }

    /**
     * Returns true if this set contains the specified element.
     * O(1) for average
     */
    bool contains(const T& elem) const {
        int pos = H::hashcode(elem) % length;
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
    Iterator iterator() {
        Iterator *tmp = new Iterator(this);
        return *tmp;
    }

    /**
     * Returns an const iterator over the elements in this set.
     */
    ConstIterator constIterator() const {
        ConstIterator *tmp = new ConstIterator(this);
        return *tmp;
    }

    /**
     * Removes the specified element from this set if it is present.
     * O(1) for average
     */
    bool remove(const T& elem) {
        int pos = H::hashcode(elem) % length;
        node *p = array[pos];
        while (p->next != NULL && p->next->data != elem) p = p->next;
        if (p->next != NULL) {
            --siz;
            node *q = p->next;
            p->next = q->next;
            if (q->next != NULL) q->next->prev = p;
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

