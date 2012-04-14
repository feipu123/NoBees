#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "Utility.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T> class LinkedList {
    struct node{
        T data;
        node *next;
        node *prev;
    };
    node *head;
    node *tail;
public:
    node(T &x) {
        data = x;
        next = NULL;
        tail = NULL;
    }
    node() {
        next = NULL;
        tail = NULL;
    }
    class ConstIterator {
        LinkedList::node *pos;
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(1).
         */
        bool hasNext() {
            if (pos->next == NULL) return false;
            return true;
        }

        /**
         * Returns the next element in the iteration.
         * O(1).
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T& next() {
            pos = pos->next;
            return pos->data;
        }
    };

    class Iterator {
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(1).
         */
        bool hasNext() {
            if (pos->next == NULL) return false;
            return true;
        }

        /**
         * Returns the next element in the iteration.
         * O(1).
         * @throw ElementNotExist exception when hasNext() == false
         */
        T& next() {
            pos = pos->next;
            return pos->data;
        }

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator
         * O(1).
         * @throw ElementNotExist
         */
        void remove() {
            LinkedList::node *tmp = pos->prev;
            tmp->next = pos->next;
            pos->next->prev = tmp;
            delete pos;
            pos = tmp;
        }
    };

    /**
     * Constructs an empty list
     */
    LinkedList() {
        node *tmp = new node();
        head = tail = tmp;
    }

    /**
     * Copy constructor
     * You may utilize the ``addAll'' function from Utility.h
     */
    LinkedList(const LinkedList<T> &c) {
        node *p = c->head;
        node *q = new node();
        head = q;
        while (p->next != NULL) {
            p = p->next;
            node *tmp = new node(p->data);
            q->next = tmp;
            tmp->prev = q;
            q = tmp;
        }
        tail = q;
    }

    /**
     * Assignment operator
     * You may utilize the ``addAll'' function from Utility.h
     */
    LinkedList<T>& operator=(const LinkedList<T> &c) {
        node *p = head->next;
        while (p != NULL) {
            p = p->next;
            delete p->prev;
        }
        if (head != tail) {
            delete tail;
            tail = head;
        }
        p = c->head->next;
        while (p != NULL) {
            node *tmp = new node(p->data);
            tail->next = tmp;
            tmp->prev = tail;
            tail = tmp;
            p = p->next;
        }
    return *this;
    }

    /**
     * Constructs a list containing the elements of the specified
     * collection, in the order they are returned by the collection's
     * const iterator.
     * You may utilize the ``addAll'' function from Utility.h
     */
    template <class C>
    LinkedList(const C& c) {}

    /**
     * Desturctor
     */
    ~LinkedList() {
        node *p = head;
        while (p != NULL) {
            p = p->next;
            delete p->prev;
        }
        delete tail;
    }

    /**
     * Inserts the specified element at the specified position in
     * this list.
     * O(n)
     * @throw IndexOutOfBound exception when index is out of bound
     */
    void add(int index, const T& elem) {
        node *p = head->next;
        for (int i = 0; i < index; ++i) {
            p = p->next;
        }
        node *tmp = new node(elem);
        p->prev->next = tmp;
        tmp->prev = p->prev;
        tmp->next = p;
        p->prev = tmp;
    }

    /**
     * Appends the specified element to the end of this list.
     * O(1).
     * Always returns true;
     */
    bool add(const T& elem) {
        node *tmp = new node(elem);
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
        return true;
    }

    /**
     * Inserts the specified element at the beginning of this list.
     * O(1).
     */
    void addFirst(const T& elem) {
        node *tmp = new node(elem);
        tmp->next = head->next;
        tmp->next->prev = tmp;
        head->next = tmp;
        tmp->prev = head;
    }

    /**
     * Removes all of the elements from this list.
     * O(n).
     */
    void clear() {
        node *p = head->next;
        while (p != NULL) {
            p = p->next;
            delete p->prev;
        }
        if (head != tail) delete tail;
        tail = head;
    }

    /**
     * Returns true if this list contains the specified element.
     * O(n).
     */
    bool contains(const T& elem) const {
        node *p = head->next;
        while (p!= NULL) {
            if (p->data == elem) return true;
        }
    return false;
    }

    /**
     * Returns a reference to the element at the specified position.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T& get(int index) {
        node *p = head->next;
        for (int i = 0; i < index; ++i) {
            p = p->next;
        }
    return p->data;
    }

    /**
     * Returns a const reference to the element at the specified position.
     * O(n).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const {
        node *p = head->next;
        for (int i = 0; i < index; ++i) {
            p = p->next;
        }
    return p->data;
    }

    /**
     * Returns a reference to the first element.
     * O(1).
     * @throw ElementNotExist
     */
    T& getFirst() {
        return head->next->data;
    }

    /**
     * Returns a const reference to the first element.
     * O(1).
     * @throw ElementNotExist
     */
    const T& getFirst() const {
        return head->next->data;
    }

    /**
     * Returns a reference to the last element.
     * O(1).
     * @throw ElementNotExist
     */
    T& getLast() {
        return tail->data;
    }

    /**
     * Returns a const reference to the last element.
     * O(1).
     * @throw ElementNotExist
     */
    const T& getLast() const {
        return tail->data;
    }

    /**
     * Returns the index of the first occurrence of the specified element
     * O(1).
     * in this list, or -1 if this list does not contain the element.
     */
    int indexOf(const T& elem) const {
        node *p = head->next;
        int k = 0;
        while (p != NULL) {
            if (p->data == elem) return k;
            ++k;
            p = p->next;
        }
    return -1;
    }

    /**
     * Returns true if this list contains no elements.
     * O(1).
     */
    bool isEmpty() const {
        return (head == tail);
    }

    /**
     * Returns an iterator
     * O(1).
     */
    Iterator iterator() {}

    /**
     * Returns an const iterator
     * O(1).
     */
    ConstIterator constIterator() const {}

    /**
     * Removes the element at the specified position in this list.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T removeIndex(int index) {}

    /**
     * Removes the first occurrence of the specified element from this
     * O(n).
     * list, if it is present.
     */
    bool remove(const T& elem) {}

    /**
     * Removes and returns the first element from this list.
     * O(1).
     * @throw ElementNotExist
     */
    T removeFirst() {
        node *tmp = head->next;
        T tmpData = tmp->data;
        head->next = tmp->next;
        tmp->next->prev = head;
        delete tmp;
    return tmpData;
    }

    /**
     * Removes and returns the last element from this list.
     * O(1).
     * @throw ElementNotExist
     */
    T removeLast() {
        node *tmp = tail->prev;
        T tmpdata = tail->data;
        tmp->next = NULL;
        delete tail;
        tail = tmp;
        return tmpdata;
    }

    /**
     * Replaces the element at the specified position in this list with
     * the specified element.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T set(int index, const T& elem) {
        node *p = head->next;
        for (int i = 0; i < index; ++i) {
            p = p->next;
        }
        T tmp = p->data;
        p->data = elem;
        return tmp;
    }

    /**
     * Returns the number of elements in this list.
     */
    int size() const {
        int counter = 0;
        node *p = head->next;
        while (p != NULL) {
            ++counter;
            p = p->next;
        }
    return counter;
    }

    /**
     * Returns a view of the portion of this list between the specified
     * fromIndex, inclusive, and toIndex, exclusive.
     * O(n).
     * @throw IndexOutOfBound
     */
    LinkedList<T> subList(int fromIndex, int toIndex) {
        LinkedList *tmp = new LinkedList();
        node *p = head->next;
        for (int i = 0; i < fromIndex; ++i) {
            p = p->next;
        }
        for (int i = fromIndex; i < toIndex; ++i) {
            tmp->
        }
    }
};
#endif

