module Gomalish

using Libdl
using Pkg.Artifacts

using CxxWrap

const libgomalish = joinpath(@__DIR__, "..", "deps", "build", "lib", "libgomalish.$(dlext)")
# const libgomalish = joinpath(artifact"libgomalish","libgomalish.$(Libdl.dlext)")
isfile(libgomalish) && @wrapmodule(libgomalish, :define_julia_module)

function do_something(N::Int)
    v = vector(N, 1., 2.)
    dot(v, v)
end

function mydot(N, value::AbstractFloat)
    v = vector(N, value)
    dot(v, v)
end

function __init__()
    @initcxx
end

end # module