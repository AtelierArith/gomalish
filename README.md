# gomalish(Gomalish.jl)

- Unofficial [JuliaLang](https://julialang.org/) interface of MONOlithic LInear equation Solvers for Highly-parallel architecture a.k.a [monolish](https://github.com/ricosjp/monolish) with [CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl)

# Usage

## TL;DR (今北産業)

```console
$ git clone https://github.com/AtelierArith/gomalish && cd gomalish
$ make # to build Docker image
$ docker-compose run --rm julia julia -e 'using Pkg; Pkg.build(); Pkg.test()'
```

# Developer workflow basics

- Let's clone this repository via:

```console
$ git clone https://github.com/AtelierArith/gomalish
$ cd gomalish
```

- Execute `make` command to build an Docker image from `Dockerfile` we've prepared.

```console
$ make
```

- Open a Docker container via:

```console
$ docker-compose run --rm julia bash
root@gomagoma99:/work#
```

In the following, we will assume we are living in the docker container with prompt `root@gomagoma99:/work#`. It is a good idea to view our code on VSCode with [Visual Studio Code Remote - Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers).

- To build a shared library `libgomalish.so`, cd `deps` directory and execute `make`.

```console
root@gomagoma99:/work# cd deps
root@gomagoma99:/work/deps# make
```

You'll find `work/deps/build/lib/libgomalish.so`. Our repository gomalish provides C++ codes that wrap monolish API. See `deps/monolish_<xxxx>.cpp` and `deps/monoish_module.hpp` to learn more. Your contribution is welcome. If you modified these C++ codes, please re-run `make -C /work/deps` again.

- Let's call monolish API from Julia! Lots of examples are stored in `/work/tests/runtests.jl`. The following command will run the tests for our package `Gomalish.jl`.

```console
root@gomagoma99:/work# julia -e 'using Pkg; Pkg.test()'
```

However, it is recommended to run tests on [Pkg mode](https://docs.julialang.org/en/v1/stdlib/Pkg/#Pkg):

```console
root@gomagoma99:/work# julia
               _
   _       _ _(_)_     |  Documentation: https://docs.julialang.org
  (_)     | (_) (_)    |
   _ _   _| |_  __ _   |  Type "?" for help, "]?" for Pkg help.
  | | | | | | |/ _` |  |
  | | |_| | | | (_| |  |  Version 1.6.3 (2021-09-23)
 _/ |\__'_|_|_|\__'_|  |  Official https://julialang.org/ release
|__/                   |

julia> # press ] key
(Gomalish) pkg> # This is the Pkg REPL. Let's enter `test` to run tests
(Gomalish) pkg> test
# some staff happens ...
```

Congrats! You have a complete understanding of Gomalish.jl.

# What's next?

To move on to the next step, we recommend to take a look at these materials:

- https://barche.github.io/cxxwrap-juliacon2020/#/
  - [JuliaCon 2020 | Julia and C++: a technical overview of CxxWrap.jl | Bart Janssens](https://www.youtube.com/watch?v=u7IaXwKSUU0)
- https://github.com/JuliaInterop/libcxxwrap-julia
  - especially [examples](https://github.com/JuliaInterop/libcxxwrap-julia/tree/master/examples) directory
- https://github.com/JuliaInterop/CxxWrap.jl
- https://github.com/ricosjp/monolish
