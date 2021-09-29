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
    wrapped.method("get_row", &WrappedT::get_row);
    wrapped.method("get_col", &WrappedT::get_col);
  }
};

struct WrapMonolishCOO_float
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const char*>();
    wrapped.method("get_row", &WrappedT::get_row);
    wrapped.method("get_col", &WrappedT::get_col);
  }
};

struct WrapMonolishCRS_double
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<monolish::matrix::COO<double>>();
    wrapped.method("get_row", &WrappedT::get_row);
    wrapped.method("get_col", &WrappedT::get_col);
  }
};

struct WrapMonolishCRS_float
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<monolish::matrix::COO<float>>();
    wrapped.method("get_row", &WrappedT::get_row);
    wrapped.method("get_col", &WrappedT::get_col);
  }
};

template<typename T> struct IsMirroredType<monolish::matrix::COO<T>> : std::false_type { };
template<typename T> struct IsMirroredType<monolish::matrix::CRS<T>> : std::false_type { };

void wrap_matrix(Module &mod)
{
  mod.add_type<Parametric<TypeVar<1>>>("monolish_COO")
     .apply<monolish::matrix::COO<double>>(WrapMonolishCOO_double())
     .apply<monolish::matrix::COO<float>>(WrapMonolishCOO_float());

  mod.add_type<Parametric<TypeVar<1>>>("monolish_CRS")
     .apply<monolish::matrix::CRS<double>>(WrapMonolishCRS_double())
     .apply<monolish::matrix::CRS<float>>(WrapMonolishCRS_float());
}
