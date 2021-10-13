#include<jlcxx/jlcxx.hpp>
#include<vml/monolish_vector_vml.hpp>

using namespace jlcxx;

void wrap_vml(Module &mod){
    mod.method("add", [](const monolish::vector<double> &a, const monolish::vector<double> &b, monolish::vector<double> &y){monolish::vml::add(a, b, y);});
    mod.method("add", [](const monolish::vector<float> &a, const monolish::vector<float> &b, monolish::vector<float> &y){monolish::vml::add(a, b, y);});
    mod.method("sub", [](const monolish::vector<double> &a, const monolish::vector<double> &b, monolish::vector<double> &y){monolish::vml::sub(a, b, y);});
    mod.method("sub", [](const monolish::vector<float> &a, const monolish::vector<float> &b, monolish::vector<float> &y){monolish::vml::sub(a, b, y);});
}