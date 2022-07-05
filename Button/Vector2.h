/**********************************************
 *
 *  Vector2.h
 *  Vector2に関するいろいろを記載
 *
 *  製作者：牛丸文仁
 *  制作日：2022/07/05
 *
 **********************************************/

#pragma once

#include <math.h>

class Vector2
{
public :
	//	デフォルトのコンストラクタ
	Vector2()
	{
		x = 0;
		y = 0;
	};

	//	引数を持つコンストラクタ
	Vector2(int X, int Y)
	{
		x = X;
		y = Y;
	};

	int x;
	int y;

	//	ベクトルの長さを返す
	static float Magnitude(Vector2 vec)
	{
		return sqrtf((float)vec.x * vec.x + (float)vec.y * vec.y);
	}

	//	2点間の距離を返す
	static float Distance(Vector2 posA, Vector2 posB)
	{
		Vector2 vec = posB - posA;
		return Magnitude(vec);
	}

	//	以下演算子
	Vector2 operator +(Vector2 vec)
	{
		Vector2 vector;
		vector.x = this->x + vec.x;
		vector.y = this->y + vec.y;
		return vector;
	}

	Vector2 operator -(Vector2 vec)
	{
		Vector2 vector;
		vector.x = this->x - vec.x;
		vector.y = this->y - vec.y;
		return vector;
	}

	Vector2 operator *(int value)
	{
		Vector2 vector;
		vector.x = this->x * value;
		vector.y = this->y * value;
		return vector;
	}

	Vector2 operator /(int value)
	{
		Vector2 vector;
		vector.x = this->x / value;
		vector.y = this->y / value;
		return vector;
	}

	Vector2 operator +=(Vector2 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	Vector2 operator -=(Vector2 vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		return *this;
	}

	Vector2 operator *=(int value)
	{
		this->x *= value;
		this->y *= value;
		return *this;
	}

	Vector2 operator /=(int value)
	{
		this->x /= value;
		this->y /= value;
		return *this;
	}

	bool operator ==(Vector2 vec)
	{
		bool bx = this->x == vec.x;
		bool by = this->y == vec.y;
		return bx && by;
	}

	bool operator !=(Vector2 vec)
	{
		bool bx = this->x != vec.x;
		bool by = this->y != vec.y;
		return bx || by;
	}
};