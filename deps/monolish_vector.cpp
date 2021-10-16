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
  
template<typename T1> struct IsMirroredType<monolish::vector<T1>> : std::false_type { };

void wrap_vector(Module &mod)
{

  mod.add_type<Parametric<TypeVar<1>>>("vector")
     .apply<monolish::vector<double>>(WrapMonolishVector<double>())
     .apply<monolish::vector<float>>(WrapMonolishVector<float>());
}
