#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "ArrayList.h"
#include "LinkedList.h"
#include "Utility.h"

using namespace std;

int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    ArrayList<int> list;
    LinkedList<int> llist;
    for (int i = 0; i < 10; ++i) {
        list.add(i + 1);
        llist.add(i * i);
    }
    cout << list.size() << endl;
    cout << llist.size() << endl;

    for (LinkedList<int>::ConstIterator iter = llist.constIterator(); iter.hasNext();) {
        cout << iter.next() << endl;
    }




     for (int i = 0; i < 10; ++i) {
        cout << list.get(i) << endl;

     }
     //system("pause");


return 0;
}
