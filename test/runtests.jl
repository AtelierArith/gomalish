using Gomalish
using CxxWrap
using Test

@testset "dot Float64" begin
    stdv1 = StdVector(Float64[1,2,3])
    stdv2 = StdVector(Float64[-1,-2,-3])
    mv1 = Gomalish.monolish_vector{Float64}(stdv1)
    mv2 = Gomalish.monolish_vector{Float64}(stdv2)
    Gomalish.print_all(mv1, false)
    Gomalish.print_all(mv2, false)
    @test Gomalish.dot(mv1, mv2) ≈ -Float64(14)
end

@testset "dot Float32" begin
    stdv1 = StdVector(Float32[1,2,3])
    stdv2 = StdVector(Float32[-1,-2,-3])
    mv1 = Gomalish.monolish_vector{Float32}(stdv1)
    mv2 = Gomalish.monolish_vector{Float32}(stdv2)
    Gomalish.print_all(mv1, false)
    Gomalish.print_all(mv2, false)
    @test Gomalish.dot(mv1, mv2) ≈ -Float32(14)
end

@testset "solver" begin
    A_COO = Gomalish.monolish_COO{Float64}("../playground/cpp/sample.mtx")
    A = Gomalish.monolish_CRS{Float64}(A_COO)
    x = Gomalish.monolish_vector{Float64}(Gomalish.get_row(A), 1., 2.)
    b = Gomalish.monolish_vector{Float64}(Gomalish.get_row(A), 1., 2.)
    x = 1 .+ rand(Gomalish.get_row(A))
    jl_b = 1 .+ rand(Gomalish.get_row(A))
    x = Gomalish.monolish_vector{Float64}(StdVector(x))
    b = Gomalish.monolish_vector{Float64}(StdVector(jl_b))

    solver = Gomalish.monolish_CG{Gomalish.monolish_CRS{Float64},Float64}()
    precond = Gomalish.monolish_Jacobi{Gomalish.monolish_CRS{Float64},Float64}()
    Gomalish.set_create_precond(solver, CxxRef(precond))
    Gomalish.set_apply_precond(solver, CxxRef(precond))
    Gomalish.set_tol(solver, 1.0e-12)
    Gomalish.set_maxiter(solver, Gomalish.get_row(A))
    Gomalish.print_all(A, false)
    println("---")
    Gomalish.print_all(x, false)
    println("---")
    Gomalish.print_all(b, false)

    @show Gomalish.solve(solver, A, x, b)
    jl_A = Float64[
        2 -1 0
        -1 2 -1
         0 -1 2
    ]
    println("Result by Gomalish/monolish")
    Gomalish.print_all(x, false)
    println("Result by Julia")
    println(jl_A \ jl_b)
end