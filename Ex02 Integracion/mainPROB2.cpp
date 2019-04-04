
// Guillermo Arriaga Garcia
// Metodos Numericos Demat Cimat 2013
// Problema 2 examen 2.


#include "Matriz.h"
#include "Matriz.cpp"


int main(int argc, char **argv){

   MATRIZ A,X,B,C,U,S,V,A1;
   double N=1000;


   X.desde("x.bin",'B');
   // X es una matriz de 1000 x 10


   // Calculo del centroide de los datos
   MATRIZ MU(10,1,'m'); // Lo inica con ceros
   for(int i=0;i<10;i++){
      for(int j=0;j<N;j++){
         MU.celda[i][0]+=X.celda[i][j];
      }
   }
   MU=MU/1000;  // MU es el centroide
   A=X.transpuesta();
   B=A;

   for(int i=0;i<N;i++){
     B.NewCol((A.GetCol(i)-MU),i);
   }
   B=B.transpuesta();
   C=B.transpuesta()*B;



   C.SVD(U,S,V);   // Descomposicion espectral de C


   // Error aproximacion SVD
   cout<<"\nError de calculo SVD: "<<(U*S*V.transpuesta()-C).norma1()/N;


   // Calculo del K más pequeño
   double suma,suma2;
   int K;
   suma=0;

   cout<<"\n\nValores propios X.trans * X :\n";

   for(int i=0;i<S.col;i++){
      suma+=S.celda[i][i];
      cout<<S.celda[i][i]<<" ";
   }
   suma2=0;
   for(K=0;(suma2/suma)<0.95;K++){
      suma2+=S.celda[K][K];
   }

   // K ya tiene su valor minimo
   cout<<"\n\nEl valor minimo de K es "<<K<<endl;





   // El error de aproximacion promedio es:
   A1=U.reducida(0,K)*S.reducida(K,K)*(V.reducida(0,K)).transpuesta();
   A1.hacia("Aprox.bin",'B');

   // C es Xtrans * X
   // A1 es la aproximacion con un solo eigenvector.

   cout<<"\n\nEl error de aproximacion promedio es "<<(C-A1).norma1()/N;

   cout<<"\n\nLa economizacion de espacio es : \n"
       <<"10 por mu, K*(10) para los K eigenvectores "
       <<"y N*K para los coeficientes xkT . Vi"
       <<"\n\nEn total se requieren 10 + (10+N)K espacios para double."
       <<"\n\nEn este caso K=1, N=1000 y se requieren N+20=1020 espacios para double.\n\n\n";

   return 0;
}

