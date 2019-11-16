#ifndef __TOPO_TWO_DIM_H_
#define __TOPO_TWO_DIM_H_

#include <math.h>
#include <sys/stat.h>
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <mol_sys.hpp>
#include <order_parameter.hpp>
#include <ring.hpp>
#include <seams_input.hpp>
#include <seams_output.hpp>

/*! \file topo_one_dim.hpp
    \brief File containing functions used specific to quasi-one-dimensional
   topological network critera (the prism identification scheme).
*/

/*!
 *  \addtogroup ring
 *  @{
 */

namespace ring {

// Find out which rings are prisms, looping through all ring sizes upto the
// maxDepth The input ringsAllSizes array has rings of every size.
int polygonRingAnalysis(
    std::string path, std::vector<std::vector<int>> rings,
    std::vector<std::vector<int>> nList,
    molSys::PointCloud<molSys::Point<double>, double> *yCloud, int maxDepth,
    double sheetArea);

// Assign an atomType (equal to the number of nodes in the ring)
// given a vector with a list of indices of rings comprising the prisms
int assignPolygonType(std::vector<std::vector<int>> rings,
                      std::vector<int> listPrism, int ringSize,
                      std::vector<int> *atomTypes);

}  // namespace ring

#endif  // __TOPOCONFINED_H_
