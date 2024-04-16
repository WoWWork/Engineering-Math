#include "math.h"
#include <vector>
#include <iostream>

using namespace std;

double determine(vector<double>);
void arrange(vector<int>, int);
void swap(vector<int>, int, int);
vector<vector<int>> uni(vector<vector<int>>);
double multi(vector<double>, int);

vector<vector<int>> gather;

int main(int argc, char* argv[])
{
    vector<double> arr;
    for(int x = 1; x < argc; x++) arr.push_back(stod(argv[x]));
    double ans = determine(arr);
    cout << "determine number is " << ans << endl;
    return 0;
}

double determine(vector<double> mat)
{
    double square = mat.size();
    double len = sqrt(square);
    if(fabs(len-(int)len) > 1e-5) return -1;
    vector<int> vec;
    for(int i = 0; i < len; i++) vec.push_back(i);
    gather.push_back(vec);
    arrange(vec, 0);
    gather = uni(gather);
    /*
    for(int i = 0; i < gather.size(); i++)
    {
	for(int j = 0; j < len; j++)
    	    cout << gather[i][0];
	cout << endl;
    }
    */
    return multi(mat, (int)len);
}

void arrange(vector<int> vec, int idx)
{
    for(int i = idx; i < vec.size(); i++)
	swap(vec, idx, i);
}

void swap(vector<int> vec, int idx_s, int idx_e)
{
    if(idx_s != idx_e)
    {
    	int temp = vec[idx_s];
    	vec[idx_s] = vec[idx_e];
    	vec[idx_e] = temp;
	    gather.push_back(vec);
    }
    for(int j = idx_s; j < vec.size(); j++)
	arrange(vec, j + 1);
}

vector<vector<int>> uni(vector<vector<int>> gather)
{
    int count = 0;
    
    for(int i = 0; i < (gather.size() - 1); i++) 
    {
	    for(int j = (i + 1); j < gather.size(); j++)
	    {
	        for(int k = 0; k < gather[i].size(); k++)
	        {
		        if(gather[i][k] == gather[j][k]) count++;
	        }
	        if(count == gather[i].size())
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
    for(int i = 0; i < gather.size(); i++)
    {
	    double column = 0;
	    int direct = 1;
	    for(int l = 0; l < len; l++)
	        for(int k = l + 1; k < len; k++)
		        direct = gather[i][l] > gather[i][k] ? -direct : direct;
	    column = direct;
	    for(int j = 0; j < len; j++) column *= mat[j * len + gather[i][j]];
	    //cout << column << endl;
	    total += column;
    }
    return total;
}