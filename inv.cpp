#include "iostream"
#include <vector>
#include <math.h>
using namespace std;

// Function to display a matrix
void display(int*, int, int);
/* function for exchanging two rows of a matrix */
void swap(int*, int, int, int);
/* function for finding rank of matrix */
vector<double> inverse(vector<double>, int, int* rank = 0);

int main(int argc, char* argv[])
{
    vector<double> mat;
    for(int i = 1; i < argc; i++)  mat.push_back(stod(argv[i]));
    double len = sqrt(mat.size());
    if(fabs(len-(int)len) > 1e-5) return -1;
    vector<double> inv_m = inverse(mat, (int)len);
    for(int i = 0; i < inv_m.size(); i++) cout << inv_m[i] << " ";
    cout << endl;
    return 0;
}

/* function for exchanging two rows of a matrix */
void swap(double* mat, int row1, int row2, int col)
{
    for (int i = 0; i < col; i++)
    {
        double temp = mat[row1 * col + i];
        mat[row1 * col + i] = mat[row2 * col + i];
        mat[row2 * col + i] = temp;
    }
}
 
/* function for finding rank of matrix */
vector<double> inverse(vector<double> mat, int R, int* rank)
{
    vector<double> inv_m;
    for(int i = 0; i < mat.size(); i++) inv_m.push_back(0.0);
    for(int i = 0; i < R; i++) inv_m[i * R + i] = 1.0; 
    rank = &R;

    for (int row = 0; row < *rank; row++)
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
                    for (int i = 0; i < R; i++) 
                    {
                        mat[col * R + i] -= mult * mat[row * R + i];
                        inv_m[col * R + i] -= mult * inv_m[row * R + i];
                    }
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
                    swap(&inv_m[0], row, i, R);
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
                (*rank)--;
 
                // Copy the last column here
                for (int i = 0; i < R; i ++) 
                {
                    mat[i * R + row] = mat[i * R + *rank];
                    inv_m[i * R + row] = inv_m[i * R + *rank];
                }
            }
 
            // Process this row again
            row--;
        }
 
        // Uncomment these lines to see intermediate results
        // display(mat, R, R);
        // printf("\n");
    }

    double factor;
    for(int i = 0; i < R; i++)
    {
        if(mat[i * R + i] != 1.0)
        {
            factor = mat[i * R + i] / 1.0;
            for(int j = 0; j < R; j++)
            {
                mat[i * R + j] /= factor;
                inv_m[i * R + j] /= factor;
            }
        }
    }
    return inv_m;
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