// Henry Jindrich Hajek, jh109@hw.ac.uk
// SUPA C++ course, assessment 1

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

// structure to hold data: (vectors of values of x, y, and magnitude)
// note: magnitude kept alongside x and y vectors,
// to be calculated immdediately on import to reduce loops required
struct x_vect_y_vect_pair
{
    std::vector<double> x; // x values
    std::vector<double> y; // y values
    std::vector<double> mag; // magnitude values
    int count; // datapoint count
};


// structure to hold linear fit constants:
// y = px + q
struct fit_parameters
{
    double p;
    double q;
};

// function that returns 2-D vector magnitude given (x, y)
// arguments: x, y
double magnitude(double, double);

// function that prints a requested number of datapoints data
// arguments: data structure, number of datapoints
void print_data(x_vect_y_vect_pair, int);

// function that returns a structure containing vector of x values and vector of y values
// arguments: input file path
x_vect_y_vect_pair import_data(std::string);

// function that returns x powered to the nearest integer of y
// arguments: x, y
double integer_power(double, double, double partial = 1);

// function that calculates least squares fit:
// arguments: data structure
// note: this could probably be done more efficiently and elegantly
// with some sort of vectorised code (array operations) like in MATLAB or numpy?
fit_parameters LSfit(x_vect_y_vect_pair);

// function that calculates goodness of fit aka chi2:
// arguments: data structure, error structure, fit structure
double chi2(x_vect_y_vect_pair data, x_vect_y_vect_pair errors, fit_parameters fit);
