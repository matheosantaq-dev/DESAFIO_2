#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <iostream>
using namespace std;

class Medidor{
public:
    static long long iter, mem;

    static void it();
    static void add(size_t b);
    static void sub(size_t b);
    static void print();
};

#endif
