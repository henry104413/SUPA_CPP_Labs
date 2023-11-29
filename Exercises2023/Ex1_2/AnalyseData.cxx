// Henry Jindrich Hajek, jh109@hw.ac.uk
// SUPA C++ course, assessment 1

#include "CustomFunctions.h"


int main()
{


// filenames:
std::string data_file = "input2D_float.txt";
std::string error_file = "input2D_float.txt";

// import data:
x_vect_y_vect_pair data = import_data(data_file);
x_vect_y_vect_pair errors = import_data(error_file);



// user controlled processing:
// note: user control over output and input could be added as needed,
// including file paths, conditional processing (only if data loaded) etc...

std::cout << "Data loaded, now choose an option!";
char choice;
while(true)
{
    std::cout << "\n\nOptions:\nA...print data\nB...fit data to line\nC...power x to y-nearest-integer\nD...exit\n...";
    std::cin >> choice;
    switch(choice)
        {
        case 'A': case 'a':  // print
            {
                // choose number of datapoints:
                // (assumes valid input)
                std::cout << "\nPrinting... how many datapoints? ";
                int up_to;
                std::cin >> up_to;

                print_data(data, up_to);
    
                break;
            }
        
        case 'B': case 'b':  // fit
            {
                std::cout << "\nFitting...\n";

                // perform the fit and evaluate chi2:
                fit_parameters my_fit = LSfit(data);
                double my_chi2 = chi2(data, errors, my_fit);

                // note: tried to format the output to limit the number of significant figures
                // but not working - apparently <format> isn't installed here...
                /*std::string linear_fit_output = "y = " + std::format("{:.3f}", my_fit.p)
                + "x + " + std::format("{:.3f}", my_fit.q) + ", chi2 = " +
                std::format("{:.3f}", my_chi2);*/
                
                std::string linear_fit_output = "y = " + std::to_string(my_fit.p)
                + "x + " + std::to_string(my_fit.q) + ", chi2 = " +
                std::to_string(my_chi2);

                std::cout << "Linear data fit is:" << linear_fit_output << std::endl;

                if (true) // swich on/off result output to textfile

                    {
                    std::ofstream fout;
                    fout.open("line_fit.txt");
                    if (fout.fail()) {std::cout << "Couldn't save fit...\n";}
                    fout << linear_fit_output;
                    fout.close();
                    }

                break;
            }


        case 'C': case 'c':  // power
            {
                std::cout << "\nPowers...\n";
                
                // file output stream:
                std::ofstream fout;
                fout.open("powers.txt");
                if (fout.fail()) {std::cout << "Couldn't save powers...\n";}
                
                // note: this doesn't seem to have anything to do with the data,
                // hence performed on an arbitrary set as a test
                // including file output

                int samples = 5;
                double xs[5] = {2, 3, 6.8, -1, -1};
                double ys[5] = {2.8, 2.2, 5, 5, 6};
                for (int i = 0; i < 5; i++)
                    {
                    std::cout << xs[i] << "^" << round(ys[i]) << " = " 
                    << integer_power(xs[i], ys[i]) << std::endl;

                    fout << xs[i] << "^" << round(ys[i]) << " = " 
                    << integer_power(xs[i], ys[i]) << std::endl;
                    
                    }
        
                
                fout.close();
                break;
            }


        case 'D': case 'd':  // exit
            {
                return 0;
            }

        default: std::cout << "Invalid choice!\n";    
        } 
}

// for testing:
//print_data(data, 4);
//std::cout << magnitude(2,-2) << std::endl;
//std::cout << integer_power(3.3,2.8) << std::endl;





return 0;
}

/* command to compile and run in terminal:
g++ -std=c++20 -w AnalyseData.cxx CustomFunctions.cxx -o Output
./Output
*/

