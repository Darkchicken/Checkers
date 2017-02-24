#pragma once
#include <string>
class Piece
{
public:
	Piece();
	Piece(std::string owner);
	~Piece();

	void setPosition(int x, int y);
	void setOwner(std::string owner);

	void movePiece(int targetX, int targetY);

	inline int getX() { return _x; }
	inline int getY() { return _y; }
	inline std::string getOwner() { return _owner; }
	inline bool isAlive() { return _isAlive; };

	void kill() { _isAlive = false; }
	

private:
	int _x, _y;
	std::string _owner;
	bool _isAlive = true;
};

