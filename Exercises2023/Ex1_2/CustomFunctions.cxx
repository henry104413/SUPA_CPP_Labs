// Henry Jindrich Hajek, jh109@hw.ac.uk
// SUPA C++ course, assessment 1

#include "CustomFunctions.h"


// function that returns 2-D vector magnitude given (x, y)
// arguments: x, y
double magnitude(double x, double y)
    {return std::sqrt(std::abs(std::pow(x, 2) + std::pow(y,2)));
    }



// function that returns a structure containing vector of x values and vector of y values
// arguments: input file path
x_vect_y_vect_pair import_data(std::string filename)
    {

    // create return structure:
    x_vect_y_vect_pair data;
        

    // data file input object:
    std::ifstream input_file(filename);

    // check if file opened:
    if (!input_file.is_open())
        {std::cout << "Data file couldn't be opened...\n"; return data;}
        // note: ?? not sure how to return error code
        // when my return type is something complex (like structure of vectors here)
    else
        {std::cout << "Opened successfully...\n";}



    int count = 0; // datapoints counter
    std::string newline = ""; // string to hold new line data

    // containers to hold separated x and y string components from each line
    std::string x_str = "";
    std::string y_str = "";

    // go through all the lines:
    // note: assumes that first line is labels (characters), 
    // and  further lines valid data (numbers), comma delimited
    std::getline(input_file, newline, '\n'); // first line with labels (effectively dumped)
    while(!input_file.eof())
        {

        // get new line:
        std::getline(input_file, newline, '\n');

        // don't try and process an empty line!
        // note: happens otherwise since new line above drawn AFTER eof() check
        if(newline.empty())
            {break;}
        
        // update datapoint counter: 
        count++;        
    

        // convert comma delimited string from current line into two values:

        // separate into two strings of just numbers:
        std::stringstream ss(newline);
        std::getline(ss, x_str, ',');
        std::getline(ss, y_str, ',');

        // append x and y values as well as magnitude to respective containers:
        // note: I believe this is an awfully suboptimal way to do it,
        // since the container gets resized in every iteration of the loop?
        data.x.push_back(std::stod(x_str));
        data.y.push_back(std::stod(y_str));
        data.mag.push_back(magnitude(std::stod(x_str), std::stod(y_str)));
        

        
        //functionality testing:
        if (false)
            {std::cout << "x: " << x_str << " y: " << y_str << std::endl; // test
            
            
            //double x = std::stod(x_str);
            //x += 0.1;
            //std::cout << std::to_string(x) << std::endl;
            }

        }

    // close input file:
    input_file.close();

    // populate return structure:
    //data.x = x_vals;
    //data.y = y_vals;
    data.count = count;

    return data;
    }



// function that prints a requested number of datapoints data
// arguments: data structure, number of datapoints to show
void print_data(x_vect_y_vect_pair data, int up_to)
    {
        // check if number larger than datapoint count:
        // (if so, print 5 instead as per instructions)
        if (up_to > data.count)
            {std::cout << "Don't have that many datapoints!\nShowing first five:" << std::endl;
            up_to = 5;}

        for (int i = 0; i < up_to; i++)
            {  
            std::cout << "x: " << std::to_string(data.x[i]) << 
            " y: " << std::to_string(data.y[i]) << 
            " mag: " << std::to_string(data.mag[i]) << std::endl;
            }
    }




// function that returns x powered to the nearest integer of y
// arguments: x, y
// note: assumes POSITIVE y; if NEGATIVE values had to be considered,
// another branch could be added with condition y<0 that performes /= x instead
double integer_power(double x, double y, double partial)
{
    // enforce positivity and round to nearest integer
    y = std::round(std::abs(y));

    // note: effectively perform y iterations of multiplication by x,
    // result stored in implicit parameter partial
    // (honestly I can't see how this is more optimal or more elegant than a loop?)
    if(y < 1)
        {return partial;}
    else
        {
            y--;
            partial *= x;
            return integer_power(x, y, partial);
        }

}


// function that calculates least squares fit:
// arguments: data structure
// note: this could probably be done more efficiently and elegantly
// with some sort of vectorised code (array operations) like in MATLAB or numpy?
fit_parameters LSfit(x_vect_y_vect_pair data)
{
    fit_parameters fit;
    
    // shorthand for x, y value vectors and datapoint count:
    auto X = data.x;
    auto Y = data.y;
    int N = data.count;

    // partial sums for each of the terms
    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumXsq = 0; 

    // sum across the length of data vectors:
    for(int i = 0; i < N; i++)
        {
            sumX += X[i];
            sumY += Y[i];
            sumXY += X[i]*Y[i];
            sumXsq += X[i]*X[i];
        }

    
    //build expressions for p and q:

    double denominator = N*sumXsq - sumX*sumX;

    fit.p = (N*sumXY - sumX*sumY)/denominator;

    fit.q = (sumXsq*sumY - sumXY*sumX)/denominator;

    return fit;

}

// function that calculates goodness of fit aka chi2:
// arguments: data structure, error structure, fit structure
double chi2(x_vect_y_vect_pair data, x_vect_y_vect_pair errors, fit_parameters fit)
{
        
    // shorthand for x, y value vectors, datapoint count, and vector of errors in y:
    auto X = data.x;
    auto Y = data.y;
    int N = data.count; 
    auto DY = errors.y;


    // partial sum:
    double chi2 = 0;

    // sum across the length of data vectors:
    for(int i = 0; i < N; i++)
        {
            // expected value according to fit at X[i]:
            // note: code could be modified to store these in a vector for plotting the fit etc.
            double E = fit.p*X[i] + fit.q;

            // build chi2:
            chi2 += (Y[i]-E)*(Y[i]-E)/(DY[i]*DY[i]);
        }

    return chi2;

}