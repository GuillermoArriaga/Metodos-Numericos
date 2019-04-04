
// Metodos numericos 2013 Epsilon Machine
// Guillermo Arriaga Garcia





#include <iostream>

using namespace std;

#define SALIDA cout<<"\n\nUna tecla para salir  "; char g; cin >> g; return(0);


int main(){

   float yf=2, epsf=1;
   double yd=2, epsd=1;
   long double yld=2, epsld=1;

   while(yf>1){
      epsf=epsf/2;
      yf=1+epsf;
   }

   epsf=2*epsf;

   cout << "\nEpsilon Machine para float de "<<epsf<<endl;

   while(yd>1){
      epsd=epsd/2;
      yd=1+epsd;
   }
   epsd=2*epsd;

   cout << "Epsilon Machine para double de "<<epsd<<endl;

   while(yld>1){
      epsld=epsld/2;
      yld=1+epsld;
   }
   epsld=2*epsld;

   cout << "Epsilon Machine para long double de "<<epsld<<endl;


   SALIDA

}

