module Gomalish

using Libdl
using Pkg.Artifacts

using CxxWrap

const libgomalish = joinpath(@__DIR__, "..", "deps", "build", "lib", "libgomalish.$(dlext)")
# const libgomalish = joinpath(artifact"libgomalish","libgomalish.$(Libdl.dlext)")
isfile(libgomalish) && @wrapmodule(libgomalish, :define_julia_module)

export do_something, norm
function do_something(N, value::T) where T <: AbstractFloat
    v = vector{T}(N, value)
    dot(v, v)
end

function norm(N, value::Float64)
    v = vector{Float64}(N, value)
    dot_f64(get_v(v), get_v(v))
end

function norm(N, value::Float32)
    v = vector{Float32}(N, value)
    dot_f32(get_v(v), get_v(v))
end


function __init__()
    @initcxx
end

end # module