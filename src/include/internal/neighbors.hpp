#ifndef __NEIGHBORS_H_
#define __NEIGHBORS_H_

#include "molecular_system.h"
#include "molecule.h"
#include "parameter.h"
#include <iostream>
#include <yodaNanoFlann.hpp>

namespace neigh {
// Struct to hold points and functions
template <typename T> struct PointCloud {
  struct Point {
    T x, y, z;
  };

  std::vector<Point> pts;

  std::array<double, 3> box;

  // Must return the number of data points
  inline size_t kdtree_get_point_count() const { return pts.size(); }

  // Returns the dim'th component of the idx'th point in the class:
  // Since this is inlined and the "dim" argument is typically an immediate value, the
  //  "if/else's" are actually solved at compile time.
  inline double kdtree_get_pt(const size_t idx, const size_t dim) const {
    if (dim == 0)
      return pts[idx].x;
    else if (dim == 1)
      return pts[idx].y;
    else
      return pts[idx].z;
  }

  // Optional bounding-box computation: return false to default to a standard bbox computation loop.
  //   Return true if the BBOX was already computed by the class and returned in "bb" so it can be avoided to redo it again.
  //   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3 for point clouds)
  template <class BBOX> bool kdtree_get_bbox(BBOX & /* bb */) const {
    return false;
  }
}; // namespace neigh

class treeKNN {
private:
public:
  //  Super cool C++11
  std::array<double, 3> coordHigh;
  std::array<double, 3> coordLow;
  // Initializes Frames (CMolSys Obj)
  void prepFrame(int nop, std::string filename);
  void populateCloud(int typeI);
  // Check if atom is within limits
  bool isThere(int iatom, CMolecularSystem *frame);

  // Things above this are actually private.

  treeKNN();
  virtual ~treeKNN();

  CMolecularSystem *frame;
  neigh::PointCloud<double> cloud;
  // Returns the points as a vector and the distance
  // std::vector<double> byNumber();

  neigh::PointCloud<double> byNumber(int particle, size_t nearest);
  // void kdtree_demo();
};

} // namespace neigh

#endif // __NEIGHBORS_H_