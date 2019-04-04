
// Guillermo Arriaga Garcia
// Metodos Numericos Demat-Cimat 2013
// Clase Matriz


#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;


class MATRIZ{

   // Todo es publico
   public:
      int ren,col;
      double** celda;
      double* x;               // Resultados
      int *renglon, *columna;  // Para registrar intercambios
      char nombre;

   // Constructor y destructor

   MATRIZ(int nr=1,int nc=1,char nom='X');
   ~MATRIZ();

   // Funciones
   void desde(char* Fmat,char tipo='B', bool vec=0); // Captura desde archivo
   void hacia(char* Fmat, char tipo='B');            // Graba vector
   void resultados(const MATRIZ &Vec);   // Captura resultados, Mat nxn
   void liberar();                       // Libera memoria de la matriz
   void nueva(int nr,int nc,char nom);   // Libera lo anterior y crea nueva
   void imprimir(bool resultados=0);
   double norma1();                      // Norma 1: suma de valores absolutos
   double norma2();                      // Norma euclidea
   double norma3();                      // Norma infinito: max val abs

   void pivPAR(int reng);                // Pivoteo parcial
   void pivGAG();
   double ABS (double d);
   double RAIZ(double a, int iter=500);
   void DESintercambio();
   double TRUNC(double a, int dig);
   double POT(double a, int exp);

// Eliminacion Gaussiana
   void RedGauss(int tipo_pivoteo=0); // Eliminacion Gaussiana
   void COLUMNAintercambio(int c1, int c2);
   void RENGLONintercambio(int r1, int r2);
   void RENGLONsuma(int r1, double a1, int r2, double a2);
   void RENGLONprod(int r1, double a1);
   int  PIVOTEOtotal(int columna, bool inspeccion=0);
   int  PIVOTEOparcial(int columna, bool inspeccion=0);
   void RedGaussTRUNC(int tipo_pivoteo=0, int tr=2);
   void RENGLONsumaTRUNC(int r1, double a1, int r2, double a2, int tr=2);
   void truncar(int tr=2);

// Factorizacion LU
   void U (const MATRIZ &LU);
   void L (const MATRIZ &LU);
   void LU(const MATRIZ &B);

   MATRIZ susATR();                       // Para reduccion gaussiana
   MATRIZ susATR(const MATRIZ &Vec);      // Para evaluar diferentes vectores
   MATRIZ susADE(const MATRIZ &Res);

// Inversa de A (sin pivoteo)
   MATRIZ inversa();
   MATRIZ transpuesta();

// Iterativo Gauss-Seidel Converge si es def positiva o diagonal dominante
   MATRIZ GS(const MATRIZ &A, const MATRIZ &B, double relax=1, int iter=1000);
   //  Graba G y M tq x=Gx+M
   void GS(const MATRIZ &A, const MATRIZ &B,MATRIZ &G, MATRIZ &M);
   MATRIZ GaussSeidel(MATRIZ &A, MATRIZ &B,double relax=1, int iter=1000);
   MATRIZ Jacobi(MATRIZ &A, MATRIZ &B,double relax=1, int iter=1000);
   
   MATRIZ Givens(int i, int j);


   // Sobrecarga de Operadores
   void   operator=(const MATRIZ &B);
   MATRIZ operator+(const MATRIZ &B);
   MATRIZ operator-(const MATRIZ &B);
   MATRIZ operator*(const MATRIZ &B);
   MATRIZ operator*(double d);
   MATRIZ operator/(double d);

   void suma(const MATRIZ &B,const MATRIZ &C);
   void producto(const MATRIZ &B,const MATRIZ &C);
   void igual(const MATRIZ &B);


};


#endif // MATRIZ_H
