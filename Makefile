######################################################################################
## A generic Makefile for a C++ library project, assuming the following layout:
##
##  <pkg>/
##    Makefile
##    <pkg>.h (master header that includes headers for all client classes)
##    lib<pkg>.a (library file containing all project classes, including those in any modules)
##    src/
##      <prog>.cc, ... (source for binary programs)
##    bin/
##      <prog>, ... (binary executables, one per source in )
##    <pkg>/
##      <class>.h, <class>.cc, ... (top-level project classes)
##      <module1>/
##        <class>.h, <class>.cc, ... (project classes organized into optional modules)
##      ...
##    build/
##      <prog>.d, ... (dependency files for binary program sources)
##      <class>.o, <class>.d, ... (dependency files for project top-level classes)
##      <module1>/
##        <class>.o, <class>.d, ... (dependency files for project module classes)
##      ...
##
## David Kirkby (University of California, Irvine) <dkirkby@uci.edu>
######################################################################################

# name of the package to build
PKG := imengine

# names of any subdirs under $(PKG) that also contain library code
# (handling of these loosely inspired by http://aegis.sourceforge.net/auug97.pdf)
MODULES := models

# location of the boost installation to use
BOOST := /Users/david/Clib/boost_1_45_0

# compile and link options
CXXFLAGS := -I. -I$(BOOST) -O3 -fno-implicit-templates
LDFLAGS := -L. -l$(PKG) $(BOOST)/stage/lib/libboost_program_options.a

# sources under src/ to build as executables in bin/ linked against the library
BIN_SRCS := $(wildcard src/*.cc)
BIN_NAMES := $(patsubst src/%.cc,bin/%,$(BIN_SRCS))

# sources under $(PKG)/ to compile into build/ and include in the library
LIB_NAME := lib$(PKG).a
LIB_SRCS := $(wildcard $(PKG)/*.cc $(MODULES:%=$(PKG)/%/*.cc))
LIB_OBJS := $(LIB_SRCS:$(PKG)/%.cc=build/%.o)

# automatically generated dependency files
ALL_DEPS := $(wildcard build/*.d $(MODULES:%=build/%/*.d))

# named targets
bin: $(BIN_NAMES)

lib: $(LIB_NAME)

clean:
	rm -f $(LIB_NAME) $(LIB_OBJS) $(ALL_DEPS)

# implicit rules

# compiling a library or bin source updates its dependency file for next time
# (see http://www.gnu.org/software/automake/manual/make/Automatic-Prerequisites.html
# and http://mad-scientist.net/make/autodep.html for details of this logic)

$(BIN_NAMES) : bin/% : src/%.cc $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -MMD -MF build/$(@F).d -o $@ $< $(LDFLAGS)

$(LIB_NAME) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $(LIB_NAME) $(LIB_OBJS)

build/%.o : $(PKG)/%.cc
	$(CXX) -c $< $(CXXFLAGS) -MMD -o $@

# include dependencies

include $(ALL_DEPS)
