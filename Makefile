#
#   Thomas Russel Carrel
#
#   Makefile
#
#   Define DEBUG, by uncommenting the last argument in CXXFLAGS, will
#  enable detailed debug out put.
#   
#   All of these compile lines are set up to duplicate all output (errors) 
#  from g++ and copy it into a file.
#

CXX = g++

SDL2_CFLAGS := $(shell sdl2-config --cflags)

CXXFLAGS = $(SDL2_CFLAGS) -time -Wall -g -std=c++11 -D TIMED -D DEBUG \
		   -D GLEW_STATIC -O0
MAIN = gg

SHADERS = simple.v.glsl simple.f.glsl
SHADER_HEADER = shaders.h
SHADER_DEF = shaders.cpp
SHADER_OBJ = .shaders.o
SHADER_PROCESSOR = glsl_to_c

APP_DIR = app/
MODEL_DIR = model/
CONS_DIR = input/
DOC_DIR = .doxy/

OBJ_FILES = .entry_point.o .app.o .window.o .GLSL_except.o .shader_program.o \
			.model.o .mesh.o .vertex_array.o .input_handler.o .SG_except.o \
			.scene_graph.o $(SHADER_OBJ) 
GCCERREXT = gccerr
ERROR_DIR = ./Errors
COPYOUTPUT = 2>&1 | tee $(ERROR_DIR)/$<.$(GCCERREXT)

jFML_LIB = -lsfml-graphics
SDL2_LIB := $(shell sdl2-config --libs)
GLUT_LIB = -lGL -lGLU -lGLEW -lglut
ALL_LIBS = $(SDL2_LIB) $(GLUT_LIB)

$(MAIN): $(OBJ_FILES) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(ALL_LIBS) -o $(MAIN) \
		2>&1 | tee $(ERROR_DIR)/$(MAIN).$(GCCERREXT)

.entry_point.o: $(APP_DIR)entry_point.cpp $(APP_DIR)app.h constants.h \
		$(SHADER_HEADER) $(ERROR_DIR)
	$(TIME) $(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.app.o: $(APP_DIR)app.cpp $(APP_DIR)app.h constants.h $(APP_DIR)window.h \
		shader_externs.h $(SHADER_HEADER) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.window.o: $(APP_DIR)window.cpp $(APP_DIR)window.h constants.h $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.GLSL_except.o: GLSL_except.cpp GLSL_except.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.shader_program.o: shader_program.cpp shader_program.h constants.h \
		shader_externs.h GLSL_except.h $(SHADER_HEADER) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)


.model.o: $(MODEL_DIR)model.cpp $(MODEL_DIR)mesh.h \
		$(MODEL_DIR)model.h constants.h shader_program.h \
		$(MODEL_DIR)vertex.h $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.mesh.o: $(MODEL_DIR)mesh.cpp $(MODEL_DIR)mesh.h \
		$(MODEL_DIR)vertex.h $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.scene_graph.o: $(MODEL_DIR)scene_graph.cpp $(MODEL_DIR)scene_graph.h \
		$(MODEL_DIR)SG_except.h $(MODEL_DIR)model.h $(APP_DIR)window.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.SG_except.o: $(MODEL_DIR)SG_except.cpp $(MODEL_DIR)SG_except.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.vertex_array.o: $(MODEL_DIR)vertex_array.cpp $(MODEL_DIR)vertex_array.h \
		$(MODEL_DIR)vertex.h $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.input_handler.o: $(CONS_DIR)input_handler.cpp $(CONS_DIR)input_handler.h \
		$(CONS_DIR)command.h $(CONS_DIR)exit.h $(CONS_DIR)window_show.h \
		$(APP_DIR)window.h $(ERROR_DIR)
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
	mkdir $@/$(MODEL_DIR)
	mkdir $@/$(APP_DIR)
	mkdir $@/$(CONS_DIR)

#$(SHADER_PROCESSOR): shader_to_structs/glsl_to_c.cpp
#	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f .*.o $(MAIN) $(SHADER_HEADER) $(SHADER_DEF) a.out
	rm -rf $(ERROR_DIR)
	rm -rf $(DOC_DIR)

doc: Doxyfile $(DOC_DIR) *.cpp *.h $(MAIN)
	doxygen

$(DOC_DIR):
	mkdir .doxy

all: Main doc

Main: $(MAIN)
