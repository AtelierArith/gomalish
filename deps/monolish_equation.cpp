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
    wrapped.method("set_maxiter", &WrappedT::set_maxiter);
    wrapped.method("set_tol", &WrappedT::set_tol);
    wrapped.method(
      "set_create_precond", 
      [](WrappedT& w, monolish::equation::Jacobi<monolish::matrix::CRS<double>, double> &p){w.set_create_precond(p);}
    );
    wrapped.method(
      "set_apply_precond", 
      [](WrappedT& w, monolish::equation::Jacobi<monolish::matrix::CRS<double>, double> &p){w.set_apply_precond(p);}
    );
    wrapped.method("solve", &WrappedT::solve);
  }
};

struct WrapMonolishCG_float
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
    wrapped.method("set_maxiter", &WrappedT::set_maxiter);
    wrapped.method("set_tol", &WrappedT::set_tol);
    wrapped.method(
      "set_create_precond", 
      [](WrappedT& w, monolish::equation::Jacobi<monolish::matrix::CRS<float>, float> p){w.set_create_precond(p);}
    );
    wrapped.method(
      "set_apply_precond", 
      [](WrappedT& w, monolish::equation::Jacobi<monolish::matrix::CRS<float>, float> p){w.set_apply_precond(p);}
    );
    wrapped.method("solve", &WrappedT::solve);
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

template<typename T1, typename T2> struct IsMirroredType<monolish::equation::CG<T1, T2>> : std::false_type { };
template<typename T1, typename T2> struct IsMirroredType<monolish::equation::Jacobi<T1, T2>> : std::false_type { };

void wrap_equation(Module &mod){
  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("monolish_Jacobi")
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<double>, double>>(WrapMonolishJacobi_double())
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<float>, float>>(WrapMonolishJacobi_float());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("monolish_CG")
     .apply<monolish::equation::CG<monolish::matrix::CRS<double>, double>>(WrapMonolishCG_double())
     .apply<monolish::equation::CG<monolish::matrix::CRS<float>, float>>(WrapMonolishCG_float());

}