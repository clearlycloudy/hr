#source files---

src_files = $(wildcard *.cpp)

#source files end---

#include directories start---

#include directories end---

dir_out = build

$(shell mkdir -p $(dir_out))

.PHONY: all
all: $(src_files)
	$(CXX) -g -O3 -std=c++14 $(src_files) -o $(dir_out)/out

.PHONY: clean
clean:
	rm -f $(dir_out)/* 
