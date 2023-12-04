CC 		:= clang
EXAMPLE := graph_example
EXAMPLE_SRCS := $(wildcard examples/*.cpp)
EXAMPLES := $(patsubst examples/%.cpp, %, $(EXAMPLE_SRCS))

LD_FLAGS := -Lbuild/ -lrandomgraph -Wl,-rpath=build/
INC_FLAGS := -Isrc/
# MACRO_FLAGS := -DFMTLOG_HEADER_ONLY -DFMT_HEADER_ONLY

.PHONY: build example clean

build:
	mkdir -p build 
	cd build && cmake .. && make

example: build
	@$(CC) examples/$(EXAMPLE).cpp $(INC_FLAGS) $(LD_FLAGS) -o build/$(EXAMPLE) 
	@./build/$(EXAMPLE)

clean:
	rm -rf build