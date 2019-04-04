
#include "Matriz.h"
#include "Matriz.cpp"


int main(){
   MATRIZ A(2,3,'A'),B(3,1,'B'),C;

   for(int i=0;i<6;i++){
      A.celda[0][i]=i*i+1;
   }

   B.celda[0][0]=2;
   B.celda[0][1]=3;
   B.celda[0][2]=4;

   C=(A+A);
   (B+B).imprimir();
   C.imprimir();
   A.imprimir();
   B.imprimir();
   C=(A*(B*3))/2;
   C.imprimir();



   // El destructor libera la memoria pedida

   return 0;
}
