
// Guillermo Arriaga Garcia
// Metodos Numericos Demat Cimat 2013
// Tarea 8  SVC Descomposicion espectral


#include "Matriz.h"
#include "Matriz.cpp"


int main(int argc, char **argv){

   // Ya teniendo los resultados que mainT08.cpp hace
   //   Aqui se comparan las similitudes de las imagenes pues scilab se me ha trabado

   MATRIZ A,A5,A15,A25,A50;
   A.desde("imagen2.txt",'T');
   A5.desde("Bimred_5.txt",'T');
   A15.desde("Bimred_15.txt",'T');
   A25.desde("Bimred_25.txt",'T');
   A50.desde("Bimred_50.txt",'T');

   // Redondeo a enteros

   for(int i=0;i<512*512;i++){
      A5.celda[0][i]=(A5.celda[0][i]+0.5);
      A15.celda[0][i]=(A15.celda[0][i]+0.5);
      A25.celda[0][i]=(A25.celda[0][i]+0.5);
      A50.celda[0][i]=(A50.celda[0][i]+0.5);
   }

   A5.truncar(0);
   A15.truncar(0);
   A25.truncar(0);
   A50.truncar(0);

   cout<<"\nLas imagenes reducidas distan de la original por\n\n";
   cout<<"La de 5 vectores dista "<<(A-A5).norma1()/(512*512)<<endl;
   cout<<"La de 15 vectores dista "<<(A-A15).norma1()/(512*512)<<endl;
   cout<<"La de 25 vectores dista "<<(A-A25).norma1()/(512*512)<<endl;
   cout<<"La de 50 vectores dista "<<(A-A50).norma1()/(512*512)<<endl;


   return 0;
}


