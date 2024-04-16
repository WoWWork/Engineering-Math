#include <math.h>
#include <complex.h>
#include <vector>
#include <iostream>

using namespace std;

double determine(vector<double>, int);
void arrange(vector<int>, int);
void swap(vector<int>, int, int);
vector<vector<int>> uni(vector<vector<int>>);
double multi(vector<double>, int);
vector<complex<double>> eigvalues(vector<double>, int);
void select_cross(vector<int>, int, int, int);
double pick_elements(vector<double>, int, int);
vector<double> polynomial(vector<double>, int);
vector<complex<double>> dpolynomial(vector<complex<double>>);
complex<double> newton(vector<complex<double>>, vector<complex<double>>);
complex<double> powf(vector<complex<double>>, complex<double>);
vector<complex<double>> dividf(vector<complex<double>>, vector<complex<double>>);

vector<vector<int>> gather;
vector<vector<int>> C;

int main(int argc, char *argv[])
{
    vector<double> arr;
    for (int x = 1; x < argc; x++) arr.push_back(stod(argv[x]));
    double square = arr.size();
    double len = sqrt(square);
    if (fabs(len - (int)len) > 1e-5) return -1;
    vector<complex<double>> roots = eigvalues(arr, (int)len);
    // cout << "eigvalues number is " << ans << endl;
    return 0;
}

vector<complex<double>> eigvalues(vector<double> mat, int level)
{
    vector<double> poly;
    vector<complex<double>> polyC;
    vector<complex<double>> dpolyC;
    vector<complex<double>> roots;
    poly = polynomial(mat, level);   
    for(int i = 0; i < poly.size(); i++) polyC.push_back(complex<double>(poly[i], 0.0));
    for(int i = 0; i < poly.size() - 1; i++)
    {
        dpolyC = dpolynomial(polyC);
        complex<double> root = newton(polyC, dpolyC);
        root.real(abs(root.real() - round(root.real())) > 2e-4 ? root.real() : round(root.real()));
        root.imag(abs(root.imag() - round(root.imag())) > 2e-4 ? root.imag() : round(root.imag()));
        roots.push_back(root);
        cout << root.real() << " " << root.imag() << endl;
        vector<complex<double>> dvecC = {complex<double>(-root.real(), -root.imag()), complex<double>(1.0, 0)};
        polyC = dividf(polyC, dvecC);
        //for(int x = 0; x < polyC.size(); x++) cout << polyC[x].real() << " " << polyC[x].imag() << " ";
        //cout << endl;
    } 
    return roots;
}

vector<complex<double>> dividf(vector<complex<double>> vec, vector<complex<double>> dvec)
{
    complex<double> factor;
    vector<complex<double>> result;
    for(int i = vec.size() - 1; i >= dvec.size() - 1; i--)
    {
        factor = vec[i] / dvec[dvec.size() - 1];
        //cout << factor.real() << " " << factor.imag() << " " << endl;
        for(int j = 0; j < dvec.size(); j++)
        {
            vec[i - j] -= factor * dvec[dvec.size() - 1 - j];
        }
        if(factor != complex<double>(0.0, 0.0)) result.insert(result.begin(), factor);
        else break;
    }
    return result;
}

complex<double> powf(vector<complex<double>> vec, complex<double> n)
{
    complex<double> ans;
    for(int x = 0; x < vec.size(); x++)
    {
        ans += vec[x] * pow(n, x);
    }
    return ans;
}

complex<double> newton(vector<complex<double>> func, vector<complex<double>> dfunc)
{
    complex<double> n0 = complex<double>(1, 1);
    complex<double> n1 = n0 - (f(func, n0) / f(dfunc, n0));
    for(int i = 0; i < 1000; i++)
    {
        n0 = n1;
        n1 = n0 - f(func, n0) / f(dfunc, n0);
        if(norm(n1 - n0) < 1e-8) break;
    }
    return n1;
}

vector<double> polynomial(vector<double> mat, int level)
{
    double totalC;
    vector<int> vec;
    vector<double> result;
    result.push_back(determine(mat, level));
    for (int x = 1; x < level - 1; x++)
    {
        totalC = 0.0;
        gather.clear();
        C.clear();
        select_cross(vec, 0, x, level);
        for (int y = 0; y < C.size(); y++) totalC += pick_elements(mat, y, level);
        result.push_back(totalC);
        /*
        for (int i = 0; i < C.size(); i++)
        {
            for (int j = 0; j < C[i].size(); j++) cout << C[i][j] << " ";
            cout << endl;
        }
        */
    }
    totalC = 0.0;
    for(int tr = 0; tr < level; tr++) totalC += mat[tr * level + tr];
    result.push_back(totalC);
    result.push_back(1.0);
    int direct = 1;
    for(int a = result.size() - 1; a >= 0; a--) 
    {
        result[a] *= direct;
        direct *= -1; 
    }
    //for(int a = 0; a < result.size(); a++) cout << result[a] << " ";
    //cout << endl;
    return result;
}

vector<complex<double>> dpolynomial(vector<complex<double>> vec)
{
    vector<complex<double>> result;
    double power = 1.0;
    for(int i = 1; i < vec.size(); i++)
    {
        result.push_back(vec[i] * power);
        power++;
        //cout << result[i - 1] << " ";
    }
    //cout << endl;
    return result;
}

void select_cross(vector<int> vec, int idx, int len, int level)
{
    for (int i = idx; i < level; i++)
    {
        vec.push_back(i);
        if (vec.size() < len) select_cross(vec, i + 1, len, level);
        else C.push_back(vec);
        vec.pop_back();
    }
}

double pick_elements(vector<double> mat, int idx, int level)
{
    bool flag;
    int row, col;
    double result;
    vector<double> det;
    for (int j = 0; j < mat.size(); j++)
    {
        flag = false;
        row = j % level;
        col = j / level;
        for (int i = 0; i < C[idx].size(); i++)
        {
            if (row == C[idx][i] || col == C[idx][i])
            {
                flag = true;
                break;
            }
        }
        if (!flag) det.push_back(mat[j]);
    }

    return determine(det, (level - C[idx].size()));
}

double determine(vector<double> mat, int len)
{
    vector<int> vec;
    for (int i = 0; i < len; i++) vec.push_back(i);
    gather.push_back(vec);
    arrange(vec, 0);
    gather = uni(gather);
    return multi(mat, len);
}

void arrange(vector<int> vec, int idx)
{
    for (int i = idx; i < vec.size(); i++) swap(vec, idx, i);
}

void swap(vector<int> vec, int idx_s, int idx_e)
{
    if (idx_s != idx_e)
    {
        int temp = vec[idx_s];
        vec[idx_s] = vec[idx_e];
        vec[idx_e] = temp;
        gather.push_back(vec);
    }
    for (int j = idx_s; j < vec.size(); j++) arrange(vec, j + 1);
}

vector<vector<int>> uni(vector<vector<int>> gather)
{
    int count = 0;

    for (int i = 0; i < (gather.size() - 1); i++)
    {
        for (int j = (i + 1); j < gather.size(); j++)
        {
            for (int k = 0; k < gather[i].size(); k++)
            {
                if (gather[i][k] == gather[j][k])
                    count++;
            }
            if (count == gather[i].size())
            {
                swap(gather[j], gather[gather.size() - 1]);
                gather.pop_back();
            }
            count = 0;
        }
    }
    return gather;
}

double multi(vector<double> mat, int len)
{
    double total = 0;
    for (int i = 0; i < gather.size(); i++)
    {
        double column = 0;
        int direct = 1;
        for (int l = 0; l < len; l++)
            for (int k = l + 1; k < len; k++)
                direct = gather[i][l] > gather[i][k] ? -direct : direct;
        column = direct;
        for (int j = 0; j < len; j++)
            column *= mat[j * len + gather[i][j]];
        // cout << column << endl;
        total += column;
    }
    return total;
}
