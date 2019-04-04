
// Guillermo Arriaga Garcia
// Metodos Numericos Demat Cimat 2013
// Tarea 4 Factorizacion LU con archivos binarios


#include "Matriz.h"
// #include "Matriz.cpp"


int main(int argc, char *argv[]){

   MATRIZ A1,V1,X,Y,Z;

   if(argc>1){
      A1.desde(argv[1],'B');
      V1.desde(argv[2],'B',1);
      A1.resultados(V1);
   }
   else{
      A1.desde("Ags.bin",'B');
      V1.desde("bgs.bin",'B',1);
      A1.resultados(V1);
   }

   //A1.imprimir();
   //V1.imprimir();


   double w=1.0;
   int iteraciones=10000;

   X=X.GaussSeidel(A1,V1,w,iteraciones);
   cout<<"\nError operando entrada por entrada: "<<(A1*X-V1).norma1()<<endl;
   X.hacia("RESUL_gseidel.bin");


   //X=X.GS(A1,V1,w,iteraciones);
   //cout<<"\nError operando de modo matricial: "<<(A1*X-V1).norma1()<<endl;

   // Jacobi
   X=X.Jacobi(A1,V1,1,iteraciones);
   cout<<"\nError operando de modo matricial Jacobi: "<<(A1*X-V1).norma1()<<endl;


   // Crea el archivo con resultado, para graficar con Scilab
   X.hacia("RESUL_jacobi.bin");

   Y.desde("RESUL_jacobi.bin",'B',1);
   //Y.imprimir();
   Z.desde("RESUL_gseidel.bin",'B',1);
   //Z.imprimir();



   // El destructor libera la memoria pedida

   return 0;
}
