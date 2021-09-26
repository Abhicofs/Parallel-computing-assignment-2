//dot product
/*
*suppose V = [1 2 3 4], V^T = [1
*                              2
*                              3
*                              4]
* n=4
*/
#include<stdio.h>
#include<mpi.h>
int main(int argc, char ** argv)
{
    int i,rank,size,v_loc[100],final_res[100],v[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    int input_size = 4;
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    MPI_Bcast(&input_size,1, MPI_INT, 0,MPI_COMM_WORLD);
    int loc_num = input_size / size;
 
    MPI_Scatter(&v, loc_num, MPI_INT, v_loc, loc_num,MPI_INT, 0, MPI_COMM_WORLD);
     
    int loc_sum = 0;
    for(int i=0;i<loc_num;i++)
    {
        loc_sum += v_loc[i]*v_loc[i];
    }

    MPI_Gather(&loc_sum, 1, MPI_INT, final_res,1,MPI_INT, 0, MPI_COMM_WORLD);
  
    if(rank == 0)
    {
        int fin = 0;
        for(int i=0;i<size;i++)
        {
            fin += final_res[i];
        }
        printf("Dot product of V and their transpose : %d\n",fin);
    }
    MPI_Finalize();
    return 0;
}