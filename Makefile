# name of the package to build
PKG = imengine

# Location of the boost installation to use
BOOST = /Users/david/Clib/boost_1_45_0

# sources under src/ to build as executables in bin/ linked against the library
BIN_SRCS = $(wildcard src/*.cc)

BIN_NAMES := $(patsubst src/%.cc,%,$(BIN_SRCS))

# sources under $(PKG)/ to compile into build/ and include in the library
LIB_SRCS = $(wildcard $(PKG)/*.cc)

LIB_NAME := lib$(PKG).a
LIB_OBJS := $(patsubst $(PKG)/%.cc,build/%.o,$(LIB_SRCS))

CXXFLAGS = -I. -I$(BOOST)
LDFLAGS = -L. -l$(PKG)

bin: $(BIN_NAMES)

lib: $(LIB_NAME)

$(BIN_NAMES) : bin/% : src/%.cc $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

$(LIB_NAME) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $(LIB_NAME) $(LIB_OBJS)

clean:
	rm -f $(LIB_NAME) $(LIB_OBJS) build/*.d

# See http://www.gnu.org/software/automake/manual/make/Automatic-Prerequisites.html
# and http://mad-scientist.net/make/autodep.html

build/%.o : $(PKG)/%.cc
	$(CXX) -c $< $(CXXFLAGS) -MD -o $@

include $(wildcard build/*.d)
