//
// Copyright 2017 Wyatt Miller
//


    #include "clustergen.h"
    #include <chrono>
    #include <iostream>
    #include <random>
    #include <sstream>

    double default_distribution(double & dimension) {
        static std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());   // Random seed
        // static std::default_random_engine gen(std::random_device{}());   // Not randomizing??
        std::normal_distribution<double> distr(dimension, 1);
        return distr(gen);
    }

    // Import centroids from file with specified delimiter into a temporary vector - calls import_centroids()
    cluster_set::cluster_set(std::ifstream & input_file, char delimiter) {
        this->distribution = default_distribution;
        std::string line;
        std::vector<std::vector<double>> temp_centroid_vector;
        while (std::getline(input_file, line)) {
            while ((line.length() == 0) && !(input_file.eof())) {
                std::getline(input_file, line);   // Skips blank lines in file
            }
            std::string parameter;
            std::stringstream ss(line);
            std::vector<double> temp_point;
            if ((line.length() != 0)) {
                while (std::getline(ss, parameter, delimiter)) {
                    temp_point.push_back(atof(parameter.c_str()));
                }
                temp_centroid_vector.push_back(temp_point);
            }
        }
        this->import_centroids(temp_centroid_vector);
    }

    // Import centroids from vector on construction
    cluster_set::cluster_set(std::vector<std::vector<double>> & centroid_vector) {
        this->distribution = default_distribution;
        this->import_centroids(centroid_vector);
    }

    // Primary centroid import function - Assures dimensional integrity by comparing all intake to the first point in the [centroids] vector
    void cluster_set::import_centroids(std::vector<std::vector<double>> & centroid_vector) {
        for (auto centroid_vector_iter = centroid_vector.begin(); centroid_vector_iter != centroid_vector.end(); ++centroid_vector_iter) {
            if (this->centroids.empty()) {
                this->centroids.push_back(*centroid_vector_iter);
            } else if (centroid_vector_iter->size() == this->centroids.front().size()) {   // Assures dimensional integrity
                this->centroids.push_back(*centroid_vector_iter);
            }
        }
    }

    // Primary cluster generator - aborts if no centroids have been imported.
    void cluster_set::clustergen(unsigned int k, std::ostream & output, char delimiter) {
        if (this->centroids.empty()) {
            output << "ERROR: No centroids have been imported. Aborting operation.";
            return;
        }
        if (k < this->centroids.size()) { k = this->centroids.size(); }
        unsigned int ct = 0;
        const unsigned int n = k / this->centroids.size();   // Evenly distributes points across centroids
        unsigned int rem = k % this->centroids.size();           // Evenly distributes points across centroids
        for (auto centroid_iter = this->centroids.begin(); centroid_iter != this->centroids.end(); ++centroid_iter) {
            unsigned int subset = n + (rem ? 1 : 0);         // Evenly distributes points across centroids
            while (subset) {
                std::vector<double> temp_point;
                for (auto dimension_iter = centroid_iter->begin(); dimension_iter != centroid_iter->end(); ++dimension_iter) {
                    temp_point.push_back(distribution(*dimension_iter));
                }
                for (auto temp_point_iter = temp_point.begin(); temp_point_iter != temp_point.end(); ++temp_point_iter) {
                    if (temp_point_iter != temp_point.begin()) { output << delimiter; }
                    output << (*temp_point_iter);
                }
                if (subset - 1) { output << "\n"; };
                --subset;
            }
            if (rem) { --rem; }   // Evenly distributes points across centroids
            auto centroid_iter_peek = centroid_iter;
            ++centroid_iter_peek;
            if (centroid_iter_peek != centroids.end()) { output << "\n"; };
        }
    }


