#ifndef __SEAMS_OUTPUT_H_
#define __SEAMS_OUTPUT_H_

#include <bond.hpp>
#include <cage.hpp>
#include <generic.hpp>
#include <iostream>
#include <memory>
#include <mol_sys.hpp>

//// Boost
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
namespace fs = boost::filesystem;
// #include <filesystem>
// namespace fs = std::filesystem;

/*! \file seams_output.hpp
    \brief File for functions that write out output to files).

    Details.
*/

/*!
 *  \addtogroup sout
 *  @{
 */

/*! \brief Functions for output
 *         This namespace contains functions that are used for writing the
various outputs produced by d-SEAMS to text files, LAMMPS data files and
trajectory files.
 *
The LAMMPS data files and trajectory files can be easily visualized in <a
href="https://www.ovito.org/">OVITO</a> or <a
href="http://www.ks.uiuc.edu/Research/vmd/">VMD</a>, although
OVITO is recommended.

  ### Changelog ###

  - Amrita Goswami [amrita16thaug646@gmail.com]; date modified: Dec 26, 2019
 */

namespace sout {

// Function for printing out ring info, when there is no volume slice
int writeRings(std::vector<std::vector<int>> rings,
               std::string filename = "rings.dat");

// Function for printing out the number of prism blocks, with or without slices.
// Be careful when using slices!
int writePrismNum(std::string path, int currentFrame, std::vector<int> nPrisms,
                  std::vector<double> heightPercent, int maxDepth);

// Function for printing out the coverage area and the number of rings of each
// type
int writeRingNum(std::string path, int currentFrame, std::vector<int> nRings,
                 std::vector<double> coverageAreaXY,
                 std::vector<double> coverageAreaXZ,
                 std::vector<double> coverageAreaYZ, int maxDepth);

// Function for printing out the RDF, given the filename
int printRDF(std::string fileName, std::vector<double> *rdfValues,
             double binwidth, int nbin);

// Function for printing out the number of DDCs, HCs, mixed rings, basal and
// prismatic rings
int writeTopoBulkData(std::string path, int currentFrame, int numHC, int numDDC,
                      int mixedRings, int basalRings, int prismaticRings);

// Function for writing out each prism
int writePrisms(std::vector<int> *basal1, std::vector<int> *basal2,
                int prismNum,
                molSys::PointCloud<molSys::Point<double>, double> *yCloud);

// Function for writing out cluster statistics
int writeClusterStats(std::string path, int currentFrame, int largestCluster,
                      int numOfClusters, int smallestCluster,
                      double avgClusterSize);

// Write a data file for rings
int writeLAMMPSdata(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
                    std::vector<std::vector<int>> rings,
                    std::vector<std::vector<int>> bonds,
                    std::string filename = "system-rings.data");

// Write a data file for prisms of every type
int writeLAMMPSdataAllPrisms(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    std::vector<std::vector<int>> nList, std::vector<int> atomTypes,
    int maxDepth, std::string path);

// Write a data file for rings of every type for a monolayer
int writeLAMMPSdataAllRings(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    std::vector<std::vector<int>> nList, std::vector<int> atomTypes,
    int maxDepth, std::string path);

// Write a data file for a particular frame, writing out topological bulk ice
// structures (DDCs/HCs)
int writeLAMMPSdataTopoBulk(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    std::vector<std::vector<int>> nList, std::vector<cage::iceType> atomTypes,
    std::string path, bool bondsBetweenDummy = false);

// Write a data file for prisms of a single type
int writeLAMMPSdataPrisms(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    std::vector<std::vector<int>> rings, bool useBondFile, std::string bondFile,
    std::vector<int> listPrism, std::vector<std::vector<int>> nList,
    std::string filename = "system-prisms.data");

// Write out a lammps data file for DDCs or HCs, assuming that there is no slice
int writeLAMMPSdataCages(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    std::vector<std::vector<int>> rings, std::vector<cage::Cage> *cageList,
    cage::cageType type, int numCages,
    std::string filename = "system-cages.data");

// Write out all cages of all types into a folder called cages inside the output
// directory
int writeAllCages(std::string path, std::vector<cage::Cage> *cageList,
                  std::vector<std::vector<int>> rings,
                  std::vector<std::vector<int>> nList,
                  molSys::PointCloud<molSys::Point<double>, double> *yCloud,
                  int currentFrame);

// Write out a particular cage to a file
int writeEachCage(std::vector<int> currentCage, int cageNum,
                  cage::cageType type, std::vector<std::vector<int>> rings,
                  molSys::PointCloud<molSys::Point<double>, double> *yCloud);

// Write out the basal rings of a particular Hexagonal cage
int writeBasalRingsHex(std::vector<int> currentCage, int cageNum,
                       std::vector<std::vector<int>> nList,
                       std::vector<std::vector<int>> rings);

// Write out the basal rings for a particular prism
int writeBasalRingsPrism(
    std::vector<int> *basal1, std::vector<int> *basal2, int prismNum,
    std::vector<std::vector<int>> nList,
    molSys::PointCloud<molSys::Point<double>, double> *yCloud, bool isDeformed);

// Generic function for writing out to a dump file
int writeDump(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
              std::string path, std::string outFile);

// Function for printing out Q6, Cij and averaged Q3 values as single columns to
// text files The file names are cij, q6, q3
int writeHisto(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
               std::vector<std::vector<int>> nList, std::vector<double> avgQ6);

// Function for printing the largest ice cluster
int writeCluster(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
                 std::string fileName = "cluster.txt", bool isSlice = false,
                 int largestIceCluster = 0);
}  // namespace sout
#endif  // __SEAMS_OUTPUT_H_
