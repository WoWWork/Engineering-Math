#include "iostream"
#include <math.h>
using namespace std;
//#define R 3
//#define C 3

// Function to display a matrix
void display(int*, int, int);
/* function for exchanging two rows of a matrix */
void swap(int*, int, int, int);
/* function for finding rank of matrix */
int rankOfMatrix(double*, int, int);

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
    auto len = sqrt(argc - 3);
    double* mat;
    for(int i = 3; i < argc; i++) *(mat + (i - 3)) = stod(argv[i]);
    
    //if(fabs(len-(int)len) > 1e-5) return -1;
    int num = rankOfMatrix(mat, atoi(argv[1]), atoi(argv[2]));
    cout << num << endl;
    return num;
}
 
/* function for finding rank of matrix */
int rankOfMatrix(double* mat, int R, int C)
{
    int rank = R > C ? C : R;
 
    for (int row = 0; row < rank; row++)
    {
        // Before we visit current row 'row', we make
        // sure that mat[row][0],....mat[row][row-1]
        // are 0.
 
        // Diagonal element is not zero
        if (mat[row * R + row])
        {
           for (int col = 0; col < C; col++)
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
            for (int i = row + 1; i < C;  i++)
            {
                // Swap the row with non-zero element
                // with this row.
                if (mat[i * R + row])
                {
                    swap(mat, row, i, R);
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
                for (int i = 0; i < C; i ++) mat[i * R + row] = mat[i * R + rank];
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