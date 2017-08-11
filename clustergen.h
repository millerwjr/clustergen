//
// Copyright 2017 Wyatt Miller
//

    #include <string>
    #include <vector>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <random>
    #include <chrono>

    #ifndef CLUSTERGEN_H
    #define CLUSTERGEN_H

    // CENTROID GENERATION - COMMON USER DEFINED VARIABLES
    // Note: These are unused if centroids are imported from a .dat file
    unsigned int const K = 3;        // Dimension of centroids and points
    bool const CENT_NORM = 0;        // 0 - UNIFORM distribution on centroid generation; 1 - NORMAL distribution
    double const CENT_CTR = 0;       // Defines the center of the centroid generation universe (x_1 = 0, x_2 = 0, etc.)
    double const CENT_BOUND = 100;   // Defines the +/- around the universe center for centroid generation if UNIFORM
    double const CENT_SD = 50;       // Defines the stddev around the universe center for centroid generation if NORMAL

    // POINT GENERATION - COMMON USER DEFINED VARIABLES
    double const PT_BOUND = 10;   // Defines the +/- around a centroid for point generation if UNIFORM
    double const PT_SD = 5;       // Defines the stddev around a centroid for point generation if NORMAL

    // UNCOMMON USER DEFINED VARIABLES (These should not need to be changed often)
    unsigned int const MAX_K = 100;     // MAXIMUM number of allowed centroids - NOT the TOTAL number of centroids
    unsigned int const MAX_DIM = 100;   // Maximum allowed dimension of centroids and points (x_1, x_2, etc.)

    // Example:
    // ctr_type const K = 3;              // Sets centroid (and thus point) dimension to 3
    // bool const CENT_NORM = 0;          // Centroids will be uniformly distributed around the universe center
    // double const CENT_CTR = 0;         // The universe center is at (0, 0, 0)
    // double const CENT_BOUND = 100;     // Centroids are generated between -100 and 100 if CENT_NORM = 0
    // double const CENT_SD = 50;         // Centroids are generated around the center with a stddev of 50 if CENT_NORM = 1
    // bool const PT_NORM = 1;            // Points will be uniformly distributed around a centroid
    // double const PT_BOUND = 10;        // Points are generated between -10 and +10 from the centroid if PT_NORM = 0
    // double const PT_SD = 5;            // Points are generated around the centroid with a stddev of 5 if PT_NORM = 1
    // unsigned int const MAX_K = 11;     // Forces the program to constrain to the first 11 centroids inserted
    // unsigned int const MAX_DIM = 59;   // Forces the program to omit any point with a dimension higher than 59



    // PRIMARY ALGORITHM
    void clustergen(unsigned int k, std::vector<std::vector<double>> &c, std::string file_out, std::string file_rpt, bool csv, bool norm);
    // Produces [k] points in [file_out]; all points are separated by line breaks
    // If [csv] = 0, dimensions for each point are whitespace-separated
    // If [csv] = 1, dimensions for each point are comma-separated
    // [c] is a vector of vectors; it's size is the number of centroids
    // The first insertion in [c] sets dimensional precedence; dimensional mismatches are always omitted/avoided.

    #endif //CLUSTERGEN_H
