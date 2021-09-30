#include<jlcxx/jlcxx.hpp>
#include<common/monolish_common.hpp>

using namespace jlcxx;

void wrap_util(Module &mod){
  mod.method("solver_check", &monolish::util::solver_check);
  mod.method("tridiagonal_toeplitz_matrix", &monolish::util::tridiagonal_toeplitz_matrix<double>);
  mod.method("tridiagonal_toeplitz_matrix", &monolish::util::tridiagonal_toeplitz_matrix<float>);
}