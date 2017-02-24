#include "Piece.h"

Piece::Piece()
{
	_owner = "None";
	_x = 0;
	_y = 0;
}

Piece::Piece(std::string owner)
{
	_owner = owner;
	_x = 0;
	_y = 0;
}


Piece::~Piece()
{
}

void Piece::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Piece::setOwner(std::string owner)
{
	_owner = owner;
}


void Piece::movePiece(int targetX, int targetY)
{

	//_x = x;
	//_y = y;
}
