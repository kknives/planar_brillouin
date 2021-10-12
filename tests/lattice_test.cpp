#include "lattice.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("First planar Brillouin zone is correct", "[find_vertices]")
{
  auto basis = BasisMat{};
  basis << 1, 0, 0, 1;
  auto vert_store = Lattice{};

  find_vertices(1, basis, vert_store);
  REQUIRE(vert_store.contains(1));
}
TEST_CASE("First 5 planar Brillouin zones are correct", "[find_vertices]")
{
  auto basis = BasisMat{};
  basis << 1, 0, 0, 1;
  auto vert_store = Lattice{};

  find_vertices(5, basis, vert_store);
  REQUIRE(vert_store.contains(1));
  REQUIRE(vert_store.contains(2));
  REQUIRE(vert_store.contains(4));
  REQUIRE(vert_store.contains(5));
  REQUIRE(vert_store.contains(9));
}
TEST_CASE("4 orthogonal neighbours are found from origin", "[find_immediate]")
{
  // These neighbours are all distance of 1 unit from origin
  auto basis = BasisMat{};
  basis << 1, 0, 0, 1;
  auto origin = P_Vec{ 0, 0 };

  auto res = find_immediate(origin, basis);
  for (auto x : res.colwise()) {
    REQUIRE(x.dot(x) == 1);
  }
}
