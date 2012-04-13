/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Utility.h"

/**
 * A map is a sequence of (key, value) entries that provides fast retrieval
 * based on the key. At most one value is held for each key.
 *
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V> class TreeMap {
public:
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
    TreeMap() { }

    /**
     * Copy constructor
     */
    TreeMap(const TreeMap &c) {}

    /**
     * Destructor
     */
    ~TreeMap() { }

    /**
     * Assignment operator
     */
    TreeMap& operator=(const TreeMap &c) {}

    /**
     * Constructs a new tree map containing the same mappings as the
     * given map
     */
    template <class C> TreeMap(const C& c) {}

    /**
     * Returns an iterator over the elements in this map.
     * O(1).
     */
    Iterator iterator() {}

    /**
     * Returns an const iterator over the elements in this map.
     * O(1).
     */
    ConstIterator constIterator() const {}

    /**
     * Removes all of the mappings from this map.
     * O(n).
     */
    void clear() {}

    /**
     * Returns true if this map contains a mapping for the specified key.
     * O(logn).
     */
    bool containsKey(const K& key) const {}

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

