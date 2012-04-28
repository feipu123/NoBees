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
private:
    struct node {
        E value;
        node *left, *right;
        int level;
        node() {level = 1;left=NULL;right=NULL;}
        node(E v):value(v) {level = 1;left=NULL;right=NULL;}
    } ;
    node *root;
    int currentsize;
public:

    class ConstIterator
    {
    private:
        const TreeSet *tree;
        node *position;
        E a;
    public:
        ConstIterator(const TreeSet *t) {
            tree = t;
            position = NULL;
        }
        
        node* findnext(node *t, E x) {
            if (t == NULL) return NULL;
            if (t->value > x) {
                node *tmp = findnext(t->left, x);
                if (tmp != NULL) return (t->value < tmp->value ? t : tmp);
                else return t;
            }
            else return findnext(t->right, x);
        }
        
        node* findm() {
            node *tmp = tree->root;
            while (tmp->left) tmp = tmp->left;
            return tmp;
        }
        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
         bool hasNext() {
            if (tree->currentsize == 0) return false;
            if (position == NULL) {
                if (tree->root) return true;
                else return false;
            }
            node *tmp = findnext(tree->root, position->value);
            return tmp != NULL;
        }

        /**
         * Returns a const reference the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next() {
            if (hasNext()) {
                if (position == NULL) {
                    position = findm();
                    return position->value;
                }
                position = findnext(tree->root, position->value);
                return position->value;
            }
            else throw ElementNotExist();
        }

        
    };
    class Iterator
    {
    private:
        node *position;
        TreeSet *tree;
        bool hasremoved;
        E a;
        node* b;
    public:
        Iterator(TreeSet *t) {
            tree = t;
            position = NULL;
        }
        node* findnext(node *t, E x) {
            if (t == NULL) return NULL;
            if (t->value > x) {
                node *tmp = findnext(t->left, x);
                if (tmp != NULL) return (t->value < tmp->value ? t : tmp);
                else return t;
            }
            else return findnext(t->right, x);
        }

        node* findm() {
            node *tmp = tree->root;
            while (tmp->left) tmp = tmp->left;
            return tmp;
        }
        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
         bool hasNext() {
            if (tree->currentsize == 0) return false;
            if (position == NULL) {
                if (tree->root) return true;
                else return false;
            }
            node *tmp = findnext(tree->root, position->value);
            return tmp != NULL;
        }

        /**
         * Returns a const reference the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next() {
            if (hasNext()) {
                if (position == NULL) {
                    position = findm();
                    return position->value;
                }
                position = findnext(tree->root, position->value);
                return position->value;}
            else throw ElementNotExist();
        }

        void remove1(E x, node *&t) {
            if (t == NULL) return;
            if (x < t->value) remove1(x, t->left);
            else if (t->value < x) remove1(x, t->right);
                 else if (t->left != NULL && t->right != NULL) {
                          node *tmp = t->right;
                          while(tmp->left != NULL) tmp = tmp->left;
                          t->value = tmp->value;
                          remove1(t->value, t->right);
                      }
                      else {
                          node *oldNode = t;
                          t = (t->left != NULL) ? t->left : t->right;
                          delete oldNode;
                          return;
                      }
        }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(logn)
         * @throw ElementNotExist
         */
        void remove() {
            if (position == NULL) throw ElementNotExist();
            if (!hasremoved) {
                remove1(position->value, tree->root);
                tree->currentsize--;
                hasremoved = true;
            }
        }
    };
    
    /**
     * Returns an iterator over the elements in this set in proper sequence.
     */
    Iterator iterator() {
        Iterator *iter = new Iterator(this);
        return (*iter);
    }

    /**
     * Returns an CONST iterator over the elements in this set in proper sequence.
     */
    ConstIterator constIterator() const {
        ConstIterator *iter = new ConstIterator(this);
        return (*iter);
    }
    
    void LL(node *&t) {
        if (t->left != NULL && t->left->level == t->level) {
            node *t1 = t->left;
            t->left = t1->right;
            t1->right = t;
            t = t1;
        }
    }

    void RR(node *&t) {
        if (t->right != NULL && t->right->right != NULL) {
            node *t1 = t->right;
            t->right = t1->left;
            t1->left = t;
            t = t1;
            t->level++;
        }
    }

    void insert(const E x, node *&t) {
        if (!t) t = new node(x);
        else if (x < t->value) insert(x, t->left);
             else if (x > t->value) insert(x, t->right);
                  else return;
        LL(t);
        RR(t);
    }
    
    void removet(node *t) {
        if (t != NULL) {
            if (t->left != NULL) removet(t->left);
            if (t->right != NULL) removet(t->right);
            delete t;
        }
    }
    
    /**
     * Adds the specified element to this set if it is not already present.
     * Returns true if this set did not already contain the specified element.
     * O(logn)
     */
    bool add(const E& e) {
        if (currentsize == 0) root->value = e,root->level = 1,currentsize++;
        else insert(e, root),currentsize++;
        return true;
    }
    
    /**
     * Constructs a new, empty tree set, sorted according to the natural ordering of its elements.
     */
    TreeSet() {root = new node(),currentsize = 0; }

    /**
     * Constructs a set containing the elements of the specified collection, in
     * the order they are returned by the collection's iterator.
     */
    template <class E2>
    explicit TreeSet(const E2& x) {
        root = new node(),currentsize = 0;
        addAll(*this, x);
    }
    
    /**
     * Destructor
     */
    ~TreeSet() {clear(); }

    /**
     * Assignment operator
     */
    TreeSet& operator=(const TreeSet& x) {
        clear();
        root = new node(),currentsize = 0;
        addAll(*this, x);
    }

    /**
     * Copy-constructor
     */
    TreeSet(const TreeSet& x) {
        root = new node(),currentsize = 0;
        addAll(*this, x);
    }
    
    /**
     * Returns true if this set contains the specified element.
     * O(logn)
     */
    bool find(const E& x, node *t) const {
        if (t == NULL) return false;
        else if (x < t->value) return find(x, t->left);
             else if (x > t->value) return find(x, t->right);
                  else return true;
    }

    bool contains(const E& e) const {
        return find(e, root);
    }
    
    /**
     * Returns a const reference to the first (lowest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& first() const {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->left != NULL) tmp = tmp->left;
        return tmp->value;
    }

    /**
     * Returns true if this set contains no elements.
     * O(1)
     */
    bool isEmpty() const {return currentsize == 0; }

    /**
     * Returns a const reference to the last (highest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& last() const {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->right != NULL) tmp = tmp->right;
        return tmp->value;
    }
    
    /**
     * Removes all of the elements from this set.
     */
    void clear() {
        if (root != NULL) removet(root);
        root = NULL,currentsize = 0;
    }
    
    /**
     * Removes the specified element from this set if it is present.
     * O(logn)
     */
    void remove2(E x, node *&t) {
            if (t == NULL) return;
            if (x < t->value) remove2(x, t->left);
            else if (t->value < x) remove2(x, t->right);
                 else if (t->left != NULL && t->right != NULL) {
                          node *tmp = t->right;
                          while(tmp->left != NULL) tmp = tmp->left;
                          t->value = tmp->value;
                          remove2(t->value, t->right);
                      }
                      else {
                          node *oldNode = t;
                          t = (t->left != NULL) ? t->left : t->right;
                          delete oldNode;
                          return;
                      }
        }

    bool remove(const E& e) {
        remove2(e, root);
        currentsize--;
        return true;
    }
    
    int size() const {return currentsize; }
};
#endif

