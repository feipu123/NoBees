#include <iostream>
#include <fstream>

#include "Utility.h"
#include "LinkedList.h"
#include "ArrayList.h"
#include "TreeSet.h"
#include "TreeMap.h"
#include "HashSet.h"
#include "HashMap.h"

using namespace std;

class Hashint {
public:
    static int hashcode(int x) {
        return x;
    }
};

void displayLinkedList(LinkedList<int> a)
{
    LinkedList<int>::Iterator iter = a.iterator();
    while (iter.hasNext())
    {
        cout << iter.next() << " ";
    }
    cout << endl;
}

void displayArrayList(ArrayList<char> a)
{
    ArrayList<char>::Iterator iter = a.iterator();
    while (iter.hasNext())
    {
        cout << iter.next() << " ";
    }
    cout << endl;
}

void displayTreeSet(TreeSet<int> a)
{
    TreeSet<int>::Iterator iter = a.iterator();
    while (iter.hasNext())
    {
        cout << iter.next() << " ";
    }
    cout << endl;
}

void displayHashSet(HashSet<int,Hashint> a)
{
    HashSet<int,Hashint>::Iterator iter = a.iterator();
    while (iter.hasNext())
    {
        cout << iter.next() << " ";
    }
    cout << endl;
}

void displayTreeMap(TreeMap<int,char> a)
{
    TreeMap<int,char>::Iterator iter = a.iterator();
    while (iter.hasNext())
    {
        Entry<int,char> *tmp = &iter.next();
        cout << "(" << tmp->key << "," << tmp->value << ") ";
    }
    cout << endl;
}

void displayHashMap(HashMap<int,char,Hashint> a)
{
    HashMap<int,char,Hashint>::Iterator iter = a.iterator();
    while (iter.hasNext())
    {
        Entry<int,char> *tmp = &iter.next();
        cout << "(" << tmp->key << "," << tmp->value << ") ";
    }
    cout << endl;
}

int main() {
        freopen("out.txt", "w", stdout);

    /*cout << "--- Testing LinkedList.h ---" << endl;
    LinkedList<int> link_a;
    cout << "\n### Part I : method Add ###" << endl;
        for (int i = 1; i <= 10; i++) link_a.add(i);
        displayLinkedList(link_a);
        link_a.clear();
        for (int i = 1; i <= 10; i++) link_a.addFirst(i);
        displayLinkedList(link_a);
        link_a.add(3,11);
        cout << "add(3,11): "; displayLinkedList(link_a);
        link_a.add(10,12);
        cout << "add(10,12): "; displayLinkedList(link_a);

   cout << "\n### Part II : method Get ###" << endl;
        for (int i = 0; i < 12; i++) cout << link_a.get(i) << " ";
        cout << endl;
        cout << link_a.getFirst() << " " << link_a.getLast() << endl;

    cout << "\n### Part III : method Remove ###" << endl;
        LinkedList<int> link_b(link_a);
        link_b.remove(3); link_b.remove(12);
        cout << "remove(3) & remove(12): "; displayLinkedList(link_b);
        link_b = link_a;
        link_b.removeIndex(5);
        cout << "removeIndex(5): "; displayLinkedList(link_b);
        link_b = link_a;
        link_b.removeFirst(); link_b.removeLast();
        cout << "removeFirst() & removeLast(): "; displayLinkedList(link_b);

    cout << "\n### Part IV : method subList ###" << endl;
        LinkedList<int> link_c;
        link_c = link_a.subList(1,3);
        cout << "subList(1,3): "; displayLinkedList(link_c);

	cout << "\n--- Testing ArrayList.h ---" << endl;
    ArrayList<char> array_a;
    cout << "\n### Part I : method Add ###" << endl;
        for (int i = 1; i <= 10; i++) array_a.add(i+64);
        displayArrayList(array_a);
        array_a.clear();
        array_a.add(65);
        for (int i = 2; i <= 10; i++) array_a.add(0,i+64);
        displayArrayList(array_a);
        array_a.add(3,75);
        cout << "add(3,K): "; displayArrayList(array_a);
        array_a.add(10,76);
        cout << "add(10,L): "; displayArrayList(array_a);

    cout << "\n### Part II : method Get & Contains ###" << endl;
        for (int i = 0; i < 12; i++) cout << array_a.get(i) << " ";
        cout << endl;
        for (int i = 0; i <= 12; i++) cout << array_a.indexOf(i+64) << " ";
        cout << endl;
        cout << ((array_a.contains('C'))?("contains C"):("not contains C")) << endl;
        cout << ((array_a.contains('Z'))?("contains Z"):("not contains Z")) << endl;

    cout << "\n### Part III : method Remove ###" << endl;
        ArrayList<char> array_b(array_a);
        array_b.remove(67); array_b.remove(75);
        cout << "remove(C) & remove(K): "; displayArrayList(array_b);
        array_b = array_a;
        array_b.removeIndex(5);
        cout << "removeIndex(5): "; displayArrayList(array_b);
        array_b = array_a;
        array_b.removeIndex(0); array_b.removeIndex(10);
        cout << "removeIndex(0) & removeIndex(10): "; displayArrayList(array_b);
        array_b.removeRange(0,3);
        cout << "removeRange(0,3): "; displayArrayList(array_b);

    cout << "\n### Part IV : method subList ###" << endl;
        ArrayList<char> array_c;
        array_c = array_a.subList(1,3);
        cout << "subList(1,3): "; displayArrayList(array_c);

    cout << "\n### Part V : method explicit ArrayList ###" << endl;
        ArrayList<int> array_exp_a(link_a);
        for (int i = 0; i < array_exp_a.size(); i++) cout << array_exp_a.get(i) << " ";
        cout << endl;

	cout << "\n--- Testing TreeSet.h ---" << endl;
        TreeSet<int> treeset_a;
    cout << "\n### Part I : method Add ###" << endl;
        for (int i = 1; i <= 10; i++) treeset_a.add(i);
        displayTreeSet(treeset_a);
        treeset_a.clear();

    cout << "\n### Part II : method Get & Contains ###" << endl;
        for (int i = 1; i <= 12; i++) treeset_a.add(i);
        displayTreeSet(treeset_a);
        cout << "first() : " << treeset_a.first() << "\tlast() : " << treeset_a.last() << endl;
        cout << ((treeset_a.contains(2))?("contains 2"):("not contains 2")) << endl;
        cout << ((treeset_a.contains(15))?("contains 15"):("not contains 15")) << endl;

    cout << "\n### Part III : method Remove ###" << endl;
        TreeSet<int> treeset_b(treeset_a);
        treeset_b.remove(3);
        cout << "remove(3) : "; displayTreeSet(treeset_b);
        treeset_b.remove(10);
        cout << "remove(10) : "; displayTreeSet(treeset_b);
        TreeSet<int>::Iterator treeset_iter = treeset_b.iterator();
        treeset_iter.next();
        treeset_iter.remove();
        cout << "remove the first element using Iterator::remove() : "; displayTreeSet(treeset_b);*/

	cout << "\n--- Testing HashSet.h ---" << endl;
    HashSet<int,Hashint> hashset_a(7);
    cout << "\n### Part I : method Add ###" << endl;
        for (int i = 1; i <= 10; i++) hashset_a.add(i);

        displayHashSet(hashset_a);
        hashset_a.clear();

    cout << "\n### Part II : method Get & Contains ###" << endl;
        for (int i = 1; i <= 12; i++) hashset_a.add(i);
        displayHashSet(hashset_a);
        cout << ((hashset_a.contains(2))?("contains 2"):("not contains 2")) << endl;
        cout << ((hashset_a.contains(15))?("contains 15"):("not contains 15")) << endl;

    /*cout << "\n### Part III : method Remove ###" << endl;
        HashSet<int,Hashint> hashset_b(treeset_a);
        hashset_b.remove(3);
        cout << "remove(3) : "; displayHashSet(hashset_b);
        hashset_b.remove(10);
        cout << "remove(10) : "; displayHashSet(hashset_b);
        HashSet<int,Hashint>::Iterator hashset_iter = hashset_b.iterator();
        hashset_iter.next();
        hashset_iter.remove();
        cout << "remove the first element using Iterator::remove() : "; displayHashSet(hashset_b);

    cout << "\n### Part IV : method explicit HashSet ###" << endl;
        HashSet<int,Hashint> hashset_exp_a(treeset_a);
        displayHashSet(hashset_exp_a);*/

	/*cout << "\n--- Testing TreeMap.h ---" << endl;
    TreeMap<int,char> treemap_a;
    cout << "\n### Part I : method Add ###" << endl;
       for (int i = 1; i <= 10; i++) treemap_a.put(i,i+64);
        displayTreeMap(treemap_a);
        treemap_a.clear();

    cout << "\n### Part II : method Get & Contains ###" << endl;
        for (int i = 1; i <= 12; i++) treemap_a.put(i,i+64);
        displayTreeMap(treemap_a);
        cout << "firstKey() : " << treemap_a.firstKey() << "\t";
        cout << "firstEntry() : (" << treemap_a.firstEntry().key << "," << treemap_a.firstEntry().value << ")"<< endl;
        cout << "lastKey() : " << treemap_a.lastKey() << "\t";
        cout << "lastEntry() : (" << treemap_a.lastEntry().key << "," << treemap_a.lastEntry().value << ")" << endl;
        cout << ((treemap_a.containsKey(2))?("contains Key 2"):("not contains Key 2")) << endl;
        cout << ((treemap_a.containsKey(15))?("contains Key 15"):("not contains Key 15")) << endl;
        cout << ((treemap_a.containsValue('A'))?("contains Value A"):("not contains Value A")) << endl;
        cout << ((treemap_a.containsValue('Z'))?("contains Value Z"):("not contains Value Z")) << endl;

    cout << "\n### Part III : method Remove ###" << endl;
        TreeMap<int,char> treemap_b(treemap_a);
        treemap_b.remove(3);
        cout << "remove(3) : "; displayTreeMap(treemap_b);
        treemap_b.remove(10);
        cout << "remove(10) : "; displayTreeMap(treemap_b);
        TreeMap<int,char>::Iterator treemap_iter = treemap_b.iterator();
        treemap_iter.next();
        treemap_iter.remove();
        cout << "remove the first Entry using Iterator::remove() : "; displayTreeMap(treemap_b);*/

	cout << "\n--- Testing HashMap.h ---" << endl;
    HashMap<int,char,Hashint> hashmap_a(7);
    cout << "\n### Part I : method Add ###" << endl;
        for (int i = 1; i <= 10; i++) hashmap_a.put(i,i+64);
        displayHashMap(hashmap_a);
        hashmap_a.clear();

    cout << "\n### Part II : method Get & Contains ###" << endl;
        for (int i = 1; i <= 12; i++) hashmap_a.put(i,i+64);
        displayHashMap(hashmap_a);
        cout << ((hashmap_a.containsKey(2))?("contains Key 2"):("not contains Key 2")) << endl;
        cout << ((hashmap_a.containsKey(15))?("contains Key 15"):("not contains Key 15")) << endl;
        cout << ((hashmap_a.containsValue('A'))?("contains Value A"):("not contains Value A")) << endl;
        cout << ((hashmap_a.containsValue('Z'))?("contains Value Z"):("not contains Value Z")) << endl;

    cout << "\n### Part III : method Remove ###" << endl;
        HashMap<int,char,Hashint> hashmap_b(hashmap_a);
       hashmap_b.remove(3);
        cout << "remove(3) : "; displayHashMap(hashmap_b);
        hashmap_b.remove(10);
        cout << "remove(10) : "; displayHashMap(hashmap_b);
        HashMap<int,char,Hashint>::Iterator hashmap_iter = hashmap_b.iterator();
        hashmap_iter.next();
        hashmap_iter.remove();
        cout << "remove the first Entry using Iterator::remove() : "; displayHashMap(hashmap_b);

    cout << "Hello World!" << endl;
}
