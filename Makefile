CC:=gcc
CXX:=g++
OC:=objcopy

# setup our targets
target = $(notdir $(CURDIR))
release = $(addprefix bin/rel/, $(target))
debug = $(addprefix bin/dbg/, $(target))

INCLUDES:=-I../include -I.  $(ADDITION_INC)
CXXFLAGS:=-Wall -ggdb -std=gnu++17 -DWEBRTC_POSIX -DASIO_STANDALONE
LDLIBS:= -lpthread -lm -lboost_system -lssl -lcrypto #-lSDP -llibwebrtc -llibwebrtc_full
LDFLAGS:=-L/usr/lib -L/home/lib/rel $(ADDITION_LIB)

# make lists of our sources and objects
sources = $(wildcard *.cpp)
txtsources = $(filter-out buildstamp.txt,$(wildcard *.txt))
txtobjs = $(patsubst %.txt,%.o,$(txtsources))
relobjs = $(patsubst %.cpp,obj/rel/%.o,$(notdir $(sources))) $(txtobjs)
dbgobjs = $(patsubst %.cpp,obj/dbg/%.o,$(notdir $(sources))) $(txtobjs)

# modify build options for release
$(release): CXXFLAGS+=-O2
$(release): LDFLAGS+=-L/home/lib/rel

# modify build options for debug
$(debug): CXXFLAGS+=-g -O0
$(debug): LDFLAGS+=-L/home/lib/dbg

# tag our phony targets
.PHONY: clean dirs buildstamp.txt

# set default targets
all: dirs $(release) $(debug)

# recipe to create the obj and bin folders
dirs:
	mkdir -p obj/rel
	mkdir -p obj/dbg
	mkdir -p bin/rel
	mkdir -p bin/dbg

# recipe to update the build timestamp file
buildstamp.txt:
	date -u > buildstamp.txt

# recipe to convert text files to object files
%.o: %.txt
	$(OC) --input binary --output elf64-x86-64 --binary-architecture i386:x86-64 $< $@

# recipe to create the release objects
obj/rel/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< $(INCLUDES) -I./inc  -I./Common -c -o $@

# recipe to create the debug objects
obj/dbg/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< $(INCLUDES) -I./inc  -I./Common -c -o $@

# recipe to build the release target
$(release): $(relobjs) buildstamp.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

# recipe to build the debug target
$(debug): $(dbgobjs) buildstamp.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

# clean-up recipe
clean:
	rm -rf obj
	rm -rf bin
	rm -f *.o
	rm -f buildstamp.txt

