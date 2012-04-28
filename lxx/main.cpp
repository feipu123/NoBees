#include <iostream>
#include <fstream>

#include "Utility.h"
#include "TreeSet.h"
using namespace std;

void displayTreeSet(TreeSet<int> a)
{
    TreeSet<int>::Iterator iter = a.iterator();
    while (iter.hasNext())
    {
        cout << iter.next() << " ";
    }
    cout << endl;
}

int main() {
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
        cout << "remove the first element using Iterator::remove() : "; displayTreeSet(treeset_b);
    while(1);
    return 0;
}

