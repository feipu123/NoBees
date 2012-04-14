#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "ArrayList.h"
#include "Utility.h"

using namespace std;

int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    ArrayList<int> list;
    for (int i = 0; i < 10; ++i) {
        list.add(i + 1);
    }
    cout << list.size() << endl;

    for (ArrayList<int>::ConstIterator iter = list.constIterator(); iter.hasNext();) {
        cout << iter.next() << endl;
    }



     for (int i = 0; i < 10; ++i) {
        cout << list.get(i) << endl;

     }
     //system("pause");


return 0;
}
