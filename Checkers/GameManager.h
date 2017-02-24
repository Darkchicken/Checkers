#pragma once

#include "Player.h"
#include "Piece.h"
enum GameState 
{
	MENU, GAMEPLAY, END
};
class GameManager
{
public:
	GameManager();
	~GameManager();

	//initial setup of game
	void setup();
	//handles game loop
	void run();
	//draws main menu
	void drawMenu();
	//draw end screen
	void drawEnd();
	//draws board and pieces
	void drawBoard();
	//get user input
	void input();
	//handle game logic
	void logic();

	//handle AI player movement
	void aiMove();

	//handle moving logic, return true if successful
	bool attemptMove(Piece &heldPiece, int targetX, int targetY);
	//checks if another piece is at this location
	bool CheckLocationOccupied(int targetX, int targetY);

private:
	Player realPlayer; 
	Player compPlayer; 

	bool computerTurn = false;
	//is the AI currently trying to move
	bool aiActive = false;

	bool quit;
	GameState currentState;

	const int boardWidth = 8;
	const int boardHeight = 8;

	char defaultCursor = '\xB0';
	char cursor = '\xB0';
	// moveable spaces
	char blackSpace = '\xFE';
	//unmoveable spaces
	char whiteSpace = ' ';
	//real player pieces
	char realPiece = 'O';
	//comp player pieces
	char compPiece = '@';

	//position for realPlayer cursor
	int cursorX;
	int cursorY;

	bool pieceIsHeld = false;
	bool jumpChain = false;
	Piece* heldPiece;

	bool win = false;
};

