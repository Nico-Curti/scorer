# Scorer Version
MAJOR 	 := 1
MINOR 	 := 0
REVISION := 0

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

OMP     ?= 1
DEBUG   ?= 0

STD     := -std=c++17

CFLAGS  := -Wall -Wextra -Wno-unused-result
CFLAGS  += -DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -DREVISION=$(REVISION)

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

PYC_DIR := ./scorer
INC_DIR := $(PYC_DIR)/include
TST_DIR := $(PYC_DIR)/example
OUT_DIR    := ./bin
UTIL_DIR   := ./utility

DFLAGS  = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td

INC := -I$(INC_DIR)

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
#                         UTILS RULES                           #
#################################################################

pythonic: ##@utils Build Cython version of Scorer package
	python setup.py build_ext --inplace

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
	@rm -rf ./*.so $(PYC_DIR)/*.so $(PYC_DIR)/*.cpp ./build ./bin
	@printf "[done]\n"
