//
// Copyright 2017 Wyatt Miller
//


    #include "clustergen.h"
    #include <sstream>
    #include <iostream>
    #include <chrono>
    #include <random>

    // Default everything - centroid import or generation required
    cluster_set::cluster_set(void) {
        this->file_out_str = "clustergen_out.dat";
        this->file_rpt_str = "clustergen_rpt.dat";
        this->delim_in = ',';
        this->delim_out = ',';
        this->file_rpt.open(this->file_rpt_str);
        this->file_rpt << "CLUSTERGEN STATUS REPORT FOLLOWS";
        this->file_rpt.close();
    }

    // User specified output file and delimiter - centroid import or generation required
    cluster_set::cluster_set(const std::string &fout, const std::string &rout) :
        file_out_str(fout),
        file_rpt_str(rout) {
        this->delim_in = ',';
        this->delim_out = ',';
        this->file_rpt.open(this->file_rpt_str);
        this->file_rpt << "CLUSTERGEN STATUS REPORT FOLLOWS";
        this->file_rpt.close();
    }

    // Reads in a file to a vector then passes to the primary centroid import function
    void cluster_set::import_centroids(const std::string &fin) {
        std::ifstream file_in(fin);
        this->file_rpt.open(this->file_rpt_str, std::ios_base::app);
        this->file_rpt << "\n" << "\n" << "Importing file to centroid vector: \"" << fin << "\" ...";
        std::string line;
        std::vector<std::vector<double>> temp_centroid_vec;
        while (std::getline(file_in, line)) {
            while ((line.length() == 0) && !(file_in.eof())) {
                std::getline(file_in, line);
            }   // Skips blank lines in file
            std::string param;
            std::stringstream ss(line);
            std::vector<double> temp_point;
            if ((line.length() != 0)) {
                while (std::getline(ss, param, this->delim_in)) {
                    temp_point.push_back(atof(param.c_str()));
                }
                temp_centroid_vec.push_back(temp_point);
            }
        }
        this->file_rpt.close();
        this->import_centroids(temp_centroid_vec);
    }

    // Primary centroid import function
    void cluster_set::import_centroids(const std::vector<std::vector<double>> &centroid_vec) {
        this->file_rpt.open(this->file_rpt_str, std::ios_base::app);
        this->file_rpt << "\n" << "\n" << "Importing centroid vector to universe:";
        if (!(this->centroids.empty())) {
            this->file_rpt << "\n" << "    WARNING: Universe already initialized - flushing all clusters ...";
            this->centroids.clear();   // TODO - CHECK IF THIS IS PROPERLY DESTRUCTING EVERYTHING ...
        }
        for (auto cent_vec_iter = centroid_vec.begin(); cent_vec_iter != centroid_vec.end(); ++cent_vec_iter) {
            if (this->centroids.empty()) {
                this->centroids.push_back(*cent_vec_iter);
            } else if (cent_vec_iter->size() == this->centroids.front().size()) {
                this->centroids.push_back(*cent_vec_iter);
            }
        }
        this->file_rpt << "\n" << "    " << this->centroids.size() << " Centroid imports SUCCESSFUL.";
        this->file_rpt << "\n" << "    " << centroid_vec.size() - this->centroids.size() << " Centroid imports FAILED.";
        this->file_rpt.close();
    }

    // Primary cluster generator - aborts if no centroids exists.
    void cluster_set::clustergen(const unsigned int k) {
        static std::default_random_engine gen(
                std::chrono::system_clock::now().time_since_epoch().count());   // Random seed
        this->file_rpt.open(this->file_rpt_str, std::ios_base::app);
        this->file_out.open(this->file_out_str);
        this->file_rpt << "\n" << "\n" << "Generating Points:";
        if (this->centroids.empty()) {
            this->file_rpt << "\n" << "ERROR: No centroids have been imported. Aborting operation.";
            return;
        }
        const unsigned int n = k / this->centroids.size();
        unsigned rem = k % this->centroids.size();
        unsigned int centroid_ct = 0;
        for (auto centroid_iter = this->centroids.begin(); centroid_iter != this->centroids.end(); ++centroid_iter) {
            unsigned int subset = n + (rem ? 1 : 0);
            this->file_rpt << "\n" << "    Generating " << subset << " points around centroid " << ++centroid_ct
                           << " ...";
            while (subset) {
                std::vector<double> temp_point;
                for (auto dimension_iter = centroid_iter->begin();
                     dimension_iter != centroid_iter->end(); ++dimension_iter) {
                    // Would love to put something here to allow users to specify their own distribution...
                    std::normal_distribution<double> distr(*dimension_iter, 10);
                    temp_point.push_back(distr(gen));
                }
                for (auto temp_point_iter = temp_point.begin();
                     temp_point_iter != temp_point.end(); ++temp_point_iter) {
                    if (temp_point_iter != temp_point.begin()) { this->file_out << this->delim_out; }
                    this->file_out << (*temp_point_iter);
                }
                if (subset - 1) { this->file_out << "\n"; };
                --subset;
                if (rem) { --rem; }
            }
            this->file_rpt << " Done.";
            auto centroid_iter_peek = centroid_iter;
            ++centroid_iter_peek;
            if (centroid_iter_peek != centroids.end()) { this->file_out << "\n"; };
        }
        this->file_rpt << "\n\n    " << k << " total points generated around " << centroid_ct << " centroids.";
        this->file_out.close();
        this->file_rpt.close();
    }


