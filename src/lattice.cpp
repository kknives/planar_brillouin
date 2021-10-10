#include "lattice.h"
#include <Eigen/Geometry>
#include <bits/stdc++.h>
#include <fmt/core.h>

auto
draw_zone(cairo_t* cr, Lattice& graph, int sf) -> void
{
  auto rot_45 = Eigen::Rotation2D<float>(asin(1));

  cairo_set_line_width(cr, 2);
  cairo_set_source_rgb(cr, 0, 0.19, 0.69);
  for (const auto& [r_sq, p] : graph) {

    auto scaled_p =
      (sf * p) / 2; // Taking midpoint of scale_factor*p and origin
    cairo_move_to(cr, scaled_p(0), scaled_p(1));
    for (P_Vec rot_p = rot_45 * scaled_p; !rot_p.isApprox(scaled_p);
         rot_p = rot_45 * rot_p) {
      cairo_line_to(cr, std::roundf(rot_p(0)), std::roundf(rot_p(1)));
      cairo_stroke(cr);
      cairo_move_to(cr, std::roundf(rot_p(0)), std::roundf(rot_p(1)));
    }
    cairo_line_to(cr, scaled_p(0), scaled_p(1));
    cairo_stroke(cr);
    fmt::print("\r[~] Drew zone with R²: {}", r_sq);
  }
  fmt::print("\n[+] All zones drawn\n");
}

auto
draw(Lattice& graph, int sf, int size, std::string filename) -> void
{
  cairo_surface_t* surface =
    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size, size);
  cairo_t* cr = cairo_create(surface);

  cairo_translate(cr, size / 2, size / 2);
  fmt::print("[+] Drawing...\n");
  draw_zone(cr, graph, sf);

  cairo_destroy(cr);
  cairo_surface_write_to_png(surface, filename.c_str());
  cairo_surface_destroy(surface);
  fmt::print("[+] Written to file {}\n", filename);
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

  fmt::print("[~] Finding zone verticies...\n");
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
        fmt::print("\r[~] Found zone {} of {}", f_zones, zones);
      }
    }
    position = nearest.col(0);
  }
  fmt::print("\n");
  // for (const auto& [k, v] : r_sq)
  // fmt::print("{}:({},{})\n", k, v(0), v(1));
}
