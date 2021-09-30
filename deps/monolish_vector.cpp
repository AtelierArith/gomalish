#include <vector>

#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;

template<typename T>
T monolish_blas_dot(monolish::vector<T> x, monolish::vector<T> y)
{
  return monolish::blas::dot(x, y);
}

struct WrapMonolishVector_double
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const size_t>();
    wrapped.template constructor<const size_t, const double>();
    wrapped.template constructor<const size_t, const double, const double>();
    wrapped.template constructor<const std::vector<double>&>();
    wrapped.method("print_all", [](WrappedT &w, bool force_cpu=false){w.print_all(force_cpu);});
    wrapped.method("print_all", [](WrappedT &w, std::string filename){w.print_all(filename);});
  }
};

struct WrapMonolishVector_float
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const size_t>();
    wrapped.template constructor<const size_t, const float>();
    wrapped.template constructor<const size_t, const float, const float>();
    wrapped.template constructor<const std::vector<float>&>();
    wrapped.method("print_all", [](WrappedT &w, bool force_cpu=false){w.print_all(force_cpu);});
    wrapped.method("print_all", [](WrappedT &w, std::string filename){w.print_all(filename);});
  }
};

template<typename T>
struct gomalish_vector
{
  typedef T type_value;
  gomalish_vector(const size_t N): v(monolish::vector<T>(N)){}
  gomalish_vector(const size_t N, const T value): v(monolish::vector<T>(N, value)){}
  gomalish_vector(const size_t N, const T min, const T max): v(monolish::vector<T>(N, min, max)){}
  monolish::vector<T> v;
  monolish::vector<T> val(){return v;}
};
  
struct WrapGomalishVector{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped){
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const size_t>();
    wrapped.template constructor<const size_t, const typename WrappedT::type_value>();
    wrapped.template constructor<const size_t, const typename WrappedT::type_value, const typename WrappedT::type_value>();
    wrapped.method("val", &WrappedT::val);
  }
};

template<typename T1> struct IsMirroredType<gomalish_vector<T1>> : std::false_type { };
template<typename T1> struct IsMirroredType<monolish::vector<T1>> : std::false_type { };

void wrap_vector(Module &mod)
{

  mod.add_type<Parametric<TypeVar<1>>>("monolish_vector")
     .apply<monolish::vector<double>>(WrapMonolishVector_double())
     .apply<monolish::vector<float>>(WrapMonolishVector_float());

  mod.add_type<Parametric<TypeVar<1>>>("gomalish_vector")
     .apply<gomalish_vector<double>, gomalish_vector<float>>(WrapGomalishVector());

  mod.method("dot_f64", &monolish_blas_dot<double>);
  mod.method("dot_f32", &monolish_blas_dot<float>);
}
