//sum of array
#include<stdio.h>
#include<mpi.h>
#define n 10
int a[] = {1,2,3,4,5,6,7,8,9,10};
int a2[100]; //temp array for slave processes

int main(int argc, char ** argv)
{
    int rank,size,n_elements_received;
    int np; //element per processes
    MPI_Status status;
     
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        int index, i;
        np = n/size;

        if(size>1)
        {
            //distribute the portion of array to child process to calculate their portion
            for(i=1;i<size - 1;i++)
            {
                index = i*np;
                MPI_Send(&np, 1,MPI_INT,i,0,MPI_COMM_WORLD);
                MPI_Send(&a[index],np, MPI_INT,i,0,MPI_COMM_WORLD);
            }

            index = i*np;
            int element_left = n-index;

            MPI_Send(&element_left, 1, MPI_INT,i, 0,MPI_COMM_WORLD);
            MPI_Send(&a[index], element_left, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        int sum=0;
        for(int i=0;i<np;i++)
        {
            sum += a[i];
        }
        //collect partial sum from another process
        int temp;
        for(int i=1;i<size;i++)
        {
            MPI_Recv(&temp, 1, MPI_INT,MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,&status);
            int sender = status.MPI_SOURCE;
         
            sum += temp;
        }
      printf("Sum of array is : %d\n",sum);
    }
    else
    {
        MPI_Recv(&n_elements_received, 1, MPI_INT, 0,0 ,MPI_COMM_WORLD, &status);
        MPI_Recv(&a2, n_elements_received, MPI_INT, 0,0,MPI_COMM_WORLD, &status);
     
        int partial_sum = 0;
        for(int i=0;i<n_elements_received;i++)
        {
            partial_sum += a2[i];
        }
        MPI_Send(&partial_sum, 1, MPI_INT,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}