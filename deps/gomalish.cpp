#include <jlcxx/jlcxx.hpp>

#include "wrap_module.hpp"

using namespace jlcxx;

JLCXX_MODULE define_julia_module(Module &mod)
{
  wrap_vector(mod);
  //wrap_matrix(mod);
}
