//
// Copyright 2017 Wyatt Miller
//
    #include "clustergen.h"

    void clustergen(unsigned int k, std::vector<std::vector<double>> &c, std::string file_out, std::string file_rpt, bool csv, bool norm) {

        std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());   // Random seed
        std::ofstream fout(file_out);                // This is the useful output of all points
        std::ofstream rout(file_rpt);                // Report file to avoid console output
        std::vector<unsigned int> ct(c.size(), 0);   // Independent counting vector for reporting
        auto ct_iter = ct.begin();                   // Counting vector iterator - used below primary for()

        rout << "CLUSTERGEN STATUS REPORT FOLLOWS..." << std::endl;   // Begin reporting to file

        for (auto c_iter = c.begin(); k > 0; --k) {
            if (c_iter == c.end()) { c_iter = c.begin(); }       // Continuously loop through cluster vec until k = 0
            if (ct_iter == ct.end()) { ct_iter = ct.begin(); }   // Continuously loop through counting vec until k = 0

            for (auto d_iter = c_iter->begin(); d_iter != c_iter->end(); ++d_iter) {
                if (norm) {
                    // Point generation occurs NORMALLY distributed around centroid
                    std::normal_distribution<double> distr(*d_iter, PT_SD);
                    fout << distr(gen);
                } else {
                    // Point generation occurs UNIFORMLY distributed around centroid
                    std::uniform_real_distribution<double> distr(*d_iter - PT_BOUND, *d_iter + PT_BOUND);
                    fout << distr(gen);
                }

                std::vector<double>::iterator temp_d_iter = d_iter;   // Used to peek at the next dimensional element

                if (++temp_d_iter != c_iter->end()) { (csv == 0) ? (fout << " ") : (fout << ","); }   // WS or CSV
                else if (k > 1) { fout << std::endl; }   // Line break on all but last line
            }
            ++c_iter;
            ++(*ct_iter);
            ++ct_iter;
        }

        // Reporting to file follows
        unsigned int ct_tot = 0;
        unsigned int i = 0;
        for (ct_iter = ct.begin(); ct_iter != ct.end(); ++ct_iter) {
            rout << std::endl << *ct_iter << " points ";
            rout << ((norm) ? "normally" : "uniformly");
            rout << " distributed around centroid " << ++i << " ...";
            ct_tot += *ct_iter;
        }

        rout << std::endl << std::endl << ct_tot << " total points assigned.";
    }




