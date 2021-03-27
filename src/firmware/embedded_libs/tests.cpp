#include <tests.h>


#include <matrix_vector.h>

#define INPUTS_COUNT  ((unsigned int)64)
#define OUTPUTS_COUNT ((unsigned int)64)
 
template<unsigned int size>
int32_t vector_dot(int8_t *w, int8_t *x)
{
  int32_t result = 0;
  for (unsigned int i = 0; i < size; i++)
  {
    result+= w[i]*x[i];
  }

  return result;
}

void performance_test(bool cache_enabled)
{
  terminal << "\n";
  terminal << "cache enabled " << cache_enabled << "\n";

  if (cache_enabled)
  {
    SCB_EnableICache();
	SCB_EnableDCache();
  }
  else
  {
    SCB_DisableICache();
	SCB_DisableDCache();
  }
  
  timer.reset();

  float pi    = 0.0;
  for (unsigned int i = 0; i < 1000000; i+= 8)
  {
    pi  = pi + 4.0/(2.0*(i+0) + 1); 
    pi  = pi - 4.0/(2.0*(i+1) + 1);
    pi  = pi + 4.0/(2.0*(i+2) + 1);
    pi  = pi - 4.0/(2.0*(i+3) + 1);
    pi  = pi + 4.0/(2.0*(i+4) + 1);
    pi  = pi - 4.0/(2.0*(i+5) + 1);
    pi  = pi + 4.0/(2.0*(i+6) + 1);
    pi  = pi - 4.0/(2.0*(i+7) + 1);
  } 

  auto time_a =  timer.elapsed_time();
  float performance_a = 5*1.0/(time_a*0.001);

  terminal << "cpu float32 performance " << performance_a <<  "M FLOPS\n";
  terminal << "pi result " << pi << "\n";

  
  int8_t    mat_w[INPUTS_COUNT*OUTPUTS_COUNT];
  int8_t    mat_x[INPUTS_COUNT];
  int32_t   mat_y[OUTPUTS_COUNT];

  for (unsigned int i = 0; i < INPUTS_COUNT*OUTPUTS_COUNT; i++)
    mat_w[i] = i*27 + 55;
 
  for (unsigned int i = 0; i < INPUTS_COUNT; i++)
    mat_x[i] = i*27 + 55;

  for (unsigned int i = 0; i < OUTPUTS_COUNT; i++)
    mat_y[i] = i*27 + 55;


  timer.reset();

  for (unsigned int j = 0; j < 1000; j++)
  {     
    for (unsigned int i = 0; i < INPUTS_COUNT; i++)
      mat_x[i]+= 1;

    matrix_vector<INPUTS_COUNT, OUTPUTS_COUNT>(mat_y, mat_w, mat_x);
  } 

  auto time_b =  timer.elapsed_time();
 
  int32_t sum = 0;
  for (unsigned int i = 0; i < OUTPUTS_COUNT; i++)
    sum+= mat_y[i];  

  float performance_b = 1000*2*INPUTS_COUNT*OUTPUTS_COUNT*1.0/(time_b*0.001*1000000);

  terminal << "cpu int8 AI performance : matrix-vector " << performance_b << " Mops/s\n";
  terminal << "result " << sum << "\n"; 

  


  terminal << "\n\n\n";
}
