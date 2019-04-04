
// Metodos numericos 2013 Tarea 2
// Guillermo Arriaga Garcia

// Creacion y operacion de matrices




#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define SALIDA cout<<"\n\nUna tecla para salir  "; char g; cin >> g; return(0);


double** createMatrix(int nr, int nc);
double** prodMatrix(double **M1, double **M2,int nr,int nc);
double** sumMatrix(double **M1, double **M2,int nr,int nc);
void printMatrix(double **mat,int nr, int nc, char nombre);
void freeMatrix(double **mat);


int main(int argc, char **argv){

   int n;

   // Captura desde consola de dimension
   if(argc>1){
      n=atoi(argv[1]);
   }
   else {
      n=4;
   }


   double **A=createMatrix(n,n);
   double **B=createMatrix(n,n);

   // Inicializacion
   for(int i=0;i<n;++i){
      for(int j=0;j<n;++j){
         A[i][j]=i+j;
         B[i][j]=i*j;
      }
   }

   printMatrix(A,n,n,'A');
   printMatrix(B,n,n,'B');

   double** C=sumMatrix(A,B,n,n);
   double** D=prodMatrix(A,B,n,n);

   printMatrix(C,n,n,'C');
   printMatrix(D,n,n,'D');

   freeMatrix(A);
   freeMatrix(B);
   freeMatrix(C);
   freeMatrix(D);

   //SALIDA
   return(0);

}



double** createMatrix(int nr, int nc) {
   int i;
   double** mat;

   // Un apuntador a los apuntadores de cada renglon

   mat = (double**) malloc( (nr)*sizeof(double *));
   if(mat==NULL) return(NULL);
   mat[0] = (double *) malloc( nr*nc*sizeof(double));

   if(mat[0]==NULL) return(NULL);
   for(i=1; i<nr; ++i)
      mat[i] = mat[i-1] + nc;
   return(mat);
}



void freeMatrix(double **mat){
   free (mat[0]);
   free (mat);
   return ;
}



void printMatrix(double **mat,int nr, int nc, char nombre){
   cout<<"\n\nMatriz "<<nombre<<endl;
   for(int i=0;i<nr;++i){
      for(int j=0;j<nc;++j){
         cout<<mat[i][j]<<" ";
      }
      cout << endl;
   }
   return ;
}


double** sumMatrix(double **M1, double **M2,int nr,int nc){

   double **M3=createMatrix(nr,nc);

   for(int i=0;i<nr;++i){
      for(int j=0;j<nc;++j){
         M3[i][j]=M1[i][j]+M2[i][j];
      }
   }

   return (M3);
}



double** prodMatrix(double **M1, double **M2,int nr,int nc){

   double **M3=createMatrix(nr,nc);

   for(int i=0;i<nr;++i){
      for(int j=0;j<nc;++j){
         M3[i][j]=0;
         for(int k=0;k<nc;++k){
            M3[i][j]+=M1[i][k]*M2[k][j];
         }
      }
   }

   return (M3);
}
