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
class HashMap
{
public:
    class ConstIterator
    {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container.
         */
        bool hasNext() { }

        /**
         * Returns the next element in the iteration.
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        const Entry<K, V>& next() { }
    };

    class Iterator
    {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container.
         */
        bool hasNext() { }

        /**
         * Returns a const reference the next element in the iteration.
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        Entry<K, V>& next() { }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(1)
         * @throw ElementNotExist
         */
        void remove() { }
    };

    /**
     * Constructs an empty list with an initial capacity.
     * You can construct it with your own initial capacity.
     */
    HashMap() { }

    /**
     * Copy-constructor
     */
    HashMap(const HashMap& x) { }

    /**
     * Constructs an empty HashMap with the specified initial capacity
     */
    HashMap(int initialCapacity) { }

    /**
     * Constructs a new HashMap with the same mappings as the specified Map.
     */
    template <class E2>
    explicit HashMap(const E2 &m);

    /**
     * assignment operator
     */
    HashMap& operator=(const HashMap& x) { }

    /**
     * destructor
     */
    ~HashMap() { }

    /**
     * Returns an iterator over the elements in this map in proper sequence.
     */
    Iterator iterator() { }

    /**
     * Returns an CONST iterator over the elements in this map in proper sequence.
     */
    ConstIterator constIterator() const { }

    /**
     * Removes all of the mappings from this map.
     */
    void clear() { }

    /**
     * Returns true if this map contains a mapping for the specified key.
     * O(1) for average
     */
    bool containsKey(const K& key) const { }

    /**
     * Returns true if this map maps one or more keys to the specified value.
     * O(n)
     */
    bool containsValue(const V& value) const { }

    /**
     * Returns a reference to the value to which the specified key is mapped.
     * O(1) for average
     * @throw ElementNotExist
     */
    V& get(const K& key) { }

    /**
     * Returns a const reference to the value to which the specified key is mapped.
     * O(1) for average
     * @throw ElementNotExist
     */
    const V& get(const K& key) const { }

    /**
     * Returns true if this map contains no key-value mappings.
     * O(1)
     */
    bool isEmpty() const { }

    /**
     * Associates the specified value with the specified key in this map.
     * Returns the previous value, if not exist, a value returned by the default-constructor.
     * O(1)
     */
    V put(const K& key, const V& value) { }

    /**
     * Removes the mapping for the specified key from this map if present.
     * Returns the previous value.
     * O(1) for average
     * @throw ElementNotExist
     */
    V remove(const K& key) { }

    /**
     * Returns the number of key-value mappings in this map.
     * O(1)
     */
    int size() const { }
};
#endif
