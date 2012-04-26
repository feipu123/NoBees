/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "Utility.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your inner implemention, not the current number of the
 * elements.
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
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * We don't require an order in the iteration, but you should
 * guarantee all elements will be iterated.
 */
template <class K, class V, class H>
class HashMap {
    struct node{
        Entry<K, V> data;
        node *next, *prev;
        node() {
            prev = next = NULL;
        }
        node(const K& x, const V& y) {
            data.key = x;
            data.value = y;
            prev = next = NULL;
        }
        node(const Entry<K, V> &x) {
            data.key = x.key;
            data.value = x.value;
            prev = next = NULL;
        }
    };
    node **array;
    int length;
    int siz;
public:
    class ConstIterator {
        const HashMap* parent;
        int pos;
        int counter;
        node *npos;
    public:
        ConstIterator(const HashMap* const x){
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
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        const Entry<K, V>& next() {
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
        HashMap *parent;
        int pos;
        int counter;
        node *npos;
    public:
        Iterator(HashMap* x){
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
         * Returns a const reference the next element in the iteration.
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        Entry<K, V>& next() {
            while (npos->next == NULL) {
                ++pos;
                npos = parent->array[pos];
            }
            npos = npos->next;
            ++counter;
            return npos->data;
        }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(1)
         * @throw ElementNotExist
         */
        void remove() {
            if (parent->remove(npos->data.key)) --counter;
        }
    };

    /**
     * Constructs an empty list with an initial capacity.
     * You can construct it with your own initial capacity.
     */
    HashMap() {
        length = 101;
        siz = 0;
        array = new node* [length];
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
    }

    /**
     * destructor
     */
    ~HashMap() {
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
     * Copy-constructor
     */
    HashMap(const HashMap& c) {
        array = new node* [c.length];
        length = c.length;
        siz = 0;
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
        HashMap::ConstIterator iter = c.constIterator();
        while (iter.hasNext()) {
            Entry<K, V> tmp = iter.next();
            int pos = H::hashcode(tmp.key) % length;
            node *p = array[pos]->next;
            while (p != NULL && p->data.key != tmp.key) p = p->next;
            if (p == NULL) {
                p = new node(tmp);
                p->next = array[pos]->next;
                if (array[pos]->next != NULL) array[pos]->next->prev = p;
                array[pos]->next = p;
                p->prev = array[pos];
                ++siz;
            }
        }
    }

    /**
     * Constructs an empty HashMap with the specified initial capacity
     */
    HashMap(int initialCapacity) {
        length = initialCapacity;
        siz = 0;
        array = new node* [length];
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
    }

    /**
     * Constructs a new HashMap with the same mappings as the specified Map.
     */
    template <class E2>
    explicit HashMap(const E2 &c) {
        array = new node* [101];
        siz = 0;
        length = 101;
        for (int i = 0; i < length; ++i) {
            array[i] = new node();
        }
        addAll(*this, c);
    }

    /**
     * assignment operator
     */
    HashMap& operator=(const HashMap& c) {
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
     * Returns an iterator over the elements in this map in proper sequence.
     */
    Iterator iterator() {
        Iterator *tmp = new Iterator(this);
        return *tmp;
    }

    /**
     * Returns an CONST iterator over the elements in this map in proper sequence.
     */
    ConstIterator constIterator() const {
        ConstIterator *tmp = new ConstIterator(this);
        return *tmp;
    }

    /**
     * Removes all of the mappings from this map.
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
     * Returns true if this map contains a mapping for the specified key.
     * O(1) for average
     */
    bool containsKey(const K& key) const {
        int pos = H::hashcode(key) % length;
        node *p = array[pos];
        while (p->next != NULL && p->next->data.key != key) p = p->next;
        if (p->next != NULL) return true;
        return false;
    }

    /**
     * Returns true if this map maps one or more keys to the specified value.
     * O(n)
     */
    bool containsValue(const V& value) const {
        HashMap::ConstIterator iter = this->constIterator();
        while (iter.hasNext()) if (iter.next().value == value) return true;
        return false;
    }

    /**
     * Returns a reference to the value to which the specified key is mapped.
     * O(1) for average
     * @throw ElementNotExist
     */
    V& get(const K& key) {
        int pos = H::hashcode(key) % length;
        node *p = array[pos];
        while (p->next != NULL && p->next->data.key != key) p = p->next;
        return p->next->data.key;
    }

    /**
     * Returns a const reference to the value to which the specified key is mapped.
     * O(1) for average
     * @throw ElementNotExist
     */
    const V& get(const K& key) const {
        int pos = H::hashcode(key) % length;
        node *p = array[pos];
        while (p->next != NULL && p->next->data.key != key) p = p->next;
        return p->next->data.key;
    }

    /**
     * Returns true if this map contains no key-value mappings.
     * O(1)
     */
    bool isEmpty() const {
        return (siz == 0);
    }

    /**
     * Associates the specified value with the specified key in this map.
     * Returns the previous value, if not exist, a value returned by the default-constructor.
     * O(1)
     */
    V put(const K& key, const V& value) {

    }

    /**
     * Removes the mapping for the specified key from this map if present.
     * Returns the previous value.
     * O(1) for average
     * @throw ElementNotExist
     */
    V remove(const K& key) {
        int pos = H::hashcode(key) % length;
        node *p = array[pos];
        while (p->next != NULL && p->next->data.key != key) p = p->next;
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
     * Returns the number of key-value mappings in this map.
     * O(1)
     */
    int size() const {
        return siz;
    }
};
#endif
