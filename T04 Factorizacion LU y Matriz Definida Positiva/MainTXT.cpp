
// Guillermo Arriaga Garcia
// Metodos Numericos Demat Cimat 2013
// Tarea 4 Factorizacion LU con entrada de archivos de texto


#include "Matriz.h"
#include "Matriz.cpp"


int main(int argc, char *argv[]){

   MATRIZ A1(1,1,'A'),V1(1,1,'V'),LU,L,U,RESULTADO(1,1,'R');

   if(argc>1){
      A1.desde(argv[1],'T');
      V1.desde(argv[2],'T',1);
      A1.resultados(V1);
   }
   else{
      A1.desde("matA1.txt",'T');
      V1.desde("vecb1.txt",'T',1);
      A1.resultados(V1);
   }

   //A1.imprimir(1);

   // LU tiene juntas a L y a U
   LU.LU(A1);
   L.L(LU);
   U.U(LU);
   L.imprimir();
   U.imprimir();
   //(L*U).imprimir();

   // Valores solucion
   RESULTADO=(U.susATR( L.susADE(V1) ));
   RESULTADO.imprimir();

   // Comprobacion
   // (A1*RESULTADO).imprimir();
   // V1.imprimir();

   // Error
   cout<<"\n\nError = |Ax-B| = "<<(((A1*RESULTADO)-V1).norma1())<<" Usando la norma 1"<<endl;

   // El destructor libera la memoria pedida

   return 0;
}
