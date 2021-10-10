#include "lattice.h"
#include <Eigen/Geometry>
#include <bits/stdc++.h>
#include <fmt/core.h>

int
main()
{
  auto basis = BasisMat{};
  basis << 1, 0, 0, 1;

  auto vert_store = Lattice{};
  find_vertices(100, basis, vert_store);

  draw(vert_store);
}
