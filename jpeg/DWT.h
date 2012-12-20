#pragma once

#include <vector>


class DWTBlock
{
public:
	DWTBlock(void);
	std::vector<double> decompression1D(std::vector<double> s);
	std::vector<double> encompression1D( std::vector<double> s);
	~DWTBlock(void);
	void encompressionStep( std::vector<double>& s, std::vector<double>& result, int length );
	void decompressionStep( std::vector<double>& s, std::vector<double>& result, int length );
	std::vector<double>::iterator getIt(int i, std::vector<double>& s); 
};

