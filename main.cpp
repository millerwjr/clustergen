//
// Copyright 2017 Wyatt Miller
//

#include "clustergen.h"

int main() {

    std::vector<std::vector<double>> v = {{0,0}, {50,30}, {100,120}};
    clustergen(11, v, "clustergen_out.dat", "clustergen_report.dat", 1, 0);

}