
// Guillermo Arriaga Garcia
// Metodos Numericos Demat Cimat 2013
// Tarea 8  SVC Descomposicion espectral


#include "Matriz.h"
#include "Matriz.cpp"


int main(int argc, char **argv){

   MATRIZ A,U,S,V,A1;
   A.desde("imagen2.txt",'T');

   A.SVD(U,S,V);

   //(A-U*S*V.transpuesta()).imprimir();
   //U.imprimir();

   int fr=5; // Factor de reduccion
   A1=U.reducida(0,fr)*S.reducida(fr,fr)*(V.reducida(0,fr)).transpuesta();
   A1.hacia2("imred_5.txt");

   fr=15;
   A1=U.reducida(0,fr)*S.reducida(fr,fr)*(V.reducida(0,fr)).transpuesta();
   A1.hacia2("imred_15.txt");

   fr=25;
   A1=U.reducida(0,fr)*S.reducida(fr,fr)*(V.reducida(0,fr)).transpuesta();
   A1.hacia2("imred_25.txt");

   fr=50;
   A1=U.reducida(0,fr)*S.reducida(fr,fr)*(V.reducida(0,fr)).transpuesta();
   A1.hacia2("imred_50.txt");


   return 0;
}





/*  antiguo


int main(int argc, char **argv){

   MATRIZ A,B,C,D;  // C tendra los eigenvectores, D los eigenvalores

   A.desde("Ejemplo.txt",'T');

   B=A*A.transpuesta();


   C.nueva(B.ren,B.col,'C');
   D.nueva(B.ren,B.col,'D');

   // ************************************************************
   // Eigen valores con metodo de la potencia

   MATRIZ Y(B.col,1), V(B.col,1,'V'),V2;
   double lam,resultadoanterior;
   double tolerancia=0.00000001; // 10^-8



   for(int j=0;j<A.ren;j++){

      int iteraciones=0;
      V=1.0;
      resultadoanterior=0;
      do{
         Y=B*V;
         V=Y/Y.norma2();
         lam=((V.transpuesta())*B*V).celda[0][0];
         //cout<<lam<<" "<<(Y-V*lam).norma1()<<endl;
         iteraciones++;

         // Si los resultados son similares, avanza en iteraciones pues puede ya no mejorar
         if(abs(resultadoanterior/(Y-V*lam).norma1())<2)
            iteraciones+=20;
         resultadoanterior=(Y-V*lam).norma1();

      }while(resultadoanterior>tolerancia && iteraciones<1000);

      C.NewCol(V,j);
      D.celda[j][j]=lam;


      // Supresion del eigenvalor mayor, antes encontrado
      V2=V/V.norma2();
      B=B-((V*V2.transpuesta())*lam);

   }


   // Ya se tienen los eigenvalores y eigen vectores de la matriz




   // *****************************************************************
   // Base ortonormal de eigen vectores

   C.Ortonormalizacion();
   D.EigenValor(A,C);

      // Se ponen no negativos los eigenvalores
   for(int j=0;j<D.col;j++){
      if(D.celda[j][j]<0){
         D.celda[j][j]*=(-1.0);
         V=C.GetCol(j);
         V=V*(-1.0);
         C.NewCol(V,j);
      }
   }


   C.imprimir();
   D.imprimir();


   return 0;
}



*/
