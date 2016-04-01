#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

ofstream outfile("minimal_spanning_tree.txt");
int main(int argc, char **argv)
{
	if(argc < 2)
	{
		cout <<"Error !!!, please provide the input file." << endl;
		return -1;
	}
	
	ifstream infile(argv[1]);
	cout<<"Prim.s Algorithm."<<endl;
	int m,n,i,j;
	//Read adjacency matrix of weights from graph.txt
	infile>>n;
	vector< vector<float> > weight; 
	float val;
	for(i=0; i<n; i++)
	{
		vector<float> row;
		for(j=0; j<n; j++)
		{
			infile>>val;
			row.push_back(val);
		}
		weight.push_back(row);
	}
	//Initialize Table

	const float infinity=1000000;
	vector<bool> known;
	for(i=0; i<n; i++) 
		known.push_back(false);

	vector<float> d;
	d.push_back(0);

	for(i=1; i<n; i++) 
		d.push_back(infinity);

	vector<int> p;
	for(i=0; i<n; i++) 
		p.push_back(-1);

	//Print Table
	outfile<<endl<<"INITIAL TABLE:"<<endl;
	outfile<<endl<<"Vertex : "<<'\t';

	for(i=0; i<n; i++) 
		outfile<<i<<'\t';
	outfile<<endl<<"Known : "<<'\t';

	for(i=0; i<n; i++) 
		outfile<<known[i]<<'\t';
	outfile<<endl<<"Distance: "<<'\t';
	for(i=0; i<n; i++) 
		outfile<<d[i]<<'\t';
	outfile<<endl<<"Path : "<<'\t';
	for(i=0; i<n; i++) 
		outfile<<p[i]<<'\t';
	outfile<<endl;

	//Iteration

	for(m=0; m<n; m++)
	{
		//Find min of d for unknown vertices
		int min=0;
		while(known[min]==true)
			min++;
		for(i=0; i<n; i++)
			if(known[i]==false && d[i]<d[min])
				min=i;
		
		//Update Table
		known[min]=true;
		for(j=0; j<n; j++)
		{
			if(weight[min][j]!=0 && d[j]>weight[min][j] && known[j]==false)
			{
				d[j]=weight[min][j];
				p[j]=min;
			}
		}

		//Print Table
		outfile<<endl<<endl<<"TABLE No."<<m<<":"<<endl;
		outfile<<endl<<"Vertex : "<<'\t';
		for(i=0; i<n; i++) 
			outfile<<i<<'\t';
		outfile<<endl<<"Known : "<<'\t';
		for(i=0; i<n; i++) 
			outfile<<known[i]<<'\t';
		outfile<<endl<<"Distance: "<<'\t';
		for(i=0; i<n; i++) 
			outfile<<d[i]<<'\t';
		outfile<<endl<<"Path : "<<'\t'<<'\t';
		for(i=0; i<n; i++) 
			outfile<<p[i]<<'\t';
		outfile<<endl;
	}

	//Print minimal spanning tree
	outfile<<endl<<"MINIMAL SPANNING TREE:"<<endl;
	for(i=1; i<n; i++)
		outfile<<"("<<i<<","<<p[i]<<")";
	outfile << endl;
	cout<<"See minimal spanning tree.txt."<<endl;
	return 0;
}
