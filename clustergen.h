//
// Copyright 2017 Wyatt Miller
//


#ifndef KC_CLUSTERGEN_H
#define KC_CLUSTERGEN_H

#include <fstream>
#include <vector>

namespace kc {

    class cluster_set {
        std::vector<std::vector<double>> centroids;   // Centroids around which to evenly generate all points
        double (*distribution)(double &);             // Changeable pointer to a distribution function

        void import_centroids(std::vector<std::vector<double>> &);   // Import centroids from vector

    public:
        cluster_set(std::ifstream &, char);                // Import centroids from file with specified delimiter
        cluster_set(std::vector<std::vector<double>> &);   // Import centroids from vector on construction

        void clustergen(unsigned int, std::ostream &, char);

        void set_distribution(double (*new_distribution)(double &)) { this->distribution = new_distribution; }
    };

}

#endif //KC_CLUSTERGEN_H
