using Gomalish
using CxxWrap
using Test

for T in [Float64, Float32]
    @testset "dot $T" begin
        stdv1 = StdVector(T[1,2,3])
        stdv2 = StdVector(T[-1,-2,-3])
        mv1 = Gomalish.vector{T}(stdv1)
        mv2 = Gomalish.vector{T}(stdv2)
        Gomalish.print_all(mv1, false)
        Gomalish.print_all(mv2, false)
        @test Gomalish.dot(mv1, mv2) ≈ -T(14)
    end
end

for T in [Float64, Float32]
    @testset "cg $T" begin
        A_COO = Gomalish.monolish_COO{T}("matrixfiles/sample.mtx")
        Gomalish.print_all(A_COO, false)
        A = Gomalish.monolish_CRS{T}(A_COO)
        x = Gomalish.vector{T}(Gomalish.get_row(A), T(1), T(2))
        b = Gomalish.vector{T}(Gomalish.get_row(A), T(1), T(2))
        x = one(T) .+ rand(T, Gomalish.get_row(A))
        jl_b = one(T) .+ rand(T, Gomalish.get_row(A))
        x = Gomalish.vector{T}(StdVector(x))
        b = Gomalish.vector{T}(StdVector(jl_b))

        solver = Gomalish.monolish_CG{Gomalish.monolish_CRS{T},T}()
        precond = Gomalish.monolish_Jacobi{Gomalish.monolish_CRS{T},T}()
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
        jl_A = T[
            2 -1 0
            -1 2 -1
            0 -1 2
        ]
        println("Result by Gomalish/monolish")
        Gomalish.print_all(x, false)
        println("Result by Julia")
        println(jl_A \ jl_b)
    end
end

for T in [Float64, Float32]
    @testset "cg-impl $T" begin
        DIM = 100
        coo = Gomalish.tridiagonal_toeplitz_matrix(DIM, T(11.0), T(-1.0));
        A = Gomalish.monolish_CRS{T}(coo);

        println("===== Matrix informatrion =====")
        println("# of rows : ", Gomalish.get_row(A))
        println("# of cols : ", Gomalish.get_col(A))
        println("# of nnz  : ", Gomalish.get_nnz(A))

        # initial x is rand(0~1)
        x = Gomalish.vector{T}(Gomalish.get_row(A), T(0.0), T(1.0))
        # initial b is {1, 1, 1, ...,1}
        b = Gomalish.vector{T}(Gomalish.get_row(A), T(1.0))
        tol::T = 1.0e-12

        r = Gomalish.vector{T}(Gomalish.get_row(A), T(0.0))
        p = Gomalish.vector{T}(Gomalish.get_row(A), T(0.0))
        q = Gomalish.vector{T}(Gomalish.get_row(A), T(0.0))
        
        Gomalish.matvec(A, x, q)
        Gomalish.sub(b, q, r)
        Gomalish.copy(r, p)

        for iter in 1:Gomalish.get_row(A)
            Gomalish.matvec(A, p, q)
            tmp = Gomalish.dot(r, r)
            α = tmp / Gomalish.dot(p, q);
            Gomalish.axpy(α, p, x)
            Gomalish.axpy(-α, q, r)
            β = Gomalish.dot(r, r) / tmp
            Gomalish.xpay(β, r, p)
            resid = Gomalish.nrm2(r);
            println(iter + 1)
            @show resid
            (resid < tol) && return
            isnan(resid) && return
        end
    end
end
