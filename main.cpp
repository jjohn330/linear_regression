/*
    Developer: Justin Johnson
    Date: April 10th, 2018
    Coding Language: C++

    Description: This program applies linear regression to data sets to provide the best fit line for predictive modeling.
    The program takes a number of data set entries and provides input options for the x and y entries for each data point.
    Next, the program calculates basic summary statistical attributes such as mean, standard deviation, variance, etc. The program
    uses this information to convert data using exponential, quadratic, logarithmic, and other models to find the most accurate
    modeling method. Finally, it will give you a summary of the efficiency of each method, the most effective one, and their various
    probabilities of predicting the correct y value (dependent variable) based on the x value (independent variable).

*/
#include <iostream>
#include <math.h>
#include <vector>
#include <sstream>

using namespace std;

double calculate_r(vector<int> x_upd_entries, vector<int> y_upd_entries);

double x_std_dev, y_std_dev, y_mean, x_mean;
int num;

double find_xmean(vector<int> x_entries) { // finds the mean of any x vector being passed in by a regression method function
    double mean = 0;
    for (int i = 0; i < num; i++) {
        mean += x_entries[i];
    }

    return mean/num;
}

double find_ymean(vector<int> y_entries) { // finds the mean of any y vector being passed in by a regression method function
    double mean = 0;
    for (int i = 0; i < num; i++) {
        mean += y_entries[i];
    }

    return mean/num;
}

double find_x_std_dev(vector<int> x_entries, double mean) { // find the x std deviation of any x vector being passed in by a RMF
    double x_var = 0;
    for (int i = 0; i < num; i++) {
        x_var += pow(x_entries[i] - mean, 2);
    }

    x_var = x_var/num;
    return sqrt(x_var);
}

double find_y_std_dev(vector<int> y_entries, double mean) { // finds the y std deviation of any y vector being passed in by a RMF
    double y_var = 0;
    for (int i = 0; i < num; i++) {
        y_var += pow(y_entries[i] - mean, 2);
    }

    y_var = y_var/num;
    return sqrt(y_var);
}

void set_best_r2(double r2, int& best_option, int& counter, double& best_r2) { // finds the most accurate regression method based on the correlation coefficient r
    if (r2 > best_r2) {
        best_r2 = r2;
        best_option = counter;
    }

    counter++;

    return;
}

double apply_linear_reg(vector<string>& regression_list, vector<int> x_entries, vector<int> y_entries) { // standard linear regression method
    double r = calculate_r(x_entries,y_entries);
    double slope = r * y_std_dev/x_std_dev;
    double y_intercept = y_mean - slope*x_mean;

    string regression_line = "y = ";
    ostringstream strs;
    strs << slope;
    string str = strs.str();
    regression_line = regression_line + str + "x + ";
    strs.str("");
    strs << y_intercept;
    str = strs.str();
    regression_line = regression_line + str;
    regression_list.push_back(regression_line);
    return pow(r,2);

}

double apply_exp_model(vector<string>& regression_list, vector<int> x_entries, vector<int> y_entries) { // exponential model for linear regression
    vector<int> y_upd_entries;
    double y_sum = 0;

    for (int i = 0; i < num; i++) {
        y_upd_entries.push_back(log(y_entries[i]));
        y_sum += log(y_entries[i]);
    }

    x_mean = find_xmean(x_entries);
    y_mean = find_ymean(y_upd_entries);
    x_std_dev = find_x_std_dev(x_entries, x_mean);
    y_std_dev = find_y_std_dev(y_entries, y_mean);

    double r = calculate_r(x_entries, y_upd_entries);
    double slope = r * y_std_dev/x_std_dev;
    double y_intercept = sqrt(y_mean) - slope*x_mean;

    string regression_line = " y = 10^(";
    ostringstream strs;
    strs << slope;
    string str = strs.str();
    regression_line = regression_line + str + "x + ";
    strs.str("");
    strs << y_intercept;
    str = strs.str();
    regression_line = regression_line + str + ")";
    regression_list.push_back(regression_line);
    return pow(r,2);
}

double apply_quad_model(vector<string>& regression_list, vector<int> x_entries, vector<int> y_entries) { // quadratic model for linear regression method
    vector<int> y_upd_entries;
    for (int i = 0; i < num; i++) {
        y_upd_entries.push_back(sqrt(y_entries[i]));
    }

    x_mean = find_xmean(x_entries);
    y_mean = find_ymean(y_upd_entries);
    x_std_dev = find_x_std_dev(x_entries, x_mean);
    y_std_dev = find_y_std_dev(y_upd_entries, y_mean);

    double r = calculate_r(x_entries, y_upd_entries);
    double slope = r * y_std_dev/x_std_dev;
    double y_intercept = sqrt(y_mean) - slope*x_mean;

    string regression_line = "y = (";
    ostringstream strs;
    strs << slope;
    string str = strs.str();
    regression_line = regression_line + str + "x + ";
    strs.str("");
    strs << y_intercept;
    str = strs.str();
    regression_line = regression_line + str + ")^2 ";
    regression_list.push_back(regression_line);
    return pow(r,2);
}

double apply_recip_model(vector<string>& regression_list, vector<int> x_entries, vector<int> y_entries) { // reciprocal method for linear regression method
    vector<int> y_upd_entries;
    for (int i = 0; i < num; i++) {
        y_upd_entries.push_back(1/y_entries[i]);
    }

    x_mean = find_xmean(x_entries);
    y_mean = find_ymean(y_upd_entries);
    x_std_dev = find_x_std_dev(x_entries, x_mean);
    y_std_dev = find_y_std_dev(y_upd_entries, y_mean);

    double r = calculate_r(x_entries, y_upd_entries);
    double slope = r * y_std_dev/x_std_dev;
    double y_intercept = 1/y_mean - slope*x_mean;

    string regression_line = " y = 1/(";
    ostringstream strs;
    strs << slope;
    string str = strs.str();
    regression_line = regression_line + str + "x + ";
    strs.str("");
    strs << y_intercept;
    str = strs.str();
    regression_line = regression_line + str + ")";
    regression_list.push_back(regression_line);
    return pow(r,2);

}

double apply_log_model(vector<string>& regression_list, vector<int> x_entries, vector<int> y_entries) { // logarithmic model for linear regression method
    vector<int> x_upd_entries;
    for (int i = 0; i < num; i++) {
        x_upd_entries.push_back(log(x_entries[i]));
    }

    x_mean = find_xmean(x_upd_entries);
    y_mean = find_ymean(y_entries);
    x_std_dev = find_x_std_dev(x_upd_entries, x_mean);
    y_std_dev = find_y_std_dev(y_entries, y_mean);

    double r = calculate_r(x_upd_entries, y_entries);
    double slope = r * y_std_dev/x_std_dev;
    double y_intercept = y_mean * slope*log(x_mean);

    string regression_line = "y = ";
    ostringstream strs;
    strs << slope;
    string str = strs.str();
    regression_line = regression_line + str + "log(x) + ";
    strs.str("");
    strs << y_intercept;
    str = strs.str();
    regression_line = regression_line + str;
    return pow(r,2);
}

double calculate_r(vector<int> x_upd_entries, vector<int> y_upd_entries) { // finds correlation coefficient (the numerical relationship between y and x)
    double sum = 0;
    double zscore_x, zscore_y;

    for (int i = 0; i < num; i++) {
        zscore_x = (x_upd_entries[i] - x_mean)/x_std_dev;
        zscore_y = (y_upd_entries[i] - y_mean)/y_std_dev;

        sum += zscore_x * zscore_y;
    }

    sum = sum/num;

    return sum;
}

int main()
{
    cout << "Enter the number of entries for the data set: ";
    cin >> num;

    vector<int> x_entries;
    vector<int> y_entries;

    cout << "Enter each x value (independent variable) for each data entry: " << endl;

    double value, y_sum = 0, x_sum = 0;

    for (int i = 0; i < num; i++) {
        cin >> value;
        x_sum += value;
        x_entries.push_back(value);
    }

    cout << "Enter each y value (dependent variable) for each data entry: " << endl;

    for (int i = 0; i < num; i++) {
        cin >> value;
        y_sum += value;
        y_entries.push_back(value);
    }

    y_mean = y_sum/num;
    x_mean = x_sum/num;

    double y_var = 0, x_var = 0;

    for (int i = 0; i < num; i++) {
        y_var += pow(y_entries[i] - y_mean,2);
        x_var += pow(x_entries[i]- x_mean, 2);
    }

    y_var = y_var/num;
    x_var = x_var/num;
    y_std_dev = sqrt(y_var);
    x_std_dev = sqrt(x_var);

    double r2;
    double best_r2 = 0;
    int best_option = 0, counter = 0;

    vector<string> regression_list;

    r2 = apply_linear_reg(regression_list, x_entries, y_entries);
    set_best_r2(r2,best_option,counter,best_r2);

    cout << "Standard: " << r2 << endl;

    r2 = apply_exp_model(regression_list, x_entries, y_entries);
    set_best_r2(r2,best_option,counter,best_r2);

    cout << "Exp model: " << r2 << endl;

    r2 = apply_quad_model(regression_list,x_entries,y_entries);
    set_best_r2(r2,best_option,counter,best_r2);

    cout << "Quad model: " << r2 << endl;

    r2 = apply_recip_model(regression_list,x_entries,y_entries);
    set_best_r2(r2,best_option,counter,best_r2);

    cout << "Recip model: " << r2 << endl;

    r2 = apply_log_model(regression_list,x_entries,y_entries);
    set_best_r2(r2, best_option,counter,best_r2);

    cout << "Log model: " << r2 << endl;

    switch(best_option+1) { // gives the best model for the data set in question and provides its effectiveness
        case 1: cout << "The standard linear regression model is the best regression method for the data set " << endl;
                cout << regression_list[best_option] << " with a coefficient of determination of " << best_r2 << endl;
                break;
        case 2: cout << "The exponential method is the best regression method for the data set " << endl;
                cout << regression_list[best_option] << " with a coefficient of determination of " << best_r2 << endl;
                break;
        case 3: cout << "The quadratic model is the best regression method for the data set " << endl;
                cout << regression_list[best_option] << " with a coefficient of determination of " << best_r2 << endl;
                break;
        case 4: cout << "The reciprocal model is the best regression method for the data set " << endl;
                cout << regression_list[best_option] << " with a coefficient of determination of " << best_r2 << endl;
                break;
        case 5: cout << "The logarithmic model is the best regression method for the data set " << endl;
                cout << regression_list[best_option] << " with a coefficient of determination of " << best_r2 << endl;
                break;
    }
    return 0;
}
