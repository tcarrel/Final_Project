#
#   Thomas Russel Carrel
#
#   Makefile
#
#   Define DEBUG, by uncommenting the last argument in CXXFLAGS, will enable
#  detailed debug out put.
#   
#   All of these compile lines are set up to duplicate all output (errors) from
#  g++ and copy it into a file.
#

CXX = gcc
DEBUG = 0
CXXFLAGS = -g -Wall -W -pedantic -Werror -D TIMED #-D DEBUG
MAIN = game
SHADERS = simple.v.glsl simple.f.glsl
SHADER_HEADER = shaders.h
SHADER_PROCESSOR = glsl_to_c
GCCERREXT = gccerr
ERROR_DIR = ./Errors
COPYOUTPUT = 2>&1 | tee $(ERROR_DIR)/$<.$(GCCERREXT)

$(MAIN): .entry_point.o $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) .*.o -o $(MAIN) 2>&1 \
		| tee $(ERROR_DIR)/$(MAIN).$(GCCERREXT)

.entry_point.o: entry_point.cpp $(SHADER_HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(SHADER_HEADER): $(SHADERS) $(SHADER_PROCESSOR) $(ERROR_DIR)
	$(SHADER_PROCESSOR) $@ $(COPYOUTPUT)

$(ERROR_DIR):
	mkdir $@

clean:
	rm -f .*.o $(MAIN) $(SHADER_HEADER) a.out
	rm -rf $(ERROR_DIR)

all: Main

Main: $(MAIN)
