#include <vector>

#include <jlcxx/jlcxx.hpp>
#include <monolish_blas.hpp>

using namespace jlcxx;


double monolish_dot_double(monolish::vector<double> x, monolish::vector<double> y)
{
  return monolish::blas::dot(x, y);
}

float monolish_dot_float(monolish::vector<float> x, monolish::vector<float> y)
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
  }
};

template<typename T>
struct gomalish_vector
{
  typedef T type_value;
  gomalish_vector(const size_t N): v(monolish::vector<T>(N)){}
  gomalish_vector(const size_t N, const T value): v(monolish::vector<T>(N, value)){}
  gomalish_vector(const size_t N, const T value1, const T value2): v(monolish::vector<T>(N, value1, value2)){}
  monolish::vector<T> v;
  monolish::vector<T> get_v(){return v;}
};
  
struct WrapGomalishVector{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped){
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const size_t>();
    wrapped.template constructor<const size_t, const typename WrappedT::type_value>();
    wrapped.template constructor<const size_t, const typename WrappedT::type_value, const typename WrappedT::type_value>();
    wrapped.method("get_v", &WrappedT::get_v);
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
  }
};

template<typename T1> struct IsMirroredType<gomalish_vector<T1>> : std::false_type { };
template<typename T1> struct IsMirroredType<monolish::vector<T1>> : std::false_type { };

JLCXX_MODULE define_julia_module(Module &mod)
{
  mod.add_type<Parametric<TypeVar<1>>>("vector")
     .apply<monolish::vector<double>>(WrapMonolishVector_double())
     .apply<monolish::vector<float>>(WrapMonolishVector_float());
  
  mod.add_type<Parametric<TypeVar<1>>>("MyVector")
     .apply<gomalish_vector<double>, gomalish_vector<float>>(WrapGomalishVector());

  mod.method("dot", &monolish_dot_double);
  mod.method("dot_float", &monolish_dot_float);
}
