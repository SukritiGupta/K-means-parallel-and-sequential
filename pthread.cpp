#include "lab1_io.h"
#include "lab1_pthread.h"

#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <vector>
#include <math.h>
#include <pthread.h>

struct dim
{
	float a,b,c;
	int belong;
};

std::vector<dim> points;
std::vector<dim> centroid;
std::vector<int> belongs;

int n, k,t;
int delta;

int Kbelong(int x)
{
	double min=99999999, temp;
	int tempi;
	dim *a_pointer=&(points.at(x));
	dim a=*a_pointer;
	dim b;
	for (int j = 0; j < k; ++j)
	{
		b=centroid.at(j);
		temp=sqrt( ((a.a-b.a)*(a.a-b.a)) + ((a.b-b.b)*(a.b-b.b)) + ((a.c-b.c)*(a.c-b.c)) );
		if(temp<min)
		{
			tempi=j;
			min=temp;
		}
	}
	if(a.belong!=tempi)
		delta++;
	(*a_pointer).belong=tempi;
	return tempi;
}

void *PrintHello(void *threadarg) {
	int s;
	s = *((int *) threadarg);
	int block=n/t;
	int start=block*(s);
	int finish=block*(s+1);
	if (s==t-1)
	{
		finish=n;
	}

	// std::vector<int>::iterator it;
	// if(start>=n)
	// {
	// 	std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!11";
	// 	goto X;
	// }
	for (int i = start; i < finish; ++i)
	{
		belongs.at(i)=Kbelong(i);
	}
   	pthread_exit(NULL);
}


void kmeans_pthread(int T,int N, int K, int* data_points, int** cluster_points, float** centroids, int* num_iterations)
{

	n=N;
	k=K;
	t=T;
	int iterlim=1500;
	

	int limit=n/1000;


	*cluster_points=(int*) malloc(4*N*sizeof(int));
	*centroids=(float*) malloc(15000*3*K*sizeof(float));
	// belongs.reserve(n*sizeof(int));

	for (int i = 0; i < n; ++i)
	{
		belongs.push_back(k+1);
	}

	int* outp=*(cluster_points);
	float* coutp=*(centroids);

	// cluster_points=&(outp);
	// centroids=&(coutp);

	dim x;
	x.belong=0;
	int dsize=3*n;
	for (int i = 0; i < dsize;)
	{
		x.a=*(data_points+i);
		++i;
		x.b=*(data_points+i);
		++i;
		x.c=*(data_points+i);
		++i;
		points.push_back(x);
	}



	for (int i = 0; i < k; ++i)
	{
		centroid.push_back(points.at(rand()%n));
	}

	int g=0;
	for (int i = 0, j=0; j<k;)
	{
		x=centroid.at(j);
		*(coutp+i)=x.a;
		++i;
		*(coutp+i)=x.b;
		++i;
		*(coutp+i)=x.c;
		++i;
		++j;
	}
	g=k;


	int iter=0;
	int sizek[k];
	while(true)
	{
		std::vector<int> memk[k];
		
		delta=0;

		for (int i = 0; i < k; ++i)
		{
			sizek[i]=0;
		}

		pthread_t threads[t];
		int rc;
		int tid[t];
 		for( int i = 0; i < t; i++ ) 
 		{
 			tid[i]=i;
      		rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&(tid[i]));
      
      		if (rc) 
      		{
         		std::cout << "Error:unable to create thread," << rc << std::endl;
      		}
   		}

   		for (int i = 0; i < t; ++i)
   		{
   			(void) pthread_join(threads[i], NULL);
   		}
   		// pthread_exit(NULL);


   		int tempi;
   		for (int i = 0; i < n; ++i)
   		{
   			tempi=belongs.at(i);
   			memk[tempi].push_back(i);
			sizek[tempi]++;
   		}
   		

		double a=0, b=0, c=0;
		for (int i = 0; i < k; ++i)
		{
			a=0;
			b=0;
			c=0;
			dim temp;
			for (std::vector<int>::iterator it = memk[i].begin() ; it != memk[i].end(); ++it)
			{
				temp=points.at(*it);
				a+=temp.a;
				b+=temp.b;
				c+=temp.c;
			}

			a/=sizek[i];
			b/=sizek[i];
			c/=sizek[i];

			temp.a=a;
			temp.b=b;
			temp.c=c;
			temp.belong=0;

			centroid.at(i)=temp;

			*(coutp+g)=a;
			++g;
			*(coutp+g)=b;
			++g;
			*(coutp+g)=c;
			++g;
	

			if(sizek[i]==0)
			std::cout<<"ooOO";
		}

		++iter;

		if((iter>2 && delta<limit) || iter>iterlim)
			break;
	}

	std::cout<<std:: endl<<iter<<std::endl;

	dim temp;

	// for (int i = 0; i < k; ++i)
	// {
	// 	temp=centroid.at(i);
	// 	std::cout<<i<<". "<<temp.a<<"   "<<temp.b<<"   "<<temp.c<<"   "<<sizek[i]<<std::endl;
	// }

	int count=4*n;
	int j=0;
	for (int i = 0; i < count;)
	{
		temp=points.at(j);
		*(outp+i)=(int)temp.a;
		++i;
		*(outp+i)=(int)temp.b;
		++i;
		*(outp+i)=(int)temp.c;
		++i;
		*(outp+i)=temp.belong;
		++i;
		++j;
	}

	*num_iterations=iter;

}
