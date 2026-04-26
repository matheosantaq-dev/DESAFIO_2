#include "Medidor.h"

long long Medidor::iter = 0;
long long Medidor::mem = 0;

void Medidor::it(){ iter++; }
void Medidor::add(size_t b){ mem += b; }
void Medidor::sub(size_t b){ mem -= b; }

void Medidor::print(){
    cout << "Iteraciones: " << iter << endl;
    cout << "Memoria: " << mem << " bytes" << endl;
}
