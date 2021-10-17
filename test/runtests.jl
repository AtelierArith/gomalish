using Gomalish
using CxxWrap
using Test
using Random

for T in [Float64, Float32]
    @testset "dot $T" begin
        stdv1 = StdVector(T[1,2,3])
        stdv2 = StdVector(T[-1,-2,-3])
        mv1 = vector{T}(stdv1)
        mv2 = vector{T}(stdv2)
        print_all(mv1)
        print_all(mv2)
        @test Gomalish.dot(mv1, mv2) ≈ -T(14)
        @test mv1[1] ≈ stdv1[1]
        @test mv1[2] ≈ stdv1[2]
        @test mv1[3] ≈ stdv1[3]
    end
end

for T in [Float64, Float32]
    Random.seed!(12345)
    @testset "cg $T" begin
        coo = COO{T}("matrixfiles/sample.mtx")
        print_all(coo)
        A = CRS{T}(coo)
        jl_x = one(T) .+ rand(T, get_row(A))
        jl_b = one(T) .+ rand(T, get_row(A))
        x = vector{T}(StdVector(jl_x))
        b = vector{T}(StdVector(jl_b))

        solver = CG{CRS{T},T}()
        precond = Jacobi{CRS{T},T}()
        set_create_precond(solver, precond)
        set_apply_precond(solver, precond)
        set_tol(solver, 1.0e-12)
        set_maxiter(solver, get_row(A))
        print_all(A)
        println("---")
        print_all(x)
        println("---")
        print_all(b)

        if solver_check(solve(solver, A, x, b))
            return
        end
        jl_A = T[
            2 -1 0
            -1 2 -1
            0 -1 2
        ]
        println("Result by Gomalish/monolish")
        print_all(x)
        println("Result by Julia")
        jl_x = jl_A \ jl_b
        println(jl_x)
        @test x[1] ≈ jl_x[1]
        @test x[2] ≈ jl_x[2]
        @test x[3] ≈ jl_x[3]
    end
end
        
for T in [Float64, Float32]
    @testset "cg-impl $T" begin
        DIM = 100
    coo = tridiagonal_toeplitz_matrix(DIM, T(11.0), T(-1.0));
        A = CRS{T}(coo);

        println("===== Matrix informatrion =====")
        println("# of rows : ", get_row(A))
        println("# of cols : ", get_col(A))
        println("# of nnz  : ", get_nnz(A))

        # initial x is rand(0~1)
        x = vector{T}(get_row(A), T(0.0), T(1.0))
        # initial b is {1, 1, 1, ...,1}
        b = vector{T}(get_row(A), T(1.0))
        tol::T = 1.0e-12

        r = vector{T}(get_row(A), T(0.0))
        p = vector{T}(get_row(A), T(0.0))
        q = vector{T}(get_row(A), T(0.0))
        
        matvec(A, x, q)
        sub(b, q, r)
        Gomalish.copy(r, p)

        for iter in 1:get_row(A)
            matvec(A, p, q)
            tmp = Gomalish.dot(r, r)
            α = tmp / Gomalish.dot(p, q);
            axpy(α, p, x)
            axpy(-α, q, r)
            β = Gomalish.dot(r, r) / tmp
            xpay(β, r, p)
            resid = nrm2(r);
            println(iter + 1)
            @show resid
            (resid < tol) && return
            isnan(resid) && return
        end
    end
end

for T in [Float64, Float32]
    @testset "template solver $T" begin
        Random.seed!(12345)
        coo = COO{T}("matrixfiles/sample.mtx")
        A = CRS{T}(coo)
        jl_x = one(T) .+ rand(T, get_row(A))
        jl_b = one(T) .+ rand(T, get_row(A))
        x = vector{T}(StdVector(jl_x))
        b = vector{T}(StdVector(jl_b))
        solver = CG{CRS{T},T}()
        precond = Jacobi{CRS{T},T}()
        set_create_precond(solver, precond)
        set_apply_precond(solver, precond)
        set_tol(solver, 1.0e-12)
        set_maxiter(solver, get_row(A))
        if solver_check(solve(solver, A, x, b))
        return
        end
        print_all(x)
        jl_A = T[
            2 -1 0
            -1 2 -1
            0 -1 2
        ]
        println("Result by Gomalish/monolish")
        print_all(x)
        println("Result by Julia")
        jl_x = jl_A \ jl_b
        println(jl_x)
        @test x[1] ≈ jl_x[1]
        @test x[2] ≈ jl_x[2]
        @test x[3] ≈ jl_x[3]
    end
end

for T in [Float64, Float32]
    @testset "template solver part2 $T" begin
        Random.seed!(12345)
        coo = COO{T}("matrixfiles/sample.mtx")
        A = Dense{T}(coo)
        jl_x = one(T) .+ rand(T, get_row(A))
        jl_b = one(T) .+ rand(T, get_row(A))
        x = vector{T}(StdVector(jl_x))
        b = vector{T}(StdVector(jl_b))
        solver = BiCGSTAB{Dense{T},T}()
        precond = Gomalish.none{Dense{T},T}()
        set_create_precond(solver, precond)
        set_apply_precond(solver, precond)
        set_tol(solver, 1.0e-12)
        set_maxiter(solver, get_row(A))
        if solver_check(solve(solver, A, x, b))
        return
        end
        print_all(x)
        jl_A = T[
            2 -1 0
            -1 2 -1
            0 -1 2
        ]
        println("Result by Gomalish/monolish")
            print_all(x)
        println("Result by Julia")
        jl_x = jl_A \ jl_b
        println(jl_x)
        @test x[1] ≈ jl_x[1]
        @test x[2] ≈ jl_x[2]
        @test x[3] ≈ jl_x[3]
    end
end
        
for T in [Float64, Float32]
    @testset "template solver part3 $T" begin
        Random.seed!(12345)
        coo = COO{T}("matrixfiles/sample.mtx")
        A = Dense{T}(coo)
        jl_x = one(T) .+ rand(T, get_row(A))
        jl_b = one(T) .+ rand(T, get_row(A))
        x = vector{T}(StdVector(jl_x))
        b = vector{T}(StdVector(jl_b))
        solver = Gomalish.LU{Dense{T},T}()
        @test Gomalish.name(solver) == "monolish::equation::LU"
        precond = Gomalish.none{Dense{T},T}()
        set_create_precond(solver, precond)
        set_apply_precond(solver, precond)
        set_tol(solver, 1.0e-12)
        set_maxiter(solver, get_row(A))
        if solver_check(solve(solver, A, x, b))
            return
        end
        print_all(x)
        jl_A = T[
            2 -1 0
           -1 2 -1
            0 -1 2
        ]
        println("Result by Gomalish/monolish")
        print_all(x)
        println("Result by Julia")
        jl_x = jl_A \ jl_b
        println(jl_x)
        @test x[1] ≈ jl_x[1]
        @test x[2] ≈ jl_x[2]
        @test x[3] ≈ jl_x[3]
    end
end