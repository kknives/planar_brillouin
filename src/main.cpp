#include "lattice.h"
#include <docopt.h>
#include <fmt/core.h>
#include <iostream>

static const char MSG[] =
  R"(Planar Brillouin

  Usage:
    pb zone <zones> [--scale=<sf>] [--size=<sz>] [-o FILE]

  Options:
    -h --help       Show this screen
    --version       Show the version
    --scale=<sf>    Scale the image by this factor [default: 30]
    --size=<sz>     The output image is a square sz by sz [default: 240]
    -o FILE         Specify output image file [default: ./zones.png]
    )";
int
main(int argc, const char** argv)
{
  std::map<std::string, docopt::value> args =
    docopt::docopt(MSG,
                   { argv + 1, argv + argc },
                   true,                      // show help if requested
                   "Planar Brillouin 0.1.0"); // version string

  for (auto const& arg : args) {
    std::cout << arg.first << arg.second << std::endl;
  }

  auto basis = BasisMat{};
  basis << 1, 0, 0, 1;

  auto vert_store = Lattice{};
  find_vertices(100, basis, vert_store);

  draw(vert_store);
}
