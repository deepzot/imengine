# name of the package to build
PKG := imengine

# names of any subdirs under $(PKG) that also contain library code
# (handling of these loosely inspired by http://aegis.sourceforge.net/auug97.pdf)
MODULES := models

# location of the boost installation to use
BOOST := /Users/david/Clib/boost_1_45_0

# sources under src/ to build as executables in bin/ linked against the library
BIN_SRCS := $(wildcard src/*.cc)
BIN_NAMES := $(patsubst src/%.cc,%,$(BIN_SRCS))

# sources under $(PKG)/ to compile into build/ and include in the library
LIB_NAME := lib$(PKG).a
LIB_SRCS := $(wildcard $(PKG)/*.cc $(MODULES:%=$(PKG)/%/*.cc))
LIB_OBJS := $(LIB_SRCS:$(PKG)/%.cc=build/%.o)
LIB_DEPS := $(wildcard build/*.d $(MODULES:%=build/%/*.d))

# compile and link options
CXXFLAGS := -I. -I$(BOOST)
LDFLAGS := -L. -l$(PKG)

# named targets
test:
	echo $(LIB_DEPS)

bin: $(BIN_NAMES)

lib: $(LIB_NAME)

clean:
	rm -f $(LIB_NAME) $(LIB_OBJS) $(LIB_DEPS)

# implicit rules

$(BIN_NAMES) : % : src/%.cc $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o bin/$@ $< $(LDFLAGS)

$(LIB_NAME) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $(LIB_NAME) $(LIB_OBJS)

# compiling a library source updates its dependency file for next time
# (see http://www.gnu.org/software/automake/manual/make/Automatic-Prerequisites.html
# and http://mad-scientist.net/make/autodep.html for details of this logic)

build/%.o : $(PKG)/%.cc
	$(CXX) -c $< $(CXXFLAGS) -MD -o $@

# include dependencies

include $(LIB_DEPS)
