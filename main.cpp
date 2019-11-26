#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <random>


using namespace std;
static mt19937 generator{random_device{}()};

double Function(double x, int key) {
    if (key == 0)
        return -2 * sqrt(x) * sin(0.5 * x);
    else if (key == 1)
        return -2 * sqrt(x) * sin(0.5 * x) * sin(5 * x);
}


void simulatedAnnealing(int key) {
    double a = 2.0, b = 6.0;
    auto distance = std::uniform_real_distribution<double>(a, b);
    auto temp = std::uniform_real_distribution<double>(0, 1);
    double xmin = distance(generator);
    double tmax = 10000, tmin = 0.01;
    cout << "  N         T         x         f(x)                      P         accept?" << endl;
    int i = 1;
    string str = "";
    while (tmax > tmin) {
        double Xi = distance(generator);
        double difference = Function(Xi, key) - Function(xmin, key);
        double probability=0.0;
        str = "N";
        if (difference <= 0) {
            xmin = Xi;
            str = "Y";
            probability = 1;
        }
        else {
            double temp1 = temp(generator);
            probability = exp(-difference / tmax);
            str = "N";
            if (temp1 < probability) {
                xmin = Xi;
                str = "Y";
            }
        }
        if (i < 10)
            cout << "  " << i << setw(12) << std::fixed <<std::setprecision(4) <<  tmax << setw(12) << xmin << setw(12) << Function(xmin, key) << setw(20) << setprecision(3) << probability << setw(12) << str << endl;
        else if (i < 100)
            cout << " " << i << setw(12) << std::fixed  << std::setprecision(4) << tmax << setw(12) << xmin << setw(12) << Function(xmin, key) << setw(20) << probability << setw(12) << str << endl;
        else
            cout << i << setw(12) << std::fixed << std::setprecision(4) << tmax << setw(12) << xmin << setw(12) << Function(xmin, key) << setw(20) << probability << setw(12) << str << endl;
        tmax *= 0.95;
        i++;
    }
    cout << "\n\nResult: xmin: " << xmin << " ;Fmin= " << Function(xmin, key) << endl;
}

int main() {
    cout << "Unimodal function:" << endl;
    simulatedAnnealing(0);
    cout << endl << endl << "Multimodal function:" << endl;
    simulatedAnnealing(1);


    return 0;
}