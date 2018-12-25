#ifndef __MOL_SYS_H_
#define __MOL_SYS_H_

#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <array>

namespace molSys{

	// Enum type for bond type
	enum bond_type
	{
		staggered, eclipsed, out_of_range
	};

	// Enum type for bond type
	enum atom_state_type
	{
		cubic, hexagonal, water, interfacial, clathrate, interClathrate, unclassified
	};

	// Struct containing the result
	struct Result
	{
		bond_type classifier;   // Classifier according to CHILL, CHILL+ etc
		double c_value; // Bond correlation factor
	};

	template <typename T> struct Point
		{
  			int type, molID, atomID ; 	// type ID, molID, atomID
  			T x, y, z; 					// coordinates
  			std::vector<int> neighList; // Neighbour list 
  			std::vector<Result> c_ij; 	// Results (contains bond correlation type)
  			atom_state_type iceType = molSys::unclassified;// Type of ice/water etc based on cij
  			bool inSlice=true; 			// Is the point inside the slice or not?
		};

	template <typename S, typename T> struct PointCloud
	{

		std::vector<S> pts; 	// Collection of points
		int currentFrame; 		// Current frame number
		int nop; 				// Number of atoms
		std::vector<T> box; 	// Periodic box lengths
		std::vector<T> boxLow;  // xlo, ylo, zlo

	};

	inline bool file_exists (const std::string& name) {
  		struct stat buffer;   
  		return (stat (name.c_str(), &buffer) == 0); 
	}

	// Function for tokenizing line strings into words (strings) delimited
	// by whitespace. This returns a vector with the words in it
	inline std::vector<std::string> tokenizer(std::string line)
	{
		std::istringstream iss(line);
		std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, 
										std::istream_iterator<std::string>{}};
		return tokens;
	}

	// Function for tokenizing line strings into a vector of doubles
	inline std::vector<double> tokenizerDouble(std::string line)
	{
		std::istringstream iss(line);
		std::vector<double> tokens;
		double number; // Each number being read in from the line
		while (iss >> number) {tokens.push_back(number);}
		return tokens;
	}

	// Function for reading in a specified frame (frame number and not timestep value)
	PointCloud<Point<double>, double> readLammpsTrj(std::string filename, int targetFrame, PointCloud<Point<double>, double> *yCloud, 
		bool isSlice=false, std::array<double,3> = std::array<double,3>{0,0,0}, std::array<double,3> = std::array<double,3>{0,0,0});

	// Function for reading in a specified frame (frame number and not timestep value)
	// This only reads in oxygen atoms
	PointCloud<Point<double>, double> readLammpsTrj(std::string filename, int targetFrame, PointCloud<Point<double>, double> *yCloud, 
		int typeO ,bool isSlice=false, std::array<double,3> = std::array<double,3>{0,0,0}, std::array<double,3> = std::array<double,3>{0,0,0});

	// Function for clearing vectors in PointCloud after multiple usage
	PointCloud<Point<double>, double> clearPointCloud(PointCloud<Point<double>, double> *yCloud);

	inline bool atomInSlice(double x, double y, double z, std::array<double,3> coordLow, std::array<double,3> coordHigh){
		int flag=0; // If this is 3 then the particle is inside the volume slice

		if(x>=coordLow[0] && x<=coordHigh[0]){flag++;}
		if(y>=coordLow[1] && y<=coordHigh[1]){flag++;}
		if(z>=coordLow[2] && z<=coordHigh[2]){flag++;}

		if(flag==3){return true;}
		else{return false;}
	}
	

}

#endif // __MOL_SYS_H_
