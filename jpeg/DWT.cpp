#include "DWT.h"
#include <assert.h>

using namespace std;

DWTBlock::DWTBlock( void )
{

}

DWTBlock::~DWTBlock( void )
{

}

std::vector<double> DWTBlock::encompression1D( std::vector<double> s )
{
	int length = s.size();

	if( length & (length - 1) != 0)
		return vector<double>(0);

	vector<double> result(s);


	while( length > 1 )
	{
		encompressionStep( s, result, length);
		length = length / 2;
		s = result;
	}

	return result;

}

void DWTBlock::encompressionStep( std::vector<double>& s, std::vector<double>& result, int length )
{
	for( int i = 1; i <= length/2; i++)
	{
		*getIt(i,result) = (*getIt(2*i - 1, s) + *getIt(2*i, s)) / 2;
		*getIt(i + length / 2,result) = (*getIt(2*i - 1, s) - *getIt(2*i, s)) / 2;
	}
}

std::vector<double>::iterator DWTBlock::getIt( int i, std::vector<double>& s )
{
	assert(i > 0);
	return s.begin() + i - 1;
}

std::vector<double> DWTBlock::decompression1D( std::vector<double> s )
{
	int length = s.size();

	if( length & (length - 1) != 0)
		return vector<double>(0);

	vector<double> result(s);


	int h = 2;
	while( h <= length)
	{
		decompressionStep( s, result, h);
		h = h * 2;
		s = result;
	}

	return result;
}

void DWTBlock::decompressionStep( std::vector<double>& s, std::vector<double>& result, int h )
{
	for( int i = 1; i <= h/2; i++)
	{
		*getIt(2*i - 1,result) = *getIt(i, s) + *getIt(i + h/2, s);
		*getIt(2*i,result) = *getIt(i, s) - *getIt(i + h/2, s);
	}
}



