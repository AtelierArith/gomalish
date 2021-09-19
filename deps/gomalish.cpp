#include <vector>

#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;

double monolish_dot(monolish::vector<double> x, monolish::vector<double> y)
{
  return monolish::blas::dot(x, y);
}

JLCXX_MODULE define_julia_module(Module &mod)
{
  mod.add_type<monolish::vector<double>>("vector").constructor<const size_t, double, double>();
  mod.method("dot", monolish_dot);
}
