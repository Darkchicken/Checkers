#pragma once
#include "Piece.h"
#include <vector>
#include <string>
class Player
{
public:
	Player();
	~Player();

	std::vector<Piece*> pieces;

	inline int getRemainingPieces() { return remainingPieces; }

	void init(std::string name);

	void destroyPiece(Piece* piece);

private:
	const int maxPieces = 12;

	std::string _name;

	int remainingPieces;
};

