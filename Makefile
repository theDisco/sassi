NAME = sassi
INI_DIR = /etc/php5/mods-available
CLI_DIR = /etc/php5/cli/conf.d
EXTENSION_DIR = $(shell php-config --extension-dir)
EXTENSION = ${NAME}.so
INI = ${NAME}.ini
COMPILER = g++
LINKER = g++
COMPILER_FLAGS = -Wall -c -O2 -std=c++11 -fpic -o
LINKER_FLAGS = -shared
LINKER_DEPENDENCIES = -lphpcpp -lsass -L"`pwd`"/lib/libsass/

RM = rm -f
CP = cp -f
LN = ln -sf
MKDIR = mkdir -p

SOURCES = $(wildcard src/*.cpp)
OBJECTS	= $(SOURCES:src/%.cpp=%.o)

all: ${OBJECTS} ${EXTENSION}

${EXTENSION}: ${OBJECTS}
	${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
	${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=src/%.cpp}

install:
	${CP} ${EXTENSION} ${EXTENSION_DIR}
	${CP} ${INI} ${INI_DIR} 
	${LN} ${INI_DIR}/${INI} ${CLI_DIR}/30-${INI}

clean:
	${RM} ${EXTENSION} ${OBJECTS}