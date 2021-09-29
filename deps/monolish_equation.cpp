#include <jlcxx/jlcxx.hpp>

#include <monolish_equation.hpp>

using namespace jlcxx;

struct WrapMonolishCG_double
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
  }
};

struct WrapMonolishCG_float
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
  }
};

struct WrapMonolishJacobi_double
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
  }
};

struct WrapMonolishJacobi_float
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
  }
};

template<typename T> struct IsMirroredType<monolish::equation::CG<monolish::matrix::CRS<T>, T>> : std::false_type { };

void wrap_equation(Module &mod){
  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("monolish_CG")
     .apply<monolish::equation::CG<monolish::matrix::CRS<double>, double>>(WrapMonolishCG_float())
     .apply<monolish::equation::CG<monolish::matrix::CRS<float>, float>>(WrapMonolishCG_float());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("monolish_Jacobi")
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<double>, double>>(WrapMonolishJacobi_double())
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<float>, double>>(WrapMonolishJacobi_float());
}