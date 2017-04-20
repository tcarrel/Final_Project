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
#
#  Set variables.
#
###############################################################################
CXX = g++
CXX_VERS := $(shell g++ -dumpversion)
OS_VERS := $(shell g++ -dumpmachine)

AUTHOR := Thomas R. Carrel

SDL2_CFLAGS := $(shell sdl2-config --cflags)

MAIN = gg

SHADERS = simple.v.glsl simple.f.glsl plane.t.glsl plane.e.glsl
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
            .OBJ_except.o .colors.o .null_command.o $(SHADER_OBJ) \
			.texture_2D.o .texture_base.o .world_loader.o \
			.Render_except.o .skybox.o
GLSL_FILES := $(shell ls *.glsl)
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
CLEAR_ARGS = -D CLEAR_ARGS

INFO = $(COMPILER_ID) $(OS_ID) $(AUTHOR_ID) $(DATE) $(COLOR) $(CLEAR_ARGS)


#CXXFLAGS = $(SDL2_CFLAGS) -time -Wall -g -std=c++11 -D TIMED -D DEBUG \
#		   -D GLEW_STATIC -O0
CXXFLAGS = $(SDL2_CFLAGS) -time -Wall -g -std=c++11 -D TIMED -D DEBUG \
		   -D GLEW_STATIC -O0 $(INFO)
###############################################################################
#
#  The adjacency list.
#
###############################################################################

# link
$(MAIN): $(OBJ_FILES) $(ERROR_DIR) Makefile
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(ALL_LIBS) -o $(MAIN) \
		2>&1 | tee $(ERROR_DIR)/$(MAIN).$(GCCERREXT)

# compile App namespace.
#.entry_point.o: $(APP_DIR)/entry_point.cpp $(APP_DIR)/app.h constants.h \
#		$(SHADER_HEADER) $(APP_ERROR_DIR)
#	$(TIME) $(CXX) $(CXXFLAGS) $(INFO) -c $< -o $@ $(COPYOUTPUT)
.entry_point.o: $(APP_DIR)/entry_point.cpp $(APP_DIR)/app.h constants.h \
		$(SHADER_HEADER) $(APP_ERROR_DIR)
	$(TIME) $(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.app.o: $(APP_DIR)/app.cpp $(APP_DIR)/app.h $(APP_DIR)/window.h \
		$(SHADER_HEADER) $(MODEL_DIR)/scene_graph.h $(MODEL_DIR)/model.h \
		$(APP_ERROR_DIR) $(OBJ_PATH)/obj.h $(OBJ_PATH)/world_loader.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.window.o: $(APP_DIR)/window.cpp $(APP_DIR)/window.h helper_functions.h \
		$(APP_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(APP_DIR)/app.h: constants.h shader_program.h $(INPUT_DIR)/input_handler.h

$(APP_DIR)/window.h: constants.h shader_program.h

$(APP_ERROR_DIR): $(ERROR_DIR)
	mkdir -p $@

# compile the global namespace
.shader_program.o: shader_program.cpp shader_program.h helper_functions.h \
		$(SHADER_HEADER) $(ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.helper_functions.o: helper_functions.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.colors.o: colors.cpp colors.h random.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

constants.h: colors.h

shader_program.h: constants.h GLSL_except.h $(SHADER_HEADER) \
		helper_functions.h tracking_list.h

helper_functions.h: $(SHADER_HEADER)

$(ERROR_DIR):
	mkdir -p $@

# compile Model namespace
.model.o: $(MODEL_DIR)/model.cpp $(MODEL_DIR)/model.h $(MODEL_DIR)/mesh.h \
		$(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.mesh.o: $(MODEL_DIR)/mesh.cpp $(MODEL_DIR)/mesh.h shader_program.h colors.h \
		helper_functions.h $(APP_DIR)/window.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.scene_graph.o: $(MODEL_DIR)/scene_graph.cpp $(MODEL_DIR)/scene_graph.h \
		$(MODEL_DIR)/sg_setup.h $(MODEL_DIR)/model.h \
		$(MODEL_DIR)/mesh.h $(MODEL_DIR)/skybox.h $(APP_DIR)/window.h \
		$(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.sg_setup.o: $(MODEL_DIR)/sg_setup.cpp $(MODEL_DIR)/sg_setup.h \
		$(MODEL_DIR)/scene_graph.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.vertex_array.o: $(MODEL_DIR)/vertex_array.cpp $(MODEL_DIR)/vertex_array.h \
		$(MODEL_DIR)/vertex.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.skybox.o: $(MODEL_DIR)/skybox.cpp $(MODEL_DIR)/skybox.h shader_program.h \
		$(SHADER_HEADER) helper_functions.h $(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.SG_except.o: $(MODEL_DIR)/SG_except.cpp $(MODEL_DIR)/SG_except.h \
		$(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.Render_except.o: $(MODEL_DIR)/Render_except.cpp $(MODEL_DIR)/Render_except.h \
		$(MODEL_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(MODEL_DIR)/mesh.h: $(MODEL_DIR)/vertex_array.h $(MODEL_DIR)/SG_except.h \
		constants.h

$(MDOEL_DIR)/model.h: $(MODEL_DIR)/Render_except.h constants.h shader_program.h

$(MODEL_DIR)/scene_graph.h: $(MODEL_DIR)/SG_except.h constants.h

$(MODEL_DIR)/sg_setup.h: constants.h $(APP_DIR)/window.h

$(MODEL_ERROR_DIR): $(ERROR_DIR)
	mkdir -p $@

# compile Model::OBJ namespace
.obj.o: $(OBJ_PATH)/obj.cpp $(OBJ_PATH)/obj.h $(OBJ_PATH)/OBJ_except.h \
		$(MODEL_DIR)/vertex_array.h $(MODEL_DIR)/vertex.h $(MODEL_DIR)/mesh.h \
		colors.h shader_program.h helper_functions.h tracking_list.h \
		$(OBJ_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.OBJ_except.o: $(OBJ_PATH)/OBJ_except.cpp $(OBJ_PATH)/OBJ_except.h \
		$(OBJ_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.world_loader.o: $(OBJ_PATH)/world_loader.cpp $(OBJ_PATH)/world_loader.h \
		$(MODEL_DIR)/scene_graph.h $(MODEL_DIR)/sg_setup.h $(MODEL_DIR)/mesh.h \
		$(SHADER_HEADER) shader_program.h helper_functions.h $(APP_DIR)/window.h \
		$(OBJ_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

$(OBJ_PATH)/obj.h: $(OBJ_PATH)/OBJ_except.h $(MODEL_DIR)/model.h 

$(OBJ_PATH)/world_loader.h: $(OBJ_PATH)/obj.h

$(OBJ_ERROR_DIR): $(ERROR_DIR) $(MODEL_ERROR_DIR)
	mkdir -p $@

# compile Model::Texture namespace
.texture_base.o: $(TEX_PATH)/texture_base.cpp $(TEX_PATH)/texture_base.h \
		$(TEX_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

.texture_2D.o: $(TEX_PATH)/2D.texture.cpp $(TEX_PATH)/2D.texture.h \
		$(TEX_PATH)/texture_base.h $(TEX_ERROR_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(COPYOUTPUT)

__all_texture_types.h: $(TEX_PATH)/texture_base.h $(TEX_PATH)/2D.texture.h

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

$(SHADER_OBJ): $(SHADER_DEF) $(SHADER_HEADER)
	$(CXX) $(CXXFLAGS) -c $(SHADER_DEF) -o $@

$(SHADER_HEADER): $(SHADER_DEF) $(SHADERS)

$(SHADER_DEF): $(SHADERS) $(ERROR_DIR) $(SHADER_PROCESSOR) $(GLSL_FILES)
	$(SHADER_PROCESSOR) $(SHADER_HEADER) \
			2>&1 | tee $(ERROR_DIR)/$(SHADER_PROCESSOR).$(GCCERREXT)

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
#
#  Grouped commands.
#
###############################################################################

all: Main doc

Main: $(MAIN)

