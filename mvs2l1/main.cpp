#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

const double a = -3;
const double b = 3;

double F1(double x)
{
    return x*x*cos(2*x);
}

double F2(double x)
{
    return 1/(1+5*x*x);
}

void fillValuesEquidistant(vector <double>& X, vector <double>& Y, int N, int func=1)
{
    double step = (b - a) / (N-1);
    for(int i=0; i<N; ++i)
    {
        X[i] = (a+i*step);
        if(func==1)
        {
            Y[i] = F1(X[i]);
        }
        if(func==2)
        {
            Y[i] = F2(X[i]);
        }
    }
}

void fillValuesChebyshev(vector <double>& X, vector <double>& Y, int N, int func=1)
{
    for(int i=0; i<N; ++i)
    {
        double theta = (2.0 * i + 1.0) * M_PI / (2.0 * N);
        X[i] =(a+b)/2.0 + (b-a)/2.0 * cos(theta);
        if(func==1)
        {
            Y[i] = F1(X[i]);
        }
        if(func==2)
        {
            Y[i] = F2(X[i]);
        }
    }
}

void printVector(vector<double>& vec, int precision = 4)
{
    int width = 8;

    for (const auto& element : vec)
    {
        cout << setw(width) << setprecision(precision) << fixed << element << endl;
    }
}

void printMatrix(vector<vector<double>>& matrix, int precision =4)
{
    for (const auto& row : matrix)
    {
        for (const auto& element : row)
        {
            cout << setw(8) << fixed << setprecision(precision) << element;
        }
        cout << endl;
    }
    cout << endl;
}
pair<vector<double>,vector<double>> interpolate(vector<double>&X,vector<double>&Y)
{
     ///constructing the DD table
     vector<vector<double>> DDTable(X.size(),vector<double>(X.size()));
     for (int i = 0; i < X.size(); i++)
     {
        DDTable[i][0] = Y[i];
     }
     for (int j = 1; j < X.size(); j++)
     {
            for (int i = 0; i < X.size() - j; i++)
            {
                DDTable[i][j] = (DDTable[i + 1][j - 1] - DDTable[i][j - 1]) /(X[i + j] - X[i]);
            }
    }

    //printMatrix(DDTable);


    vector <double> Xi(101);
    for(int i=0; i<Xi.size(); i++)
    {
        Xi[i]=a+(i*(b-a))/100;
    }

    ///computing values at Xi`s
    vector <double> PXi(101);
    for(int i=0; i<Xi.size(); i++)
    {
        double res = DDTable[0][0];
        double term = 1.0;
        for(int j = 1; j<X.size();j++)
        {
            term*=(Xi[i]-X[j-1]);
            res+=DDTable[0][j] * term;
        }
        PXi[i]=res;
    }
    return {Xi,PXi};
}

void output(pair<vector<double>,vector<double>>& res, string name)
{
    ofstream fout(name);
    for(int i=0; i<res.first.size(); i++)
    {
        fout << res.first[i] << ' ' << res.second[i] << endl;
    }
    fout.close();
}

double err(pair<vector<double>,vector<double>>& res, int func)
{
    double maximum = INT_MIN;
    if(func == 1)
    {
        for(int i=0; i<res.first.size();i++)
        {
            if(res.second[i]-F1(res.first[i]) > maximum)
            {
                maximum = res.second[i]-F1(res.first[i]);
            }
        }
    }
    else
    {
        for(int i=0; i<res.first.size();i++)
        {
            if(res.second[i]-F2(res.first[i]) > maximum)
            {
                maximum = res.second[i]-F2(res.first[i]);
            }
        }
    }
    return maximum;
}
void logError(double error, int n, int func, bool cheb)
{
    cout << "The error in interpolation with n = " << n << " of function " << func << " using ";
    if(cheb)
        cout << "Chebyshev nodes ";
    else
        cout << "Equidistant nodes ";
    cout << "is " << error << endl;
}
void runInterpolation(int n, int func, bool cheb, string name)
{
    vector <double> X(n);
    vector <double> Y(n);
    if(cheb)
        fillValuesChebyshev(X,Y,X.size(),func);
    else
        fillValuesEquidistant(X,Y,X.size(),func);
    pair<vector<double>,vector<double>> res = interpolate(X,Y);
    output(res, name);
    logError(err(res,func),n,func,cheb);
}
int main()
{
    ///Function 1
    runInterpolation(3,1,0,"equid1-3.txt");
    runInterpolation(3,1,1,"cheb1-3.txt");
    runInterpolation(10,1,0,"equid1-10.txt");
    runInterpolation(10,1,1,"cheb1-10.txt");
    runInterpolation(20,1,0,"equid1-20.txt");
    runInterpolation(20,1,1,"cheb1-20.txt");

    ///Function 2
    runInterpolation(3,2,0,"equid2-3.txt");
    runInterpolation(3,2,1,"cheb2-3.txt");
    runInterpolation(10,2,0,"equid2-10.txt");
    runInterpolation(10,2,1,"cheb2-10.txt");
    runInterpolation(20,2,0,"equid2-20.txt");
    runInterpolation(20,2,1,"cheb2-20.txt");
    return 0;
}
