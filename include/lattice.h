#pragma once

#include <Eigen/Dense>
#include <cairo.h>

typedef Eigen::Matrix<float, 2, 1> P_Vec;
typedef Eigen::Matrix<float, 2, 2> BasisMat;
typedef std::unordered_map<int, P_Vec> Lattice;

auto
draw(Lattice& graph) -> void;

auto
find_immediate(P_Vec& p, BasisMat& basis) -> Eigen::Matrix<float, 2, 4>;

auto
find_vertices(int zones, BasisMat basis, std::unordered_map<int, P_Vec>& r_sq)
  -> void;
// template<class V>
// struct Position
// {
// V x;
// V y;

// auto distance_to(Position<V> op) -> V;
// auto reflect_x() -> Position;
// auto reflect_y() -> Position;
// auto reflect_o() -> Position;
// };
