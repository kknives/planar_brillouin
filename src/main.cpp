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

auto
draw_zone(cairo_t* cr, Lattice& graph) -> void
{
  auto rot_45 = Eigen::Rotation2D<float>(asin(1));

  cairo_set_line_width(cr, 2);
  cairo_set_source_rgb(cr, 0, 0.19, 0.69);
  for (const auto& [r_sq, p] : graph) {

    auto scaled_p =
      (20 * p) / 2; // Taking midpoint of scale_factor*p and origin
    cairo_move_to(cr, scaled_p(0), scaled_p(1));
    for (P_Vec rot_p = rot_45 * scaled_p; !rot_p.isApprox(scaled_p);
         rot_p = rot_45 * rot_p) {
      cairo_line_to(cr, std::roundf(rot_p(0)), std::roundf(rot_p(1)));
      cairo_stroke(cr);
      cairo_move_to(cr, std::roundf(rot_p(0)), std::roundf(rot_p(1)));
      fmt::print("{},{}\n", std::roundf(rot_p(0)), std::roundf(rot_p(1)));
    }
    cairo_line_to(cr, scaled_p(0), scaled_p(1));
    cairo_stroke(cr);
  }
}

auto
draw(Lattice& graph) -> void
{
  cairo_surface_t* surface =
    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 240, 240);
  cairo_t* cr = cairo_create(surface);

  cairo_translate(cr, 120, 120);
  draw_zone(cr, graph);

  cairo_destroy(cr);
  cairo_surface_write_to_png(surface, "zones.png");
  cairo_surface_destroy(surface);
}

auto
find_immediate(P_Vec& p, BasisMat& basis) -> Eigen::Matrix<float, 2, 4>
{
  auto n1 = p + basis.col(0);
  auto n2 = p - basis.col(0);
  auto n3 = p + basis.col(1);
  auto n4 = p - basis.col(1);
  auto nx = Eigen::Matrix<float, 2, 4>{};
  nx << n1, n2, n3, n4;
  return nx;
}

auto
find_vertices(int zones, BasisMat basis, std::unordered_map<int, P_Vec>& r_sq)
  -> void
{
  // Starting from origin
  auto ref = P_Vec{ 0, 0 };
  auto position = ref;

  int f_zones = 0;
  while (f_zones < zones) {
    // A breadth-first search of the lattice:
    auto nearest = find_immediate(position, basis);
    // A matrix optimization can be done here which will benefit from
    // vectorised instructions
    for (auto x : nearest.colwise()) {
      auto norm = x.dot(x);
      if (!r_sq.contains(norm)) {
        r_sq[norm] = x;
        f_zones++;
      }
    }
    position = nearest.col(0);
  }
  for (const auto& [k, v] : r_sq)
    fmt::print("{}:({},{})\n", k, v(0), v(1));
}
