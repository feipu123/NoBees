#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "Utility.h"

template <class E>
class ArrayList {
    E *data;
    int currentSize, capacity;
public:
    class ConstIterator {
        int position;
    public:
        const ArrayList<E> *parent;
        ConstIterator() {
            position = -1;
        }

        /**
         * Returns true if the iteration has more elements.
         * O(1)
         */
        bool hasNext() {
            if (position < parent->size() - 1) return true;
            return false;
        }

        /**
         * Returns the next element in the iteration.
         * O(1)
         * @throw ElementNotExist
         */
        const E& next() {
            return parent->data[++position];
        }
    };

    class Iterator {
        int position;
    public:
        const ArrayList<E> *parent;
        Iterator() {
            position = -1;
        }
        /**
         * Returns true if the iteration has more elements.
         * O(1)
         */
        bool hasNext() {
            if (position < parent->size() - 1) return true;
            return false;
        }

        /**
         * Returns the next element in the iteration.
         * O(1)
         * @throw ElementNotExist
         */
        E& next() {
            return parent->data[++position];
        }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(n)
         * @throw ElementNotExist
         */
        void remove() {
            parent->removeIndex(position);
            --position;
        }
    };

    /**
     * Constructs an empty list with an initial capacity of ten.
     */
    ArrayList() {
        data = new E[10];
        capacity = 10;
        currentSize = 0;
    }

    /**
     * Constructs a list containing the elements of the specified collection, in
     * the order they are returned by the collection's iterator.
     */
    template <class E2>
    explicit ArrayList(E2& x) {
        data = new E[10];
        capacity = 10;
        currentSize = 0;
        typename E2::Iterator iter = x.iterator();
        while (iter.hasNext()) {
            if (currentSize == capacity) ensureCapacity(capacity << 1);
            data[currentSize] = iter.next();
            ++currentSize;
        }
    }

    /**
     * Constructs an empty list with the specified initial capacity.
     */
    ArrayList(int initialCapacity) {
        data = new E[initialCapacity];
        capacity = initialCapacity;
        currentSize = 0;
    }

    ArrayList(int initialCapacity, int initialCurrentsize) {
        data = new E[initialCapacity];
        capacity = initialCapacity;
        currentSize = initialCurrentsize;
    }

    /**
     * Destructor
     */
    ~ArrayList() {
        capacity = 0;
        currentSize = 0;
        delete []data;
    }

    /**
     * Assignment operator
     */
    ArrayList& operator=(const ArrayList& x) {
        delete []data;
        data = new E[x.size() * 2];
        currentSize = 0;
        for (int i = 0; i < x.size(); ++i) {
            add(x.get(i));
        }
        return *this;
    }

    /**
     * Copy-constructor
     */
    ArrayList(const ArrayList& x) {
        data = new E[x.size() * 2];
        capacity = x.size() * 2;
        currentSize = 0;
        for (int i = 0; i < x.size(); ++i) {
            add(x.get(i));
        }
    }

    /**
     * Returns an iterator over the elements in this list in proper sequence.
     */
    Iterator iterator() {
        Iterator tmp;
        tmp.parent = this;
        return tmp;
    }

    /**
     * Returns an CONST iterator over the elements in this list in proper sequence.
     */
    ConstIterator constIterator() const {
        ConstIterator tmp;
        tmp.parent = this;
        return tmp;
    }

    /**
     * Appends the specified element to the end of this list.
     * O(1)
     */
    bool add(const E& e) {
        if (currentSize == capacity) ensureCapacity(capacity << 1);
        data[currentSize] = e;
        ++currentSize;
        return true;
    }

    /**
     * Inserts the specified element at the specified position in this list.
     * The range of index is [0, currentSize].
     * O(n)
     * @throw IndexOutOfBound
     */
    void add(int index, const E& element) {
        if (currentSize == capacity) ensureCapacity(capacity << 1);
        for (int i = currentSize; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        ++currentSize;
    }

    /**
     * Removes all of the elements from this list.
     */
    void clear() {
        delete []data;
        data = new E[capacity];
        currentSize = 0;
    }

    /**
     * Returns true if this list contains the specified element.
     * O(n)
     */
    bool contains(const E& e) const {
        for (int i = 0; i < currentSize; ++i) {
            if (data[i] == e) return true;
        }
        return false;
    }

    /**
     * Increases the capacity of this ArrayList instance, if necessary, to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
     */
    void ensureCapacity(int minCapacity) {
        E tmp[currentSize];
        for (int i = 0; i < currentSize; ++i) {
            tmp[i] = data[i];
        }
        delete []data;
        data = new E[minCapacity];
        for (int i = 0; i < currentSize; ++i) {
            data[i] = tmp[i];
        }
        capacity = minCapacity;
    }

    /**
     * Returns a reference to the element at the specified position in this list.
     * O(1)
     * @throw IndexOutOfBound
     */
    E& get(int index) {
        return data[index];
    }

    /**
     * Returns a const reference to the element at the specified position in this list.
     * O(1)
     * @throw IndexOutOfBound
     */
    const E& get(int index) const {
        return data[index];
    }

    /**
     * Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * O(n)
     */
    int indexOf(const E& e) const {
        for (int i = 0; i < currentSize; ++i) {
            if (data[i] == e) return i;
        }
        return -1;
    }

    /**
     * Returns true if this list contains no elements.
     * O(1)
     */
    bool isEmpty() const { return (currentSize == 0); }

    /**
     * Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * O(n)
     */
    int lastIndexOf(const E& e) const {
        for (int i = currentSize - 1; i >= 0; --i) {
            if (data[i] == e) return i;
        }
    return -1;
    }

    /**
     * Removes the element at the specified position in this list.
     * Returns the element that was removed from the list.
     * O(n)
     * @throw IndexOutOfBound
     */
    E removeIndex(int index) {
        E tmp = data[index];
        for (int i = index; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        --currentSize;
        return tmp;
    }

    /**
     * Removes the first occurrence of the specified element from this list, if it is present.
     * O(n)
     */
    bool remove(const E& e) {
        for (int i = 0; i < currentSize; ++i)
            if (data[i] == e) {
                removeIndex(i);
                return true;
            }
    return false;
    }

    /**
     * Removes from this list all of the elements whose index is between fromIndex, inclusive, and toIndex, exclusive.
     * O(n)
     * @throw IndexOutOfBound
     */
    void removeRange(int fromIndex, int toIndex) {
        for (int i = fromIndex; i < currentSize - toIndex + fromIndex; ++i) {
            data[i] = data[i + toIndex - fromIndex];
        }
        currentSize -= (toIndex - fromIndex);
    }

    /**
     * Replaces the element at the specified position in this list with the specified element.
     * Returns the element previously at the specified position.
     * O(1)
     * @throw IndexOutOfBound
     */
    E set(int index, const E& element) {
        E tmp = data[index];
        data[index] = element;
        return tmp;
    }

    /**
     * Returns the number of elements in this list.
     * O(1)
     */
    int size() const {
        return currentSize;
    }

    /**
     * Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
     * O(n)
     * @throw IndexOutOfBound
     */
    ArrayList subList(int fromIndex, int toIndex) const {
        ArrayList tmp = ArrayList(toIndex - fromIndex + 1, toIndex - fromIndex);
        for (int i = 0; i < toIndex - fromIndex; ++i) {
            tmp.get(i) = data[fromIndex + i];
        }
        return tmp;
    }
};
#endif

