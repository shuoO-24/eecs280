#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <vector>
#include <string>


using namespace std;


int main() {
    
    string filename;
    string col_name;

    cout << "enter a filename" << endl;
    cin >> filename;

    cout << "enter a column name" << endl;
    cin >> col_name;
    
    // get the column of data
    vector<double> col = extract_column(filename, col_name);

    cout << "reading column " << col_name << " from " << filename << endl;

    // Get statistics

    vector<vector<double>> summary = summarize(col);
    int col_count = count(col);
    double col_sum = sum(col);
    double col_mean = mean(col);
    double col_median = median(col);
    double col_mode = mode(col);
    double col_min = min(col);
    double col_max = max(col);
    double col_stdev = stdev(col);
    double col_percentile_0 = percentile(col, 0.0);
    double col_percentile_25 = percentile(col, 0.25);
    double col_percentile_50 = percentile(col, 0.50);
    double col_percentile_75 = percentile(col, 0.75);
    double col_percentile_100 = percentile(col, 1.0);


    cout << "Summary (value: frequency)" << endl;

    for(int i=0; i < summary.size(); ++i) {

        double val = summary[i][0];
        double freq = summary[i][1];

        cout << val << ": " << freq << endl;

    }

    cout << "" << endl;
    
    cout << "count = " << col_count << endl;
    cout << "sum = " << col_sum << endl;
    cout << "mean = " << col_mean << endl;
    cout << "stdev = " << col_stdev << endl;
    cout << "median = " << col_median << endl;
    cout << "mode = " << col_mode << endl;
    cout << "min = " << col_min << endl;
    cout << "max = " << col_max << endl;

    cout << "  0th percentile = " << col_percentile_0 << endl;
    cout << " 25th percentile = " << col_percentile_25 << endl;
    cout << " 50th percentile = " << col_percentile_50 << endl;
    cout << " 75th percentile = " << col_percentile_75 << endl;
    cout << "100th percentile = " << col_percentile_100 << endl;

}