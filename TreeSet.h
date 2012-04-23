#ifndef __TREESET_H
#define __TREESET_H

#include "Utility.h"
#include <cstdlib>
#include <ctime>

/**
 * A set implemented by balanced tree,
 * the elements being putted must guarantee operator'<'
 *
 * The iterator must iterates in the order defined by the operator'<' (from the smallest to the biggest)
 */

template <class E>
class TreeSet {
public:
static const int MAXN = 1000000000;
    struct node{
        E data;
        int aux;
        node *lf, *rh;
        node() {
            srand(time(NULL));
            aux = rand() % MAXN;
            lf = rh = NULL;
        }
        node(E x) {
            data = x;
            srand(time(NULL));
            aux = rand() % MAXN;
            lf = rh = NULL;
        }
        node(const node* const y) {
            data = y->data;
            lf = y->lf;
            rh = y->rh;
            aux = y->aux;
        }
    };
private:
    node *Root;
    int siz;
public:
    void RotateL(node* &x) {
        node *y = x->rh;
        x->rh = y->lf;
        y->lf = x;
        x = y;
    }
    void RotateR(node* &x) {
        node *y = x->lf;
        x->lf = y->rh;
        y->rh = x;
        x = y;
    }
    void Insert(node* &nd, const E &e) {
        if (nd == NULL) {
            nd = new node(e);
            ++siz;
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
    void Delete(node* &nd, const E &e) {
        if (nd == NULL) return;
        if (nd->data == e) {
            if (nd->lf == NULL || nd->rh == NULL) {
                if (nd->lf == NULL) {
                    --siz;
                    node *tmp = nd;
                    nd = nd->rh;
                    delete tmp;
                }
                else {
                    --siz;
                    node *tmp = nd;
                    nd = nd->lf;
                    delete tmp;
                }
            }
            else {
                if (nd->lf->aux < nd->rh->aux) {
                    RotateR(nd);
                    Delete(nd->rh, e);
                }
                else {
                    RotateL(nd);
                    Delete(nd->lf, e);
                }
            }
        }
        else {
            if (e < nd->data) Delete(nd->lf, e);
            else Delete(nd->rh, e);
        }
    }
    class ConstIterator {
        TreeSet *parent;
        E value;
    public:
        ConstIterator(TreeSet* const x) {
            parent = x;
            node *p = x->Root;
            while (p->lf != NULL) {
                p = p->lf;
            }
            if (p != NULL) value = p->data;
            else throw;
        }

        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
        bool hasNext() {
            if (value < parent->last()) return true;
            return false;
        }

        /**
         * Returns a const reference to the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next() {
            node *p = parent->getRoot();
            node *tag = p;
            while (p->data != value) {
                tag = p;
                if (value < p->data) p = p->lf;
                else p = p->rh;
            }
            if (p->rh != NULL) {
                p = p->rh;
                while (p->lf != NULL) {
                    p = p->lf;
                }
            }
            if (p->data != value) tag = p;
            value = tag->data;
            return value;
        }
    };

    class Iterator {
        TreeSet *parent;
        E value;
    public:
        Iterator(TreeSet* const x) {
            parent = x;
            node *p = x->getRoot();
            while (p->lf != NULL) {
                p = p->lf;
            }
            if (p != NULL) value = p->data;
            else throw;
        }

        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
        bool hasNext() {
            if (value < parent->last()) return true;
            return false;
        }

        /**
         * Returns a const reference the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next() {
            node *p = parent->getRoot();
            node *tag = p;
            while (p->data != value) {
                tag = p;
                if (value < p->data) p = p->lf;
                else p = p->rh;
            }
            if (p->rh != NULL) {
                p = p->rh;
                while (p->lf != NULL) {
                    p = p->lf;
                }
            }
            if (value < p->data) tag = p;
            value = tag->data;
            return value;
        }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(logn)
         * @throw ElementNotExist
         */
        void remove() {
            node *p = parent->getRoot();
            node *tag = p;
            while (p->data != value) {
                tag = p;
                if (value < p->data) p = p->lf;
                else p = p->rh;
            }
            if (p->lf != NULL) {
                p = p->lf;
                while (p->rh != NULL) {
                    p = p->rh;
                }
            }
            if (p->data < value) tag = p;
            E tmp = value;
            value = tag->data;
            parent->remove(tmp);
        }
    };

    /**
     * Constructs a new, empty tree set, sorted according to the natural ordering of its elements.
     */
    TreeSet() {
        Root = NULL;
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
    ~TreeSet() {
        clear();
    }

    /**
     * Assignment operator
     */
    void makeTree(node* &x, node* y){
        if (y == NULL) {
            x = NULL;
            return;
        }
        x = new node(y);
        makeTree(x->lf, y->lf);
        makeTree(x->rh, y->rh);
    }

    TreeSet& operator=(const TreeSet& x) {
        clear();
        siz = x->size();
        makeTree(Root, x->getRoot());
        return *this;
    }

    /**
     * Copy-constructor
     */


    TreeSet(const TreeSet& x) {
        makeTree(Root, x.getRoot());
    }

    /**
     * Returns an iterator over the elements in this set in proper sequence.
     */
    Iterator iterator() {
        Iterator *tmp = new Iterator(this);
    return *tmp;
    }

    /**
     * Returns an CONST iterator over the elements in this set in proper sequence.
     */
    ConstIterator constIterator() const {
        ConstIterator *tmp = new ConstIterator(this);
        return *tmp;
    }

    /**
     * Adds the specified element to this set if it is not already present.
     * Returns true if this set did not already contain the specified element.
     * O(logn)
     */

    bool add(const E& e) {
        if (contains(e)) return false;
        Insert(Root, e);
        return true;
    }

    /**
     * Removes all of the elements from this set.
     */

    void clear(node *p) {
        if (p == NULL) return;
        clear(p->lf);
        clear(p->rh);
        delete p;
    }

    void clear() {
        clear(Root);
    }

    /**
     * Returns true if this set contains the specified element.
     * O(logn)
     */
    bool contain(node *p, const E& e) const {
        if (p == NULL) return false;
        if (p->data == e) return true;
        if (e < p->data) return contain(p->lf, e);
        else return contain(p->rh, e);
    }

    bool contains(const E& e) const {
        return contain(Root, e);
    }


    /**
     * Returns a const reference to the first (lowest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& first() const {
        node *tmp = Root;
        while (tmp->lf != NULL) {
            tmp = tmp->lf;
        }
        if (tmp != NULL) return tmp->data;
        else throw;
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
        node *tmp = Root;
        while (tmp->rh != NULL) {
            tmp = tmp->rh;
        }
        if (tmp != NULL) return tmp->data;
        else throw;
    }

    /**
     * Removes the specified element from this set if it is present.
     * O(logn)
     */
    bool remove(const E& e) {
        Delete(Root, e);
    }

    /**
     * Returns the number of elements in this set (its cardinality).
     * O(1)
     */
    int size() const {
        return siz;
    }

    node* getRoot() const{
        return Root;
    }
};
#endif
