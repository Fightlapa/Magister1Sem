CPYTHON3 = python3
CPP = g++

# C++ example
HEADERS = ListaSasiedztwa.h
OBJECTS = ListaSasiedztwa.o

# Python module
MODULE_SOURCE = car.cpp car2py.cpp
MODULE_COMPILE_SCRIPT = compile.py

%.o: %.cpp $(HEADERS)
		$(CPP) -c $<


# Build Python `Car` module
car_py_module: $(MODULE_SOURCE) $(MODULE_COMPILE_SCRIPT) $(HEADERS)
	$(CPYTHON3) $(MODULE_COMPILE_SCRIPT) build_ext --inplace

# Clean up the current directory
.PHONY: clean
clean:
	rm -fR build
	rm -f *.so
	rm -f *.o
	rm -fR __pycache__
	rm -f use_car