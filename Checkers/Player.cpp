#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{
}

void Player::init(std::string name)
{
	_name = name;
	//give each player 12 pieces
	for (int i = 0; i < maxPieces; i++)
	{
		pieces.push_back(new Piece(_name));
	}

	remainingPieces = maxPieces;
}

void Player::destroyPiece(Piece* piece)
{
	remainingPieces -= 1;
	piece->kill();
}
