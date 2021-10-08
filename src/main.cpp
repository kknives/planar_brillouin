#include "lattice.h"
#include <bits/stdc++.h>
#include <fmt/core.h>

int
main()
{
  auto basis = BasisMat{};
  basis << 1, 0, 0, 1;
  find_vertices(5, basis);
}

auto
find_immediate(P_Vec& p, BasisMat& basis) -> Eigen::Matrix<int, 4, 2>
{
  auto n1 = p + basis.row(0);
  auto n2 = p - basis.row(0);
  auto n3 = p + basis.row(1);
  auto n4 = p - basis.row(1);
  auto nx = Eigen::Matrix<int, 4, 2>{};
  nx << n1, n2, n3, n4;
  return nx;
}

auto
find_vertices(int zones, BasisMat basis) -> void
{
  // Starting from origin
  auto ref = P_Vec{ 0, 0 };
  auto position = ref;

  auto r_sq = std::unordered_map<int, P_Vec>{};

  int f_zones = 0;
  while (f_zones < zones) {
    // A breadth-first search of the lattice:
    auto nearest = find_immediate(position, basis);
    for (auto x : nearest.rowwise()) {
      auto norm = x.dot(x);
      if (!r_sq.contains(norm)) {
        r_sq[norm] = x;
        f_zones++;
      }
    }
    position = nearest.row(0);
  }
  for (const auto& [k, v] : r_sq)
    fmt::print("{}:({},{})\n", k, v(0), v(1));
}
