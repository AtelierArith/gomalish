module Gomalish

using Libdl
using Pkg.Artifacts

using CxxWrap

# types
export vector, COO, CRS, Dense, tridiagonal_toeplitz_matrix
export CG, Jacobi, BiCGSTAB
# functions
export print_all
export get_row, get_col, get_nnz
export matvec, add, sub, axpy, xpay, nrm2
export set_create_precond, set_apply_precond, set_tol, set_maxiter, solve, solver_check

const libgomalish = joinpath(@__DIR__, "..", "deps", "build", "lib", "libgomalish.$(dlext)")
# const libgomalish = joinpath(artifact"libgomalish","libgomalish.$(Libdl.dlext)")
isfile(libgomalish) && @wrapmodule(libgomalish, :define_julia_module)

function __init__()
    @initcxx
end

function Base.show(io::IO, x::vector)
    print_all(x)
end

end # module