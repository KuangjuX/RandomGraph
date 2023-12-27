CC 		:= g++

EXAMPLE ?= perf
EXAMPLE_SRCS := $(wildcard examples/*.cpp)
EXAMPLES := $(patsubst examples/%.cpp, %, $(EXAMPLE_SRCS))

LD_FLAGS := -Lbuild/ -lrandomgraph -Wl,-rpath=build/
INC_FLAGS := -Isrc/ -I3rd-party/fmt/include/
MACRO_FLAGS := -DFMTLOG_HEADER_ONLY -DFMT_HEADER_ONLY

COMMAND_ARGS ?=

T0 ?= 1000
DEBUG ?= N

ifeq ($(DEBUG),Y)
	COMMAND_ARGS += -DENABLE_DEBUG=ON
endif

.PHONY: build example clean test

build:
	@mkdir -p build 
	@cd build && cmake $(COMMAND_ARGS) .. && make

example: build
	@$(CC) examples/$(EXAMPLE).cpp $(INC_FLAGS) $(LD_FLAGS) $(MACRO_FLAGS) -o build/$(EXAMPLE) 
	@./build/$(EXAMPLE) $(T0)

test: build
	@make -C build/ test

clean:
	@rm -rf build