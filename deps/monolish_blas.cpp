#include<vector>

#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;

void wrap_blas(Module &mod){
  mod.method("dot", [](const monolish::vector<double> &x, const monolish::vector<double> &y){return monolish::blas::dot(x, y);});
  mod.method("dot", [](const monolish::vector<float> &x, const monolish::vector<float> &y){return monolish::blas::dot(x, y);});
}