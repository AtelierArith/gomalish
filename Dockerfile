FROM ghcr.io/ricosjp/monolish/oss:0.15.2

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

# Install Julia via jill.sh
# https://github.com/abelsiqueira/jill
RUN wget https://raw.githubusercontent.com/abelsiqueira/jill/main/jill.sh && \
    /bin/bash jill.sh --version 1.7.1 --yes && \
    rm jill.sh

# Install basic packages on default environment
RUN julia -e 'using Pkg; Pkg.add("Revise")'

WORKDIR /work
ENV JULIA_PROJECT=/work

COPY Project.toml /work/
RUN mkdir /work/src/ && echo "module Gomalish; end">> /work/src/Gomalish.jl

RUN julia -e 'using Pkg; Pkg.instantiate(); Pkg.precompile()'
