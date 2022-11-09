#include<stdio.h>

#define ROW 3
#define COL 3

int main(){
    int i, j, mat[ROW][COL], trans[COL][ROW];
    printf("Enter matrix: \n");
    // input matrix
    for(i = 0; i < ROW; i++)
    {
            for(j = 0; j < COL; j++)
            {
                    printf("mat[%d][%d] = ",i,j);
                    scanf("%d", &mat[i][j]);
            }
    }
    // create transpose
    for(i = 0; i < ROW; i++){
            for(j = 0; j < COL; j++){
                    trans[j][i] = mat[i][j];
            }
    }
    printf("\nTranspose matrix: \n");
    // print transpose
    for(i = 0; i < COL; i++){
            for(j = 0; j < ROW; j++){
                    printf("%d ", trans[i][j]);
            }
            printf("\n");
    }
   return 0;
}