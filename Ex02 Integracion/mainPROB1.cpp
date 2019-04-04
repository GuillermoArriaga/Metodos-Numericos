
// Guillermo Arriaga García

// Problema 1, segundo examen.


#include <iostream>
#include <math.h>

using namespace std;

double f(double x);
double F(double a, double b, int n);
void   evaluador(double a, double b, int nivel);
double abs(double y);

double integral;





int main(){


   // Newton Rhapson para hallar una raíz

   double x,y;

   x=7;



   do{
      y=F(0,x,10);
      x=x-y/f(x);
      //cout<<x<<y<<endl;
   }while(abs(y)>0.000001);

   cout<<"El valor F( "<<x<<" )="<<y<<" por lo que es un cero de los buscados."<<endl;


   return 0;
}


double f(double x){
   return exp(-x*x)-0.75*exp(-0.25*(x-6)*(x-6));
}

double F(double a, double b, int nivel){

   integral=(f(b)+f(a))/2;  // Metodo del trapecio
   evaluador(a,b,nivel);
   integral*=pow(2,-(nivel+1)); // Multiplicacion por el ancho

   return  integral;
}


// Particiones por mitad
void evaluador(double a, double b, int nivel){

   if(nivel-1){
      // Recorrido de arbol binario
      evaluador(a,(a+b)/2.0,nivel-1);
      evaluador((a+b)/2.0,b,nivel-1);
   }
   else{
      integral+=f((a+b)/2.0);
   }
}


double abs(double y){
   if(y<0){
      y=y*-1;
   }
   return y;
}
