/* stats.cpp
 *
 * Statistics library
 *
 * EECS 280 Project 1
 *
 */


#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <cmath>

using namespace std;

vector<vector<double>> summarize(vector<double> v) {

    // sort v to order by value

    sort(v);

    vector<vector<double>> summary;
    vector<double> val_freq;

    double curr_num = 0;
    double curr_count = 0;

    for (size_t i = 0; i < v.size(); ++i) {

        if (i == 0) {

            curr_num = v[i];
            curr_count = 1;

        } else {

            if (v[i] == curr_num) {

                // same number as the previous one, update count
                curr_count += 1;

            } else {

                // different number, push value-frequency vector
                // update current number and count

                val_freq = {curr_num, curr_count};

                summary.push_back(val_freq);

                curr_num = v[i];
                curr_count = 1;
            }
        }
    }


    // push final val_freq pair
    
    val_freq = {curr_num, curr_count};
    summary.push_back(val_freq);


    return summary;
    
}

int count(vector<double> v) {

    return v.size();
}

double sum(vector<double> v) {

    //requires non-empty vector
    //assert(v.size() > 0);

    double total = 0.0;

    for (size_t i = 0; i < v.size(); ++i) {

        total += v[i];

    }

    return total;
}

double mean(vector<double> v) {

    //requires non-empty vector
    //assert(v.size() > 0);

    double total = 0.0;

    if (v.size() == 0) {
        
        return total;

    } else {

        for (size_t i = 0; i < v.size(); ++i) {

            total += v[i];

        }

        return total/v.size();

    }

}

double median(vector<double> v) {

    if (v.size() == 0) {

        return 0;

    } else {

        if (v.size() % 2 == 0) {
            // mean of middle two items

            size_t index = v.size()/2;

            return (v[index - 1] + v[index])/2;
        } else {
            //middle item
            
            size_t index = v.size()/2;

            return v[index];
        }
    }
}

double mode(vector<double> v) {

    if (v.size() == 0) {

        return 0;

    } else {

        // sort vector, keep track of current mode and count
        // update as you change numbers

        sort(v);

        double curr_mode = 0;
        int max_count = 0;

        double curr_num = 0;
        int curr_count = 0;

        for (size_t i = 0; i < v.size(); ++i) {

            if (i == 0) {
                // first number, initialize values
                curr_num = v[i];
                curr_count = 1;

            } else if (v[i] == curr_num) {
                // same number as before, just update count

                curr_count += 1;

            } else {
                // different number than before
                // update count and update min after comparison

                if (curr_count > max_count) {

                    // found new mode
                    //cout << "Found new mode " << curr_num << endl;

                    curr_mode = curr_num;
                    max_count = curr_count;

                    curr_num = v[i]; //update current_number
                    curr_count = 1;

                } else if (curr_count == max_count) {

                    // tie

                    if (curr_num < curr_mode) {

                        // found new mode after tie
                        //cout << "Found new mode after tie " << curr_num << endl;

                        curr_mode = curr_num;
                        max_count = curr_count;

                        curr_num = v[i]; //update current number
                        curr_count = 1;
                    }

                } else {

                    curr_num = v[i];
                }

            }
        }


        // finally check if last number is the mode

        if (curr_count > max_count) {

            // found new mode
            //cout << "Found new mode " << curr_num << endl;

            curr_mode = curr_num;
            max_count = curr_count;

        } else if (curr_count == max_count) {
            // tie

            if (curr_num < curr_mode) {

                // found new mode after tie
                cout << "Found new mode after tie " << curr_num << endl;

                curr_mode = curr_num;
                max_count = curr_count;

            }

        }

        return curr_mode;
    }
}

double min(vector<double> v) {

    double curr_min = __DBL_MAX__;
    
    if (v.size() == 0) {

        curr_min = 0;

    } else {

        for (size_t i = 0; i < v.size(); ++i) {

            if (v[i] < curr_min) {

                curr_min = v[i];

            }
        }
    }

    return curr_min;

}

double max(vector<double> v) {

    double curr_max = -__DBL_MAX__;
    
    if (v.size() == 0) {

        curr_max = 0;

    } else {

        for (size_t i = 0; i < v.size(); ++i) {

            if (v[i] > curr_max) {

                curr_max = v[i];

            }
        }
    }

    return curr_max;
}

double stdev(vector<double> v) {

    //https://en.wikipedia.org/wiki/Standard_deviation#Corrected_sample_standard_deviation

    double data_mean = mean(v);
    
    if (v.size() == 0 || v.size() == 1) {

        return 0.0;

    } else {

        double sd = 0.0;

        for (size_t i = 0; i < v.size(); ++i) {

            sd += pow((v[i] - data_mean), 2.0);
        }

        sd /= (v.size() - 1);
        sd = sqrt(sd);
        
        return sd;
    }

}

double percentile(vector<double> v, double p) {

    if (v.size() == 0) {

        return 0;

    } else {

        // sort vector
        sort(v);

        double rank = (p * (v.size() - 1)) + 1;

        double intpart = 0;
        double fracpart = 0;

        fracpart = modf(rank, &intpart);

        double p_percentile = v[intpart - 1] + (fracpart * (v[intpart] - v[intpart - 1]));

        return p_percentile;

    }
}