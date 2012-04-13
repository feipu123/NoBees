#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "../source/ArrayList.h"
#include "../source/Utility.h"

using namespace std;

int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    ArrayList<int> list;
    for (int i = 0; i < 30; ++i) {
        list.add(i + 1);
    }
    cout << list.size() << endl;



    for (int i = 0; i < 30; ++i) {
        cout << list.get(i) << endl;
        //system("pause");
    }



return 0;
}
