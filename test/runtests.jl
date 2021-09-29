using Gomalish
using CxxWrap
using Test

@testset "dot Float64" begin
    stdv1 = StdVector(Float64[1,2,3])
    stdv2 = StdVector(Float64[-1,-2,-3])
    mv1 = Gomalish.monolish_vector{Float64}(stdv1)
    mv2 = Gomalish.monolish_vector{Float64}(stdv2)
    @test Gomalish.dot(mv1, mv2) ≈ -Float64(14)
end

@testset "dot Float32" begin
    stdv1 = StdVector(Float32[1,2,3])
    stdv2 = StdVector(Float32[-1,-2,-3])
    mv1 = Gomalish.monolish_vector{Float32}(stdv1)
    mv2 = Gomalish.monolish_vector{Float32}(stdv2)
    @test Gomalish.dot(mv1, mv2) ≈ -Float32(14)
end