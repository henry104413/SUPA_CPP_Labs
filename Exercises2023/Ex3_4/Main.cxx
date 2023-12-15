// Henry Jindrich Hajek, jh109@hw.ac.uk
// SUPA C++ course, assessment 2

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way




int main()
{
    
    // import the data:

    // data file path
    std::string filename = "some_data.txt";

    // data file input object:
    std::ifstream input_file(filename);

    // container for file data:
    std::vector<double> data; 

    // check if file opened:
    if (!input_file.is_open())
        {std::cout << "Data file couldn't be opened...\n"; return 1;}
        
    else
        {std::cout << "Opened successfully...\n";}

    std::string newline = ""; // string to hold new line data

    // go through all the lines:
    while(!input_file.eof())
        {

        // get new line:
        std::getline(input_file, newline, '\n');

        // don't try and process an empty line!
        // note: happens otherwise since new line above drawn AFTER eof() check
        if(newline.empty())
            {break;}
        
        // append new datapoint to container:
        data.push_back(std::stod(newline));
        }
    
    // close input file:
    input_file.close();

    

    /*
    Note:
    In the interest of time, I skipped the implementation of the other formulas (Gaussian and Lorenzian),
    as they obviously cannot fit the data (both are even functions and the data is clearly not symmetrical).

    They could easily be defined the same way, inheriting from FiniteFunction, defining the parameters of the distribution,
    and overriding the evaluation function.

    The Crystal Ball function parameters were found by eyeball and trial and error. For a more robust solution, one could implement
    a chi2 optimisation over a 4 dimensional space of possible parameter values.

    Plotting the data, it's clear that x0 = 0 (the centre of the Gaussian part of the distribution, s = 1 (its stdev, i. e. the distance
    of the "inflection" points of the curve).

    a was read off as the apparent divide between the Gaussian and the polynomial decay, and the interplay of n and a used to match
    the height of the curve (using the fact that reducing n reduces C and hence N).

    Finally, because our data has a tail on the right side, the function definition as given in the assignment had to be flipped
    (i. e. polynomial decay starts at x positive and larger than a, with the base term sign also flipped.

    (s, a, n, x0) = (1, 0.5, 2.2, 0) turns out to be a pretty decent fit.
    */


    // create instance of Crystall Ball function:
    // arguments: xmin, xmax, name, s a n x0
     Crystal f1(-25, 25, "CrystalBall2", 1, 0.5, 2.2, 0);
    // x_sq f1(-5, 5, "x2");

    // "to do (another time)": add checks on the input (that it's valid numbers, xmin < xmax etc.)
    // also to not try and print information before integral is calculated

    std::vector<double> sequence = f1.random_sequence(100000, 0.01); // random sequence generated from this distribution




    // execute plots:

    f1.plotFunction();   
    
    // choose here whether to plot the original file data, or a newly generated sequence (easiest by commenting one of the lines)
    // f1.plotData(data, 100, true); // plot data from file
    f1.plotData(sequence, 100, true); // plot generated random sequence
    
    f1.printInfo();

    /*
    Note: (Conclusion)
    I may have made a mistake in the implementation or understanding of the metropolis argument (can't see where).
    The results are quite bad - they are highly peaked when a sufficiently small width is selected, but the peak
    will randomly occur anywhere (possible initial choice dependence? but xi isn't meant to be reset randomly 
    in each iteration according to the algorithm, right?).
    Anyway, after exploring different regimes I haven't been able to find any good convergence for the sequence generator,
    so either there's a bug in my code, or the method like this isn't very robust.
    */

    

}

