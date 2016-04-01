#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <set>
using namespace std;

ofstream outfile("shortest_paths.txt");

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout <<"Error, please provide the input file." << endl;
		return -1;
	}
	ifstream infile(argv[1]);
	cout<<"Dijkstra.s Algorithm.."<<endl;
	int m,n,i,j,k;
	//Read adjacency matrix of weights from graph.txt
	infile>>n;
  vector< vector< float> > weight;
  float val;
  for(i=0; i<n; i++)
  {
    vector< float > row;
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

  //Print Initial Table
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
  outfile<<endl<<"Path : "<<'\t'<<'\t';
  for(i=0; i<n; i++) 
		outfile<<p[i]<<'\t';
  outfile<<endl;
  //Iteration

  for(k=0; k<n; k++)
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
    for (int j=0; j<n; j++)
    {
       if(weight[min][j]!=0 && d[j]>d[min]+weight[min][j] && known[j]==false)
       {
         d[j]=d[min]+weight[min][j];
         p[j]=min;
       }
   }

   //Print Table
  outfile<<endl<<"TABLE No."<<k<<":"<<endl;
  outfile<<endl<<"Vertex : "<<'\t';
  for(i=0; i<n; i++) 
		outfile<<i<<'\t';
  outfile<<endl<<"Known : " <<'\t';
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

 //Find shortest paths and spanning tree
 outfile<<endl<<endl<<"SHORTEST PATHS:"<<endl;
 set< vector<int> > span;
 for(i=0; i<n; i++)
 {
   outfile<<"Path="<<'\t';
   vector<int> temp;
   m=i;
  while(m!=-1)
  {
    temp.push_back(m);
    m=p[m];
  }
  outfile<<temp[temp.size()-1]<<" ";
  for(j=temp.size()-2; j>=0; j--)
  {
    outfile<<temp[j]<<" ";
    vector<int> edge;
    edge.push_back(temp[j+1]);
    edge.push_back(temp[j]);
    span.insert(edge);
  }
  outfile<<"Distance="<<d[i]<<endl;
 }
 //Print spanning tree
 outfile<<endl<<"SPANNING TREE:"<<endl;
 set< vector<int> >::iterator it;
 for(it=span.begin(); it!=span.end(); it++)
 		outfile<<"("<<(*it)[0]<<","<<(*it)[1]<<")"<<" ";
	outfile << endl;

 cout<<"See shortest_paths.txt for results." <<endl;
 return 0;
}
