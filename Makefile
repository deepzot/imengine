# name of the package to build
PKG = imengine

# sources under bin/ to build as executables linked against the library
BIN_SRCS = tester

# sources under $(PKG)/ to compile into build/ and include in the library
LIB_SRCS = $(wildcard $(PKG)/*.cc)

# Location of the boost installation to use
BOOST = /Users/david/Clib/boost_1_45_0

LIB_NAME := lib$(PKG).a
LIB_OBJS := $(patsubst $(PKG)/%.cc,build/%.o,$(LIB_SRCS))

CXXFLAGS = -I. -I$(BOOST)
LDFLAGS = -L. -l$(PKG)

$(BIN_SRCS) : % : bin/%.cc $(LIB_NAME)
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

#build/%.d : $(PKG)/%.cc
#	@set -e; rm -f $@; $(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
#	 sed 's,\($*\)\.o[ :]*,build/\1.o $@ : ,g' < $@.$$$$ > $@; \
#	 rm -f $@.$$$$

#include $(patsubst $(PKG)/%.cc,build/%.d,$(LIB_SRCS))
