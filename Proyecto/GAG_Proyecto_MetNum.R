#
## Metodos Numericos: Proyecto final.
## Guillermo Arriaga García
#
## Predictor de la sucesión de una función 
##    polinomial evaluada en 1,2,3,4,5,... 
#
## Son conocidos los primeros n terminos de
##    la sucesión. Supongamos, suficientes
##    para estimar la derivada que anula al
##    polinomio.
## Denotemos por g al grado del polinomio.
##    Entonces, n > g.
## La estimación de la primera derivada, en
##   cada punto de los n, se hará con diferencias
##   finitas hacia adelante con distancia uno.
##   Esto es tener la pendiente de la secante,
##   por el teorema del valor medio, como la función
##   polinomial es C infinito, existe un punto
##   intermedio entre n y n+1 tal que la derivada
##   en ese punto es igual al valor de la secante.
## Así que ya no es posible asegurar que los nuevos
##   puntos intermedios, tengan distancia uno entre
##   adyacentes; es menor que dos. 
## Sin embargo, en un punto de una función polinomial,
##   como la derivada es continua, hay concavidad, rectitud o
##   convexidad entre cercanos. Si hay rectitud, a
##   algo similar, entonces cualquier punto intermedio
##   se puede elegir, por ejemplo el de enmedio. 
##   Si hay concavidad o convexidad, entonces se
##   estima como el punto central en este algoritmo.
##   
## Con esto, la segunda derivada se estima como la
##  primera. Y así las demás derivadas, hasta llegar
##  a la primera derivada nula.
## Al llegar a la derivada nula, se tiene certeza de
##  un valor para todo número, igual la derivada anterior
##  es una función constante. 
##  A partir de ahí, se estiman las demás derivadas de
##  ordenes menores.

# Ejemplo
  Sucesion <- (1:10)^6
  print(Sucesion)

  n    <- length(Sucesion)
  MAT  <- matrix(0,n,n)
  MAT[1,]=Sucesion
  
  for(k in 2:n){
     MAT[k,] <- c(MAT[k-1,2:(n+2-k)]-MAT[k-1,1:(n+1-k)],rep(0,k-1))
  }
     
  recorte <- which(MAT[,1]==0)[1]  # Ceros innecesarios
  MAT=MAT[1:recorte,]
     
  # Es un polinomio mónico de sexto grado, 720=6!
  # Así que se puede rellenar la fila 7
  
  MAT[7,]=rep(MAT[7,1],n)
  
  # Para llenar lo demás, por la diferenciación
  #   hacia adelante, se tiene que 
  #   celda[i,j]=celda[i-1,j+1]-celda[i-1,j]
  #
  #   Por lo que:
  #   celda[i,j]=celda[i,j-1]+celda[i+1,j-1]

  # Para apreciar el llenado, quitemos datos
  #   para estimarlos
  
  A  <- MAT
  nA <- recorte
  for(i in 2:n){
     A[(n-i):nA,i]=0
  }
  
  write.csv(A,"GAGproyMETnum.csv")
  
  # Estimación de las derivadas en los 10 puntos
  B <- A
  for(i in (nA-1):1)
    for(j in 2:n)
      A[i,j]=A[i,j-1]+A[i+1,j-1]
  
  print(A)
  print(MAT)
  print(B)
  
  # Con el método se comprobó que la estimación
  #   para 9 y 10 es exacta.
  
  # Prolongación de estimaciones, ahora, el valor
  #   de los puntos y sus derivadas
  
  A=cbind(A,rep(0,nA))
  
  A[,11]=c(A[(1:(nA-1)),10]+A[(2:(nA)),10],0)
  
  
  # Estimando del 11 al 20
  
  for(i in 12:20){
     A=cbind(A,c(A[(1:(nA-1)),i-1]+A[(2:(nA)),i-1],0)) 
  }
  
  Sucesion2 <- A[1,]
  
  plot(Sucesion2)  
  print(Sucesion2)
  
  # Original extendida a 20
  Sucesion3 <- (1:20)^6
  
  Error <- sum( (Sucesion3-Sucesion2)^2 )/20
  
  
  ## Así que se ha tenido una predicción exacta.
  ## Observemos que la función y sus derivadas
  ##  fueron polinomios de un término.

  
  
  # Con el método propuesto, basta calcular las
  #  diferencias de la primer columna, para estimar
  #  en la primera fila.
  

##################################################
  
## Función de revision que depende de la defnicion de f
    
f <- function(n){
     return( n^6-3*n^5+3*n+1 )
} 
  

Revision <- function(){ 
  
  Sucesion <- f( 1:8 )  
  
  #print(Sucesion)  
  n <- length(Sucesion)
  
  # Formamos la matriz para el calculo de las
  #   diferencias en el primer punto
  
  MAT  <- matrix(0,n,n)
  MAT[,1]=1
  MAT[n,n]=1
  for(j in 2:(n-1) ){
     MAT[j,j]=1
     for(i in (j+1):n){
       MAT[i,j]=MAT[i-1,j]+MAT[i-1,j-1]
     }
  }
  
  
  # MAT tiene los coeficientes de cambio
  #   para calcular los datos según las diferencias
  # Su inversa es para calcular las diferencias
  #   a partir de los datos.
  
  MAT2 <- solve(MAT)
  # Se puede activar o no lo siguiente
  # MAT2[which(MAT2<0.5 & MAT2>-0.5)]=0
  
  #print(MAT2)
  
  # MAT2, la inversa, es como MAT con signos alternados
  
  # Se crea un vector con las diferencias calculadas
  #   con base a los datos. La k-ésima diferencia
  #   es el producto punto de los datos con la fila
  #   k+1 de MAT2. Si consideramos a partir del 
  #   primer dato, como la diferencia cero, nos queda
  #   el vector columna de datos por MAT2.
  
  Diferencias <- MAT2%*%Sucesion
  
  # El último término es casi cero, consideremoslo cero.
  # Se puede activar o no lo siguiente
  # Diferencias[which(Diferencias<0.01 & Diferencias>-0.01)]=0
  
  estimado_posicion_8 <- (MAT%*%Diferencias)[8]
  
  error_relativo <- abs( (Sucesion[8]-estimado_posicion_8 )/Sucesion[8])
  
  return(error_relativo)
}  

  print(Revision())
  
  # Pruebas cambiando la funcion
  f <- function(n){
     return( n^6+3*n^5-3*n )
  } 
  
  print(Revision())
  
  f <- function(n){
     return( n^6-7*n^2+n )
  } 
  
  print(Revision())
  
  
    
  f <- function(n){
     return( n^6+30*n^5-n^3-n^2 )
  } 
  
  print(Revision())

  
  f <- function(n){
     return( n^6-30*n^5-n^3-n^2 )
  } 
  
  print(Revision())

  
    
  f <- function(n){
     return( -5*n^6+3*n^4-n^3-n^2 )
  } 
  
  print(Revision())
