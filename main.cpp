//
// Copyright 2017 Wyatt Miller
//

#include "clustergen.h"

int main() {

    std::vector<std::vector<double>> v = {{11,22}, {33,44}, {55,66,77}, {88,99}, {100}};
    std::vector<std::vector<double>> v2 = {{110,120}, {130,140}, {150,160,170}, {180,190}, {200}};


    cluster_set my_clusters;
    // Vector import with default out file, reporting file, and delimiters.
    my_clusters.import_centroids(v);
    my_clusters.clustergen(10);

    cluster_set my_clusters1("1_clustergen_out.dat", "1_clustergen_rpt.dat");
    // Vector import with user specified out file and reporting file, and default delimiters.
    my_clusters1.import_centroids(v2);
    my_clusters1.clustergen(11);

    cluster_set my_clusters2("2_clustergen_out.dat", "2_clustergen_rpt.dat");
    // Vector import with user specified out file, reporting file, and delimiters.
    my_clusters2.set_delim_in(' ');
    my_clusters2.set_delim_out('@');
    my_clusters2.import_centroids(v);
    my_clusters2.clustergen(12);

    cluster_set my_clusters3("3_clustergen_out.dat", "3_clustergen_rpt.dat");
    // File import with default out file, reporting file, and delimiters.
    my_clusters3.set_delim_in(' ');
    my_clusters3.import_centroids("clustergen_in.dat");
    my_clusters3.clustergen(13);

    cluster_set my_clusters4("4_clustergen_out.dat", "4_clustergen_rpt.dat");
    // File import with user specified out file and reporting file, and default delimiters.
    my_clusters4.set_delim_in('#');
    my_clusters4.import_centroids("clustergen_in2.dat");
    my_clusters4.clustergen(14);

    cluster_set my_clusters5("5_clustergen_out.dat", "5_clustergen_rpt.dat");
    // File import with user specified out file, reporting file, and delimiters.
    my_clusters5.set_delim_in('#');
    my_clusters5.set_delim_out('@');
    my_clusters5.import_centroids("clustergen_in2.dat");
    my_clusters5.clustergen(15);

}
