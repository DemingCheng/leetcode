#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int myrank,nprocs,len;
    MPI_Status status; //状态
    char Processorname[20];
  
    MPI_Init(&argc,&argv); //初始化MPI并行环境
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);  //nprocs返回进程个数
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);   //myrank返回进程号(从0开始)
 
    MPI_Get_processor_name(Processorname, &len); //返回机器名字和名字长度
    printf("Hello world! Process %d of %d on %s.\n",myrank,nprocs,Processorname);
    MPI_Finalize();  //终止MPI处理
     
}