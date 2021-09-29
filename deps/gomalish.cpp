#include <jlcxx/jlcxx.hpp>

#include "monolish_vector.hpp"
#include "monolish_matrix.hpp"

using namespace jlcxx;

JLCXX_MODULE define_julia_module(Module &mod)
{
  wrap_vector(mod);
  wrap_matrix(mod);
}