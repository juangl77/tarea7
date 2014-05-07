#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){

  // declarando constantes 
  int n_points = 1000;
  int n_time = 1000;
  float L = 100.0;
  float tiempo = 1.5;
  float *x = malloc(n_points*sizeof(float));
  float *u_initial =  malloc(n_points*sizeof(float));
  float p = 40.0;
  float T = 0.01;
  float c = sqrt(p/T);
  int i;
  for(i = 0;i<n_points;i++){
    x[i] = L/((float)n_points-1)*(float)i;
    if(x[i]<0.8*L){
      u_initial[i] = 1.25*x[i]/L;}
    else{u_initial[i] = 5.0 - 5.0*x[i]/L;}
  }
  //Primera iteración para fijar condiciones de frontera
  float delta_x = x[1]-x[0];
  float delta_t = tiempo/(float)n_time;
  float r = c*delta_t/delta_x;
  if(r > 1){
    printf("La simulación no va a converger, valor de r = %f",r);
  }

  //Fijando condiciones iniciales.
  u_initial[0] = 0;
  u_initial[n_points -1 ] = 0;

  float *u_future = malloc(n_points*sizeof(float));
  u_future[0] = 0;
  u_future[n_points - 1] = 0;
  for(i = 1; i < n_points -1 ;i++){
    u_future[i] = u_initial[i] + (r*r/2.0)*(u_initial[i+1]-2*u_initial[i]+u_initial[i-1]);
  }
  //Creando array para todos los tiempos

  float *u = malloc(n_points*n_time*sizeof(float));
  int j;
  //Asignando condiciones iniciales
  for(i = 0; i < n_points;i++){
    u[i] = u_initial[i];
    u[n_time+i] = u_future[i];
  }
  for(j = 0; j < n_time; j++){
    u[n_points*j]=0;
    u[n_points*j+n_points-1] = 0;
  }
  //Integrando
  for(j = 2;j < n_time; j++){
    for( i = 1; i < n_points-1;i++){
      u[n_points*j+i] = (2*(1-r*r))*u[n_points*(j-1)+i]-u[n_points*(j-2)+i]+(r*r)*(u[n_points*(j-1)+(i+1)]+u[n_points*(j-1)+(i-1)]);
    }
  }
  //Imprimiendo resultados
  FILE *in;
  in = fopen("resultados_onda.txt","w");
  for(i = 0; i < n_points; i++){
    fprintf(in, "%f ", u_initial[i]);
  }

  fprintf(in, "\n");
  for(i = 0; i < n_points; i++){
    fprintf(in, "%f ", u_future[i]);
  }
  fprintf(in, "\n");
  for(i=0; i < n_time; i++){
    for(j = 0; j < n_points; j++){
      fprintf(in, "%f ", u[n_time*i+j]);
    }
    fprintf(in,"\n");
  }
  return 0;
}
