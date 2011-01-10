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
LIB_SRCS := $(wildcard $(PKG)/*.cc)
LIB_SRCS += $(wildcard $(MODULES:%=$(PKG)/%/*.cc))
LIB_OBJS := $(LIB_SRCS:$(PKG)/%.cc=build/%.o)

# compile and link options
CXXFLAGS := -I. -I$(BOOST)
LDFLAGS := -L. -l$(PKG)

# named targets
test:
	echo $(ALL_SRCS)
	echo $(ALL_OBJS)

bin: $(BIN_NAMES)

lib: $(LIB_NAME)

clean:
	rm -f $(LIB_NAME) $(LIB_OBJS) build/*.d

# implicit rules

$(BIN_NAMES) : % : src/%.cc $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o bin/$@ $< $(LDFLAGS)

$(LIB_NAME) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $(LIB_NAME) $(LIB_OBJS)

# See http://www.gnu.org/software/automake/manual/make/Automatic-Prerequisites.html
# and http://mad-scientist.net/make/autodep.html

build/%.o : $(PKG)/%.cc
	$(CXX) -c $< $(CXXFLAGS) -MD -o $@

# include dependencies

include $(wildcard build/*.d)
