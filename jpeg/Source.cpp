#include <iostream>
#include <fstream>
#include "JPEGBlock.h"
#include "DWT.h"

using namespace std;

void DWT2D( double data[BLOCKSIZE][BLOCKSIZE], DWTBlock &dwt )
{
	for( int j = 0 ; j < BLOCKSIZE; j++)
	{
		vector<double> s(data[j], data[j] + BLOCKSIZE);
		s = dwt.encompression1D(s);
		vector<double> d = dwt.decompression1D(s);
		for( int i = 0; i < BLOCKSIZE; i++)
			data[j][i] = s[i];

	}
}

void DWT2Dreverse( double data[BLOCKSIZE][BLOCKSIZE], DWTBlock &dwt )
{
	for( int j = 0 ; j < BLOCKSIZE; j++)
	{
		vector<double> s(data[j], data[j] + BLOCKSIZE);
		s = dwt.decompression1D(s);
		for( int i = 0; i < BLOCKSIZE; i++)
			data[j][i] = s[i];

	}
}


void rotate(double data[BLOCKSIZE][BLOCKSIZE])
{

	double* tempBuffer = new double[BLOCKSIZE*BLOCKSIZE];
	for( int j = 0 ; j < BLOCKSIZE; j++)
		for( int i = 0; i < BLOCKSIZE; i++)
			tempBuffer[i*BLOCKSIZE + j] = data[j][i];

	for( int j = 0 ; j < BLOCKSIZE; j++)
		for( int i = 0; i < BLOCKSIZE; i++)
			data[j][i] = tempBuffer[j*BLOCKSIZE + i];

	delete[] tempBuffer;
}

std::ostream& output( double values[BLOCKSIZE][BLOCKSIZE], std::ostream& out )
{
	for( int j = 0; j < BLOCKSIZE; j++)
	{
		for( int i = 0; i < BLOCKSIZE; i++)
		{
			out<<(int)(floor(values[j][i] + 0.5))<<"  ";
		}
		out<<"\n";
	}
	out<<endl;
	return out;
}
int main()
{
	ifstream fin("Source.in");
	ofstream fout("Source.out");

	vector<int> inputs(64), quantizationTable(64);
	for( int i = 0; i < BLOCKSIZE*BLOCKSIZE; i++)
		fin>>inputs[i];

	for( int i = 0; i < BLOCKSIZE*BLOCKSIZE; i++)
		fin>>quantizationTable[i];

	JPEGBlock block(inputs);
	block.setQuantization(quantizationTable);
	block.doDCT();
	block.doQuantization();
	block.outputDCT(fout);
	block.outputQUantized(fout);


	
	fout<<"the count zero results\n";
	vector<int> s = block.getSequence();
	for( int i = 0; i < s.size(); i++)
		fout<<s[i]<<endl;
	fout<<endl;


	fout<<"the count zero results\n";
	vector<string> sequence = block.getCountZeroResult();
	int length = sequence.size();
	for( int i = 0; i < length; i++)
		fout<<sequence[i]<<endl;
	fout<<endl;


	DWTBlock dwt;

	double data[BLOCKSIZE][BLOCKSIZE];

	for(int i = 0; i < BLOCKSIZE; i++)
		for( int j = 0; j < BLOCKSIZE; j++)
			data[i][j] = inputs[i* BLOCKSIZE + j];


	DWT2D(data, dwt);

	fout<<"this is the data through dwt row\n";
	output(data, fout);


	rotate(data);

	fout<<"this is the data after the rotation\n";
	output(data, fout);

	DWT2D(data,dwt);
	rotate(data);

	fout<<"this is the data through column\n";
	output(data, fout);


	 
	for(int i = 0; i < BLOCKSIZE; i++)
		for( int j = 0; j < BLOCKSIZE; j++)
			data[i][j]  = floor(data[i][j]/32 + 0.5);

	fout<<"this is the data after quantization\n";
	output(data, fout);

	//dequantization
	for(int i = 0; i < BLOCKSIZE; i++)
		for( int j = 0; j < BLOCKSIZE; j++)
			data[i][j]  *= 32;


	
	rotate(data);
	DWT2Dreverse(data,dwt);
	rotate(data);
	DWT2Dreverse(data,dwt);

	fout<<"this is the data recontructed from dwt\n";
	output(data, fout);

	
	
	return 0;
}

