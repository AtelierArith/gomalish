#include <jlcxx/jlcxx.hpp>

#include <monolish_equation.hpp>

using namespace jlcxx;

template<typename PRECOND>
struct WrapMonolishCG
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
      [](WrappedT &w, PRECOND &p){w.set_create_precond(p);}
    );
    wrapped.method(
      "set_apply_precond", 
      [](WrappedT &w, PRECOND &p){w.set_apply_precond(p);}
    );
    wrapped.method("solve", &WrappedT::solve);
  }
};

struct WrapMonolishJacobi
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
  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("Jacobi")
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<double>, double>>(WrapMonolishJacobi())
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<float>, float>>(WrapMonolishJacobi());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("CG")
     .apply<monolish::equation::CG<monolish::matrix::CRS<double>, double>>(WrapMonolishCG<monolish::equation::Jacobi<monolish::matrix::CRS<double>, double>>())
     .apply<monolish::equation::CG<monolish::matrix::CRS<float>, float>>(WrapMonolishCG<monolish::equation::Jacobi<monolish::matrix::CRS<float>, float>>());

}