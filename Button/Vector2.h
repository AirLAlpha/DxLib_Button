/**********************************************
 *
 *  Vector2.h
 *  Vector2�Ɋւ��邢�낢����L��
 *
 *  ����ҁF���ە��m
 *  ������F2022/07/05
 *
 **********************************************/

#pragma once

#include <math.h>

class Vector2
{
public :
	//	�f�t�H���g�̃R���X�g���N�^
	Vector2()
	{
		x = 0;
		y = 0;
	};

	//	���������R���X�g���N�^
	Vector2(int X, int Y)
	{
		x = X;
		y = Y;
	};

	int x;
	int y;

	//	�x�N�g���̒�����Ԃ�
	static float Magnitude(Vector2 vec)
	{
		return sqrtf((float)vec.x * vec.x + (float)vec.y * vec.y);
	}

	//	2�_�Ԃ̋�����Ԃ�
	static float Distance(Vector2 posA, Vector2 posB)
	{
		Vector2 vec = posB - posA;
		return Magnitude(vec);
	}

	//	�ȉ����Z�q
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