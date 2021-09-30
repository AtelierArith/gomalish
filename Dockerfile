FROM ghcr.io/ricosjp/monolish/oss:latest

ENV JULIA_PATH /usr/local/julia
ENV PATH $JULIA_PATH/bin:$PATH

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    ca-certificates \
    curl \
    nano \
    htop \
    git \
    wget \
    && \
    apt-get clean && rm -rf /var/cache/apt/archives/* /var/lib/apt/lists/* # clean up

# Install Julia
RUN wget https://julialang-s3.julialang.org/bin/linux/x64/1.6/julia-1.6.2-linux-x86_64.tar.gz && \
    mkdir "$JULIA_PATH" && \
    tar zxvf julia-1.6.2-linux-x86_64.tar.gz -C "$JULIA_PATH" --strip-components 1 && \
    rm julia-1.6.2-linux-x86_64.tar.gz # clean up

# Install basic packages on default environment
RUN julia -e 'using Pkg; Pkg.add("Revise")'

WORKDIR /work
ENV JULIA_PROJECT=/work

COPY Project.toml /work/
RUN mkdir /work/src/ && echo "module Gomalish; end">> /work/src/Gomalish.jl

RUN julia -e 'using Pkg; Pkg.instantiate(); Pkg.precompile()'