#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>

#include <chrono>

double points[1000000][3], pointk[1000000];
//#include <iomanip> //************************************

double dist(double a[], double b[])
{
	double ret=0, sum=0;
	for (int i = 0; i < 3; ++i)
	{
		sum=((a[0]-b[0])*(a[0]-b[0])) + ((a[1]-b[1])*(a[1]-b[1])) + ((a[2]-b[2])*(a[2]-b[2])) ;
		ret+=sqrt(sum);
	}
	return ret;
}

int main(int argc, char *argv[])
{
	using namespace std;

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); 

	
	srand (time(NULL));

	cout<<"hellp world";

	ifstream file;
	file.open(argv[1]);

	int n, d, k;

	//double check; //****************
	file>>n>>d>>k;

	cout<<n<<d<<k;

	//double points[n][3], pointk[n]; //$$$$$$$$$$$$$$$$$$$$$$
	//distk[n];
	double centroid[k][3];
	int limit=5000;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			file>>points[i][j];
		}
	}


	file.close();
	//cout<<"1";
	int init;

	for (int i = 0; i < k; ++i)
	{
		init=rand()%n;
		for (int j = 0; j < 3; ++j)
		{
			centroid[i][j]=points[init][j];
		}	
		//sizek[i]=0;
	}

	//cout<<"2";

	int iter=0;
	int sizek[k];
	//cout<<"ndqkIOQN";
	while(true)
	{
		//cout<<iter;
		double temp;
		vector<int> memk[k];
		
		int delta=0;

		for (int i = 0; i < k; ++i)
		{
			sizek[i]=0;
		}

		for (int i = 0; i < n; ++i)
		{
			double min=99999999;
			int tempi;
			for (int j = 0; j < k; ++j)
			{
				temp=dist(points[i], centroid[j]);
				if(temp<min)
				{
					tempi=j;
					min=temp;
				}
			}

			if(pointk[i]!=tempi)
				delta++;

			pointk[i]=tempi;
			memk[tempi].push_back(i);
			sizek[tempi]++;
		}

		double a=0, b=0, c=0;
		for (int i = 0; i < k; ++i)
		{
			a=0;
			b=0;
			c=0;
			for (vector<int>::iterator it = memk[i].begin() ; it != memk[i].end(); ++it)
			{
				a+=points[*it][0];
				b+=points[*it][1];
				c+=points[*it][2];
			}
      
			centroid[i][0]=a/sizek[i];
			centroid[i][1]=b/sizek[i];
			centroid[i][2]=c/sizek[i];

			if(sizek[i]==0)
			cout<<"ooOO";
		}
		++iter;

		if(iter>2 && delta<limit)
			break;
	}

	cout<<endl<<iter<<endl;

	for (int i = 0; i < k; ++i)
	{
		cout<<i<<". "<<centroid[i][0]<<"   "<<centroid[i][1]<<"   "<<centroid[i][2]<<"   "<<sizek[i]<<endl;
	}

	auto stop = high_resolution_clock::now(); 

	auto duration = duration_cast<microseconds>(stop - start); 
	cout << duration.count() << endl;
}
