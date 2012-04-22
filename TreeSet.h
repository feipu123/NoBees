#ifndef __TREESET_H
#define __TREESET_H

#include "Utility.h"
#include <cstdlib>

/**
 * A set implemented by balanced tree,
 * the elements being putted must guarantee operator'<'
 *
 * The iterator must iterates in the order defined by the operator'<' (from the smallest to the biggest)
 */

template <class E>
class TreeSet {
    struct node{
        E data;
        int aux;
        node *lf, *rh, *fa;
        node() {
            srand(time(NULL));
            aux = rand();
        }
    }
    node *root;
    node *Null;
    int siz;
    node::node(E x) {
        srand(time(NULL));
        aux = rand();
        data = x;
        lf = rh = Null;
    }
public:
    void RotateL(Node* &x) {
        Node *y = x->rh;
        x->rh = y->lf;
        y->lf = x;
        x = y;
    }
    void RotateR(Node* &x) {
        Node *y = x->lf;
        x->lf = y->rh;
        y->rh = x;
        x = y;
    }
    void insert(node* &nd, E &e) {
        if (nd == Null) {
            nd = new node(e);
            ++size;
            return;
        }
        if (e < nd->data) {
            Insert(nd->lf, e);
            if (nd->lf->aux < nd->aux) RotateR(nd);
        }
        else {
            Insert(nd->rh, e);
            if (nd->rh->aux < nd->aux) RotateL(nd);
        }
    }
    class ConstIterator {
        E value;
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
        bool hasNext() {
        }

        /**
         * Returns a const reference to the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next() { }
    };

    class Iterator {
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
        void remove() {

        }
    };

    /**
     * Constructs a new, empty tree set, sorted according to the natural ordering of its elements.
     */
    TreeSet() {
        Null = new node();
        root = Null;
        siz = 0;
    }

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
    TreeSet& operator=(const TreeSet& x) {
        clear();
    }

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

    bool add(const E& e) {
        if (contains(e)) return false;
        insert(root, e);
        return true;
    }

    /**
     * Removes all of the elements from this set.
     */
    void clear() { }

    /**
     * Returns true if this set contains the specified element.
     * O(logn)
     */
    bool contains(const E& e) const {

    }

    /**
     * Returns a const reference to the first (lowest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& first() const {
        node *tmp = root;
        while (tmp->lf != Null) {
            tmp = tmp->lf;
        }
        return tmp->data;
    }

    /**
     * Returns true if this set contains no elements.
     * O(1)
     */
    bool isEmpty() const {
        return (siz == 0);
    }

    /**
     * Returns a const reference to the last (highest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& last() const {
        node *tmp = root;
        while (tmp->rh != Null) {
            tmp = tmp->rh;
        }
        return tmp->data;
    }

    /**
     * Removes the specified element from this set if it is present.
     * O(logn)
     */
    bool remove(const E& e) { }

    /**
     * Returns the number of elements in this set (its cardinality).
     * O(1)
     */
    int size() const {
        return siz;
    }
};
#endif
