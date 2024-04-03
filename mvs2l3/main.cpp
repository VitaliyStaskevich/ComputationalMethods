#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

const double  a = 6;
const double  b = 9;
const double  I = M_PI;
const double eps= pow(10,-7);

const int precision = 12;
enum Func{
    middle,
    simpson
};

double F(double x)
{
    return sqrt((9-2*x)/(2*x-21));
}


double middleRectangles(int N)
{
    double h = (b-a)/N;
    double prod = h;
    double xi=a;
    double sum {};
    for(int i=0; i<N; i++)
    {
         sum += F(xi+h/2);
         xi += h;
    }

    prod*=sum;
    return prod;
}

double Simpson(int N)
{

    double h = (b-a)/N;
    double prod = h/6;
    double xi = a;
    double sum = 0;
    for(int i=0; i<N; i++)
    {
         sum += F(xi);
         sum += 4* F(xi+h/2);
         sum += F(xi+h);
         xi += h;
    }

    prod *=sum;
    return prod;

}

double Runge(Func func)
{

    double h = (b-a)/2;
    if(func == middle)
    {
        ofstream fout("MiddleRect.txt");
        fout << "Middle Rectangle Form; ; ; ; ;";
        fout << "Divisions;" << "Step;" << "Approximation;" << "Error assesment;" << "Abs error;";
        double m = 2;
        double Qprev = middleRectangles(2);
        fout << "N = 2;" << "h=(b-a)/2;";
        fout << "Q_h = " << Qprev << ";";
        fout << "—;" << abs(I-Qprev)<<";";
        double Qcurr = middleRectangles(4);
        double denom = pow(2,m) - 1;
        double R = abs((Qcurr-Qprev)/denom);
        fout << "N = 4;" << "h=(b-a)/4;";
        fout << "Q_h/2 = " << Qcurr << ";";
        fout << "R_h/2 = " << R << ";" << abs(I-Qcurr)<<";";
        double k = 8;
        while(R >=eps)
        {
            Qprev = Qcurr;
            Qcurr = middleRectangles(k);
            k*=2;
            R = abs((Qcurr-Qprev)/denom);

            fout << "N = " << k << ";" << "h=(b-a)/" << k << ";";
            fout << "Q_h/"<< k/2 << " = " << setprecision(precision) << Qcurr << ";";
            fout << "R_h/"<< k/2 << " = " << R << ";" << abs(I-Qcurr)<<";";
        }
        fout.close();
        return Qcurr;
    }
    else
    {
        ofstream fout("Simpson.txt");
        fout << "Simpson Form; ; ; ; ;";
        fout << "Divisions;" << "Step;" << "Approximation;" << "Error assesment;" << "Abs error;";
        double m = 4;
        double Qprev = Simpson(2);
        fout << "N = 2;" << "h=(b-a)/2;";
        fout << "Q_h = " << Qprev << ";";
        fout << "—;" << abs(I-Qprev)<<";";
        double Qcurr = Simpson(4);
        double denom = pow(2,m) - 1;
        double k = 8;
        double R = abs((Qcurr-Qprev)/denom);
        fout << "N = 4;" << "h=(b-a)/4;";
        fout << "Q_h/2 = " << Qcurr << ";";
        fout << "R_h/2 = " << R << ";" << abs(I-Qcurr)<<";";
        cout << R << endl << eps;
        while(R >= eps)
        {
            Qprev = Qcurr;
            Qcurr = Simpson(k);
            k*=2;
            R = abs((Qcurr-Qprev)/denom);
            fout << "N = " << k << ";" << "h=(b-a)/" << k << ";";
            fout << "Q_h/"<< k/2 << " = " << setprecision(precision) << Qcurr << ";";
            fout << "R_h/"<< k/2 << " = " << R << ";" << abs(I-Qcurr)<<";";
        }
        fout.close();
        return Qcurr;
    }
}
int main()
{
    Runge(middle);
    Runge(simpson);
    return 0;
}
