#pragma once
#include "ChessPiece.h"
#include "Station.h"
#include "ChessPiece.h"

#include <string>;
#include <list>
using namespace std;

ChessPiece::ChessPiece(wstring unicode, int color, int code)
	{
		_unicode = unicode;
		_color = color;
		_code = code;

	}

void ChessPiece::setUnicode(wstring unicode) {
		_unicode = unicode;
}
void ChessPiece::setColor(int color) {
		_color = color;
}
void ChessPiece::setCode(int code) {
		_code = code;
	}

wstring ChessPiece::getUnicode() {
		return _unicode;
}
int ChessPiece::getColor() {
		return _color;
}
int ChessPiece::getCode() {
		return _code;
}

void Bishop::giveMoves(std::list<Move> &list, Square* square, Station* station, int color)
{
	int startSquareY = square->getLine();
	int startSquareX = square->getColumn();

	int startSquarePieceColor;
	int endSquarePieceColor;

	int j;

	startSquarePieceColor = station->board[startSquareX][startSquareY]->getColor();

	//NE
	for (int i = startSquareX + 1; i<8; i++) {
		if (i == startSquareX + 1) {
			j = startSquareY + 1;
		}
		if (j < 0 || j>7 || i < 0 || i>7) {
			break;
		}
		if (station->board[i][j] == NULL) {
			list.push_back(Move(*square, Square(i, j)));
		}
		else if (station->board[i][j] != NULL) {
			endSquarePieceColor = station->board[i][j]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
				break;
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(i, j)));
				break;
			}
		}
		j++;
	}
	//SE
	for (int i = startSquareX + 1; i < 8; i++) {
		if (i == startSquareX + 1) {
			j = startSquareY - 1;
		}
		if (j < 0 || j > 7 || i < 0 || i > 7) {
			break;
		}
		if (station->board[i][j] == NULL) {
			list.push_back(Move(*square, Square(i, j)));
		}
		else if (station->board[i][j] != NULL) {
			endSquarePieceColor = station->board[i][j]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
				break;
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(i, j)));
				break;
			}
		}
		j--;
	}
	//NW
	for (int i = startSquareX - 1; i >= 0; i--) {
		if (i == startSquareX - 1) {
			j = startSquareY + 1;
		}
		if (j < 0 || j > 7 || i < 0 || i > 7) {
			break;
		}
		if (station->board[i][j] == NULL) {
			list.push_back(Move(*square, Square(i, j)));
		}
		else if (station->board[i][j] != NULL) {
			endSquarePieceColor = station->board[i][j]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
				break;
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(i, j)));
				break;
			}
		}
		j++;
	}
	//SW
	for (int i = startSquareX - 1; i >= 0; i--) {
		if (i == startSquareX - 1) {
			j = startSquareY - 1;
		}
		if (j < 0 || j > 7 || i < 0 || i > 7) {
			break;
		}
		if (station->board[i][j] == NULL) {
			list.push_back(Move(*square, Square(i, j)));
		}
		else if (station->board[i][j] != NULL) {
			endSquarePieceColor = station->board[i][j]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
				break;
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(i, j)));
				break;
			}
		}
		j--;
	}
	/*for (auto s : list) {
		std::wcout << L"Bishop";
		std::wcout << s.getStartPos.getColumn();
		std::wcout << s.getStartPos.getLine();

		std::wcout << s.getEndPos.GetColumn();
		std::wcout << s.getEndPos.getLine();
	}*/
}
void Queen::giveMoves(std::list<Move> &list, Square* square, Station* station, int color) {
	this->Bishop::giveMoves(list, square, station, color);
	this->Rook::giveMoves(list, square, station, color);
	/*for (auto s : list)
	{
		std::wcout << L"Queen";
		std::wcout << s.getStartPos.getColumn();
		std::wcout << s.getStartPos.getLine();

		std::wcout << s.getEndPos.getColumn();
		std::wcout << s.getEndPos.getLine();
	}*/
}
void Knight::giveMoves(std::list<Move> &list, Square* square, Station* station, int color)
{
	int startSquareY = square->getLine();
	int startSquareX = square->getColumn();
	int startSquarePieceColor;
	int endSquarePieceColor;
	startSquarePieceColor = station->board[startSquareX][startSquareY]->getColor();

	if (startSquareX + 1 < 8 && startSquareY + 2 < 8) {
		if (station->board[startSquareX + 1][startSquareY + 2] == NULL) {
			list.push_back(Move(*square, Square(startSquareX + 1, startSquareY + 2)));
		}
		else if (station->board[startSquareX + 1][startSquareY + 2] != NULL) {
			endSquarePieceColor = station->board[startSquareX + 1][startSquareY + 2]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX + 1, startSquareY + 2)));
			}
		}
	}
	if (startSquareX + 1 < 8 && startSquareY - 2 >= 0) {
		if (station->board[startSquareX + 1][startSquareY - 2] == NULL) {
			list.push_back(Move(*square, Square(startSquareX + 1, startSquareY - 2)));
		}
		else if (station->board[startSquareX + 1][startSquareY - 2] != NULL) {
			endSquarePieceColor = station->board[startSquareX + 1][startSquareY - 2]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX + 1, startSquareY - 2)));
			}
		}
	}
	if (startSquareX - 1 >= 0 && startSquareY + 2 < 8) {
		if (station->board[startSquareX - 1][startSquareY + 2] == NULL) {
			list.push_back(Move(*square, Square(startSquareX - 1, startSquareY + 2)));
		}
		else if (station->board[startSquareX - 1][startSquareY + 2] != NULL) {
			endSquarePieceColor = station->board[startSquareX - 1][startSquareY + 2]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX - 1, startSquareY + 2)));
			}
		}
	}
	if (startSquareX - 1 >= 0 && startSquareY - 2 >= 0) {
		if (station->board[startSquareX - 1][startSquareY - 2] == NULL) {
			list.push_back(Move(*square, Square(startSquareX - 1, startSquareY + 2)));
		}
		else if (station->board[startSquareX - 1][startSquareY - 2] != NULL) {
			endSquarePieceColor = station->board[startSquareX - 1][startSquareY - 2]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX - 1, startSquareY - 2)));
			}
		}
	}
	if (startSquareX + 2 < 8 && startSquareY + 1 < 8) {
		if (station->board[startSquareX + 2][startSquareY + 1] == NULL) {
			list.push_back(Move(*square, Square(startSquareX + 2, startSquareY + 1)));
		}
		else if (station->board[startSquareX + 2][startSquareY + 1] != NULL) {
			endSquarePieceColor = station->board[startSquareX + 2][startSquareY + 1]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX + 2, startSquareY + 1)));
			}
		}
	}
	if (startSquareX + 2 < 8 && startSquareY - 1 >= 0) {
		if (station->board[startSquareX + 2][startSquareY - 1] == NULL) {
			list.push_back(Move(*square, Square(startSquareX + 2, startSquareY - 1)));
		}
		else if (station->board[startSquareX + 2][startSquareY - 1] != NULL) {
			endSquarePieceColor = station->board[startSquareX + 2][startSquareY - 1]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX + 2, startSquareY - 1)));
			}
		}
	}
	if (startSquareX - 2 >= 0 && startSquareY + 1 < 8) {
		if (station->board[startSquareX - 2][startSquareY + 1] == NULL) {
			list.push_back(Move(*square, Square(startSquareX - 2, startSquareY + 1)));
		}
		else if (station->board[startSquareX - 2][startSquareY + 1] != NULL) {
			endSquarePieceColor = station->board[startSquareX - 2][startSquareY + 1]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX - 2, startSquareY + 1)));
			}
		}
	}
	if (startSquareX - 2 >= 0 && startSquareY - 1 >= 0) {
		if (station->board[startSquareX - 2][startSquareY - 1] == NULL) {
			list.push_back(Move(*square, Square(startSquareX - 2, startSquareY - 1)));
		}
		else if (station->board[startSquareX - 2][startSquareY - 1] != NULL) {
			endSquarePieceColor = station->board[startSquareX - 2][startSquareY - 1]->getColor();
			if (startSquarePieceColor == endSquarePieceColor) {
			}
			if (startSquarePieceColor != endSquarePieceColor) {
				list.push_back(Move(*square, Square(startSquareX - 2, startSquareY - 1)));
			}
		}
	}
}
void Pawn::giveMoves(std::list<Move> &list, Square* square, Station* station, int color)
{
	int startSquareY = square->getLine();
	int startSquareX = square->getColumn();
	int startSquarePieceColor;
	int endSquarePieceColor;
	startSquarePieceColor = station->board[startSquareX][startSquareY]->getColor();

	if (startSquareY == 1 && startSquarePieceColor == 0) {
		for (int i = startSquareY + 1; i < startSquareY + 3; i++) {
			if (station->board[startSquareX][i] == NULL) {
				list.push_back(Move(*square, Square(startSquareX, i)));
			}
			else
				break;
		}
	}
	if (startSquareY == 6 && startSquarePieceColor == 1) {
		for (int i = startSquareY - 1; i > startSquareY - 3; i--) {
			if (station->board[startSquareX][i] == NULL) {
				list.push_back(Move(*square, Square(startSquareX, i)));
			}
			else
				break;
		}
	}
	if ((startSquareY == 2 || startSquareY == 3 || startSquareY == 4 || startSquareY == 5 || startSquareY == 6) && startSquarePieceColor == 0) {
		if (station->board[startSquareX][startSquareY + 1] == NULL) {
			if (startSquareY < 6) {
				list.push_back(Move(*square, Square(startSquareX, startSquareY + 1)));
			}
		}
		if (startSquareX + 1 < 8) {
			if (station->board[startSquareX + 1][startSquareY + 1] != NULL) {
				endSquarePieceColor = station->board[startSquareX + 1][startSquareY + 1]->getColor();
				if (startSquarePieceColor == endSquarePieceColor) {

				}
				if (startSquarePieceColor != endSquarePieceColor) {
					if (startSquareY < 6)
						list.push_back(Move(*square, Square(startSquareX + 1, startSquareY + 1)));
				}
			}
		}
		if (startSquareX - 1 >= 0) {
			if (station->board[startSquareX - 1][startSquareY + 1] != NULL) {
				endSquarePieceColor = station->board[startSquareX - 1][startSquareY + 1]->getColor();
				if (startSquarePieceColor == endSquarePieceColor) {

				}
				if (startSquarePieceColor != endSquarePieceColor) {
					if (startSquareY < 6)
						list.push_back(Move(*square, Square(startSquareX - 1, startSquareY + 1)));
				}
			}
		}
	}

	//black
	if ((startSquareY == 5 || startSquareY == 4 || startSquareY == 3 || startSquareY == 2 || startSquareY == 1) && startSquarePieceColor == 1) {
		if (station->board[startSquareX][startSquareY - 1] == NULL) {
			if (startSquareY > 1) {
				list.push_back(Move(*square, Square(startSquareX, startSquareY - 1)));
			}
		}
		if (startSquareX + 1 < 8) {
			if (station->board[startSquareX + 1][startSquareY - 1] != NULL) {
				endSquarePieceColor = station->board[startSquareX + 1][startSquareY - 1]->getColor();
				if (startSquarePieceColor == endSquarePieceColor) {

				}
				if (startSquarePieceColor != endSquarePieceColor) {
					if (startSquareY > 1)
						list.push_back(Move(*square, Square(startSquareX + 1, startSquareY - 1)));
				}
			}
		}
		if (startSquareX - 1 >= 0) {
			if (station->board[startSquareX - 1][startSquareY - 1] != NULL) {
				endSquarePieceColor = station->board[startSquareX - 1][startSquareY - 1]->getColor();
				if (startSquarePieceColor == endSquarePieceColor) {

				}
				if (startSquarePieceColor != endSquarePieceColor) {
					if (startSquareY < 6)
						list.push_back(Move(*square, Square(startSquareX - 1, startSquareY - 1)));
				}
			}
		}
	}
}
void Rook::giveMoves(list<Move> &list, Square* square, Station* station, int color) {

	int startX = square->getColumn();
	int startY = square->getLine();


	int startChessPieceColor;
	int endChessPieceColor;

	startChessPieceColor = station->board[startX][startY]->getColor();

	for (int i = startX + 1; i < 8; i++)
	{

		if (station->board[i][startY] == NULL) {
			list.push_back(Move(*square, Square(i, startY)));
		}
		else if (station->board[i][startY] != NULL) {
			endChessPieceColor = station->board[i][startY]->getColor();

			if (startChessPieceColor == endChessPieceColor) {
				break;
			}

			if (startChessPieceColor != endChessPieceColor) {

				list.push_back(Move(*square, Square(i, startY)));
				break;
			}

		}

	}

	for (int i = startX - 1; i >= 0; i--)
	{

		if (station->board[i][startY] == NULL) {
			list.push_back(Move(*square, Square(i, startY)));
		}
		else if (station->board[i][startY] != NULL) {
			endChessPieceColor = station->board[i][startY]->getColor();

			if (startChessPieceColor == endChessPieceColor) {
				break;
			}

			if (startChessPieceColor != endChessPieceColor) {

				list.push_back(Move(*square, Square(i, startY)));
				break;
			}

		}

	}

	for (int i = startY + 1; i < 8; i++)
	{
		if (station->board[startX][i] == NULL) {
			list.push_back(Move(*square, Square(startX, i)));
		}
		else if (station->board[startX][i] != NULL) {
			endChessPieceColor = station->board[startX][i]->getColor();

			if (startChessPieceColor == endChessPieceColor) {
				break;
			}

			if (startChessPieceColor != endChessPieceColor) {

				list.push_back(Move(*square, Square(startX, i)));
				break;
			}

		}

	}

	for (int i = startY - 1; i >= 0; i--)
	{
		if (station->board[startX][i] == NULL) {
			list.push_back(Move(*square, Square(startX, i)));
		}
		else if (station->board[startX][i] != NULL) {
			endChessPieceColor = station->board[startX][i]->getColor();

			if (startChessPieceColor == endChessPieceColor) {
				break;
			}

			if (startChessPieceColor != endChessPieceColor) {

				list.push_back(Move(*square, Square(startX, i)));
				break;
			}

		}
	}
}
void King::giveMoves(list<Move> &list, Square* square, Station* station, int color) {
	int startX = square->getColumn();
	int startY = square->getLine();


	int startChessPieceColor;
	int endChessPieceColor;

	startChessPieceColor = station->board[startX][startY]->getColor();

	if (startX + 1 < 8)
	{
		if (station->board[startX + 1][startY] == NULL) {
			list.push_back(Move(*square, Square(startX + 1, startY)));
		}
		else if (station->board[startX + 1][startY] != NULL) {
			endChessPieceColor = station->board[startX + 1][startY]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX + 1, startY)));
			}
		}
	}

	if (startX + 1 < 8 && startY + 1 < 8)
	{
		if (station->board[startX + 1][startY + 1] == NULL) {
			list.push_back(Move(*square, Square(startX + 1, startY + 1)));
		}
		else if (station->board[startX + 1][startY + 1] != NULL) {
			endChessPieceColor = station->board[startX + 1][startY + 1]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX + 1, startY + 1)));
			}
		}
	}

	if (startX + 1 < 8 && startY - 1 >= 0)
	{
		if (station->board[startX + 1][startY - 1] == NULL) {
			list.push_back(Move(*square, Square(startX + 1, startY - 1)));
		}
		else if (station->board[startX + 1][startY - 1] != NULL) {
			endChessPieceColor = station->board[startX + 1][startY - 1]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX + 1, startY - 1)));
			}
		}
	}

	if (startX - 1 >= 0)
	{
		if (station->board[startX - 1][startY] == NULL)
		{
			list.push_back(Move(*square, Square(startX - 1, startY)));
		}
		else if (station->board[startX - 1][startY] != NULL)
		{
			endChessPieceColor = station->board[startX - 1][startY]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX - 1, startY)));
			}
		}
	}

	if (startX - 1 >= 0 && startY + 1 < 8)
	{
		if (station->board[startX - 1][startY + 1] == NULL) {
			list.push_back(Move(*square, Square(startX - 1, startY + 1)));
		}
		else if (station->board[startX - 1][startY + 1] != NULL) {
			endChessPieceColor = station->board[startX - 1][startY + 1]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX - 1, startY + 1)));
			}
		}
	}

	if (startX - 1 >= 0 && startY - 1 >= 0)
	{
		if (station->board[startX - 1][startY - 1] == NULL) {
			list.push_back(Move(*square, Square(startX - 1, startY - 1)));
		}
		else if (station->board[startX - 1][startY - 1] != NULL) {
			endChessPieceColor = station->board[startX - 1][startY - 1]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX - 1, startY - 1)));
			}
		}
	}

	if (startY + 1 < 8)
	{
		if (station->board[startX][startY + 1] == NULL) {
			list.push_back(Move(*square, Square(startX, startY + 1)));
		}
		else if (station->board[startX][startY + 1] != NULL) {
			endChessPieceColor = station->board[startX][startY + 1]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX, startY + 1)));
			}
		}
	}

	if (startY - 1 >= 0)
	{
		if (station->board[startX][startY - 1] == NULL) {
			list.push_back(Move(*square, Square(startX, startY - 1)));
		}
		else if (station->board[startX][startY - 1] != NULL) {
			endChessPieceColor = station->board[startX][startY - 1]->getColor();

			if (startChessPieceColor != endChessPieceColor) {
				list.push_back(Move(*square, Square(startX, startY - 1)));
			}
		}
	}
}















