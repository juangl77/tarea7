#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){

  // declarando constantes 
  int n_points = 1000;
  float k = 16*3.141592;
  float sigma = 0.05;
  float *x = malloc(n_points*sizeof(float));
  float *v = malloc(n_points*sizeof(float));
  float *i_initial = malloc(n_points*sizeof(float));
  float *r_initial = malloc(n_points*sizeof(float));
  int n_time = 1000; 
  int i;
  for(i = 0;i<n_points;i++){
    x[i] = 10/((float)n_points-1)*i;
    i_initial[i] = exp(-0.5*pow(((x[i]-5.0)/sigma),2))*cos(k*x[i]);
    r_initial[i] = exp(-0.5*pow(((x[i]-5.0)/sigma),2))*sin(k*x[i]);
    v[i] = x[i]*x[i]/2;
  }
  //Primera iteración para fijar condiciones de frontera
  float delta_x = x[1]-x[0];
  float delta_t = 0.00005;
  
  
  //Fijando condiciones iniciales.
  i_initial[0] = 0;
  i_initial[n_points -1 ] = 0;
  r_initial[0] = 0;
  r_initial[n_points -1 ] = 0;
  

  //Creando array para todos los tiempos
 
  float *r = malloc(n_points*n_time*sizeof(float));
  float *im = malloc(n_points*n_time*sizeof(float));
  float *p = malloc(n_points*n_time*sizeof(float));
  int j;
  //Asignando condiciones iniciales
  for(i = 0; i < n_points;i++){
    r[i] = r_initial[i];
    im[i] = i_initial[i];
    p[i] = pow(r_initial[i],2) +  pow(i_initial[i],2);
  }
  for(j = 0; j < n_time; j++){
    r[n_points*j]=0;
    r[n_points*j+n_points-1] = 0;
    im[n_points*j]=0;
    im[n_points*j+n_points-1] = 0;
    p[n_points*j]=0;
    p[n_points*j+n_points-1] = 0;
  }
  //Integrando
  float alpha = delta_t/(delta_x*delta_x);
  for(j = 1;j < n_time; j++){
    for( i = 1; i < n_points-1;i++){
      r[n_points*j+i] = r[n_points*(j-1)+i] - (alpha*(im[n_points*(j-1)+i+1]+im[n_points*(j+1)+i-1])-4*(alpha/2+v[i]*delta_t)*im[n_points*(j-1)+i]);
    
      im[n_points*j+i] = im[n_points*(j-1)+i] + (alpha*(r[n_points*j+i+1]+r[n_points*j+i-1])-4*(alpha/2+v[i]*delta_t)*r[n_points*j+i]);;
      p[n_points*j+i] = r[n_points*j+i]*r[n_points*(j-1)+i] +  pow(im[n_points*j+i],2);
     
    }
  
  }
  //Imprimiendo resultados
  FILE *in;
  in = fopen("resultados_schro.txt","w");
  for(i=0; i < n_time; i++){
    for(j = 0; j < n_points; j++){
      fprintf(in, "%f ", p[n_points*i+j]);
    }
    fprintf(in,"\n");
  }
  return 0;
}
