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

CXX = g++
DEBUG = 0
CXXFLAGS = -g -std=c++11 -Wall -W -pedantic -Werror -D TIMED #-D DEBUG
MAIN = game
SHADERS = simple.v.glsl simple.f.glsl
SHADER_HEADER = shaders.h
SHADER_PROCESSOR = glsl_to_c
GCCERREXT = gccerr
ERROR_DIR = ./Errors
COPYOUTPUT = 2>&1 | tee $(ERROR_DIR)/$<.$(GCCERREXT)

$(MAIN): .entry_point.o .app.o .window.o .shader_program.o $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) .*.o -o $(MAIN) 2>&1 \
		| tee $(ERROR_DIR)/$(MAIN).$(GCCERREXT)

.entry_point.o: entry_point.cpp $(SHADER_HEADER) app.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.app.o: app.cpp app.h constants.h window.h shader_program.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.window.o: window.cpp window.h constants.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.shader_program.o: shader_program.cpp shader_program.h constants.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)


$(SHADER_HEADER): $(SHADERS) $(SHADER_PROCESSOR) $(ERROR_DIR)
	$(SHADER_PROCESSOR) $@ $(COPYOUTPUT)

$(ERROR_DIR):
	mkdir $@

$(SHADER_PROCESSOR): shader_to_structs/glsl_to_c.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(COPYOUTPUT)

clean:
	rm -f .*.o $(MAIN) $(SHADER_HEADER) a.out
	rm -rf $(ERROR_DIR)

all: Main

Main: $(MAIN)
