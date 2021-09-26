//sum of array in parallel
#include<stdio.h>
#include<mpi.h>
int main(int argc, char ** argv)
{
    int rank, size, root=0, data[100], data_loc[100],final_res[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int input_size = 8;
    data[0] =1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    data[5] = 6;
    data[6] = 7;
    data[7] = 8;

    MPI_Bcast(&input_size,1, MPI_INT, root,MPI_COMM_WORLD);
    int loc_num = input_size / size;
 
    MPI_Scatter(&data, loc_num, MPI_INT, data_loc, loc_num,MPI_INT, root, MPI_COMM_WORLD);
     
    int loc_sum = 0;
    for(int i=0;i<loc_num;i++)
    {
        loc_sum += data_loc[i];
    }

    MPI_Gather(&loc_sum, 1, MPI_INT, final_res,1,MPI_INT, root, MPI_COMM_WORLD);
  
    if(rank == 0)
    {
        int fin = 0;
        for(int i=0;i<size;i++)
        {
            fin += final_res[i];
        }
        printf("Final sum : %d\n",fin);
    }
    MPI_Finalize();
    return 0;
}