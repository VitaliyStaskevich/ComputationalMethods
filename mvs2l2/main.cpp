#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

const double  a = -3;
const double  b =  3;
const int N = 15;
struct SplineSet{
    vector <double> a;
    vector <double> b;
    vector <double> c;
    vector <double> x;
};

double F(double x)
{
    return x*x*cos(2.0*x);
}

double derF(double x)
{
    return 2.0*x*(cos(2.0*x)-x*sin(2.0*x));
}

double cond1 = derF(a);
double cond2 = derF(b);

SplineSet contructSOLAE(vector <double>& x, vector <double>& y)
{
    double h =x[1]-x[0];
    double n = x.size();
    vector <double> a(n,0);
    vector <double> b(n,0);
    vector <double> c(n,0);
    vector <double> xNew(n,0);
    for(int i=1; i<n-1; i++)
    {
        b[i]=h/6.0;
        a[i]= (2.0*h)/3.0;
        c[i]= h/6.0;

        xNew[i] = ((y[i+1]-y[i])/h) - ((y[i]-y[i-1])/h);
    }
    ///Additional conditions
    c[0] = h/6.0;
    a[0] = h/3.0;
    xNew[0] = ((y[1]-y[0])/h) - cond1;
    ///
    b[n-1] = h/6.0;
    a[n-1] = h/3.0;
    xNew[n-1] = cond2 - (y[n-1]-y[n-2])/h;


    SplineSet outputSet{a,b,c,xNew};
    return outputSet;
}

void fillPoints(vector <double>& x, vector <double>& y)
{
    x.resize(N+1);
    y.resize(N+1);
    for(int i=0; i<=N; i++)
    {
        double h = (b-a)/N;
        x[i]=a+i*h;
        y[i]=F(x[i]);
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


vector<double> solveTridiagonal(vector<double>& A_diag, vector<double>& A_upper, vector<double>& A_lower, vector<double>& b)
{
    int N = A_diag.size();
    vector<double> a(N);
    vector<double> B(N);
    vector<double> matRes(N);

    double y = A_diag[0];
    a[0] = -A_upper[0] / y;
    B[0] = b[0] / y;

    for (int i = 1; i < N; ++i)
    {
        y = A_diag[i] + A_lower[i - 1] * a[i - 1];
        a[i] = -A_upper[i] / y;
        B[i] = (b[i] - A_lower[i - 1] * B[i - 1]) / y;
    }

    matRes[N - 1] = (b[N - 1] - A_lower[N - 2] * B[N - 2]) / (A_diag[N - 1] + A_lower[N - 2] * a[N - 2]);

    for (int i = N - 2; i >= 0; --i)
    {
        matRes[i] = a[i] * matRes[i + 1] + B[i];
    }

    return matRes;
}

int Range(double x)
{
    int range = ((x - a)/((b-a)/N)) + 1;
    if(range>N) range = N;
    if(range<1) range = 1;
    return range;
}

double computeValue(vector<double>& M, double point, vector <double>& x, vector <double>& y)
{
    int i = Range(point);
    double h =x[1]-x[0];
    ///
    double value = M[i-1] * (pow((x[i]-point),3)/(6.0*h));
    value += M[i] * (pow((point - x[i-1]),3)/(6.0*h));
    value +=(y[i-1]- ((h*h)/6.0)*M[i-1]) * (x[i]-point)/h;
    value +=(y[i]- ((h*h)/6.0)*M[i]) * (point-x[i-1])/h;
    ///
    return value;
}

void output(vector<double>& x, vector<double>&y, string name)
{
    ofstream fout(name);
    for(int i=0; i<x.size(); i++)
    {
        fout << x[i] << ' ' << y[i] << endl;
    }
    fout.close();
}


double err(vector<double>& x, vector<double>&y)
{
    double maximum = INT_MIN;
    for(int i=0; i<x.size();i++)
    {
        if(abs(y[i]-F(x[i]))>maximum)
        {
            maximum = abs(y[i]-F(x[i]));
        }
    }
    return maximum;
}


void runErrors(vector<double>& x, vector<double>&y, string name)
{
    ofstream fout(name);
    for(int i=0; i<x.size();i++)
    {
        fout << x[i] << ' ' << abs(y[i]-F(x[i])) << endl;
    }
    fout.close();
}

void runSpline(string name)
{
    vector <double> x;
    vector <double> y;
    fillPoints(x,y);
    SplineSet spline = contructSOLAE(x,y);
    vector <double> M = solveTridiagonal(spline.a,spline.c,spline.b,spline.x);

    vector <double> Xi(101);
    for(int i=0; i<Xi.size(); i++)
    {
        Xi[i]=a+(i*(b-a))/100;
    }

    vector <double> SXi(101);
    for(int i=0; i<Xi.size();i++)
    {
        SXi[i]=computeValue(M,Xi[i],x,y);
    }
    output(Xi,SXi,name);

    double error = err(Xi, SXi);
    cout << "Maximum absolute value of the error at [" << a <<','<< b << "] is " << error;
    runErrors(Xi, SXi, "errors.txt");
}
int main()
{
    runSpline("Spline.txt");
    return 0;
}
