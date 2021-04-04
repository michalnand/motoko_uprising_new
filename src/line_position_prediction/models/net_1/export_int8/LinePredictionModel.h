#ifndef _LinePredictionModel_H_
#define _LinePredictionModel_H_


#include <ModelInterface.h>

class LinePredictionModel : public ModelInterface<int8_t>
{
	public:
		 LinePredictionModel();
		 void reset();
		 void forward();
	private:
		 float *hidden_state;
};


#endif
