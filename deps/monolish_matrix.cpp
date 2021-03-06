#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;

template<typename Float>
struct WrapMonolishCOO
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const char*>();
    wrapped.method("get_row", &WrappedT::get_row);
    wrapped.method("get_col", &WrappedT::get_col);
    wrapped.method("get_nnz", &WrappedT::get_nnz);
    wrapped.method("print_all", [](WrappedT &w){w.print_all(false);});
    wrapped.method("print_all", [](WrappedT &w, bool force_cpu){w.print_all(force_cpu);});
    wrapped.method("print_all", [](WrappedT &w, std::string filename){w.print_all(filename);});
  }
};

template<typename Float>
struct WrapMonolishCRS
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<monolish::matrix::COO<Float>>();
    wrapped.method("get_row", &WrappedT::get_row);
    wrapped.method("get_col", &WrappedT::get_col);
    wrapped.method("get_nnz", &WrappedT::get_nnz);
    wrapped.method("print_all", [](WrappedT &w){w.print_all(false);});
    wrapped.method("print_all", [](WrappedT &w, bool force_cpu){w.print_all(force_cpu);});
  }
};

template<typename Float>
struct WrapMonolishDense
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<monolish::matrix::COO<Float>>();
    wrapped.method("get_row", &WrappedT::get_row);
    wrapped.method("get_col", &WrappedT::get_col);
    wrapped.method("get_nnz", &WrappedT::get_nnz);
    wrapped.method("print_all", [](WrappedT &w){w.print_all(false);});
    wrapped.method("print_all", [](WrappedT &w, bool force_cpu){w.print_all(force_cpu);});
  }
};
template<typename T> struct IsMirroredType<monolish::matrix::COO<T>> : std::false_type { };
template<typename T> struct IsMirroredType<monolish::matrix::CRS<T>> : std::false_type { };
template<typename T> struct IsMirroredType<monolish::matrix::Dense<T>> : std::false_type { };

void wrap_matrix(Module &mod)
{
  mod.add_type<Parametric<TypeVar<1>>>("COO")
     .apply<monolish::matrix::COO<double>>(WrapMonolishCOO<double>())
     .apply<monolish::matrix::COO<float>>(WrapMonolishCOO<float>());

  mod.add_type<Parametric<TypeVar<1>>>("CRS")
     .apply<monolish::matrix::CRS<double>>(WrapMonolishCRS<double>())
     .apply<monolish::matrix::CRS<float>>(WrapMonolishCRS<float>());
  
  mod.add_type<Parametric<TypeVar<1>>>("Dense")
     .apply<monolish::matrix::Dense<double>>(WrapMonolishDense<double>())
     .apply<monolish::matrix::Dense<float>>(WrapMonolishDense<float>());
}
