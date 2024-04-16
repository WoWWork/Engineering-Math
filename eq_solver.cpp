#include "iostream"
#include <vector>
#include <math.h>
using namespace std;

// Function to display a matrix
void display(int*, int, int);
/* function for exchanging two rows of a matrix */
void swap(int*, int, int, int);
/* function for finding rank of matrix */
int rankOfMatrix(vector<double>, int);
double determine(vector<double>);
void arrange(vector<int>, int);
void swap(vector<int>, int, int);
vector<vector<int>> uni(vector<vector<int>>);
double multi(vector<double>, int);

vector<vector<int>> gather;

/* function for exchanging two rows of a matrix */
void swap(double* mat, int row1, int row2, int col)
{
    for (int i = 0; i < col; i++)
    {
        int temp = mat[row1 * col + i];
        mat[row1 * col + i] = mat[row2 * col + i];
        mat[row2 * col + i] = temp;
    }
}
 
int main(int argc, char* argv[])
{
    auto len = sqrt(argc - 1);
    vector<double> a;
    vector<double> b; 
    for(int i = 1; i < argc; i++)
    {
        if(((i - 1) % (int)(len + 1)) != (int)len) a.push_back(stod(argv[i]));
        else b.push_back(stod(argv[i]));
    }
    int num = rankOfMatrix(a, (int)len);
    vector<double> roots;
    if(num == (int)len)
    {
        double det = determine(a);
        vector<double> var;
        for(int i = 0; i < num; i++)
        {
            var = a;
            for(int j = 0; j < num; j++) var[j * num + i] = b[j];
            roots.push_back(determine(var) / det);
        }
        for(int k = 0; k < num; k++) cout << roots[k] << " ";
        cout << endl;
    }
    else return -1;
    return 0;
}
 
/* function for finding rank of matrix */
int rankOfMatrix(vector<double> mat, int R)
{
    int rank = R;
 
    for (int row = 0; row < rank; row++)
    {
        // Before we visit current row 'row', we make
        // sure that mat[row][0],....mat[row][row-1]
        // are 0.
 
        // Diagonal element is not zero
        if (mat[row * R + row])
        {
           for (int col = 0; col < R; col++)
           {
               if (col != row)
               {
                 // This makes all entries of current
                 // column as 0 except entry 'mat[row][row]'
                 double mult = (double)mat[col * R + row] / mat[row * R + row];
                 for (int i = 0; i < R; i++) mat[col * R + i] -= mult * mat[row * R + i];
              }
           }
        }
 
        // Diagonal element is already zero. Two cases
        // arise:
        // 1) If there is a row below it with non-zero
        //    entry, then swap this row with that row
        //    and process that row
        // 2) If all elements in current column below
        //    mat[r][row] are 0, then remove this column
        //    by swapping it with last column and
        //    reducing number of columns by 1.
        else
        {
            bool reduce = true;
 
            /* Find the non-zero element in current
                column  */
            for (int i = row + 1; i < R;  i++)
            {
                // Swap the row with non-zero element
                // with this row.
                if (mat[i * R + row])
                {
                    swap(&mat[0], row, i, R);
                    reduce = false;
                    break ;
                }
            }
 
            // If we did not find any row with non-zero
            // element in current column, then all
            // values in this column are 0.
            if (reduce)
            {
                // Reduce number of columns
                rank--;
 
                // Copy the last column here
                for (int i = 0; i < R; i ++) mat[i * R + row] = mat[i * R + rank];
            }
 
            // Process this row again
            row--;
        }
 
       // Uncomment these lines to see intermediate results
       // display(mat, R, C);
       // printf("\n");
    }
    return rank;
}
 
/* function for displaying the matrix */
void display(double* mat, int row, int col)
{
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++) printf("  %d", mat[i * row + j]);
        printf("\n");
    }
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