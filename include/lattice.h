#pragma once

#include <Eigen/Dense>

typedef Eigen::Matrix<int, 1, 2> P_Vec;
typedef Eigen::Matrix<int, 2, 2> BasisMat;

auto
find_immediate(P_Vec& p, BasisMat& basis) -> Eigen::Matrix<int, 4, 2>;

auto
find_vertices(int zones) -> void;
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
