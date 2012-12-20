#include "JPEGBlock.h"
#include <math.h>
#include <sstream>

#define  PI 3.1415926

using namespace std;


template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

JPEGBlock::JPEGBlock(void)
{
}

JPEGBlock::JPEGBlock( std::vector<int>& input )
{
	this->setImage(input);
}


JPEGBlock::~JPEGBlock(void)
{
}

void JPEGBlock::setQuantization( std::vector<int> quantizationTable )
{
	for( int j = 0; j < BLOCKSIZE; j++)
	{
		for( int i = 0; i < BLOCKSIZE; i++)
		{
			this->quantizationTable[j][i] = quantizationTable[j*BLOCKSIZE + i];
		}
	}
}

void JPEGBlock::doDCT()
{
	for( int j = 0; j < BLOCKSIZE; j++)
	{
		for( int i = 0; i < BLOCKSIZE; i++)
		{
			DCT[j][i] = getOneValue(i,j);

		}
	}
}

void JPEGBlock::doQuantization()
{
	for( int j = 0; j < BLOCKSIZE; j++)
	{
		for( int i = 0; i < BLOCKSIZE; i++)
		{
			Quantized[j][i] = floor(DCT[j][i] / quantizationTable [j][i] + 0.5);
		}
	}
}

std::ostream& JPEGBlock::outputDCT( std::ostream& out )
{
	out<<"output DCT result: \n";
	return output(DCT,out);
}


std::ostream& JPEGBlock::outputQUantized( std::ostream& fout )
{

	fout<<"output quantized result: \n";
	return output(Quantized,fout);
	
}

void JPEGBlock::setImage( std::vector<int>& value )
{
	for( int j = 0; j < BLOCKSIZE; j++)
		for( int i = 0; i < BLOCKSIZE; i++)
		{
			image[j][i] = value[j*BLOCKSIZE + i];
		}
} 

std::ostream& JPEGBlock::output( double values[][BLOCKSIZE], std::ostream& out )
{
	for( int j = 0; j < BLOCKSIZE; j++)
	{
		for( int i = 0; i < BLOCKSIZE; i++)
		{
			out<<values[j][i]<<"  ";
		}
		out<<std::endl;
	}
	return out;
}

double JPEGBlock::getOneValue( int u, int v )
{
	double sum = 0.0f;
	for( int y = 0; y < BLOCKSIZE; y++)
		for( int x = 0; x < BLOCKSIZE; x++)
		{
			sum += image[y][x] * cos( (2*x + 1) *u * PI/ 16.0 ) * cos( (2*y + 1) *v * PI/ 16.0 );
		}
	double cu,cv;
	cu = u == 0 ? sqrt(0.5) : 1;
	cv = v == 0 ? sqrt(0.5) : 1;

	return  sum * 0.25 * cu * cv;
}

vector<int> JPEGBlock::getSequence()
{
	vector<int> sequence;
	Point p(0,1);
	Direction d(1,-1);

	while(!isEnd(p))
	{
		int value = Quantized[p.y][p.x];
		sequence.push_back(value);

		NextStep(p, d);
	}

	return sequence;
}



bool JPEGBlock::isEnd( Point p )
{
	return p.x == BLOCKSIZE - 1 && p.y == BLOCKSIZE - 1;
}

void JPEGBlock::NextStep( Point& p, Direction& d )
{
	Point temp(p);
	temp.next(d);

	if( p.x == 0 && p.y == BLOCKSIZE - 1)
	{
		p.x = 1;
		d.dx = 1;
		d.dy = -1;
	}
	else if ( temp.x < 0)
	{
		p.y = p.y + 1;
		d.dy = -1;
		d.dx = 1;
	}
	else if( temp.y < 0)
	{
		p.x = p.x + 1;
		d.dx = -1;
		d.dy = 1;
	}
	else if( temp.x >= BLOCKSIZE)
	{
		p.y += 1;
		d.dx = -1;
		d.dy = 1;

	}
	else if(temp.y >= BLOCKSIZE)
	{
		p.x += 1;
		d.dy = -1;
		d.dx = 1;
	}
	else
	{
		p.next(d);
	}
}

std::vector<string> JPEGBlock::getCountZeroResult()
{
	vector<int> sequence = getSequence();
	vector<string> results;
	int count = 0;
	for( int i = 0; i < sequence.size(); i++)
	{
		if(sequence[i] == 0)
			count++;
		else
		{
			string result = NumberToString<int>(count) + "zeros before" + NumberToString<int>(sequence[i]);
			results.push_back(result);
			count = 0;

		}
	}

	return results;
}


