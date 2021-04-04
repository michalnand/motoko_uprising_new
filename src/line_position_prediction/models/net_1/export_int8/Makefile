LIB_NAME = ./LibEmbeddedNetwork

EMBEDDED_NEURAL_NETWORK_LIB_PATH = ../../../../../embedded_inference/libs_embedded_neural_network/

CC 	= g++



CFLAGS = -O3 -funroll-loops -Wall -Wextra -pedantic -std=c++17 -fPIC -shared -undefined dynamic_lookup

INC = -I.
INC+= -I$(EMBEDDED_NEURAL_NETWORK_LIB_PATH)
INC+= `python3-config --include`
INC+= `python3 -m pybind11 --includes`

SRCS = $(shell find . -name '*.cpp')

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(LIB_NAME)`python3-config --extension-suffix`

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

clean:
	rm -f $(LIB_NAME)*
	rm -f $(OBJS)
	
