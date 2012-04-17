/*
 * LinkedList<int>
 * append test
 * get test
 * iterator test
 */
#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <cstdlib>
using namespace std;

ofstream fout("judge.out");

void goWA() {
    cerr << "WRONG ANSWER" << endl;
    fout << 0 << endl;
    exit(0);
}

void goAC() {
    cerr << "ACCEPTED" << endl;
    fout << 1 << endl;
    exit(1);
}

const int TEST_SEQ_LEN = 10;
int test_seq[TEST_SEQ_LEN] = {2, 22, 222, 2222, 22222, 172, 827, 572287, -9998, 62};

int main() {
    LinkedList<int> l, copy_1, copy_2;
    for (int i = 0; i < TEST_SEQ_LEN; ++i) {
        l.add(test_seq[i]);
    }
    LinkedList<int>::Iterator iter = l.iterator();
    for (int i = 0; i < TEST_SEQ_LEN; ++i) {
        if (iter.next() != test_seq[i]) {
            goWA();
        }
        if (i % 2 == 1) {
            iter.remove();
        }
    }
    iter = l.iterator();
    for (int i = 0; i < 5; ++i) {
        if (iter.next() != test_seq[2 * i]) {
            goWA();
        }
    }
    goAC();
    return 0;
}


