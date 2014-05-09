#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){

  // declarando constantes 
  int n_points = 30000;
  float k = 16*3.141592;
  float sigma = 0.05;
  float *x = malloc(n_points*sizeof(float));
  float *v = malloc(n_points*sizeof(float));
  float *i_initial = malloc(n_points*sizeof(float));
  float *r_initial = malloc(n_points*sizeof(float));
  int n_time = 225000; 
  float L = 150;
  float b = -75.0;
  int i;
  for(i = 0;i<n_points;i++){
    x[i] = L/((float)n_points-1)*i + b;
    i_initial[i] = exp(-0.5*pow(((x[i]-5.0)/sigma),2))*sin(k*x[i]);
    r_initial[i] = exp(-0.5*pow(((x[i]-5.0)/sigma),2))*cos(k*x[i]);
    v[i] = x[i]*x[i]/2;
  }
  //Primera iteración para fijar condiciones de frontera
  float delta_x = x[1]-x[0];
  float delta_t = delta_x*delta_x/2.5;
  
  
  //Fijando condiciones iniciales.
  i_initial[0] = 0;
  i_initial[n_points -1 ] = 0;
  r_initial[0] = 0;
  r_initial[n_points -1 ] = 0;
  

  //Creando array para todos los tiempos
 
  float *r = malloc(n_points*sizeof(float));
  float *im = malloc(n_points*sizeof(float));
  //float *p = malloc(n_points*n_time*sizeof(float));
  int j;
  //Asignando condiciones frontera
  r[0]=0;
  r[n_points-1] = 0;
  im[0]=0;
  im[n_points-1] = 0;
  
  //Integrando
  FILE *in;
  in = fopen("resultados_schro.txt","w");
  float alpha = delta_t/(2*delta_x*delta_x);
  for(j = 0;j < n_time; j++){
    for(i = 1; i < n_points-1;i++){
      r[i] = r_initial[i] - 2*(alpha*(i_initial[i+1]+i_initial[i-1])-2*(alpha+delta_t*v[i])*i_initial[i]);
    }
    if(j%30==0){
      for(i = 0; i < n_points-1;i++){
	if(i%50 == 0){
	  //p[n_points*j + i] = pow( i_initial[i],2) +  r[i]*r_initial[i];
	  fprintf(in, "%f ",  pow( i_initial[i],2) +  r[i]*r_initial[i]);
	}
      }
      fprintf(in,"\n");
    }
    for(i = 1; i < n_points-1;i++){
      im[i] = i_initial[i] + 2*(alpha*(r[i+1]+r[i-1])-2*(alpha+delta_t*v[i])*r[i]);
    }
    for(i = 0; i < n_points;i++){
      r_initial[i] = r[i];
      i_initial[i] = im[i];
    }
   
  }
  //Imprimiendo resultados
  /*FILE *in;
  in = fopen("resultados_schro.txt","w");
  for(i=0; i < n_time; i = i+10){
    for(j = 0; j < n_points; j++){
      fprintf(in, "%f ", p[n_points*i+j]);
    }
    fprintf(in,"\n");
  }
  fclose(in);*/
  return 0;
}
