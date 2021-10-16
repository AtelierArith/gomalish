#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;

void wrap_blas(Module &mod){
  mod.method("dot", [](const monolish::vector<double> &x, const monolish::vector<double> &y){return monolish::blas::dot(x, y);});
  mod.method("dot", [](const monolish::vector<float> &x, const monolish::vector<float> &y){return monolish::blas::dot(x, y);});
  mod.method("monolish_copy", [](const monolish::vector<float> &x, monolish::vector<float> &y){monolish::blas::copy(x, y);});
  mod.method("monolish_copy", [](const monolish::vector<double> &x, monolish::vector<double> &y){monolish::blas::copy(x, y);});
  mod.method("matvec", [](const monolish::matrix::CRS<double> &A, const monolish::vector<double> &x, monolish::vector<double> &y){monolish::blas::matvec(A,x,y);});
  mod.method("matvec", [](const monolish::matrix::CRS<float> &A, const monolish::vector<float> &x, monolish::vector<float> &y){monolish::blas::matvec(A,x,y);});
}