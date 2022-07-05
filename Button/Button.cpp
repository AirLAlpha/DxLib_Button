/**********************************************
 *
 *  Button.cpp
 *  ボタンの処理を記述
 *
 *  製作者：牛丸文仁
 *  制作日：2022/07/05
 *
 **********************************************/

#include <DxLib.h>
#include "Button.h"

#define EASE_SPEED						5.0f		//	ボタンのアニメーション速度

//	画面の中心座標
#define SCREEN_CENTER					Vector2(screenSize.x / 2, screenSize.y / 2)

Button::Button()
{
	textColor = 0;
	textWidth = 0;
	buttonColor = 0;
	text = nullptr;
	textSize = 0;
	onMouse = false;
	easeType = EaseType::Static;
	isToggle = false;

	isFramelineActive = false;
	framelineColor = 0;

	ease = 0.0f;
	saveClick = false;
	buttonPressed = false;
}

Button::~Button()
{

}

//	初期化処理
void Button::Initialize(Vector2 screenSize)
{
	this->screenSize = screenSize;

	ease = 0.0f;
}

//	ボタンの更新処理
void Button::Update(float deltaTime, Vector2 mousePos)
{
	Vector2 sizeHalf = size / 2;

	//	ボタンの上にカーソルが乗ったらtrue
	if (mousePos.x > pos.x - sizeHalf.x && mousePos.x < pos.x + sizeHalf.x && 
		mousePos.y > pos.y - sizeHalf.y && mousePos.y < pos.y + sizeHalf.y)
	{
		onMouse = true;
	}
	else
	{
		onMouse = false;
	}

	bool isClick = GetMouseLeftButton();

	//	クリック時処理
	if (isToggle)
	{
		if (onMouse && isClick)
		{
			//	Toggleモード時は
			//	クリックされたら切り替える
			buttonPressed = !buttonPressed;
		}
	}
	else
	{
		if (onMouse && isClick)
		{
			//	Toggleモードではない時
			//	ボタン上でクリックされたらtrue
			buttonPressed = true;
		}
		else
		{
			//	それ以外はfalse
			buttonPressed = false;
		}
	}

	//	（非トグル時）ボタンの上にカーソルが乗ったらイージングを実行
	//	（トグル時）　ボタンがクリックされ、有効ならイージングを実行
	if ((!isToggle && onMouse) || (isToggle && buttonPressed))
	{
		ease += deltaTime * EASE_SPEED;
	}
	else
	{
		ease -= deltaTime * EASE_SPEED;
	}

	//	イージング用変数のクランプ
	ease = min(max(0.0f, ease), 1.0f);
}

//	ボタンの描画処理
void Button::Render()
{
	Vector2 sizeHalf = size / 2;

	//	枠線の描画
	if (isFramelineActive)
	{
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, false);
	}

	//	ボタンの背景を描画
	//	ボタンのタイプによってイージングを変化する
	switch (easeType)
	{
		//	動きなし
	case Button::EaseType::Static:
		
		if (onMouse)
		{
			DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
				pos.x + sizeHalf.x, pos.y + sizeHalf.y,
				buttonColor, true);
		}
		break;

		//左から右へ
	case Button::EaseType::LeftToRight:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			(pos.x - sizeHalf.x) + size.x * Ease01(ease), pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	右から左へ
	case Button::EaseType::RightToLeft:
		DrawBox((pos.x + sizeHalf.x) - size.x * Ease01(ease), pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	上から下
	case Button::EaseType::UpToDown:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, (pos.y - sizeHalf.y) + size.y * Ease01(ease),
			buttonColor, true);
		break;

		//	下から上
	case Button::EaseType::DownToUp:
		DrawBox(pos.x - sizeHalf.x, (pos.y + sizeHalf.y) - size.y * Ease01(ease),
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	外から中へ（サイド）
	case Button::EaseType::SideToCenter:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			(pos.x - sizeHalf.x) + sizeHalf.x * Ease01(ease), pos.y + sizeHalf.y,
			buttonColor, true);
		DrawBox((pos.x + sizeHalf.x) - sizeHalf.x * Ease01(ease), pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	中から外へ（サイド）
	case Button::EaseType::CenterToSide:
		DrawBox(pos.x - sizeHalf.x * Ease01(ease), pos.y - sizeHalf.y,
			pos.x, pos.y + sizeHalf.y,
			buttonColor, true);
		DrawBox(pos.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x * Ease01(ease), pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	外から中へ（上下）
	case Button::EaseType::UpAndDownToCenter:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, (pos.y - sizeHalf.y) + sizeHalf.y * Ease01(ease),
			buttonColor, true);
		DrawBox(pos.x - sizeHalf.x, (pos.y + sizeHalf.y) - sizeHalf.y * Ease01(ease),
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;
		
		//	中から外へ（上下）
	case Button::EaseType::CenterToUpAndDown:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y * Ease01(ease),
			pos.x + sizeHalf.x, pos.y,
			buttonColor, true);
		DrawBox(pos.x - sizeHalf.x, pos.y,
			pos.x + sizeHalf.x, pos.y + sizeHalf.y * Ease01(ease),
			buttonColor, true);
		break;

	default:
		break;
	}

	int saveFontSize = GetFontSize();

	//	ボタンのテキストを描画（中央揃え）
	SetFontSize(textSize);
	DrawString(((screenSize.x - textWidth) / 2) + (pos.x - SCREEN_CENTER.x), pos.y - textSize / 2.0f, text, textColor);
	SetFontSize(saveFontSize);
}

void Button::Finalize()
{

}

//	左クリックの取得
bool Button::GetMouseLeftButton()
{
	//	現在のクリック状態
	bool nowClick = (GetMouseInput() & MOUSE_INPUT_LEFT);

	//	1フレーム前にクリックされていなくて、今クリックされていたら、trueを返す
	if (nowClick == true && saveClick == false)
	{
		saveClick = nowClick;
		return true;
	}
	//	それ以外はfalseを返す
	else if (nowClick == false && saveClick == true)
	{
		saveClick = false;
	}
	
	return false;
}

//	ボタンの初期化用関数
void Button::SetButton(Vector2 pos, Vector2 size, int buttonColor, const char* text, int textSize, int textColor, EaseType type)
{
	//	各種変数を設定
	this->pos = pos;
	this->size = size;
	this->buttonColor = buttonColor;
	this->text = text;
	this->textSize = textSize;
	this->textColor = textColor;
	this->easeType = type;

	int saveFontSize = GetFontSize();

	SetFontSize(textSize);
	textWidth = GetDrawStringWidth(text, -1);
	SetFontSize(saveFontSize);
}

//	ボタンの座標を設定
void Button::SetPos(Vector2 pos)
{
	this->pos = pos;
}

//	ボタンの大きさを設定
void Button::SetSize(Vector2 pos, Vector2 size)
{
	this->pos = pos;
	this->size = size;
}

//	ボタンの背景色を設定
void Button::SetColor(int color)
{
	this->buttonColor = color;
}

//	ボタンのテキストを設定
void Button::SetText(const char* text, int textSize, int textColor)
{
	this->text = text;
	this->textSize = textSize;
	this->textColor = textColor;

	int saveFontSize = GetFontSize();

	SetFontSize(textSize);
	textWidth = GetDrawStringWidth(text, -1);
	SetFontSize(saveFontSize);
}

//	ボタンのフレームを設定
void Button::SetFrameLine(bool active, int color)
{
	this->isFramelineActive = active;
	this->framelineColor = color;
}

//	ボタンのイージングタイプを設定
void Button::SetEaseType(EaseType type)
{
	this->easeType = type;
}

//	ボタンのトグルモード切り替え
void Button::SetToggle(bool toggle)
{
	this->isToggle = toggle;
}

//	ボタンがクリックされたかの変数
bool Button::GetIsPressed()
{
	return buttonPressed;
}

//	ボタン用イージング
float Button::Ease01(float x)
{
	double dx = (double)x;
	return (float)(dx < 0.5f ? 4 * dx * dx * dx : 1 - pow(-2 * dx + 2, 3) / 2);	
}

//	ボタン用イージング
float Button::Ease02(float x)
{
	double dx = (double)x;
	const double c1 = 1.70158f;
	const double c2 = c1 * 1.525f;

	return (float)(dx < 0.5
		? (pow(2.0 * dx, 2.0) * ((c2 + 1.0) * 2.0 * dx - c2)) / 2.0
		: (pow(2.0 * dx - 2.0, 2.0) * ((c2 + 1.0) * (dx * 2.0 - 2.0) + c2) + 2.0) / 2.0);
}