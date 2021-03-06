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

template<typename PRECOND>
struct WrapMonolishBiCGSTAB
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
    wrapped.method("set_maxiter", &WrappedT::set_maxiter);
    wrapped.method("set_tol", &WrappedT::set_tol);
    wrapped.method("solve", &WrappedT::solve);
    wrapped.method(
      "set_create_precond", 
      [](WrappedT &w, PRECOND &p){w.set_create_precond(p);}
    );
    wrapped.method(
      "set_apply_precond", 
      [](WrappedT &w, PRECOND &p){w.set_apply_precond(p);}
    );
    wrapped.method("create_precond", &WrappedT::create_precond);
    wrapped.method("apply_precond", &WrappedT::apply_precond);
    wrapped.method("name", &WrappedT::name);
  }
};

template<typename MATRIX, typename Float, typename PRECOND>
struct WrapMonolishLU
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
    wrapped.method("set_maxiter", &WrappedT::set_maxiter);
    wrapped.method("set_tol", &WrappedT::set_tol);
    wrapped.method("solve", [](WrappedT &w, MATRIX &A, monolish::vector<Float> &x, monolish::vector<Float> &b){return w.solve(A, x, b);});
    wrapped.method("solve", [](WrappedT &w, MATRIX &A, monolish::vector<Float> &xb){return w.solve(A, xb);});

    wrapped.method(
      "set_create_precond", 
      [](WrappedT &w, PRECOND &p){w.set_create_precond(p);}
    );
    wrapped.method(
      "set_apply_precond", 
      [](WrappedT &w, PRECOND &p){w.set_apply_precond(p);}
    );
    wrapped.method("create_precond", &WrappedT::create_precond);
    wrapped.method("apply_precond", &WrappedT::apply_precond);
    wrapped.method("name", &WrappedT::name);
  }
};

struct WrapMonolishJacobi
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
    wrapped.method("solve", &WrappedT::solve);
    wrapped.method("create_precond", &WrappedT::create_precond);
    wrapped.method("apply_precond", &WrappedT::apply_precond);
    wrapped.method("name", &WrappedT::name);
  }
};

struct WrapMonolishnone
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<>();
  }
};

template<typename T1, typename T2> struct IsMirroredType<monolish::equation::CG<T1, T2>> : std::false_type { };
template<typename T1, typename T2> struct IsMirroredType<monolish::equation::BiCGSTAB<T1, T2>> : std::false_type { };
template<typename T1, typename T2> struct IsMirroredType<monolish::equation::LU<T1, T2>> : std::false_type { };
template<typename T1, typename T2> struct IsMirroredType<monolish::equation::Jacobi<T1, T2>> : std::false_type { };
template<typename T1, typename T2> struct IsMirroredType<monolish::equation::none<T1, T2>> : std::false_type { };

void wrap_equation(Module &mod){
  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("Jacobi")
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<double>, double>>(WrapMonolishJacobi())
     .apply<monolish::equation::Jacobi<monolish::matrix::CRS<float>, float>>(WrapMonolishJacobi());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("none")
     .apply<monolish::equation::none<monolish::matrix::Dense<double>, double>>(WrapMonolishnone())
     .apply<monolish::equation::none<monolish::matrix::Dense<float>, float>>(WrapMonolishnone());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("CG")
     .apply<monolish::equation::CG<monolish::matrix::CRS<double>, double>>(WrapMonolishCG<monolish::equation::Jacobi<monolish::matrix::CRS<double>, double>>())
     .apply<monolish::equation::CG<monolish::matrix::CRS<float>, float>>(WrapMonolishCG<monolish::equation::Jacobi<monolish::matrix::CRS<float>, float>>());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("BiCGSTAB")
     .apply<monolish::equation::BiCGSTAB<monolish::matrix::Dense<double>, double>>(WrapMonolishBiCGSTAB<monolish::equation::none<monolish::matrix::Dense<double>, double>>())
     .apply<monolish::equation::BiCGSTAB<monolish::matrix::Dense<float>, float>>(WrapMonolishBiCGSTAB<monolish::equation::none<monolish::matrix::Dense<float>, float>>());

  mod.add_type<Parametric<TypeVar<1>, TypeVar<2>>>("LU")
     .apply<monolish::equation::LU<monolish::matrix::Dense<double>, double>>(WrapMonolishLU<monolish::matrix::Dense<double>, double, monolish::equation::none<monolish::matrix::Dense<double>, double>>())
     .apply<monolish::equation::LU<monolish::matrix::Dense<float>, float>>(WrapMonolishLU<monolish::matrix::Dense<float>, float, monolish::equation::none<monolish::matrix::Dense<float>, float>>());

}