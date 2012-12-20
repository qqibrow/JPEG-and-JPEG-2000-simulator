#pragma once

#define BLOCKSIZE 8

struct Direction
{
	Direction(){};
	Direction(int dy,int dx): dy(dy), dx(dx){};

	int dx;
	int dy;
};


struct Point
{
	Point(){};
	Point(int yy,int xx): y(yy), x(xx){};
	int x;
	int y;
	void next(Direction d)
	{
		x = x + d.dx;
		y = y + d.dy;
	}
};


#include <vector>
#include <iostream>
#include <string>

class JPEGBlock
{
public:
	JPEGBlock(void);
	JPEGBlock(std::vector<int>& input);
	void setImage(std::vector<int>& value);
	~JPEGBlock(void);
	void setQuantization( std::vector<int> quantizationTable );
	void doDCT();
	void doQuantization();
	std::vector<int> getSequence();
	std::vector<std::string> getCountZeroResult();
	std::ostream& outputDCT( std::ostream& out );
	std::ostream& outputQUantized( std::ostream& out );
private:
	std::ostream& output(double values[][BLOCKSIZE], std::ostream& out);
	double getOneValue(int u, int v);
	bool isEnd( Point p );
	void NextStep( Point& p, Direction& d );
private:
	int image[BLOCKSIZE][BLOCKSIZE];
	double DCT[BLOCKSIZE][BLOCKSIZE];
	double Quantized[BLOCKSIZE][BLOCKSIZE];
	int quantizationTable[BLOCKSIZE][BLOCKSIZE];

};


