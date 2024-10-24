/**
 * CS3210 - Blocking communication in MPI.
 */

#include <iostream>
#include <mpi.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>


int main(int argc,char *argv[])
{
	int numtasks, rank, dest, source, rc, count, tag=1;  
	
	float *inmsg, *outmsg;
	inmsg = new float[10];
	outmsg = new float[10];
	char hostname[256];
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	memset(hostname, 0, sizeof(hostname));
	int sc_status = gethostname(hostname, sizeof(hostname)-1);
	if (sc_status)
	{
		perror("gethostname");
		return sc_status;
	}

	if (rank == 0)	{
		dest = 1;
		source = 1;
		for (int i = 0; i < 10; i ++) {
			outmsg[i] = i * 3.5;
		}
		rc = MPI_Send(outmsg, 10, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
		rc = MPI_Recv(inmsg, 10, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &Stat);
		printf("Task %d received %f %f %f\n", rank, inmsg[0], inmsg[1], inmsg[2]);
		
	} else if (rank == 1)	{
		dest = 0;
		source = 0;
		for (int i = 0; i < 10; i ++) {
			outmsg[i] = i * 2.5;
		}
		rc = MPI_Recv(inmsg, 10, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &Stat);
		rc = MPI_Send(outmsg, 10, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
		printf("Task %d received %f %f %f\n", rank, inmsg[0], inmsg[1], inmsg[2]);
	}

	rc = MPI_Get_count(&Stat, MPI_FLOAT, &count);
	printf("Task %d on %s: Received %d char(s) from task %d with tag %d \n",
       		rank, hostname, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	MPI_Finalize();
	
	return 0;
}

