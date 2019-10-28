#ifndef __NEIGHBOURS_H_
#define __NEIGHBOURS_H_

#include <generic.hpp>
#include <mol_sys.hpp>

namespace nneigh {

// Inefficient O(n^2) implementation of neighbour lists when there are two
// different types of atoms The neighbour list does not differentiate between
// the types of atoms
std::vector<std::vector<int> > neighList(
    double rcutoff, molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    int typeI, int typeJ);

// Inefficient O(n^2) implementation of neighbour lists
// You can only use this for neighbour lists with one type
std::vector<std::vector<int> > neighListO(
    double rcutoff, molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    int typeI);

// Inefficient O(n^2) implementation of neighbour lists
// You can only use this for neighbour lists with one type
std::vector<std::vector<int> > halfNeighList(
    double rcutoff, molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    int typeI = 1);

}  // namespace nneigh

#endif  // __NEIGHBOURS_H_
