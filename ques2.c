//problem 2, exchange the array
#include<mpi.h>
#include<stdio.h>
int main(int argc, char ** argv)
{
    int rank,data[100],data1[100],data2[100],data3[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    if(rank == 0)
    {
        data[0]= 3;
        data[1]= 2;
        //printf("Rank: %d data values data3[0]: %d data3[1]: %d\n",rank, data3[0],data3[1]);
        MPI_Send(data, 100, MPI_INT,1, 0, MPI_COMM_WORLD);
        MPI_Recv(data3,100,MPI_INT,3,0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("I am rank 0, I received 100 integer to rank 3\n");
        printf("Rank : %d data value data3[0] : %d data3[1] : %d\n",rank,data3[0],data3[1]);
    }
    else if(rank == 1)
    {
        data1[0]= 1;
        data1[1] = 4;
        //printf("Rank: %d data values data[0]: %d data[1]: %d\n",rank, data[0],data[1]);
        MPI_Send(data1,100,MPI_INT,2,0,MPI_COMM_WORLD);
        MPI_Recv(data, 100, MPI_INT,0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("I am rank 1. I received 100 integer from rank 0\n");
        printf("Rank : %d data value data[0] : %d data[1]: %d\n",rank,data[0], data[1]);
    }
    else if(rank == 2)
    {
        data2[0]= 5;
        data2[1] = 6; 
        //printf("Rank: %d data values data1[0] : %d data1[1] : %d\n",rank,data1[0],data1[1]);
        MPI_Send(data2,100, MPI_INT,3,0,MPI_COMM_WORLD);
        MPI_Recv(data1,100,MPI_INT,1,0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("I am rank 0, I received 100 integer to rank 3\n");
        printf("Rank : %d data value data1[0] : %d data1[1] : %d\n",rank,data1[0],data1[1]);
    }
    else if(rank == 3)
    {
        data3[0]=7;
        data3[1] = 8;
     
        //printf("Rank: %d data values data2[0] : %d data2[1] : %d\n",rank,data2[0],data2[1]);
        MPI_Send(data3,100, MPI_INT,0,0,MPI_COMM_WORLD);
        MPI_Recv(data2,100,MPI_INT,2,0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("I am rank 0, I received 100 integer to rank 3\n");
        printf("Rank : %d data value data2[0] : %d data2[1] : %d\n",rank,data2[0],data2[1]);
    }
    else{
        printf("I am rank %d, I am  not interested in doing any work\n",rank);
    }
    MPI_Finalize();
    return 0;
}