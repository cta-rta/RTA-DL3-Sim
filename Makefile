# ==========================================================================
# RTA-DL2-Sim C++ https://github.com/ASTRO-EDU/RTA-DL2-Sim
#
# Copyright (C) 2018 Giancarlo Zollino
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# ==========================================================================


SHELL = /bin/sh

ifndef RTALIB
$(error RTALIB is not set.)
endif
ifndef CFITSIO
$(error CFITSIO is not set.)
endif
ifndef MYSQL_CXX_CNT
$(error MYSQL_CXX_CNT is not set.)
endif
ifndef BOOST_PATH
$(error BOOST_PATH is not set.)
endif

####### 1) Project names and system
SYSTEM= $(shell gcc -dumpmachine)

# Applications
EXE = dl3Sim

####### 2) Directories for the compiler
OBJECTS_DIR = obj
SOURCE_DIR = src
INCLUDE_DIR = include
PROJECTS_DIR = projects
EXE_DESTDIR  = bin
LIB_DESTDIR = lib

####### 3) Compiler, tools and options

CXX = g++

#CXXFLAGS = -std=c++11 -O2 -I $(INCLUDE_DIR) $(RTALIB)
CXXFLAGS = -std=c++11 -O2 -I $(INCLUDE_DIR) $(RTALIB) $(MYSQL_CXX_CNT)

ifeq ($(DEBUG),1)
	CXXFLAGS += -DDEBUG
endif

ifeq ($(MULTITHREAD),1)
	CXXFLAGS += -DMULTITHREAD
endif


LIBS += -L $(RTALIB)/lib/ -lRTA

LIBS += -L$(CFITSIO)/lib -lcfitsio

LIBS += -L$(MYSQL_CXX_CNT)/lib64 -lmysqlcppconn	#NEW ADDED

CXXFLAGS += -I$(MYSQL_CXX_CNT)/include	#NEW ADDED

CXXFLAGS += -I$(CFITSIO)/include

CXXFLAGS += -I$(BOOST_PATH)	#NEW ADDED

CXXFLAGS += -Wl,-Bdynamic	#NEW ADDED

CXXFLAGS += -I/usr/local/include/cppconn	#NEW ADDED


AR       = ar cqs
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f -r
COPY_FILE= $(COPY) -p
COPY_DIR = $(COPY) -pR
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rm -rf
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p	# -p


#######  4) VPATH
VPATH=$(SOURCE_DIR):$(INCLUDE_DIR):
vpath %.o $(OBJECTS_DIR)

INCLUDE=$(foreach dir,$(INCLUDE_DIR), $(wildcard $(dir)/*.h))
SOURCE=$(foreach dir,$(SOURCE_DIR), $(wildcard $(dir)/*.cpp))
OBJECTS=$(addsuffix .o, $(basename $(notdir $(SOURCE))))

$(info $$INCLUDE is [${INCLUDE}])
$(info $$SOURCE is [${SOURCE}])
$(info $$OBJECTS is [${OBJECTS}])


# Pattern rule
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJECTS_DIR)/$@


#all: compile the entire program.	agextspot performance bayesian
all: exe
	#only if conf directory is present:
	#$(SYMLINK) $(CONF_DIR) $(CONF_DEST_DIR)

exe: makeobjdir $(OBJECTS)
	test -d $(EXE_DESTDIR) || mkdir -p $(EXE_DESTDIR)
	$(CXX) $(CPPFLAGS) $(ALL_CFLAGS) -o $(EXE_DESTDIR)/$(EXE) $(OBJECTS_DIR)/*.o $(LIBS)

makeobjdir:
	test -d $(OBJECTS_DIR) || mkdir -p $(OBJECTS_DIR)


#clean: delete all files from the current directory that are normally created by building the program.
clean:
	$(DEL_FILE) $(OBJECTS_DIR)/*.o
	$(DEL_FILE) $(EXE_DESTDIR)/*
