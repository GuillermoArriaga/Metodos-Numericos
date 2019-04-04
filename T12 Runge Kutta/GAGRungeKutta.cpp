// GAG Runge Kutta

#include <iostream>
#include <math.h>

using namespace std;



double f(double x, double y){return (2-x)*y;}
double g(double x){return exp(-(x-2)*(x-2)/2);}

void RungeKutta(int divisiones);
void Comparacion(int divisiones);


int main(){

   RungeKutta(8);
   RungeKutta(16);
   RungeKutta(32);
   RungeKutta(64);
   RungeKutta(128);
   RungeKutta(256);
   RungeKutta(512);

   Comparacion(64);
   Comparacion(128);
   Comparacion(512);

   cout<<"\n\nLa diferencia total con 32 divisiones, es menor y casi es la misma que con 64, 128, 256, 512 divisiones, por esto es buena opcion el hacer 32 divisiones.\n\n";

   return 0;
}





// Metodo de Runge Kutta de 4to orden
void RungeKutta(int divisiones){
   double h,x,y,k1,k2,k3,k4,minimo,maximo,diferencia,intervalo;
   // Valores iniciales
   x=2;
   y=4;
   intervalo=8;
   h=intervalo/divisiones;

   minimo=maximo=0;

   //cout<<x<<"\t"<<y<<"\t"<<(y-g(x))<<endl;

   for(int i=0;i<divisiones;i++){
      x=x+h;
      k1=h*f(x,y);
      k2=h*f(x+h/2,y+k1/2);
      k3=h*f(x+h/2,y+k2/2);
      k4=h*f(x+h,y+k3);

      y=y+(k1+2*k2+2*k3+k4)/6;

      diferencia=y-g(x);


      if(diferencia>maximo){
            maximo=diferencia;
      }
      if(diferencia<minimo){
            minimo=diferencia;
      }


      //cout<<x<<"\t"<<y<<"\t"<<diferencia<<endl;
   }


   cout<<"Con "<<divisiones<<"\t h="<<h<<"\t  MAX: "<<maximo<<"  \tMIN: "<<minimo<<"\t"<<endl;


}





void Comparacion(int divisiones){


   double h,x,y,x2,y2,h2,k1,k2,k3,k4,diferencia,intervalo;


   // Comparacion de nodos comunes entre "divisiones" y su mitad


   x2=x=2;
   y2=y=4;
   intervalo=8;
   h=intervalo/divisiones;
   h2=h*2;


   diferencia=0;

   for(int i=0;i<divisiones;i++){
      x=x+h;
      k1=h*f(x,y);
      k2=h*f(x+h/2,y+k1/2);
      k3=h*f(x+h/2,y+k2/2);
      k4=h*f(x+h,y+k3);

      y=y+(k1+2*k2+2*k3+k4)/6;


      if(i%2==1){

        x2=x2+h2;

        k1=h2*f(x2,y2);
        k2=h2*f(x2+h2/2,y2+k1/2);
        k3=h2*f(x2+h2/2,y2+k2/2);
        k4=h2*f(x2+h2,y2+k3);

        y2=y2+(k1+2*k2+2*k3+k4)/6;

        if(y2-y<0){
           diferencia+=y-y2;
        }
        else{
           diferencia+=y2-y;
        }
      }

   }


   cout<<"\nLa diferencia en nodos comunes de "<<divisiones<<" y "<<divisiones/2<<" divisiones:"
       <<"\n\tDiferencia Total: "<<diferencia
       <<"\n\tDiferencia Promedio: "<<diferencia/(divisiones/2)<<endl;


}
