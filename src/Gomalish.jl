module Gomalish

using Libdl
using Pkg.Artifacts

using CxxWrap

const libgomalish = joinpath(@__DIR__, "..", "deps", "build", "lib", "libgomalish.$(dlext)")
# const libgomalish = joinpath(artifact"libgomalish","libgomalish.$(Libdl.dlext)")
isfile(libgomalish) && @wrapmodule(libgomalish, :define_julia_module)

export do_something

for bit in [32, 64]
    T = Symbol("Float", bit)
    f = Symbol("dot_f", bit)
    @eval function do_something(N, min::$(T), max::$(T))
        v = gomalish_vector{$(T)}(N, min, max)
        $(f)(val(v), val(v))
    end
end

for bit in [32, 64]
    T = Symbol("Float", bit)
    f = Symbol("dot_f", bit)
    @eval function dot(a::monolish_vector{$T}, b::monolish_vector{$T})
        $(f)(a, b)
    end
end

function __init__()
    @initcxx
end

end # module