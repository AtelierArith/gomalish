#include <vector>

#include <jlcxx/jlcxx.hpp>
#include <common/monolish_vector.hpp>

using namespace jlcxx;

template<typename Float>
struct WrapMonolishVector
{
  template<typename TypeWrapperT>
  void operator()(TypeWrapperT&& wrapped)
  {
    typedef typename TypeWrapperT::type WrappedT;
    wrapped.template constructor<const size_t>();
    wrapped.template constructor<const size_t, const Float>();
    wrapped.template constructor<const size_t, const Float, const Float>();
    wrapped.template constructor<const std::vector<Float>&>();
    wrapped.method("print_all", [](WrappedT &w){w.print_all(false);});
    wrapped.method("print_all", [](WrappedT &w, bool force_cpu){w.print_all(force_cpu);});
    wrapped.method("print_all", [](WrappedT &w, std::string filename){w.print_all(filename);});
    wrapped.module().set_override_module(jl_base_module);
    wrapped.module().method("getindex", [] (WrappedT &w, int i) {return w[i];});
    wrapped.module().unset_override_module();
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

  mod.add_type<Parametric<TypeVar<1>>>("vector")
     .apply<monolish::vector<double>>(WrapMonolishVector<double>())
     .apply<monolish::vector<float>>(WrapMonolishVector<float>());

  mod.add_type<Parametric<TypeVar<1>>>("gomalish_vector")
     .apply<gomalish_vector<double>, gomalish_vector<float>>(WrapGomalishVector());
}
