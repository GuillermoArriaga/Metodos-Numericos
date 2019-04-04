
   // Guillermo Arriaga Garcia
   // Metodos numericos Demat Cimat 2013
   // Clase Matriz, funciones miembro


   #include "Matriz.h"



// Constructor  **********************************************
   MATRIZ::MATRIZ(int nr,int nc,char nom){

      if(nr<1) nr=1;
      if(nc<1) nc=1;

      ren=nr;
      col=nc;
      nombre=nom;

      // Creacion de matriz tipo vector
      celda = new double*[ren];
      if(celda!=NULL)
         celda[0] = new double[ren*col];
      if(celda[0]!=NULL){
         for(int i=1; i<ren; ++i)
            celda[i] = celda[i-1] + col;
      // Inicializacion a ceros
         for(int i=0; i<ren*col; ++i){
            celda[0][i] = 0;
         }
      }
      // Registro de intercambios y vector de resultados/incognitas
      renglon=new int[ren];
      columna=new int[col];
      x=new double[ren];     // Solo matrices cuadradas
      for(int i=0;i<ren;i++){
         renglon[i]=i;
         x[i]=0;
      }
      for(int i=0;i<col;i++)
         columna[i]=i;


   }

   // Destructor que libera memoria
   MATRIZ::~MATRIZ(){
      if(celda!=NULL){
         delete [] celda[0];   // Libera la memoria de toda la matriz
         delete [] celda;
         delete [] renglon;
         delete [] columna;
         delete [] x;
         //cout<<"\nEl destructor ha borrado la matriz "<<nombre<<endl;
      }

   }


   void MATRIZ::liberar(){
      if(celda!=NULL){
         delete [] celda[0];
         delete [] celda;
         delete [] renglon;
         delete [] columna;
         delete [] x;
      }
   }

   void MATRIZ::nueva(int nr,int nc,char nom='0'){
      liberar();
      ren=nr;
      col=nc;
      nombre=nom;

      // Creacion de matriz tipo vector
      celda = new double*[ren];
      // (double**) malloc( (ren)*sizeof(double *));
      if(celda!=NULL)
         celda[0] = new double[ren*col];
         // (double *) malloc( ren*col*sizeof(double));
      if(celda[0]!=NULL){
         for(int i=1; i<ren; ++i)
            celda[i] = celda[i-1] + col;
      // Inicializacion a ceros
         for(int i=0; i<ren*col; ++i){
            celda[0][i] = 0;
         }
      }
      // Registro de intercambios
      renglon=new int[ren];
      columna=new int[col];
      x=new double[ren];      // Solo para matrices cuadradas
      for(int i=0;i<ren;i++){
         renglon[i]=i;
         x[i]=0;
      }
      for(int i=0;i<col;i++)
         columna[i]=i;


   }

   void MATRIZ::imprimir(bool resultados){

      cout<<"\nMatriz "<<nombre<<endl;
      for(int i=0; i<ren;++i){
         for(int j=0;j<col;j++)
            cout<<"  \t"<<celda[i][j];
         cout<<endl;
      }
      if(resultados){
      cout<<"Resultados: ";
         for(int j=0;j<col;j++)
            cout<<" X["<<j<<"]="<<x[j];
         cout<<endl;
      }
   }


void MATRIZ::desde(char* Fmat, char tipo, bool vec){

   // Captura de matriz en tipo B=binario o T=texto.
   // Formato: nr nc celdas double

 ifstream In;
   int nr,nc;
   double a;

 if(tipo=='B'||tipo=='b'){

   In.open(Fmat, std::ifstream::in | std::ifstream::binary);

   if(!vec){
      In.read((char*)&nr,sizeof(int));
      In.read((char*)&nc,sizeof(int));
   }
   else{
      In.read((char*)&nr,sizeof(int));
      nc=1;
   }

   nueva(nr,nc,'A');

   for(int i=0;i<nr*nc;i++){
	   In.read((char*)&a,sizeof(double));
      celda[0][i]=(double)(a);
   }
 }

 if(tipo=='T'||tipo=='t'){
   In.open(Fmat, std::ifstream::in);

   if(!vec){
      In>>nr>>nc;
   }
   else{
      In>>nr;
      nc=1;
   }


   nueva(nr,nc,'A');

   for(int i=0;i<nr*nc;i++){
	   In>>a;
      celda[0][i]=(double)(a);
   }

 }
   In.close();
   //imprimir();
   cout<<"\nSe ha capturado "<<Fmat<<endl;;

}



void MATRIZ::hacia(char* Fmat, char tipo){

 // Graba modo vector si col=1

 ofstream Out;


 if(tipo=='B'||tipo=='b'){

   Out.open(Fmat, std::ofstream::out | std::ofstream::binary);

   Out.write((char*)&ren, sizeof (int));

   if(col!=1){
      Out.write((char*)&col, sizeof (int));
   }

   for(int i=0; i < (ren*col) ; i++){
      Out.write((char*)&celda[0][i], sizeof (double));;
   }

 }

 if(tipo=='T'||tipo=='t'){

   Out.open(Fmat, std::ofstream::out);

   Out<<ren;

   if(col!=1){
      Out<<" "<<col;
   }


   for(int i=0;i<ren*col;i++){
	   Out<<" "<<celda[0][i];
   }

 }
   Out.close();

   cout<<"\nSe ha escrito "<<Fmat<<endl;;
   return ;
}



void MATRIZ::resultados(const MATRIZ &Vec){
   if(Vec.ren!=ren){
      cout<<"\nDimensiones no compatibles de resultados y matriz\n";
      return ;
   }
   for(int i=0;i<ren;i++){
      x[i]=Vec.celda[0][i];
   }
}


//**********************************************  OPERADORES
   void MATRIZ::operator= (const MATRIZ &B){
       nueva(B.ren,B.col,nombre);

       for(int i=0; i<ren*col; ++i){
            celda[0][i] = B.celda[0][i];
       }
       for(int i=0; i<ren; ++i){
            x[i] = B.x[i];
       }


       return ;

   }

   MATRIZ MATRIZ::operator+ (const MATRIZ &B){
       MATRIZ C(ren,col,'S');

       if(ren!=B.ren || col!=B.col){
          cout<<"\n\nDimensiones incompatibles para sumar\n";
          return C;
       }

       for(int i=0; i<ren*col; i++){
            C.celda[0][i] = celda[0][i]+B.celda[0][i];
       }

       //C.imprimir();
       return C;
   }

   MATRIZ MATRIZ::operator- (const MATRIZ &B){
       MATRIZ C(ren,col,'S');

       if(ren!=B.ren || col!=B.col){
          cout<<"\n\nDimensiones incompatibles para restar\n";
          return C;
       }

       for(int i=0; i<ren*col; i++){
            C.celda[0][i] = celda[0][i]-B.celda[0][i];
       }

       //C.imprimir();
       return C;
   }



   MATRIZ MATRIZ::operator* (const MATRIZ &B){
       MATRIZ C(ren,B.col,'P');

       if(col!=B.ren){
          cout<<"\n\nDimensiones incompatibles para multiplicar\n";
          return C;
       }

       double sum;

       for(int i=0; i<ren; i++){
          for(int j=0;j<B.col;j++){
            sum=0;
            for(int k=0;k<col;k++){
               sum += celda[i][k]*B.celda[k][j];
            }
            C.celda[i][j]=sum;
          }
       }
       return C;
   }

MATRIZ MATRIZ::operator*(double d){
       MATRIZ C(ren,col,nombre);
       for(int i=0; i<ren*col; i++){
            C.celda[0][i] = celda[0][i]*d;
       }
       return C;
}

MATRIZ MATRIZ::operator/(double d){
       MATRIZ C(ren,col,nombre);
       for(int i=0; i<ren*col; i++){
            C.celda[0][i] = celda[0][i]/d;
       }
       return C;
}



void MATRIZ::suma(const MATRIZ &B,const MATRIZ &C){
       if(C.ren!=B.ren || C.col!=B.col){
          cout<<"\n\nNo son de la misma dimension\n";
          return ;
       }

       nueva(B.ren,B.col,nombre);

       for(int i=0; i<ren*col; i++){
            celda[0][i] = C.celda[0][i]+B.celda[0][i];
       }

       return ;
}

void MATRIZ::producto(const MATRIZ &B,const MATRIZ &C){
       if(B.col!=C.ren){
          cout<<"\n\nNo son de la misma dimension\n";
          return ;
       }

       nueva(B.ren,C.col,nombre);
       double sum;

       for(int i=0; i<ren; i++){
          for(int j=0;j<col;j++){
            sum=0;
            for(int k=0;k<col;k++){
               sum += B.celda[i][k]*C.celda[k][j];
            }
            celda[i][j]=sum;
          }
       }

       return ;
}


void MATRIZ::igual(const MATRIZ &B){
   nueva(B.ren,B.col,nombre);

   for(int i=0; i<ren*col; i++){
            celda[0][i] = B.celda[0][i];
       }
   for(int i=0; i<ren; ++i){
            x[i] = B.x[i];
       }


   return ;
}

//*********************************************** Normas
double MATRIZ::norma1(){
   double n1=0;
   for(int i=0;i<ren*col;i++){
      n1+=ABS(celda[0][i]);
   }
   return n1;
}

double MATRIZ::norma2(){
   double n1=0;
   for(int i=0;i<ren*col;i++){
      n1+=celda[0][i]*celda[0][i];
   }
   return RAIZ(n1);
}

double MATRIZ::norma3(){
 double n1;

 if(col==1){
   n1=ABS(celda[0][1]);
   for(int i=1;i<ren;i++){
      if(n1<ABS(celda[0][i]))
         n1=ABS(celda[0][i]);
   }
   return n1;
 }

   // Norma inf para matriz da la suma de los val abs de la fila maxima
   double Renglon[ren];

   for(int i=0;i<ren;i++){
      Renglon[i]=0;
      for(int j=0;j<col;j++){
         Renglon[i]+=ABS(celda[i][j]);
      }
   }
   n1=Renglon[0];
   for(int i=1;i<ren;i++){
      if(n1<Renglon[i]){
         n1=Renglon[i];
      }
   }
   return n1;
}

double MATRIZ::RAIZ(double a,int iter){
   if(a==0) return 0;
   double b=1;
   for(int i=0;i<iter;i++){
      b=(b+a/b)/2;
      //b=1+(a-1)/(b+1); // Converge menos rapido
   }
   return b;
}



//***********************************************  FUNCIONES



void MATRIZ::pivPAR(int reng){
      double max=celda[reng][reng];
      int pr,i;
      for(i=reng+1;i<ren;i++) // La piensa cuadrada por si esta aumentada
         if(max<celda[i][reng]){
            max=celda[i][reng];
            pr=i;
         }
      renglon[reng]=i;
      renglon[i]=reng;
      // Intercambio
      double swap;
      for(int i=0;i<col;i++){
         swap=celda[reng][i];
         celda[reng][i]=celda[pr][i];
         celda[pr][i]=swap;
      }

}


void MATRIZ::LU(const MATRIZ &B){
   nueva(B.ren,B.col,'Z');
   double sum;

   for(int j=0;j<col;j++){
       for(int i=0;i<ren;i++){
          // Calculo de U
          if(i<=j){
             sum=0;
             for(int k=0;k<i;k++){
                sum+=celda[i][k]*celda[k][j];
             }
             celda[i][j]=B.celda[i][j]-sum;
          }
          // Calculo de L con 1's en diagonal
          if(i>j){
             sum=0;
             for(int k=0;k<j;k++){
                sum+=celda[i][k]*celda[k][j];
             }
             if(celda[j][j]==0){
                cout<<"\n\nNo es posible la fact LU, div entre cero\n\n";
                return ;
             }
             celda[i][j]=(B.celda[i][j]-sum)/celda[j][j];
          }
       }
   }

}

void MATRIZ::L(const MATRIZ &LU){
   // Obtiene la L de una LU junta
   nueva(LU.ren,LU.col,'L');
   for(int i=0;i<col;i++){
      celda[i][i]=1;
      for(int j=i+1;j<ren;j++){
         celda[j][i]=LU.celda[j][i];
      }
   }

   return ;

}

void MATRIZ::U(const MATRIZ &LU){
   // Obtiene la L de una LU junta
   nueva(LU.ren,LU.col,'U');
   for(int i=0;i<col;i++){
      for(int j=0;j<=i;j++){
         celda[j][i]=LU.celda[j][i];
      }
   }

   return ;

}


void MATRIZ::pivGAG(){
   // Máximo elemento de la matriz en A11
   // Sin renglón 1 y col 1, el sigt máximo en A22 ...

   double max,swap;
   int r,c;

   for(int k=0; k<ren; k++){
      max=ABS(celda[k][k]);
      r=k;
      c=k;
      // Búsqueda de máximo
      for(int i=k; i<ren; i++){
         for(int j=k; j<ren;j++){
            if(max<ABS(celda[i][j])){
               max=ABS(celda[i][j]);
               r=i;
               c=j;
            }
         }
      }
      // Intercambio de columnas y renglones
      renglon[k]=r;
      renglon[r]=k;
      columna[k]=c;
      columna[c]=k;

      for(int ii=0;ii<col;ii++){
         swap=celda[r][ii];
         celda[r][ii]=celda[k][ii];
         celda[k][ii]=swap;
      }

      for(int jj=0;jj<ren;jj++){
         swap=celda[jj][c];
         celda[jj][c]=celda[jj][k];
         celda[jj][k]=swap;
      }

   }


}

// Valor absoluto
double MATRIZ::ABS(double d){
   if(d<0) {
      return (-1)*d;
   }
   return d;
}

void MATRIZ::DESintercambio(){
   double swap;
   int sw;
   for(int i=0;i<ren;i++){
      if(renglon[i]!=i){
         for(int k=0;k<col;k++){
            swap=celda[i][k];
            celda[i][k]=celda[renglon[i]][k];
            celda[renglon[i]][k]=swap;
         }
         sw=renglon[i];
         renglon[i]=i;
         renglon[sw]=sw;
      }
   }


   for(int i=0;i<ren;i++){
      if(columna[i]!=i){
         for(int k=0;k<ren;k++){
            swap=celda[k][i];
            celda[k][i]=celda[k][columna[i]];
            celda[k][columna[i]]=swap;
         }
         sw=columna[i];
         columna[i]=i;
         columna[sw]=sw;
      }
   }

   return ;
}




// Para la factorizacion LU Ax=b=LUx=Ly
MATRIZ MATRIZ::susADE(const MATRIZ &Res){       // y=L.x , los resultados parciales
    // Con matriz triangular inferior

    MATRIZ C(ren,1);

    if(ren!=Res.ren){
      cout<<"\n\nDimensiones incompatibles para sust ADELANTE\n";
      return C;
    }

    resultados(Res);


    for(int i=0;i<ren;i++){
      for(int j=0;j<i;j++)
         x[i]-=x[j]*celda[i][j];
      if(celda[i][i]==0){
         cout<<"\n\nDivision entre cero en sust Atras\n";
         return C;
      }
      x[i]/=celda[i][i];
      C.celda[0][i]=x[i];
    }

    return C;

}

MATRIZ MATRIZ::susATR(const MATRIZ &Vec){      // Para evaluar diferentes vectores
   // Con matriz triangular superior

    MATRIZ C(ren,1);

    if(ren!=Vec.ren){
      cout<<"\n\nDimensiones incompatibles para sust ATRAS\n";
      return C;
    }
    resultados(Vec);
    for(int i=ren-1;i>(-1);i--){
      for(int j=ren-1;j>i;j--)
         x[i]-=x[j]*celda[i][j];
      if(celda[i][i]==0){
         cout<<"\n\nDivision entre cero en sust Atras\n";
         return C;
      }
      x[i]/=celda[i][i];
      C.celda[0][i]=x[i];
    }
   return C;
}


double MATRIZ::TRUNC(double a, int dig){

   double power=POT(10,dig);
   return( ((double)((long int)(a*power)))/power );
}


double MATRIZ::POT(double a, int exp){

   double res=1;

   if(exp==0) return res;

   for(int i=0;i<ABS(exp);i++){
      if(exp<0){
         res/=a;
      }
      if(exp>0){
         res*=a;
      }
   }

   return( res );


}


//************************************************** REDUCCION GAUSSIANA

void MATRIZ::RedGauss(int tipo_pivoteo){

   if(tipo_pivoteo==0){                   // Pivoteo parcial si es necesario
      for(int j=0;j<col-1;j++){
         if(celda[j][j]==0){
            PIVOTEOparcial(j);
         }
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsuma(i,celda[j][j],j,celda[i][j]);
         }
      }
      return ;
   }


   if(tipo_pivoteo==1){                   // Pivoteo parcial en cada paso
      for(int j=0;j<col-1;j++){
         PIVOTEOparcial(j);
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsuma(i,celda[j][j],j,celda[i][j]);
         }
      }
      return ;
   }


   if(tipo_pivoteo==2){                   // Pivoteo total en cada paso
      for(int j=0;j<col-1;j++){
         PIVOTEOtotal(j);
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsuma(i,celda[j][j],j,celda[i][j]);
         }
      }
      return ;
   }


   if(tipo_pivoteo==3){                   // Pivoteo total si es necesario
      for(int j=0;j<col-1;j++){
         if(celda[j][j]==0){
            PIVOTEOtotal(j);
         }
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsuma(i,celda[j][j],j,celda[i][j]);
         }
      }
      return ;
   }

   cout<<"\n\nTipo de pivoteo incorrecto en Reduc Gauss\n";
   return ;
}

void MATRIZ::RENGLONsuma(int r1, double a1, int r2, double a2){
   // r1= a1*r1-a2*r2
   for(int j=0;j<col;j++){
      celda[r1][j]=a1*celda[r1][j]-a2*celda[r2][j];
   }
   x[r1]=x[r1]*a1-a2*x[r2]; // Vector de resultados
}


void MATRIZ::RENGLONprod(int r1, double a1){

   for(int j=0;j<col;j++){
      celda[r1][j]*=a1;
   }

}


int MATRIZ::PIVOTEOparcial(int columna, bool inspeccion){
   // Busca el max elemento para A[col][col] de los renglones de abajo
   double maximo=ABS(celda[columna][columna]);
   int renglon_final=columna;

   for(int j=columna+1;j<ren;j++){
      if(maximo<ABS(celda[j][columna])){
         maximo=ABS(celda[j][columna]);
         renglon_final=j;
      }
   }


   if(renglon_final!=columna && inspeccion!=1)
      RENGLONintercambio(columna,renglon_final);

   return renglon_final;
}

int MATRIZ::PIVOTEOtotal(int columna, bool inspeccion){
   // Busca el max elemento para A[col][col] de las columnas de derecha
   double maximo=ABS(celda[columna][columna]);
   int columna_final=columna;

   for(int j=columna+1;j<col;j++){
      if(maximo<ABS(celda[columna][j])){
         maximo<ABS(celda[columna][j]);
         columna_final=j;
      }
   }
   if(columna_final!=columna && inspeccion!=1)
      COLUMNAintercambio(columna,columna_final);

   return columna_final;

}

void MATRIZ::RENGLONintercambio(int r1, int r2){
   double a;
   for(int j=0;j<col;j++){
      a=celda[r1][j];
      celda[r1][j]=celda[r2][j];
      celda[r2][j]=a;
   }
   renglon[r1]=r2;
   renglon[r2]=r1;
   a=x[r1];
   x[r1]=x[r2];
   x[r2]=a;
}

void MATRIZ::COLUMNAintercambio(int c1, int c2){
   double a;
   for(int j=0;j<ren;j++){
      a=celda[j][c1];
      celda[j][c1]=celda[j][c2];
      celda[j][c2]=a;
   }
   columna[c1]=c2;
   columna[c2]=c1;
}


MATRIZ MATRIZ::susATR(){
   // Con matriz triangular superior

    MATRIZ C(ren,1);

    for(int i=ren-1;i>(-1);i--){
      for(int j=ren-1;j>i;j--)
         x[i]-=x[j]*celda[i][j];
      if(celda[i][i]==0){
         cout<<"\n\nDivision entre cero en sust Atras\n";
         return C;
      }
      x[i]/=celda[i][i];
      C.celda[0][i]=x[i];
    }
   return C;
}




void MATRIZ::RedGaussTRUNC(int tipo_pivoteo, int tr){

   truncar();

   if(tipo_pivoteo==0){                   // Pivoteo parcial si es necesario
      for(int j=0;j<col-1;j++){
         if(celda[j][j]==0){
            PIVOTEOparcial(j);
         }
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsumaTRUNC(i,celda[j][j],j,celda[i][j],tr);
         }
      }
      return ;
   }


   if(tipo_pivoteo==1){                   // Pivoteo parcial en cada paso
      for(int j=0;j<col-1;j++){
         PIVOTEOparcial(j);
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsumaTRUNC(i,celda[j][j],j,celda[i][j],tr);
         }
      }
      return ;
   }


   if(tipo_pivoteo==2){                   // Pivoteo total en cada paso
      for(int j=0;j<col-1;j++){
         PIVOTEOtotal(j);
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsumaTRUNC(i,celda[j][j],j,celda[i][j],tr);
         }
      }
      return ;
   }


   if(tipo_pivoteo==3){                   // Pivoteo total si es necesario
      for(int j=0;j<col-1;j++){
         if(celda[j][j]==0){
            PIVOTEOtotal(j);
         }
         if(celda[j][j]==0){
            cout<<"\n\nNo es posible la reduccion Gaussiana, no hay pivote\n";
            return ;
         }
         for(int i=j+1;i<ren;i++){
            RENGLONsumaTRUNC(i,celda[j][j],j,celda[i][j],tr);
         }
      }
      return ;
   }

   cout<<"\n\nTipo de pivoteo incorrecto en Reduc Gauss\n";
   return ;
}

void MATRIZ::RENGLONsumaTRUNC(int r1, double a1, int r2, double a2, int tr){
   // r1= a1*r1-a2*r2
   for(int j=0;j<col;j++){
      celda[r1][j]=TRUNC(TRUNC(a1*celda[r1][j],2)-TRUNC(a2*celda[r2][j],2),2);
   }
   x[r1]=TRUNC(TRUNC(x[r1]*a1,2)-TRUNC(a2*x[r2],2),2); // Vector de resultados
}


void MATRIZ::truncar(int tr){
   //Truncamiento de toda la matriz
   for(int i=0;i<ren*col;i++)
      celda[0][i]=TRUNC(celda[0][i],tr);
   for(int i=0;i<ren;i++)
      x[i]=TRUNC(x[i],2);
}



//************************************************  ITERATIVO GAUSS SEIDEL

MATRIZ MATRIZ::GS(const MATRIZ &A, const MATRIZ &B,double relax, int iter){

   // Ax=b , A=D-L-U , DL=D-L , x=(D-L)^-1 U x + (D-L)^-1 b = G x + M
   MATRIZ DL(A.ren,A.col,'D'),U(A.ren,A.col,'U'),DLinv,M,G,a,b;
   a=A;
   b=B;

   // Obtención de matrices D L U
   for(int i=0;i<A.ren;i++)
      for(int j=0;j<A.col;j++){
         if(i==j){
            DL.celda[i][i]=A.celda[i][i];
         }
         if(j<i){
            DL.celda[i][j]=(-1)*A.celda[i][j];
         }
         if(i<j){
            U.celda[i][j]=(-1)*A.celda[i][j];
         }
      }

   DLinv=DL.inversa();
   G=(DLinv*U);
   M=(DLinv*B);

   MATRIZ X1(A.ren,1),X2(A.ren,1,'R');

   // Gauss Seidel sin relajacion
   if(relax==1){
      for(int i=1;i!=iter;i++){
         X2=( (G*X1)+M );
         X1=X2;

         if(i%500==0)
            cout<<" GSeidel Matricial Error en iteracion "<<i<<" |Ax-B|(1) = "<<(a*X2-b).norma1()<<endl;

      }
   }
   else{
      for(int i=1;i!=iter;i++){
         X2=(( (G*X1)+M )*relax+X1*(1-relax));
         X1=X2;

         if(i%500==0)
            cout<<" GSeidel Matricial Error en iteracion "<<i<<" |Ax-B|(1) = "<<(a*X2-b).norma1()<<endl;
      }

   }

   return X2;
}


void GS(const MATRIZ &A, const MATRIZ &B,MATRIZ &G, MATRIZ &M){
   // Ax=b , A=D-L-U , DL=D-L , x=(D-L)^-1 U x + (D-L)^-1 b = G x + M
   MATRIZ DL(A.ren,A.col,'D'),U(A.ren,A.col,'U'),DLinv;

   // Obtención de matrices D L U
   for(int i=0;i<A.ren;i++)
      for(int j=0;j<A.col;j++){
         if(i==j){
            DL.celda[i][i]=A.celda[i][i];
         }
         if(j<i){
            DL.celda[i][j]=(-1)*A.celda[i][j];
         }
         if(i<j){
            U.celda[i][j]=(-1)*A.celda[i][j];
         }
      }

   DLinv=DL.inversa();
   G=(DLinv*U);
   M=(DLinv*B);
   return ;
}


MATRIZ MATRIZ::GaussSeidel(MATRIZ &A, MATRIZ &B,double relax, int iter){
   MATRIZ X1(A.ren,1,'1'),X2(A.ren,1,'2');
   double resultado;

   for(int it=1;it<=iter;it++){

      for(int i=0;i<A.ren;i++){
         resultado=B.celda[i][0];
         for(int j=0;j<A.col;j++){
            if(j<i){
               resultado-=A.celda[i][j]*X2.celda[j][0];
            }
            if(j>i){
               resultado-=A.celda[i][j]*X1.celda[j][0];
            }
         }

         resultado=(1-relax)*X1.celda[i][0]+resultado*relax/A.celda[i][i];
         X1.celda[i][0]=X2.celda[i][0];
         X2.celda[i][0]=resultado;
      }

      if(it%15==0){
         cout<<"\n Gauss Seidel en iteracion "<<it<<" con error |Ax-B|(1) = "<<(A*X2-B).norma1();
         //cout<<"   Tiene el siguiente vector de resultados:";
         //X2.imprimir();
         // Por si se quiere ver el vector de resultado
      }
   }
   return X2;
}



MATRIZ MATRIZ::inversa(){

   // Comienza siendo identidad
   MATRIZ I(ren,col,'I');
   for(int j=0;j<col;j++){
      I.celda[j][j]=1;
   }
   MATRIZ B;
   B=(*this);
   double x;

   for(int j=0;j<col;j++){
      x=1/B.celda[j][j];
      I.RENGLONprod(j,x);
      B.RENGLONprod(j,x);

      for(int i=0;i<ren;i++){
         if(i==j)
            i++;
         if(i==ren)
            continue;
         I.RENGLONsuma(i,B.celda[j][j],j,B.celda[i][j]);
         B.RENGLONsuma(i,B.celda[j][j],j,B.celda[i][j]);
      }
   }


   return I;
}


MATRIZ MATRIZ::Jacobi(MATRIZ &A, MATRIZ &B,double relax, int iter){
   // Ax=b , A=D-L-U , x=Dinv*(D+L)x+Dinv*b=Gx+M
   MATRIZ G,M,Dinv(A.ren,A.col),LU,X1(B.ren,1),X2(B.ren,1);

   // Obtención de matriz L+U
   LU=A*(-1);

   for(int i=0;i<A.ren;i++){
      LU.celda[i][i]=0;
      Dinv.celda[i][i]=1/A.celda[i][i];
   }

   G=(Dinv*LU);
   M=(Dinv*B);


   for(int it=1;it!=iter;it++){
      X2=((G*X1)+M);
      X1=X2;
      if(it%500==0){
         cout<<" JACOBI Error en iteracion "<<it<<" |Ax-b|(1)= "<<((A*X2)-B).norma1()<<endl;
         string Fnom;
         Fnom="JACO";
         Fnom+=it;
         Fnom+=".bin";
         //X2.hacia(Fnom.c_str());
      }
   }
   return X2;
}




// Transpuesta
MATRIZ MATRIZ::transpuesta(){
   MATRIZ A(ren,col,nombre);
   
   for(int i=0;i<ren;i++)
      for(int j=0;j<col;j++)
         A.celda[i][j]=celda[j][i];
   
   return A;
}



// Iterativo de Jacobi con Rotaciones Givens

MATRIZ MATRIZ::Givens(int i, int j){
   MATRIZ G(ren,col,'G');
   
   for(int k=0;k<ren;k++)
      G.celda[k][k]=1;
   
   double c,s,theta;
   theta=(atan(2*celda[i][j]/(celda[j][j]-celda[i][i])))/2;
   c=cos(theta);
   s=sin(theta);
   
   cout<<"\n\t\tTheta: "<<theta<<"  c="<<c<<"  s="<<s;
   
   G.celda[i][i]=c;
   G.celda[j][j]=c;
   G.celda[i][j]=s;
   G.celda[j][i]=-s;
   
   return G;
}
