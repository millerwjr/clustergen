//
// Copyright 2017 Wyatt Miller
//


    #ifndef CLUSTERGEN_H
    #define CLUSTERGEN_H

    #include <fstream>
    #include <vector>
    #include <string>

    class cluster_set {

        std::vector<std::vector<double>> centroids;   // Centroids around which to evenly generate all points

        std::string file_out_str;   // The output file name - only settable on construction
        std::string file_rpt_str;   // The report file name - only settable on construction
        std::ofstream file_out;     // Instanced on clustergen() to prevent multiple outputs to the same file
        std::ofstream file_rpt;     // Appends throughout program

        char delim_in;    // Defaults to CSV - only used in file import
        char delim_out;   // Defaults to CSV

    public:

        cluster_set();                                           // Default settings
        cluster_set(const std::string &, const std::string &);   // User specified output and report file

        void import_centroids(const std::string &);                        // File import - uses vector import
        void import_centroids(const std::vector<std::vector<double>> &);   // Vector import - primary import algo

        void clustergen(const unsigned int);   // Primary algorithm - generates [unsigned int] number of points

        void set_delim_in(const char d) { this->delim_in = d; };     // User specified delimiter for input
        void set_delim_out(const char d) { this->delim_out = d; };   // User specified delimiter for output

    };

    #endif //CLUSTERGEN_H
