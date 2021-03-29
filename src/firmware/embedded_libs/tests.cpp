#include <tests.h>
#include <Linear.h>
#include <Conv2d.h>

template<   unsigned int in_features, unsigned int out_features, 
            class IO_t, class WEIGHT_t, class ACC_t>
float linear_layer_test()
{
  IO_t weights[in_features*out_features];
  IO_t bias[out_features];
  IO_t input[in_features];
  IO_t output[out_features*4];

  for (unsigned int i = 0; i < in_features*out_features; i++)
    weights[i] = i*27 + 55;

  for (unsigned int i = 0; i < out_features; i++)
    bias[i] = 0;
 
  for (unsigned int i = 0; i < in_features; i++)
    input[i] = i*27 + 55;

  for (unsigned int i = 0; i < out_features; i++)
    output[i] = 0; 

  timer.reset();

  for (unsigned int j = 0; j < 1000; j++)
  {
    for (unsigned int i = 0; i < in_features; i++)
      input[i]+= i*27;
    Linear<in_features, out_features, IO_t, WEIGHT_t, ACC_t, 127, 521>(output, input, weights, bias);
  }

  auto time = timer.elapsed_time()*0.001;

  float performance = 1000*2*in_features*out_features*1.0/(time*1000000);

  terminal << "linear layer " << in_features << " " << out_features << " " << " performance = " << performance << "Mops/s\n";

  return performance;
}




template<   unsigned int height, unsigned int width,
            unsigned int input_channels, unsigned int out_channels, 
            class IO_t, class WEIGHT_t, class ACC_t>
float conv2d_layer_test()
{
  IO_t weights[input_channels*out_channels*3*3];
  IO_t bias[out_channels];
  IO_t input[height*width*input_channels];
  IO_t output[height*width*out_channels];

  for (unsigned int i = 0; i < input_channels*out_channels*3*3; i++)
    weights[i] = i*27 + 55;

  for (unsigned int i = 0; i < out_channels; i++)
    bias[i] = 0;
 
  for (unsigned int i = 0; i < height*width*input_channels; i++)
    input[i] = i*27 + 55;

  for (unsigned int i = 0; i < height*width*out_channels; i++)
    output[i] = 0; 

  timer.reset();

  for (unsigned int j = 0; j < 10; j++)
  {
    for (unsigned int i = 0; i < height*width*input_channels; i++)
      input[i]+= i*27;

    Conv2d<height, width, input_channels, out_channels, 3, 1, 0, IO_t, WEIGHT_t, ACC_t, 127, 571>(output, input, weights, bias);
  }

  auto time = timer.elapsed_time()*0.001; 

  float performance = 10*2*(height-2)*(width-2)*input_channels*out_channels*3*3*1.0/(time*1000000);

  terminal << "conv layer layer " << height << " " << width << " " << input_channels << " " << out_channels << " " << " performance = " << performance << "Mops/s\n";

  return performance;
}


void performance_test(bool cache_enabled)
{
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

  float score = 0;

  terminal << "cache enabled " << cache_enabled << "\n\n";

  terminal << "int8 performance\n";
  score+= linear_layer_test<64, 64, int8_t, int8_t, int32_t>();
  score+= linear_layer_test<16, 64, int8_t, int8_t, int32_t>();
  score+= linear_layer_test<64, 16, int8_t, int8_t, int32_t>(); 
  score+= linear_layer_test<128, 128, int8_t, int8_t, int32_t>();
  score+= linear_layer_test<16, 128, int8_t, int8_t, int32_t>();
  score+= linear_layer_test<128, 16, int8_t, int8_t, int32_t>();
  
  score+= conv2d_layer_test<32, 32, 1, 8,  int8_t, int8_t, int32_t>();
  score+= conv2d_layer_test<16, 16, 16, 16, int8_t, int8_t, int32_t>();
  score+= conv2d_layer_test<16, 16, 16, 32, int8_t, int8_t, int32_t>();
  score+= conv2d_layer_test<8, 8, 32, 64, int8_t, int8_t, int32_t>();
  score+= conv2d_layer_test<8, 8, 64, 64, int8_t, int8_t, int32_t>();
  score+= conv2d_layer_test<4, 4, 64, 128, int8_t, int8_t, int32_t>();


  /* 
  terminal << "\n"; 

  terminal << "float performance\n";
  score+= linear_layer_test<64, 64, float, float, float>();
  score+= linear_layer_test<16, 64, float, float, float>();
  score+= linear_layer_test<64, 16, float, float, float>();
  score+= linear_layer_test<128, 128, float, float, float>();
  score+= linear_layer_test<16, 128, float, float, float>();
  score+= linear_layer_test<128, 16, float, float, float>();
 
  score+= conv2d_layer_test<32, 32, 1, 16, float, float, float>();
  score+= conv2d_layer_test<16, 16, 16, 16, float, float, float>();
  score+= conv2d_layer_test<8, 8, 32, 32, float, float, float>();
  score+= conv2d_layer_test<4, 4, 32, 64, float, float, float>();

  terminal << "\n"; 
  */

  terminal << "score " << score << "\n";
  
  terminal << "\n\n\n";
}
