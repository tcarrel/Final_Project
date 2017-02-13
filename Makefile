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
CXXFLAGS = -time -Wall -g -std=c++11 -D TIMED -D DEBUG -D GLEW_STATIC
MAIN = game

SHADERS = simple.v.glsl simple.f.glsl
SHADER_HEADER = shaders.h
SHADER_DEF = shaders.cpp
SHADER_OBJ = .shaders.o
SHADER_PROCESSOR = glsl_to_c

OBJ_FILES = .entry_point.o .app.o .window.o .shader_program.o .model.o .mesh.o \
			$(SHADER_OBJ) 
GCCERREXT = gccerr
ERROR_DIR = ./Errors
COPYOUTPUT = 2>&1 | tee $(ERROR_DIR)/$<.$(GCCERREXT)

jFML_LIB = -lsfml-graphics
SDL2_LIB = -lSDL2
GLUT_LIB = -lGL -lGLU -lGLEW -lglut
ALL_LIBS = $(SDL2_LIB) $(GLUT_LIB)

$(MAIN): $(OBJ_FILES) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(ALL_LIBS) -o $(MAIN) \
		2>&1 | tee $(ERROR_DIR)/$(MAIN).$(GCCERREXT)

.entry_point.o: entry_point.cpp app.h constants.h \
		$(SHADER_HEADER) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.app.o: app.cpp app.h constants.h window.h shader_externs.h $(SHADER_HEADER) \
		$(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.window.o: window.cpp window.h constants.h $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.shader_program.o: shader_program.cpp shader_program.h constants.h \
		shader_externs.h $(SHADER_HEADER) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.model.o: model.cpp mesh.h model.h constants.h shader_program.h $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.mesh.o: mesh.cpp mesh.h $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(SHADER_OBJ): $(SHADER_DEF) $(SHADER_HEADER)
	$(CXX) $(CXXFLAGS) -c $(SHADER_DEF) -o $@

shader_externs.h: $(SHADER_DEF)

$(SHADER_HEADER): $(SHADER_DEF)

$(SHADER_DEF): $(SHADERS) $(ERROR_DIR) $(SHADER_PROCESSOR)
	$(SHADER_PROCESSOR) $(SHADER_HEADER) \
			2>&1 | tee $(ERROR_DIR)/$(SHADER_PROCESSOR).$(GCCERREXT)

$(ERROR_DIR):
	mkdir $@

#$(SHADER_PROCESSOR): shader_to_structs/glsl_to_c.cpp
#	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f .*.o $(MAIN) $(SHADER_HEADER) $(SHADER_DEF) a.out
	rm -rf $(ERROR_DIR)

doc: Doxyfile *.cpp *.h
	doxygen

all: Main

Main: $(MAIN)
