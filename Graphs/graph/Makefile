inc_dir := ./include
src_dir := src
cc := g++
flags := -Wall -Wextra -std=c++14 $(addprefix -I, $(inc_dir))

inc := graph.h graph_alg.h
src := graph.cpp

build := build
bin := $(build)/bin
intermediates := $(build)/intermediates

test: graph.o
	$(cc) $(flags) main.cpp $(intermediates)/$^ -o $(bin)/$@

graph.o: $(src_dir)/$(src) $(addprefix $(inc_dir)/, $(inc))
	$(cc) $(flags) -c $< -o $(intermediates)/$@