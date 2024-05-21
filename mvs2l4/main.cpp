#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

double f(double x, double u)
{
    return (u*u+u*x)/(x*x);
}

double fprime(double x, double u)
{
    return (x+2.0*u)/(x*x);
}

double exactSolution(double x)
{
 return x/(2-log(x));
}


struct point{

    double x;
    double y;

    void print() const {
         cout << "| " <<  setw(8) <<  setprecision(5) << x << " | " <<  setw(8) <<  setprecision(5) << y << " |" << setw(12) <<  setprecision(5) << abs(y-exactSolution(x))  << "|"<< endl;
    }
};

void printHeader(string header){
    cout << header << endl;
    cout << "| " << setw(8) << "x" << " | " << setw(8) << "y" << " |" << setw(11) << "Deviation" << " |" << endl;
}

const double u0 = 0.5;
double h = 0.1;
const double a = 1.0;
const double b = 2.0;
const double eps= pow(10,-6);
///
void printVector(vector<double>& vec, int precision = 4)
{
    int width = 8;

    for (const auto& element : vec)
    {
        cout << setw(width) << setprecision(precision) << fixed << element << endl;
    }
}
///
vector <point> calculateExactSolutions(){
    vector <point> solution;
    double x = a;
    while (x<=b+h)
    {
        solution.push_back({x,exactSolution(x)});
        x+=h;
    }
    return solution;
}
vector <point> midpointMethod()
{
    vector<point> solution;
    double x = a;
    double y = u0;
    solution.push_back({x,y});
    while (x < b)
    {
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2, y + k1 / 2);
        y += k2;
        x += h;
        solution.push_back({x, y});
    }
    return solution;
}


vector <point> implicitTrapezoidalMethod()
{
    vector<point> solution;
    double x = a;
    double y = u0;
    solution.push_back({x,y});

    while (x < b)
    {
        double y_next = y;
        double x_next = x + h;
        while(true)
        {
            double numerator = y_next - y - ((h / 2.0) * (f(x, y) + f(x_next, y_next)));
            double denominator = 1 - (h / 2.0)*fprime(x_next,y_next);
            double delta = numerator/denominator;
            y_next -= delta;
            if(abs(delta)<eps) break;
        }
        y = y_next;
        x = x_next;
        solution.push_back({x, y});
    }
    return solution;
}

/*vector <point> adamsBashforthMethod()
{
    vector<point> solution;
    double x = a;
    double y = u0;
    solution.push_back({x,y});

    ///RK2
    double k1 = h * f(x, y);
    double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
    y += k2;
    x += h;
    solution.push_back({x, y});
    ///ABM
    while (x < b)
    {
        double x_prev = solution[solution.size() - 2].x;
        double y_prev = solution[solution.size() - 2].y;
        double f_n = f(x, y);
        double f_n_prev = f(x_prev, y_prev);

        double yExpl = y + (h / 2.0) * (3.0 * f_n - f_n_prev);
        ///корректорный
        x += h;
        double yImpl = y + (h/2.0)*(f(x,y)+f_n);
        y = yImpl;
        solution.push_back({x, y});
    }
     return solution;

}
*/
vector <point> adamsBashforthMethod()
{
 vector<point> solution;
    double x = a;
    double y = u0;
    solution.push_back({x, y});

    ///RK2
    double k1 = h * f(x, y);
    double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
    y += k2;
    x += h;
    solution.push_back({x, y});

    ///ABM
    while (x < b) {


        double x_prev = solution[solution.size() - 2].x;
        double y_prev = solution[solution.size() - 2].y;
        double f_n_prev = f(x_prev, y_prev);
        double f_n = f(x, y);

        /// Predictor
        double yPred = y + (h / 2.0) * (3.0 * f_n - f_n_prev);

        /// Corrector
        double f_nPred = f(x + h, yPred);
        double yCorr = y + (h / 2.0) * (f_n + f_nPred);
        x += h;
        y = yCorr;

        solution.push_back({x, y});
    }

    return solution;
}

double err(vector<point>& solution)
{
    double maximum = INT_MIN;
    for(int i=0; i<solution.size();i++)
    {
        if(abs(solution[i].y-exactSolution(solution[i].x)) > maximum)
        {
            maximum = abs(solution[i].y-exactSolution(solution[i].x));
        }
    }
    return maximum;
}

void output(vector <point> &res, string name)
{
    ofstream fout(name);
    for(int i=0; i<res.size(); i++)
    {
        fout << res[i].x << ' ' << res[i].y << endl;
    }
    fout.close();
}


struct RungeErrors{
    double MPM;
    double ITM;
    double ABM;
};

/*
RungeErrors Runge(vector<point>& MPM,
                  vector<point>& ITM,
                  vector<point>& ABM){
    h/=2;
    vector <point> resultMPM2 = midpointMethod();
    vector <point> resultITM2 = implicitTrapezoidalMethod();
    vector <point> resultABM2 = adamsBashforthMethod();
    double maxMPM = INT_MIN;
    double maxITM = INT_MIN;
    double maxABM = INT_MIN;
    for(int i = 0; i<resultMPM2.size(); i+=2)
    {
        if(abs((MPM[i/2].y-resultMPM2[i].y)/3)>maxMPM) maxMPM = abs(MPM[i/2].y-resultMPM2[i].y)/3;
        if(abs((ITM[i/2].y-resultITM2[i].y)/3)>maxITM) maxITM = abs(ITM[i/2].y-resultITM2[i].y)/3;
        if(abs((ABM[i/2].y-resultABM2[i].y)/3)>maxABM) maxABM = abs(ABM[i/2].y-resultABM2[i].y)/3;
    }
    return {maxMPM, maxITM, maxABM};
}
*/

RungeErrors Runge(vector<point>& MPM,
                  vector<point>& ITM,
                  vector<point>& ABM){
    h*=2;
    vector <point> resultMPM2 = midpointMethod();
    vector <point> resultITM2 = implicitTrapezoidalMethod();
    vector <point> resultABM2 = adamsBashforthMethod();
    double maxMPM = INT_MIN;
    double maxITM = INT_MIN;
    double maxABM = INT_MIN;
    for(int i = 0; i<MPM.size(); i+=2)
    {
        if(abs((MPM[i].y-resultMPM2[i/2].y)/3)>maxMPM) maxMPM = abs(MPM[i].y-resultMPM2[i/2].y)/3;
        if(abs((ITM[i].y-resultITM2[i/2].y)/3)>maxITM) maxITM = abs(ITM[i].y-resultITM2[i/2].y)/3;
        if(abs((ABM[i].y-resultABM2[i/2].y)/3)>maxABM) maxABM = abs(ABM[i].y-resultABM2[i/2].y)/3;
    }
    return {maxMPM, maxITM, maxABM};
}
void constuctTable(string name,
                  vector<point>& MPM,
                  vector<point>& ITM,
                  vector<point>& ABM,
                  vector<point>& exact,
                  RungeErrors errors)
{
    ofstream fout(name);
    ///header
    fout << "i;x_i;Exact solution;Numerical solution for 0.1 step; ; ; ; ; ; MPM;ITM;ABM; ; ; u(x_i); y_i; y_i; y_i;";
    for(int i=0; i<MPM.size(); i++)
    {
        fout << i <<";" << MPM[i].x << ";"<<exact[i].y<<";"<<
        MPM[i].y<<";"<<ITM[i].y<<";"<<ABM[i].y<<";";
    }
    fout << "max (abs(u(x_i)-y_i)); ; ;" << err(MPM) << ";"<< err(ITM) << ";"<< err(ABM) << ";";
    fout << "Runge Method error assesment; ; ;" << errors.MPM << ";" <<errors.ITM << ";" <<errors.ABM;
}
int main()
{
    ///
    vector <point> resultMPM = midpointMethod();
    printHeader("Midpoint Method:");
    for(int i = 0; i < resultMPM.size(); ++i)
    {
         resultMPM[i].print();
    }
    cout << "The biggest deviation: \n" <<err(resultMPM) << endl;

    ///
    vector <point> resultITM = implicitTrapezoidalMethod();
    printHeader("Trapezoidal Method:");
    for(int i = 0; i < resultITM.size(); ++i)
    {
        resultITM[i].print();
    }
    cout << "The biggest deviation: \n" <<err(resultITM) << endl;

    ///
    vector <point> resultABM = adamsBashforthMethod();
    printHeader("Adams Method:");
    for(int i = 0; i < resultABM.size(); ++i)
    {
        resultABM[i].print();
    }
    cout << "The biggest deviation: \n" <<err(resultABM) << endl;
    output(resultMPM, "MPM.txt");
    output(resultITM, "ITM.txt");
    output(resultABM, "ABM.txt");

    vector <point> exact = calculateExactSolutions();
    output(exact, "exact.txt");

    RungeErrors errrors = Runge(resultMPM,resultITM,resultABM);
    constuctTable("Table.txt",resultMPM,resultITM, resultABM,exact,errrors);
    return 0;
}
