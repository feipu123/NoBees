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
           Entry<K, V> data;
        int aux;
        node *lf, *rh;
        node() {
            srand(time(NULL));
            aux = rand() % MAXN;
            lf = rh = NULL;
        }
        node(const K& x, const V& y) : data(x, y){
            srand(time(NULL));
            aux = rand() % MAXN;
            lf = rh = NULL;
        }
        node(const Entry<K, V>& x) : data(x.key, x.value){
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
    void Insert(node* &nd, const Entry<K, V>& e) {
        if (nd == NULL) {
            nd = new node(e);
            ++siz;
            return;
        }
        if (e.key < nd->data.key) {
            Insert(nd->lf, e);
            if (nd->lf->aux < nd->aux) RotateR(nd);
        }
        else {
            Insert(nd->rh, e);
            if (nd->rh->aux < nd->aux) RotateL(nd);
        }
    }
    void Delete(node* &nd, const K& key) {
        if (nd == NULL) return;
        if (nd->data.key == key) {
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
                    Delete(nd->rh, key);
                }
                else {
                    RotateL(nd);
                    Delete(nd->lf, key);
                }
            }
        }
        else {
            if (key < nd->data.key) Delete(nd->lf, key);
            else Delete(nd->rh, key);
        }
    }
    class ConstIterator {
        const TreeMap *parent;
        Entry<K, V> *value;
        bool flag;
    public:
           ConstIterator(const TreeMap* const x) {
           if (x->Root == NULL) throw;
            flag = false;
            parent = x;
            node *p = x->Root;
            while (p->lf != NULL) {
                p = p->lf;
            }
            value = new Entry<K, V>(p->data);
        }
        /**
         * Returns true if the iteration has more elements.
         * Amortized O(1).
         */
        bool hasNext() {
             if (!flag) return true;
            if (value->key < parent->lastKey()) return true;
            return false;
        }

        /**
         * Returns a const reference to the next element in the iteration.
         * Amortized O(1).
         * @throw ElementNotExist
         */
        const Entry<K, V>& next() {
              if (!flag) {
                flag = true;
                return *value;
            }
            node *p = parent->getRoot();
            node *tag = p;
            while (p->data.key != value->key) {
                tag = p;
                if (value->key < p->data.key) p = p->lf;
                else p = p->rh;
            }
            if (p->rh != NULL) {
                p = p->rh;
                while (p->lf != NULL) {
                    p = p->lf;
                }
            }
            if (p->data.key != value->key) tag = p;
            delete value;
            value = new Entry<K, V>(tag->data);
            return *value;
        }
    };

    class Iterator {
          TreeMap *parent;
        Entry<K, V> *value;
        bool flag;
    public:
           Iterator(TreeMap* const x) {
            parent = x;
            node *p = x->getRoot();
            while (p->lf != NULL) {
                p = p->lf;
            }
            value = new Entry<K, V>(p->data);
            flag = false;
        }
        /**
         * Returns true if the iteration has more elements.
         * Amortized O(1).
         */
        bool hasNext() {
             if (!flag) return true;
            if (value->key < parent->lastKey()) return true;
            return false;
        }

        /**
         * Returns a reference to the next element in the iteration.
         * Amortized O(1).
         * @throw ElementNotExist
         */
        Entry<K, V>& next() {
                 if (!flag) {
                flag = true;
                return *value;
            }
            node *p = parent->getRoot();
            node *tag = p;
            while (p->data.key != value->key) {
                if (value->key < p->data.key) {
                    p = p->lf;
                    tag = p;
                }
                else p = p->rh;
            }
            if (p->rh != NULL) {
                p = p->rh;
                while (p->lf != NULL) {
                    p = p->lf;
                }
            }
            if (value->key < p->data.key) tag = p;
            delete value;
            value = new Entry<K, V>(tag->data);
            return *value;
        }

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator
         * Amortized O(1).
         * @throw ElementNotExist
         */
        void remove() {
             node *p = parent->getRoot();
            node *tag = p;
            while (p->data.key != value->key) {
                tag = p;
                if (value->key < p->data.key) p = p->lf;
                else p = p->rh;
            }
            if (p->lf != NULL) {
                p = p->lf;
                while (p->rh != NULL) {
                    p = p->rh;
                }
            }
            if (p->data.key < value->key) tag = p;
            K tmp = value->key;
            delete value;
            value = new Entry<K, V>(tag->data);
            parent->remove(tmp);
        }
        
        ~Iterator() {
                    delete value;
        }
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
        Root = NULL;
        siz = 0;
        ConstIterator iter = c.constIterator();
             while (iter.hasNext())
                   put(iter.next());              
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
        ConstIterator iter = c.constIterator();
             while (iter.hasNext())
                   put(iter.next());
        return *this;
    }

    /**
     * Constructs a new tree map containing the same mappings as the
     * given map
     */
    template <class C> TreeMap(const C& c) {
             typename C::ConstIterator iter = c.constIterator();
             while (iter.hasNext())
                   put(iter.next());
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
    void clear(node *p) {
        if (p == NULL) return;
        clear(p->lf);
        clear(p->rh);
        delete p;
    }

    void clear() {
        clear(Root);
        siz = 0;
        Root = NULL;
    }

    bool contain(node *p, const K& key) const {
        if (p == NULL) return false;
        if (p->data.key == key) return true;
        if (key < p->data.key) return contain(p->lf, key);
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
    bool containsValue(const V& value) const {
         ConstIterator iter = constIterator();
         while (iter.hasNext()) 
               if (iter.next().value == value) 
                  return true;
         return false;
    }

    /**
     * Returns a key-value mapping associated with the least key in
     * this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const Entry<K, V>& firstEntry() const {
          node *tmp = Root;
        while (tmp->lf != NULL) {
            tmp = tmp->lf;
        }
        return tmp->data;
    }

    /**
     * Returns the first (lowest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& firstKey() const {
          return firstEntry().key;
          }

    V& getValue(node *p, const K& key) const {
        if (p == NULL) throw;
        if (p->data.key == key) return p->data.value;
        if (key < p->data.key) return getValue(p->lf, key);
        else return getValue(p->rh, key);
    }
    
    /**
     * Returns a reference to the value which the specified key is mapped
     * O(logn).
     * @throw ElementNotExist
     */
    V& get(const K& key) {
       return getValue(Root, key);
    }

    /**
     * Returns a reference to the value which the specified key is mapped
     * O(logn).
     * @throw ElementNotExist
     */
    const V& get(const K& key) const {
          return getValue(Root, key);
    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const Entry<K, V>& lastEntry() const {
          if (Root == NULL) throw;
        node *tmp = Root;
        while (tmp->rh != NULL) {
            tmp = tmp->rh;
        }
        return tmp->data;
    }

    /**
     * Returns the last (highest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& lastKey() const {
          return lastEntry().key;
    }

    /**
     * Associates the specified value with the specified key in this map.
     * Returns the previous value, if not exist, a value returned by the
     * default-constructor.
     * O(logn).
     */
    V put(const K& key, const V& value) {
                Entry<K, V> e(key, value);
                V tmp;
                if (contain(Root, e.key)) {
                   tmp = get(e.key);
                   Delete(Root, e.key);
                }
                Insert(Root, e);
                return tmp;
    }
    
    V put(const Entry<K, V>& e) {
                V tmp;
                if (contain(Root, e.key)) {
                   tmp = get(e.key);
                   Delete(Root, e.key);
                }
                Insert(Root, e);
                return tmp;
    }

    /**
     * Removes the mapping for this key from this TreeMap if present.
     * O(logn).
     * @throw ElementNotExist
     */
    V remove(const K& key) {
                   Delete(Root, key);
    }

    /**
     * Returns the number of key-value mappings in this map.
     * O(logn).
     */
    int size() const {
        return siz;
    }
    
    node* getRoot() const {
        return Root;
    }
};

#endif

