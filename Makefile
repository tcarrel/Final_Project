#
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
###############################################################################

###############################################################################
#                                                                             #
#  Set variables.                                                             #
#                                                                             #
###############################################################################

CXX = g++
CXX_VERS := $(shell g++ -dumpversion)
OS_VERS := $(shell g++ -dumpmachine)

AUTHOR := Thomas R. Carrel

SDL2_CFLAGS := $(shell sdl2-config --cflags)

MAIN = gg

SHADERS = simple.v.glsl simple.f.glsl
SHADER_HEADER = shaders.h
SHADER_DEF = shaders.cpp
SHADER_OBJ = .shaders.o
SHADER_PROCESSOR = glsl_to_c

APP_DIR = app
MODEL_DIR = model
INPUT_DIR = input
OBJ_DIR = obj_loader
TEX_DIR = texture
OBJ_PATH = $(MODEL_DIR)/$(OBJ_DIR)
TEX_PATH = $(MODEL_DIR)/$(TEX_DIR)
DOC_DIR = .doxy

ERROR_DIR = ./Errors
APP_ERROR_DIR = $(ERROR_DIR)/$(APP_DIR)
MODEL_ERROR_DIR =  $(ERROR_DIR)/$(MODEL_DIR)
OBJ_ERROR_DIR = $(MODEL_ERROR_DIR)/$(OBJ_DIR)
INPUT_ERROR_DIR = $(ERROR_DIR)/$(INPUT_DIR)
TEX_ERROR_DIR = $(MODEL_ERROR_DIR)/$(TEX_DIR)

DOXY_OUTPUT_DIR = $(ERROR_DIR)/Doxygen

OBJ_FILES = .entry_point.o .app.o .window.o .GLSL_except.o .shader_program.o \
			.model.o .mesh.o .vertex_array.o .input_handler.o .SG_except.o \
			.scene_graph.o .sg_setup.o .helper_functions.o .obj.o \
            .OBJ_except.o .colors.o .random.o .null_command.o $(SHADER_OBJ) \
			.texture.o
GCCERREXT = gccerr

COPYOUTPUT = 2>&1 | tee $(ERROR_DIR)/$<.$(GCCERREXT)
COPYDOXYOUTPUT = 2>&1 | tee $(DOXY_OUTPUT_DIR)/$<.doxy.out


SOIL_LIB = -lSOIL
SDL2_LIB := $(shell sdl2-config --libs)
GLUT_LIB = -lGL -lGLU -lGLEW -lglut
ALL_LIBS = $(SOIL_LIB) $(SDL2_LIB) $(GLUT_LIB)

COMPILER_ID = -D COMPILER_ID_STRING="$(CXX_VERS)"
OS_ID = -D OS_ID_STRING="$(OS_VERS)"
AUTHOR_ID = -D AUTHOR_ID_STRING="$(AUTHOR)"
DATE = -D COMPILE_TIME="$(shell date)"
COLOR = -D COLOR_ARRAY

INFO = $(COMPILER_ID) $(OS_ID) $(AUTHOR_ID) $(DATE) $(COLOR)


CXXFLAGS = $(SDL2_CFLAGS) -time -Wall -g -std=c++11 -D TIMED -D DEBUG \
		   -D GLEW_STATIC -O0 $(INFO)



###############################################################################
#                                                                             #
#  The adjacency list.                                                        #
#                                                                             #
###############################################################################

# link
$(MAIN): $(OBJ_FILES) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(ALL_LIBS) -o $(MAIN) \
		2>&1 | tee $(ERROR_DIR)/$(MAIN).$(GCCERREXT)





# compile App namespace.
.entry_point.o: $(APP_DIR)/entry_point.cpp $(APP_DIR)/app.h constants.h \
		$(SHADER_HEADER) $(APP_ERROR_DIR)
	$(TIME) $(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.app.o: $(APP_DIR)/app.cpp $(APP_DIR)/app.h constants.h $(APP_DIR)/window.h \
		shader_externs.h $(SHADER_HEADER) $(MODEL_DIR)/scene_graph.h \
		$(MODEL_DIR)/model.h $(APP_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.window.o: $(APP_DIR)/window.cpp $(APP_DIR)/window.h constants.h \
		$(APP_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(APP_ERROR_DIR): $(ERROR_DIR)
	mkdir -p $@





# compile the global namespace
.shader_program.o: shader_program.cpp shader_program.h constants.h \
		shader_externs.h GLSL_except.h helper_functions.h \
		$(SHADER_HEADER) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(SHADER_OBJ): $(SHADER_DEF) $(SHADER_HEADER)
	$(CXX) $(CXXFLAGS) -c $(SHADER_DEF) -o $@

$(SHADER_HEADER): $(SHADER_DEF)

$(SHADER_DEF): $(SHADERS) $(ERROR_DIR) $(SHADER_PROCESSOR)
	$(SHADER_PROCESSOR) $(SHADER_HEADER) \
			2>&1 | tee $(ERROR_DIR)/$(SHADER_PROCESSOR).$(GCCERREXT)

.helper_functions.o: helper_functions.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.colors.o: colors.cpp colors.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.random.o: random.cpp random.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

shader_externs.h: $(SHADER_DEF)

$(ERROR_DIR):
	mkdir -p $@





# compile Model namespace
.model.o: $(MODEL_DIR)/model.cpp $(MODEL_DIR)/mesh.h \
		$(MODEL_DIR)/model.h constants.h shader_program.h \
		$(MODEL_DIR)/vertex.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.mesh.o: $(MODEL_DIR)/mesh.cpp $(MODEL_DIR)/mesh.h \
		$(MODEL_DIR)/vertex.h helper_functions.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.scene_graph.o: $(MODEL_DIR)/scene_graph.cpp $(MODEL_DIR)/scene_graph.h \
		$(MODEL_DIR)/sg_setup.h $(MODEL_DIR)/SG_except.h \
		$(MODEL_DIR)/model.h $(APP_DIR)/window.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.sg_setup.o: $(MODEL_DIR)/sg_setup.cpp $(MODEL_DIR)/sg_setup.h \
		$(MODEL_DIR)/scene_graph.h $(APP_DIR)/window.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.SG_except.o: $(MODEL_DIR)/SG_except.cpp $(MODEL_DIR)/SG_except.h \
		$(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.vertex_array.o: $(MODEL_DIR)/vertex_array.cpp $(MODEL_DIR)/vertex_array.h \
		$(MODEL_DIR)/vertex.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(MODEL_ERROR_DIR): $(ERROR_DIR)
	mkdir -p $@






# compile Model::OBJ namespace
.obj.o: $(OBJ_PATH)/obj.cpp $(OBJ_PATH)/obj.h helper_functions.h \
		$(OBJ_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.OBJ_except.o: $(OBJ_PATH)/OBJ_except.cpp $(OBJ_PATH)/OBJ_except.h \
		$(OBJ_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(OBJ_ERROR_DIR): $(ERROR_DIR) $(MODEL_ERROR_DIR)
	mkdir -p $@






# compile Model::Image namespace
.texture.o: $(TEX_PATH)/texture.cpp $(TEX_PATH)/texture.h $(TEX_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(TEX_ERROR_DIR): $(MODEL_ERROR_DIR) $(ERROR_DIR)
	mkdir -p $@





# compile Input namespace
.input_handler.o: $(INPUT_DIR)/input_handler.cpp $(INPUT_DIR)/input_handler.h \
		$(INPUT_DIR)/all_commands.h $(INPUT_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.null_command.o: $(INPUT_DIR)/null.cpp $(INPUT_DIR)/null.h \
		$(INPUT_DIR)/command.h $(INPUT_DIR)/command_enum.h \
		$(INPUT_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(INPUT_DIR)/all_commands.h: $(INPUT_DIR)/command.h $(INPUT_DIR)/exit.h \
		$(INPUT_DIR)/null.h $(INPUT_DIR)/command_enum.h \
		$(INPUT_DIR)/window_show.h $(INPUT_DIR)/screenshot.h

$(INPUT_DIR)/window_show.h: $(INPUT_DIR)/command.h $(INPUT_DIR)/command_enum.h \
		$(APP_DIR)/window.h

$(INPUT_ERROR_DIR): $(ERROR_DIR)
	mkdir -p $@






# fulfill additional dependencies
.GLSL_except.o: GLSL_except.cpp GLSL_except.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

constants.h: colors.h

helper_functions.h: helper_functions.cpp






# clean
clean:
	rm -f .*.o $(MAIN) $(SHADER_HEADER) $(SHADER_DEF) a.out
	rm -rf $(ERROR_DIR)
	rm -rf $(DOC_DIR)






# compile documentation.
doc: Doxyfile $(DOC_DIR) *.cpp *.h $(MAIN) $(DOXY_OUTPUT_DIR)
	doxygen $(COPYDOXYOUTPUT)

$(DOC_DIR):
	mkdir -p $@

$(DOXY_OUTPUT_DIR): $(ERROR_DIR)
	mkdir -p $@


###############################################################################
#                                                                             #
#  Grouped commands                                                           #
#                                                                             #
###############################################################################



all: Main doc

Main: $(MAIN)
