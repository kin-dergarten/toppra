#include <bindings.hpp>

namespace toppra {
namespace python {

nparr toNumpyArray(const toppra::Vectors& ret) {
  nparr x;
  x.resize({(size_t)ret.size(), (size_t)ret[0].size()});
  for (size_t i = 0; i < x.shape()[0]; i++)
    for (size_t j = 0; j < x.shape()[1]; j++) x.mutable_at(i, j) = ret[i](j);
  return x;
}

PyPiecewisePolyPath::PyPiecewisePolyPath(const Matrices& coefficients,
                                         std::vector<value_type> breakpoints)
    : m_path{coefficients, breakpoints} {};

Vector PyPiecewisePolyPath::eval_single(value_type x, int order) const {
  return m_path.eval_single(x, order);
};

nparr PyPiecewisePolyPath::eval(const Vector& xs, int order) const {
  auto ret = m_path.eval(xs, order);
  return toNumpyArray(ret);
}

Bound PyPiecewisePolyPath::pathInterval() const { return m_path.pathInterval(); }

int PyPiecewisePolyPath::dof() const { return m_path.dof(); }

std::string PyPiecewisePolyPath::__str__() { return "PiecewisePolyPath(...)"; }
std::string PyPiecewisePolyPath::__repr__() { return "PiecewisePolyPath(...)"; }

}  // namespace python

}  // namespace toppra
