#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;

void wrap_blas(Module &mod){
  mod.method("dot", [](const monolish::vector<double> &x, const monolish::vector<double> &y){return monolish::blas::dot(x, y);});
  mod.method("dot", [](const monolish::vector<float> &x, const monolish::vector<float> &y){return monolish::blas::dot(x, y);});
  mod.method("monolish_copy", [](const monolish::vector<float> &x, monolish::vector<float> &y){monolish::blas::copy(x, y);});
  mod.method("monolish_copy", [](const monolish::vector<double> &x, monolish::vector<double> &y){monolish::blas::copy(x, y);});
  mod.method("axpy", [](const float alpha, const monolish::vector<float> &x, monolish::vector<float> &y){return monolish::blas::axpy(alpha, x, y);});
  mod.method("axpy", [](const double alpha, const monolish::vector<double> &x, monolish::vector<double> &y){return monolish::blas::axpy(alpha, x, y);});
  mod.method("xpay", [](const float beta, const monolish::vector<float> &x, monolish::vector<float> &y){return monolish::blas::xpay(beta, x, y);});
  mod.method("xpay", [](const double beta, const monolish::vector<double> &x, monolish::vector<double> &y){return monolish::blas::xpay(beta, x, y);});
  mod.method("nrm2", [](const monolish::vector<float> &x){return monolish::blas::nrm2(x);});
  mod.method("nrm2", [](const monolish::vector<double> &x){return monolish::blas::nrm2(x);});
  mod.method("matvec", [](const monolish::matrix::CRS<double> &A, const monolish::vector<double> &x, monolish::vector<double> &y){monolish::blas::matvec(A,x,y);});
  mod.method("matvec", [](const monolish::matrix::CRS<float> &A, const monolish::vector<float> &x, monolish::vector<float> &y){monolish::blas::matvec(A,x,y);});
}