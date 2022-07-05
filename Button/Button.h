/**********************************************
 *
 *  Button.h
 *  Button.cppのヘッダーファイル
 *
 *  製作者：牛丸文仁
 *  制作日：2022/07/05
 *
 **********************************************/

#pragma once
#include "Vector2.h"

class Button
{
public:
	enum class EaseType 
	{
		Static,
		LeftToRight,
		RightToLeft,
		UpToDown,
		DownToUp,
		SideToCenter,
		CenterToSide,
		UpAndDownToCenter,
		CenterToUpAndDown,
	};

private:
	EaseType easeType;
	bool isToggle;

	Vector2 screenSize;

	Vector2 pos;
	Vector2 size;
	int buttonColor;

	const char* text;
	int textSize;
	int textWidth;
	int textColor;

	bool isFramelineActive;
	int framelineColor;

	float ease;

	bool onMouse;
	bool saveClick;
	bool buttonPressed;

public:
	Button();
	~Button();

	void Initialize(Vector2 screenSize);
	void Update(float deltaTime, Vector2 mousePos);
	void Render();
	void Finalize();

	bool GetMouseLeftButton();

	void SetButton(Vector2 pos, Vector2 size, int buttonColor, const char* text, int textSize, int textColor, EaseType type);
	
	void SetPos(Vector2 pos);
	void SetSize(Vector2 pos, Vector2 size);
	void SetColor(int color);
	void SetText(const char* text, int textSize, int textColor);
	void SetEaseType(EaseType type);
	void SetToggle(bool toggle);
	void SetFrameLine(bool active, int color);

	bool GetIsPressed();

	float Ease01(float x);
	float Ease02(float x);
};