# Setting bash colors
RED    := $(shell tput -Txterm setaf 1)
YELLOW := $(shell tput -Txterm setaf 3)
GREEN  := $(shell tput -Txterm setaf 2)
PURPLE := $(shell tput -Txterm setaf 5)
WHITE  := $(shell tput -Txterm setaf 9)
LBLUE  := $(shell tput -Txterm setaf 6)
RESET  := $(shell tput -Txterm sgr0   )

#################################################################
#                         COMPILE OPTIONS                       #
#################################################################

OMP     := 1
DEBUG   := 0

STD     := -std=c++17

CFLAGS  := -lstdc++fs
#-Wall -Wextra -Wno-unused-result
LDFLAGS := -fPIC
AR      := ar
ARFLAGS := rcs

#################################################################
#                         PARSE OPTIONS                         #
#################################################################

define config
  $(if $(filter $(1), $(2)), $(3), $(4) )
endef

ifneq ($(STD), -std=c++17)
$(error $(RED)C++ minimum standard required is c++17$(RESET))
endif

CFLAGS  += $(strip $(call config, $(OMP),     1, -fopenmp, ))
OPTS    := $(strip $(call config, $(DEBUG),   1, -O0 -g -DDEBUG, -Ofast -mavx))

#################################################################
#                         SETTING DIRECTORIES                   #
#################################################################

SRC_DIR    := ./src
INC_DIR    := ./include
EXAMPLE    := ./example
OBJ_DIR    := ./obj
OUT_DIR    := ./bin
DEP_DIR    := ./.dep
UTIL_DIR   := ./utility

DFLAGS  = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td

SRC    := $(sort $(wildcard $(SRC_DIR)/*.cpp))
HEADER := $(sort $(wildcard $(INC_DIR)/*.h))
EXE    := $(sort $(wildcard $(EXAMPLE)/*.cpp))
INC    := -I$(INC_DIR)
SLIB   := libscorer.so
ALIB   := libscorer.a

OBJS   := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXEC   := $(patsubst %.cpp, %$(EXTENSION), $(EXE))
OUTPUT := $(addprefix $(OUT_DIR)/, $(notdir $(patsubst %.cpp, %$(EXTENSION), $(EXE))) )

#################################################################
#                         OS FUNCTIONS                          #
#################################################################

define MKDIR
  $(if $(filter $(OS), Windows_NT), mkdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0), mkdir -p $(1) )
endef

mkdir_dep  := $(call MKDIR, $(DEP_DIR))
mkdir_obj  := $(call MKDIR, $(OBJ_DIR))
mkdir_out  := $(call MKDIR, $(OUT_DIR))

EXTENSION  := $(call config, $(OS), Windows_NT, .exe, )

#################################################################
#                         BUILD COMMAND LINE                    #
#################################################################

CFLAGS += $(STD)
CFLAGS += $(OPTS)
CFLAGS += $(INC)

all: help

#################################################################
#                         MAIN RULES                            #
#################################################################

example: $(OUT_DIR)           ##@examples Compile test example.
	@printf "%-80s " "Compiling scorer example ..."
	@$(CXX) $(EXAMPLE)/example.cpp -o $(OUT_DIR)/example $(CFLAGS) $(LDFLAGS)
	@printf "[done]\n"

#################################################################
#                         SCORER RULES                          #
#################################################################

#scorer: $(OBJS) $(SLIB)                       ##@library Create shared scorer library.
libscorer: $(OBJS) $(ALIB)                     ##@library Create shared scorer library.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d # compile all cpp in SRC_DIR for OBJ
	@printf "%-80s " "generating obj for $<"
	@$(CXX) $(DFLAGS) $(CFLAGS) -c $< -o $@
	@mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@
	@printf "[done]\n"

$(ALIB): $(OBJS)
	@printf "%-80s " "generating $(ALIB) ..."
	@$(AR) $(ARFLAGS) $@ $^
	@printf "[done]\n"

$(SLIB): $(OBJS) # not work
	@printf "%-80s " "generating $(ALIB) ..."
	@$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@
	@printf "[done]\n"

$(OUTPUT): $(OBJS) # not work
	@$(CXX) $(CFLAGS) $< -o $@

$(DEP_DIR)/%.d: ;
.PRECIOUS: $(DEP_DIR)/%.d
include $(wildcard $(patsubst %,$(DEP_DIR)/%.d,$(basename $(SRC))))

#################################################################
#                         UTILS RULES                           #
#################################################################

pythonic: ##@utils Build Cython version of Scorer library
	python setup.py build_ext --inplace
	mv Pyscorer.cpython* pyc/

# Add the following 'help' target to your Makefile
# And add help text after each target name starting with '\#\#'
# A category can be added with @category
HELP_FUN = \
	%help; \
	while(<>) { push @{$$help{$$2 // 'options'}}, [$$1, $$3] if /^([a-zA-Z\-]+)\s*:.*\#\#(?:@([a-zA-Z\-]+))?\s(.*)$$/ }; \
	print "\t\t\t$(LBLUE)Scorer Makefile$(RESET)\n"; \
	print "usage: ${PURPLE}make${RESET} ${GREEN}<target>${RESET}\n\n"; \
	for (sort keys %help) { \
	print "${WHITE}$$_:${RESET}\n"; \
	for (@{$$help{$$_}}) { \
	$$sep = " " x (32 - length $$_->[0]); \
	print "  ${PURPLE}$$_->[0]${RESET}$$sep${GREEN}$$_->[1]${RESET}\n"; \
	}; \
	print "\n"; }
.PHONY: clean

help:                   ##@utils Show this help message.
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)

clean:                  ##@utils Clean all files.
	@printf "%-80s " "Cleaning all files..."
	@rm -rf $(OBJS) $(ALIB) $(SLIB) $(OBJ_DIR)/* $(DEP_DIR)/*
	@printf "[done]\n"
$(DEP_DIR):             ##@utils Make dependencies directory
	@printf "%-80s " "Creating dependencies directory ..."
	@$(mkdir_dep)
	@printf "[done]\n"
$(OBJ_DIR):             ##@utils Make objs directory.
	@printf "%-80s " "Creating objs directory ..."
	@$(mkdir_obj)
	@printf "[done]\n"
$(OUT_DIR):             ##@utils Make output (executables) directory.
	@printf "%-80s " "Creating output directory ..."
	@$(mkdir_out)
	@printf "[done]\n"
