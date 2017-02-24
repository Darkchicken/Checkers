#include "GameManager.h"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>

GameManager::GameManager()
{
	setup();
}


GameManager::~GameManager()
{
}

void GameManager::setup()
{
	srand(time(NULL));
	quit = false;
	currentState = MENU;
	realPlayer.init("Real");
	compPlayer.init("Comp");


	//set cursor to upper left corner
	cursorX = 2;
	cursorY = 0;

	// place pieces in proper locations
	int xPlacement = 2;
	int yPlacement = 0;
	bool xIsfirstCell = false;
	for (Piece* currentPiece : compPlayer.pieces)
	{
		// set piece position
		currentPiece->setPosition(xPlacement,yPlacement);
		// move to next cell
		xPlacement = xPlacement + 2;
		if (xPlacement >= boardWidth+1)
		{
			xIsfirstCell = !xIsfirstCell;
			if (!xIsfirstCell)
			{xPlacement = 2;}
			else
			{xPlacement = 1;}
			yPlacement++;
		}
	}
	//start at 5th row (3rd from bottom)
	yPlacement = 5;
	xPlacement = 1;
	xIsfirstCell = true;
	for (Piece* currentPiece : realPlayer.pieces)
	{
		// set piece position
		currentPiece->setPosition(xPlacement, yPlacement);
		// move to next cell
		xPlacement = xPlacement + 2;
		if (xPlacement >= boardWidth+1)
		{
			xIsfirstCell = !xIsfirstCell;
			if (!xIsfirstCell)
			{xPlacement = 2;}
			else
			{xPlacement = 1;}
			yPlacement++;
		}
	}

	


}

void GameManager::run()
{
	while (!quit)
	{
		if (currentState == MENU)
		{	
			//draw menu
			drawMenu();
			//input to start
			if (_kbhit())
			{
				currentState = GAMEPLAY;
			}
		}
		else if (currentState == GAMEPLAY)
		{
			drawBoard();
			input();
			logic();
		}	
		else if (currentState == END)
		{
			drawEnd();
			if (_kbhit())
			{
				setup();
				currentState = MENU;
			}
		}
	}
}

void GameManager::drawMenu()
{
	system("cls");
	//draw borders
	for (int i = 0; i < boardWidth + 2; i++)
	{
		std::cout << "#";
	}
	for (int i = 0; i < boardHeight; i++)
	{
		if (i == 4)
		{
			std::cout << " Checkers ";
		}
		
		std::cout << std::endl;
	}
	//draw borders
	for (int i = 0; i < boardWidth + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
}

void GameManager::drawEnd()
{
	system("cls");
	//draw borders
	for (int i = 0; i < boardWidth + 2; i++)
	{
		std::cout << "#";
	}
	for (int i = 0; i < boardHeight; i++)
	{
		if (i == 4)
		{
			if (win)
			{
				std::cout << " You Win ";
			}
			else
			{
				std::cout << " You Lose ";
			}
			
		}

		std::cout << std::endl;
	}
	//draw borders
	for (int i = 0; i < boardWidth + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
}

void GameManager::drawBoard()
{
	system("cls");
	//draw borders
	for (int i = 0; i < boardWidth + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
	//bool alternates to drop black and white tiles
	bool isBlack = true;
	//iterates rows (i is y index) (0 - boardheight)
	for (int i = 0; i < boardHeight; i++)
	{
		//iterates columns (j is x index) (add 2 for side borders) (1- boardwidth+1)
		for (int j = 0; j < boardWidth+2; j++)
		{
			// side borders
			if (j == 0 || j == boardWidth+1)
			{
				std::cout << "#";
			}
			// print cursor image
			else if (cursorX == j && cursorY == i)
			{
				std::cout << cursor;
			}

			//if its a moveable space
			else if (isBlack)
			{
				bool isPiece = false;
				//draw comp pieces
				for (Piece* currentPiece : compPlayer.pieces)
				{
					if (currentPiece->isAlive() && currentPiece->getX() == j && currentPiece->getY() == i)
					{
						isPiece = true;
						std::cout << compPiece;
						break;
					}
				}
				//draw player pieces
				for (Piece* currentPiece : realPlayer.pieces)
				{
					if (currentPiece->isAlive() && currentPiece->getX() == j && currentPiece->getY() == i)
					{
						isPiece = true;
						std::cout << realPiece;
						break;
					}
				}
				if (!isPiece)
				{
					std::cout << blackSpace;
				}
				
				
			}
			else
			{
				std::cout << whiteSpace;
			}

			//toggle bool
			isBlack = !isBlack;
			
		}
		//toggle bool
		isBlack = !isBlack;
		std::cout << std::endl;
	}
	//draw borders
	for (int i = 0; i < boardWidth + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
	if (computerTurn)
	{
		std::cout << "Computer's Turn...";
	}
	else 
	{
		std::cout << "Your Turn..."<<std::endl<<std::endl;
		std::cout << " You have " << realPlayer.getRemainingPieces() << " remaining" << std::endl;
		std::cout << " Your opponent has " << compPlayer.getRemainingPieces() << " remaining" << std::endl;
		std::cout << "\nUse WASD to move cursor" << std::endl;
		std::cout << "Press 'O' to pick up a piece or cancel a move" << std::endl;
		std::cout << "Press 'P' to drop a held piece onto a space" << std::endl;
	}
	
}

void GameManager::input()
{

	char input;
	input = _getch();
	switch (input)
	{

		int targetPos;
	case 'w':
		targetPos = cursorY - 1;
		if (targetPos >= 0)
		{
			cursorY = targetPos;
		}
		break;
	case 's':
		targetPos = cursorY + 1;
		if (targetPos < boardHeight)
		{
			cursorY = targetPos;
		}
		break;
	case 'a':
		targetPos = cursorX - 1;
		if (targetPos >= 1)
		{
			cursorX = targetPos;
		}
		break;
	case 'd':
		targetPos = cursorX + 1;
		if (targetPos < boardWidth + 1)
		{
			cursorX = targetPos;
		}
		break;
		//used to pick up and drop pieces
	case 'o':
		if (!computerTurn)
		{
			if (!pieceIsHeld)
			{
				//pick up piece
				for (Piece* currentPiece : realPlayer.pieces)
				{
					if (currentPiece->getX() == cursorX && currentPiece->getY() == cursorY)
					{
						pieceIsHeld = true;
						//make cursor look like piece
						cursor = realPiece;
						heldPiece = currentPiece;
						break;
					}
				}
			}
			else if(!jumpChain)
			{
				pieceIsHeld = false;
				//make cursor look as it normally does
				cursor = defaultCursor;
			}
		}
		break;
	case 'p':
		//drop piece
		if (pieceIsHeld)
		{
			if (attemptMove(*heldPiece, cursorX, cursorY) == true)
			{
				if (jumpChain == false)
				{
					//make cursor look as it normally does
					cursor = defaultCursor;
					pieceIsHeld = false;
					// if piece is dropped successfully, opponent plays
					computerTurn = true;
				}				
			}
		}

		break;
	default:
		break;
	}
	
	
}

void GameManager::logic()
{
	if (realPlayer.getRemainingPieces() == 0)
	{
		// you lose
		currentState = END;
		win = false;
	}
	else if (compPlayer.getRemainingPieces() == 0)
	{
		// you win
		currentState = END;
		win = true;
	}
	//computer plays
	if (aiActive == false && computerTurn)
	{
		aiActive = true;
		aiMove();	
	}



}

void GameManager::aiMove()
{
	bool success = false;
	do 
	{
		int randomIndex = rand() % compPlayer.pieces.size();
		heldPiece = compPlayer.pieces[randomIndex];
		//attempt a move
		//look for jumps first
		//attempt a jump
		int currentX = heldPiece->getX();
		int currentY = heldPiece->getY();
		//position of possible jumped piece
		int jumpX, jumpY;
		//jump to right
		if (currentX + 2 < boardWidth && currentY + 2 < boardHeight && !CheckLocationOccupied(currentX + 2, currentY + 2))
		{
			
			jumpY = heldPiece->getY() + 1;
			jumpX = currentX + 1;
			//iterate through all enemy pieces
			for (Piece* currentPiece : realPlayer.pieces)
			{
				if (currentPiece->getX() == jumpX && currentPiece->getY() == jumpY)
				{
					//jumped piece, move to new space but dont end turn
					heldPiece->setPosition(currentX + 2, currentY + 2);
					realPlayer.destroyPiece(currentPiece);
				}
			}
		}
		//jump to left
		else if (currentX - 2 > 0 && currentY + 2 < boardHeight && !CheckLocationOccupied(currentX - 2, currentY + 2))
		{
			jumpY = heldPiece->getY() + 1;
			jumpX = currentX - 1;
			//iterate through all enemy pieces
			for (Piece* currentPiece : realPlayer.pieces)
			{
				if (currentPiece->getX() == jumpX && currentPiece->getY() == jumpY)
				{
					//jumped piece, move to new space but dont end turn
					heldPiece->setPosition(currentX - 2, currentY + 2);
					realPlayer.destroyPiece(currentPiece);
				}
			}
		}
			
		//randomly choose left or right first
		int randomChoice = rand() % 2;
		// move down one and left or right 1
		switch (randomChoice)
		{
		case 0:
			if(attemptMove(*heldPiece, heldPiece->getX() + 1, heldPiece->getY() + 1))
			{
				success = true;
				break;
			}
			if (attemptMove(*heldPiece, heldPiece->getX() - 1, heldPiece->getY() + 1))
			{
				success = true;
				break;
			}
			break;
		case 1:
			if (attemptMove(*heldPiece, heldPiece->getX() - 1, heldPiece->getY() + 1))
			{
				success = true;
				break;
			}
			if (attemptMove(*heldPiece, heldPiece->getX() + 1, heldPiece->getY() + 1))
			{
				success = true;
				break;
			}
		default:
			break;
		}



	}while (success == false);
	
	system("cls");
	drawBoard();


	
	computerTurn = false;
	aiActive = false;
}

bool GameManager::attemptMove(Piece &heldPiece, int targetX, int targetY)
{
	if (targetX < 1 || targetX > boardWidth || targetY < 0 || targetY > boardHeight)
	{
		return false;
	}
	// handle real player code
	if (heldPiece.getOwner() == "Real")
	{
		if (CheckLocationOccupied(targetX, targetY))
		{
			//invalid move, occupied space
			return false;
		}
		// check if new location is above old location and the proper number of spaces away
		if (targetY < heldPiece.getY() && abs(targetX - heldPiece.getX()) % abs(targetY-heldPiece.getY()) == 0)
		{
			//if space is one row up
			if (targetY == heldPiece.getY() - 1 && abs(targetX - heldPiece.getX()) == 1)
			{
				heldPiece.setPosition(targetX, targetY);
				//piece was moved, end turn
				jumpChain = false;
				return true;
			}
			//attempt a jump
			else if (targetY == heldPiece.getY() - 2 && abs(targetX - heldPiece.getX()) == 2)
			{
				//position of possible jumped piece
				int jumpX, jumpY;
				jumpY = heldPiece.getY() - 1;
				jumpX = (targetX > heldPiece.getX()) ? targetX - 1 : targetX + 1;
				//iterate through all enemy pieces
				for (Piece* currentPiece : compPlayer.pieces)
				{
					if (currentPiece->getX() == jumpX && currentPiece->getY() == jumpY)
					{
						//jumped piece, move to new space but dont end turn
						heldPiece.setPosition(targetX, targetY);
						compPlayer.destroyPiece(currentPiece);	
						if ((targetX + 2 < boardWidth && targetY -2 > 0 && !CheckLocationOccupied(targetX + 2, targetY - 2)) 
							|| (targetX - 2 > 0 && targetY - 2 > 0 && !CheckLocationOccupied(targetX - 2, targetY - 2)))
						{
							jumpChain = true;
							return false;
						}
						jumpChain = false;
						return true;
						
	
					}
				}
				return false;

			}
		}

		return false;
	
	}
	// handle computer player code
	else if (heldPiece.getOwner() == "Comp")
	{
		if (CheckLocationOccupied(targetX, targetY))
		{
			//invalid move, occupied space
			return false;
		}
		// check if new location is below old location and the proper number of spaces away
		if (targetY > heldPiece.getY() && abs(targetX - heldPiece.getX()) % abs(targetY - heldPiece.getY()) == 0)
		{
			heldPiece.setPosition(targetX, targetY);
			return true;
		}

		return false;
	}
	else
	{
		perror("Invalid owner for piece");
		return false;
	}
}

bool GameManager::CheckLocationOccupied(int targetX, int targetY)
{
	for (Piece* currentPiece : realPlayer.pieces)
	{
		if (currentPiece->getX() == targetX && currentPiece->getY() == targetY)
		{
			return true;
		}
	}
	for (Piece* currentPiece : compPlayer.pieces)
	{
		if (currentPiece->getX() == targetX && currentPiece->getY() == targetY)
		{
			return true;
		}
	}
	return false;
}
