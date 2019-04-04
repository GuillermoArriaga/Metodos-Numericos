
// Guillermo Arriaga Garcia
// Metodos Numericos Demat Cimat 2013
// Examen Practico 1


#include "Matriz.h"
//#include "Matriz.cpp"
#include <cmath>

void MinCuad_examen(int m, char* archivo, char tipo='B', bool impresion=0);
void Seidel(int n, double gama);

int main(){


   // Seccion de minimos cuadrados ************************************

   MinCuad_examen(20,"Ex1_Coef_20.bin",'B');
   MinCuad_examen(40,"Ex1_Coef_40.bin",'B');
   MinCuad_examen(80,"Ex1_Coef_80.bin",'B');

   MATRIZ C1,C2,C3;

   // Comparacion de coeficientes para distinta cantidad de datos
   C1.desde("Ex1_Coef_20.bin",'B',1);
   C1.imprimir();
   C2.desde("Ex1_Coef_40.bin",'B',1);
   C2.imprimir();
   C3.desde("Ex1_Coef_80.bin",'B',1);
   C3.imprimir();

   // Los coeficientes se guardaron en binario, sin truncamiento, y las restas son cero
   (C1-C2).imprimir();
   (C1-C3).imprimir();
   (C2-C3).imprimir();


   /******************************************************* REPORTE
     Los coeficientes sí han variado con 20, 40 y 80 datos.
     En la corrida sale la informacion de los errores de ajustes y los valores de los coeficientes
   */



   // Parte de Gauss Seidel **********************************************
   Seidel(100,0.5);
   Seidel(100,0.75);
   Seidel(100,1.0);

   return 0;
}


void MinCuad_examen(int m, char* archivo, char tipo, bool impresion){

   MATRIZ X(m+1,1,'x'),Y(m+1,1,'y');

   // Generacion de puntos


   for(int i=1;i<=m;i++){
      X.celda[i][0]=3.14159265359*(i-1)/(m-1);
      Y.celda[i][0]=sin(X.celda[i][0]);

      if(impresion){
         X.imprimir();
         Y.imprimir();
      }
   }



   // Solucion de ecuaciones normales

   double SX1=0, SX2=0, SX3=0, SX4=0, SY=0, SYX1=0, SYX2=0;

   // Coeficientes del sistema 3x3 deducidos en hoja entregada
   for(int i=1;i<=m;i++){
      SX1+=X.celda[i][0];
      SX2+=X.celda[i][0]*X.celda[i][0];
      SX3+=X.celda[i][0]*X.celda[i][0]*X.celda[i][0];
      SX4+=X.celda[i][0]*X.celda[i][0]*X.celda[i][0]*X.celda[i][0];
      SY+=Y.celda[i][0];
      SYX1+=Y.celda[i][0]*X.celda[i][0];
      SYX2+=Y.celda[i][0]*X.celda[i][0]*X.celda[i][0];
   }

   MATRIZ A(3,3,'A');

   // Coeficientes de la matriz
   A.celda[0][0]=m;
   A.celda[0][1]=SX1;
   A.celda[0][2]=SX2;
   A.celda[1][0]=SX1;
   A.celda[1][1]=SX2;
   A.celda[1][2]=SX3;
   A.celda[2][0]=SX2;
   A.celda[2][1]=SX3;
   A.celda[2][2]=SX4;
   A.x[0]=SY;
   A.x[1]=SYX1;
   A.x[2]=SYX2;

   MATRIZ B(3,1),C,Coef;
   C=A;
   B.celda[0][0]=A.x[0];
   B.celda[1][0]=A.x[1];
   B.celda[2][0]=A.x[2];

   if(impresion){
      cout<<"\n\nMatriz de ecuaciones normales\n\n";
      A.imprimir(1);
   }
   C.RedGauss();
   //C.imprimir(1);
   Coef=C.susATR();
   Coef.imprimir();
   Coef.hacia(archivo,tipo);

   // Reporte del error

   cout<<"\n\nError |AX-B| norma 1 = "<<((A*Coef)-B).norma1()<<endl;


   // Error de la aproximacion
   MATRIZ Yestimada(m+1,1,'E');
   Y.celda[0][0]=0;
   Yestimada.celda[0][0]=0;

   for(int i=1;i<=m;i++){
      Yestimada.celda[i][0]=Coef.celda[0][0]+Coef.celda[1][0]*X.celda[i][0]+Coef.celda[2][0]*X.celda[i][0]*X.celda[i][0];
   }

   cout<<"\n\nError de la aproximacion |Y-Yestim|/|Y| norma 1: "<<(Y-Yestimada).norma1()/(Y.norma1())<<endl;
   cout<<"\n La estimacion en x1 es "<<Yestimada.celda[1][0];
   cout<<"\n La estimacion en xm es "<<Yestimada.celda[m][0]<<endl;

   //El destructor de Matriz libera la memoria

   return ;
}


void Seidel(int n, double gama){

   MATRIZ A(n,n,'A'),B(n,1,'B'),C;

   for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
         A.celda[i][j]=exp(-1*gama*(i-j)*(i-j));   // i-j no cambia en logica cero pues se suma y se resta 1.
      }
      B.celda[i][0]=sin(2*(i+1)*3.14159265359/n);  // i cambia a i+1 en lógica cero.
   }

   cout<<"\n ***** \nCon Gama "<<gama<<" y n "<<n<<endl;
   C.GaussSeidel(A,B,1,350);
   // Si se quiere ver el vector solucion activar la impresion en Matriz.cpp en el apartado de impresion segun iteraciones multiplos de 15

   return ;
}
