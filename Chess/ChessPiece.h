#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <list>

#include "Station.h"
#include "Move.h"

enum
{

	WR, WKn, WB, WQ, WK, WP,
	BR, BKn, BB, BQ, BK, BP

};

class ChessPiece {

private:
	std::wstring _unicode;
	int _color;
	int _code;

public:
	
	ChessPiece(std::wstring, int, int);
	ChessPiece() {}

	virtual void giveMoves(list<Move> &list, Square*, Station*, int color) = 0;
	
	void setUnicode(wstring);
	void setColor(int color);
	void setCode(int code);

	wstring getUnicode();
	int getColor();
	int getCode();	

	//void setUnicode(std::wstring unicode) { _unicode = unicode; }
	//std::wstring getUnicode() { return _unicode; }
	//void setColor(int color) { _color = color; }
	//int getColor() { return _color; }
	//int getCode() { return _code; }
	//void setCode(int code) { _code = code; }
};

class Rook : public virtual ChessPiece {
public:
	Rook(wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}
	void giveMoves(list<Move> &list, Square*, Station*, int color);

};

class Knight : public ChessPiece {

public:
	Knight(wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}
	void giveMoves(list<Move> &list, Square* , Station* , int color);
};

class Bishop : public virtual ChessPiece {

public:
	Bishop(wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}
	void giveMoves(list<Move> &list, Square* , Station* , int color);
};

class Queen : public Bishop, public Rook {
public:
	Queen(wstring unicode, int color, int code) : ChessPiece(unicode, color, code), Bishop(unicode, color, code), Rook(unicode, color, code) {}
	void giveMoves(list<Move> &list, Square* , Station* , int color);

};

class King : public ChessPiece {
public:
	King(wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}
	void giveMoves(list<Move> &list, Square* , Station* , int color);
};

class Pawn : public ChessPiece {

public:
	Pawn(wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}
	void giveMoves(list<Move> &list, Square* , Station* , int color);
};