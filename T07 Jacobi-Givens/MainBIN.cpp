
// Guillermo Arriaga Garcia
// Metodos Numericos Demat Cimat 2013
// Tarea 7


#include "Matriz.h"
#include "Matriz.cpp"

int main(int argc, char **argv){

   //********************************************************   Jacobi-Givens

   MATRIZ A(3,3,'A'),G(3,3,'G');
   
   A.celda[0][0]=2;
   A.celda[0][1]=1;
   A.celda[0][2]=-1;
   A.celda[0][3]=1;
   A.celda[0][4]=5;
   A.celda[0][5]=-2;
   A.celda[0][6]=-1;
   A.celda[0][7]=-2;
   A.celda[0][8]=4;
   
   cout<<"\n\n\tIteracion de Jacobi A(0)\n";
   A.imprimir();
   

   // Rotaciones de Givens
   
   G=A.Givens(1,0);
   cout<<"\n\n\tRotacion de Givens (2,1)\n";
   G.imprimir();
   MATRIZ A1=(G.transpuesta()*(A*G));
   cout<<"\n\n\tIteracion de Jacobi A(1)\n";
   A1.imprimir();

   G=A1.Givens(2,0);
   cout<<"\n\n\tRotacion de Givens (3,1)\n";
   G.imprimir();
   MATRIZ A2=(G.transpuesta()*(A1*G));
   cout<<"\n\n\tIteracion de Jacobi A(2)\n";
   A2.imprimir();

   G=A2.Givens(2,1);
   cout<<"\n\n\tRotacion de Givens (3,2)\n";
   G.imprimir();
   MATRIZ A3=(G.transpuesta()*(A2*G));
   cout<<"\n\n\tIteracion de Jacobi A(3)\n";
   A3.imprimir();
   
   cout<<"\n\nLas entradas fuera de la diagonal de A(3) son muy "
       <<"pequeñas en comparación con las de la diagonal. En comparacion "
       <<"con las correspondientes entradas de A(0), son las pequeñas de la "
       <<"matriz, y la grande de entre ellas, se ha vuelto casi cero en A(3).\n\n";
   
   double e1=1.5708263, e2=2.4698323, e3=6.9593414;  // Eigenvalores de A(0)
   
   cout<<"La precision con la que los elementos de la diagonal de A(3) aproximan "
       <<"a los eigenvalores de A(0), que son "<<e1<<"  "<<e3<<"  "<<e2<<"  es de "
       <<"una a dos decimas. Con un error promedio de ";
   
   MATRIZ RES(3,1);
   
   RES.celda[0][0]=e1-A3.celda[0][0];
   RES.celda[0][1]=e3-A3.celda[1][1];
   RES.celda[0][2]=e2-A3.celda[2][2];

   cout<<RES.norma1()/3<<endl;
   
   
   
   
   
   
   
   //************************************************************   Hoseholder
   MATRIZ X(3,1,'X');
   X.celda[0][0]=0.333333333333333333333333333333;
   X.celda[0][1]=-2*0.333333333333333333333333333333;
   X.celda[0][2]=-2*0.333333333333333333333333333333;
  
   char g;
   cin>>g;
   
   return 0;
}



