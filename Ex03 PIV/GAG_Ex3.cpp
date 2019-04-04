// GAG Runge Kutta

#include <iostream>
#include <math.h>

using namespace std;


// Funcion del problema. No requiere y pero se deja de modo ilustrativo
//   para ver el desarrollo del metodo de Runge Kutta
double f(double x, double y, double alfa){
   return (x*x+x-1)*exp(x-alfa);
}

double g_prima(double alfa){
   return ( f(0.5,0,alfa) );
}


double RungeKutta(int divisiones, double alfa);
double g_p(int divisiones, double alfa, double h);
int revision(int divisiones,double h);
int revision2(int divisiones);





int main(){

   // Chequeo. No funciona bien da valores de alfa negativos y de magnitud mayor tras cada iteracion
   cout<<"Primer chequeo pues no funciona bien:\n";
   double alfa=3;
   double g=RungeKutta(10,alfa)-4;
   double p=g_p(10,alfa,0.1);

   for(int i=0;i<100;i++){
      g=RungeKutta(10,alfa)-4;
      p=g_prima(alfa);
      alfa=alfa-g/p;
      cout<<alfa<<"\t";
   }

   cout<<"Segundo chequeo pues no funciona bien:\n";
   // Chequeo.
   alfa=0;
   for(int i=0;i<10;i++){
      g=RungeKutta(10,alfa)-4;
      p=g_p(10,alfa,0.1);   // estimando la derivada
      alfa=alfa-g/p;
      cout<<alfa<<"\t";
   }
   // Falla peor.

   // No encuentro la falla. Los métodos usados siguen su algoritmo.
   //   Runge Kutta esta como en la tarea, minimas modificaciones.

   // Ultimo intento de solucion: Evaluacion directa para buscar lugar de una raíz
   for(int i=0;i<100;i++){
      cout<<RungeKutta(100,-0.2*i)-4<<" g con alfa = "<<0.1*i<<endl;
   }




   // +++++++++++++++++++++++++
   // Resultado principal

   cout<<"\n\n\nDivis\th\talfa\terror\t\titer"<<endl;
   // Poner divisiones entre dos, se calcula con el doble de lo puesto
   revision(5,0.1);
   revision(5,0.01);
   revision(10,0.1);
   revision(10,0.01);
   revision(30,0.1);
   revision(30,0.01);
   revision(100,0.1);
   revision(100,0.01);

   cout<<"\n\nDivis\talfa\terror\t\titer"<<endl;
   revision2(5);
   revision2(10);
   revision2(30);
   revision2(100);
   revision2(200);
   revision2(500);



   return (0);
}









int revision(int divisiones,double h){
   double alfa,y,g,g2;
   int iteraciones;

   alfa=1;
   g2=1; // valor arbitrario


   for(iteraciones=1; g2 < 0.0000001 ; iteraciones++){

      g = RungeKutta(divisiones,alfa)-4; // Es y(0.5,alfa)-4=g(alfa)

      if(g<0){
         g2=(-1)*g;
      }
      else{
         g2=g;
      }

      if(g2 >= 0.0000001 ){
         //alfa=alfa-g/g_prima(alfa); // la derivada de g es la de y, que se tiene desde el inicio
         alfa=alfa-g/g_p(divisiones,alfa,h);
      }


   }

   cout<<divisiones*2<<"\t"<<h<<"\t"<<alfa<<"\t"<<g2<<"\t"<<iteraciones<<endl;

   return 0;

}





// Metodo de Runge Kutta de 4to orden
double RungeKutta(int divisiones, double alfa){

   double h,x,y,k1,k2,k3,k4,intervalo;

   // Valores iniciales
   x=0;
   y=0;
   intervalo=1;  // x0 + intervalo = medida del intervalo

   // Como se busca el valor en 0.5, la mitad del intervalo,
   // se llega con la mitad de divisiones.
   // Así que se manejara el metodo de runge kutta en [0,0.5] y n divisiones
   // pensando que se ocupó el doble de divisiones en [0,1]

   // Por lo que:
   intervalo=0.5;
   h=intervalo/divisiones;



   for(int i=0;i<divisiones;i++){
      x=x+h;
      k1=h*f(x,y,alfa);
      k2=h*f(x+h/2,y+k1/2,alfa);
      k3=h*f(x+h/2,y+k2/2,alfa);
      k4=h*f(x+h,y+k3,alfa);

      y=y+(k1+2*k2+2*k3+k4)/6;
   }

   return (y);
}




double g_p(int divisiones, double alfa, double h){
   return( (RungeKutta(divisiones,alfa-h) - RungeKutta(divisiones,alfa+h) )/(2*h) );
}


// Sin estimar la derivada, sino usando la derivada de y
int revision2(int divisiones){
   double alfa,y,g,g2;
   int iteraciones;

   alfa=0;
   g2=1; // valor arbitrario


   for(iteraciones=1; g2 < 0.0000001 ; iteraciones++){

      g = RungeKutta(divisiones,alfa)-4; // Es y(0.5,alfa);

      if(g<0){
         g2=(-1)*g;
      }
      else{
         g2=g;
      }

      if(g2 >= 0.0000001 ){
         alfa=alfa-g/g_prima(alfa);
      }
   }

   cout<<divisiones*2<<"\t"<<alfa<<"\t"<<g2<<"\t"<<iteraciones<<endl;

   return 0;

}
