

// Guillermo Arriaga Garcia
// Reduccion Gaussiana Y truncamientos

#include "Matriz.h"
//#include "Matriz.cpp"


int main(int argc, char *argv[]){

   MATRIZ A,B,C,X;

   if(argc>1){
      A.desde(argv[1],'T');
      B.desde(argv[2],'T',1);
      A.resultados(B);
      A.imprimir(1);
   }
   else{
      A.desde("Mat4.txt",'T');
      B.desde("Vec4.txt",'T',1);
      A.resultados(B);
      A.imprimir(1);
   }

   C=A;
   C.RedGauss();
   C.imprimir();
   X=C.susATR();

   cout<<"\n\nResultados\n";
   X.imprimir();

   // Error  |AX-B|
   cout<<"\n\nEl error |AX-B| con norma 1 es "<<(A*X-B).norma1()<<endl;

   // Con truncamiento a dos digitos

   A.truncar();
   B.truncar();
   C=A;
   C.RedGaussTRUNC(0,2);
   //C.imprimir();
   X=C.susATR();

   cout<<"\n\nResultados con datos truncados\n";
   X.imprimir();

   // Error  |AX-B|
   cout<<"\n\nEl error |AX-B| N1 datos truncados "<<(A*X-B).norma1()<<endl;


   // El destructor libera la memoria pedida

   return 0;
}
