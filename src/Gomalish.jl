module Gomalish

using Libdl
using Pkg.Artifacts

using CxxWrap

const libgomalish = joinpath(@__DIR__, "..", "deps", "build", "lib", "libgomalish.$(dlext)")
# const libgomalish = joinpath(artifact"libgomalish","libgomalish.$(Libdl.dlext)")
isfile(libgomalish) && @wrapmodule(libgomalish, :define_julia_module)

function __init__()
    @initcxx
end

end # module