/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Utility.h"
#include <cstdlib>
#include <ctime>

/**
 * A map is a sequence of (key, value) entries that provides fast retrieval
 * based on the key. At most one value is held for each key.
 *
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V> class TreeMap {
private:
static const int MAXN = 1000000000;
    struct node{
        K nodeKey;
        V nodeValue;
        int aux;
        node *lf, *rh;
        node() {
            srand(time(NULL));
            aux = rand() % MAXN;
            lf = rh = NULL;
        }
        node(const K& x, const V& y) {
            nodeKey = x;
            nodeValue = y;
            srand(time(NULL));
            aux = rand() % MAXN;
            lf = rh = NULL;
        }
        node(const node* const y) {
            nodeKey = y->nodeKey;
            nodeValue = y->nodeValue;
            lf = y->lf;
            rh = y->rh;
            aux = y->aux;
        }
    };
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
    void Insert(node* &nd, const E& e) {
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
    void Delete(node* &nd, const E& e) {
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
    public:
        /**
         * Returns true if the iteration has more elements.
         * Amortized O(1).
         */
        bool hasNext() {}

        /**
         * Returns a const reference to the next element in the iteration.
         * Amortized O(1).
         * @throw ElementNotExist
         */
        const Entry<K, V>& next() {}
    };

    class Iterator {
    public:
        /**
         * Returns true if the iteration has more elements.
         * Amortized O(1).
         */
        bool hasNext() {}

        /**
         * Returns a reference to the next element in the iteration.
         * Amortized O(1).
         * @throw ElementNotExist
         */
        Entry<K, V>& next() {}

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator
         * Amortized O(1).
         * @throw ElementNotExist
         */
        void remove() {}
    };

    /**
     * Constructs an empty map
     */
    TreeMap() { 
        Root = NULL;
        siz = 0;
    }

    /**
     * Copy constructor
     */
    TreeMap(const TreeMap &c) {
                  addAll(*this, c);              
    }

    /**
     * Destructor
     */
    ~TreeMap() {
               clear();
    }
    
    void makeTree(node* &x, node* y){
        if (y == NULL) {
            x = NULL;
            return;
        }
        x = new node(y);
        makeTree(x->lf, y->lf);
        makeTree(x->rh, y->rh);
    }
    
    /**
     * Assignment operator
     */
    TreeMap& operator=(const TreeMap &c) {
             clear();
        addAll(*this, c);
        return *this;
    }

    /**
     * Constructs a new tree map containing the same mappings as the
     * given map
     */
    template <class C> TreeMap(const C& c) {
             addAll(*this, c);
    }

    /**
     * Returns an iterator over the elements in this map.
     * O(1).
     */
    Iterator iterator() {
            Iterator *tmp = new Iterator(this);
            return *tmp;         
    }

    /**
     * Returns an const iterator over the elements in this map.
     * O(1).
     */
    ConstIterator constIterator() const {
        ConstIterator *tmp = new ConstIterator(this);
        return *tmp;                  
    }

    /**
     * Removes all of the mappings from this map.
     * O(n).
     */
    void clear() {
         if (p == NULL) return;
        clear(p->lf);
        clear(p->rh);
        delete p;
    }

    bool contain(node *p, const K& key) const {
        if (p == NULL) return false;
        if (p->data == key) return true;
        if (e < p->data) return contain(p->lf, key);
        else return contain(p->rh, key);
    }
    
    /**
     * Returns true if this map contains a mapping for the specified key.
     * O(logn).
     */
    bool containsKey(const K& key) const {
         return contain(Root, key);
    }

    /**
     * Returns true if this map contains a mapping for the specified value.
     * O(n).
     */
    bool containsValue(const V& value) const {}

    /**
     * Returns a key-value mapping associated with the least key in
     * this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const Entry<K, V>& firstEntry() const {}

    /**
     * Returns the first (lowest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& firstKey() const {}

    /**
     * Returns a reference to the value which the specified key is mapped
     * O(logn).
     * @throw ElementNotExist
     */
    V& get(const K& key) {}

    /**
     * Returns a reference to the value which the specified key is mapped
     * O(logn).
     * @throw ElementNotExist
     */
    const V& get(const K& key) const {}

    /**
     * Returns a key-value mapping associated with the greatest key
     * in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const Entry<K, V>& lastEntry() const {}

    /**
     * Returns the last (highest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& lastKey() const {}

    /**
     * Associates the specified value with the specified key in this map.
     * Returns the previous value, if not exist, a value returned by the
     * default-constructor.
     * O(logn).
     */
    V put(const K& key, const V& value) {}

    /**
     * Removes the mapping for this key from this TreeMap if present.
     * O(logn).
     * @throw ElementNotExist
     */
    V remove(const K& key) {}

    /**
     * Returns the number of key-value mappings in this map.
     * O(logn).
     */
    int size() const {}
};

#endif

