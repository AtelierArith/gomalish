module Gomalish

using Libdl
using Pkg.Artifacts

using CxxWrap

const libgomalish = joinpath(@__DIR__, "..", "deps", "build", "lib", "libgomalish.$(dlext)")
# const libgomalish = joinpath(artifact"libgomalish","libgomalish.$(Libdl.dlext)")
isfile(libgomalish) && @wrapmodule(libgomalish, :define_julia_module)

export mydot
function mydot(N, value::T) where T <: AbstractFloat
    v = vector{T}(N, value)
    dot(v, v)
end

export My
function My(N, value::Float64)
    v = MyVector{Float64}(N, value)
    dot(get_v(v), get_v(v))
end

function My(N, value::Float32)
    v = MyVector{Float32}(N, value)
    dot_float(get_v(v), get_v(v))
end


function __init__()
    @initcxx
end

end # module