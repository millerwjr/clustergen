//
// Copyright 2017 Wyatt Miller
//

    #include "kc_clustergen.h"
    #include <chrono>
    #include <iostream>
    #include <random>

    double new_distribution(double & dimension) {
        static std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());   // Random seed
        // static std::default_random_engine gen(std::random_device{}());   // Not randomizing??
        std::uniform_int_distribution<int> distr(-5, 5);
        return dimension + 10 * distr(gen);
    }



    double uni_distribution(double & dimension) {
        static std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());   // Random seed
        // static std::default_random_engine gen(std::random_device{}());   // Not randomizing??
        std::uniform_int_distribution<int> distr(-50, 50);
        return dimension + distr(gen);
    }


    double new_normal_distribution(double & dimension) {
        static std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());   // Random seed
        // static std::default_random_engine gen(std::random_device{}());   // Not randomizing??
        std::normal_distribution<double> distr(dimension, 10);
        return distr(gen);
    }


    int main() {
/*
        std::vector<std::vector<double>> v = {{-100, -100},
                                              {100,  100},
                                              {1000, 1000}};
        std::vector<std::vector<double>> v2 = {{-100, -100},
                                               {1},
                                               {100,  100},
                                               {1,    2, 3},
                                               {1000, 1000}}; // Dimensional mismatch

        std::ostream &output_console = std::cout;
        std::ofstream output_file;

        cluster_set my_clusters(v);                        // Vector constructor
        my_clusters.clustergen(11, output_console, ',');   // Generate 10 random points to the console (',' delimited)

        std::ofstream out2;
        out2.open("clustergen_out_2.dat");
        cluster_set my_clusters2(v2);                       // Vector constructor with invalid dimensional points (omitted)
        my_clusters2.set_distribution(new_distribution);    // Setting a user-defined distribution
        my_clusters2.clustergen(11, out2, ',');             // Generate 11 random points to "clustergen_out_2.dat" (',' delimited)

        std::ifstream v3;
        v3.open("clustergen_in.dat");
        std::ofstream out3;
        out3.open("clustergen_out_3.dat");
        cluster_set my_clusters3(v3,'$');          // File const. with user-spec. delimiter - blank lines and invalid dimensions omitted
        my_clusters3.clustergen(13, out3, '@');    // Generate 13 random points to "clustergen_out_3.dat" (',' delimited)


*/
        std::vector<std::vector<double>> v4 = {{0, 0, 0}};

        // Generate 10 centroids, uniformly distributed integers between -100 and 100 in 3 dimensions
        std::ofstream centroid_out;
        centroid_out.open("centroids.dat");
        kc::cluster_set centroids(v4);
        centroids.set_distribution(uni_distribution);
        centroids.clustergen(5, centroid_out, ',');
        centroid_out.close();   // Need to close out - "centroids.dat" is used in the following code

        // Generate 1000 points, evenly and normally distributed (SD: 10) around the previously generated centroids
        std::ifstream v5;
        v5.open("centroids.dat");
        std::ofstream test_data_out;
        test_data_out.open("test_data.dat");
        kc::cluster_set test_data(v5,',');
        test_data.clustergen(4000, test_data_out, ',');


    }