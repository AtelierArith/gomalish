#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;

struct WrapMonolishCOO_double
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const char*>();
  }
};

struct WrapMonolishCOO_float
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const char*>();
  }
};

template<typename T> struct IsMirroredType<monolish::matrix::COO<T>> : std::false_type { };

void wrap_matrix(Module &mod)
{
  mod.add_type<Parametric<TypeVar<1>>>("monolish_COO")
     .apply<monolish::matrix::COO<double>>(WrapMonolishCOO_double())
     .apply<monolish::matrix::COO<float>>(WrapMonolishCOO_float());
}
