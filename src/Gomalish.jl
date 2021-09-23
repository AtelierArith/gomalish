module Gomalish

using Libdl
using Pkg.Artifacts

using CxxWrap

const libgomalish = joinpath(@__DIR__, "..", "deps", "build", "lib", "libgomalish.$(dlext)")
# const libgomalish = joinpath(artifact"libgomalish","libgomalish.$(Libdl.dlext)")
isfile(libgomalish) && @wrapmodule(libgomalish, :define_julia_module)

export do_something, norm
function do_something(N, _min::Float64, _max::Float64)
    v = gomalish_vector{Float64}(N, _min, _max)
    dot_f64(val(v), val(v))
end

function do_something(N, _min::Float32, _max::Float32)
    v = gomalish_vector{Float32}(N, _min, _max)
    dot_f64(val(v), val(v))
end

function norm(N, value::Float64)
    v = vector{Float64}(N, value)
    dot_f64(v, v)
end

function norm(N, value::Float32)
    v = vector{Float32}(N, value)
    dot_f32(v, v)
end


function __init__()
    @initcxx
end

end # module