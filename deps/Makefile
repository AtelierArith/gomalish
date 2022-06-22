.PHONY: all, clone, clean, distclean

NPROCS:=1
OS:=$(shell uname -s)

ifeq ($(OS),Linux)
  NPROCS:=$(shell grep -c ^processor /proc/cpuinfo)
endif
ifeq ($(OS),Darwin) # Assume Mac OS X
  NPROCS:=$(shell getconf _NPROCESSORS_ONLN)
endif

OWNER=ricosjp
REPOSITORY=monolish
VERSION=0.16.3

all: build

clone:
ifeq ($(wildcard ./$(REPOSITORY)/.),)
	git clone --depth=1 -b ${VERSION} https://github.com/$(OWNER)/$(REPOSITORY).git
else
	@echo "already exists"
endif

build: clone gomalish.cpp
	rm -rf /root/.julia/compiled/v1.7/Gomalish
	cmake -S $(CURDIR) -B $(CURDIR)/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2" -DCMAKE_PREFIX_PATH=`julia --project=@. -e 'using CxxWrap; CxxWrap.prefix_path() |> print'`
	cmake --build $(CURDIR)/build --config Release -j $(NPROCS)

clean:
	rm -rf $(REPOSITORY)
	rm -rf build
	rm -f build.log

distclean:
	rm -rf $(REPOSITORY)
