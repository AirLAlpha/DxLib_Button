/**********************************************
 *
 *  Button.cpp
 *  �{�^���̏������L�q
 *
 *  ����ҁF���ە��m
 *  ������F2022/07/05
 *
 **********************************************/

#include <DxLib.h>
#include "Button.h"

#define EASE_SPEED						5.0f		//	�{�^���̃A�j���[�V�������x

//	��ʂ̒��S���W
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

//	����������
void Button::Initialize(Vector2 screenSize)
{
	this->screenSize = screenSize;

	ease = 0.0f;
}

//	�{�^���̍X�V����
void Button::Update(float deltaTime, Vector2 mousePos)
{
	Vector2 sizeHalf = size / 2;

	//	�{�^���̏�ɃJ�[�\�����������true
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

	//	�N���b�N������
	if (isToggle)
	{
		if (onMouse && isClick)
		{
			//	Toggle���[�h����
			//	�N���b�N���ꂽ��؂�ւ���
			buttonPressed = !buttonPressed;
		}
	}
	else
	{
		if (onMouse && isClick)
		{
			//	Toggle���[�h�ł͂Ȃ���
			//	�{�^����ŃN���b�N���ꂽ��true
			buttonPressed = true;
		}
		else
		{
			//	����ȊO��false
			buttonPressed = false;
		}
	}

	//	�i��g�O�����j�{�^���̏�ɃJ�[�\�����������C�[�W���O�����s
	//	�i�g�O�����j�@�{�^�����N���b�N����A�L���Ȃ�C�[�W���O�����s
	if ((!isToggle && onMouse) || (isToggle && buttonPressed))
	{
		ease += deltaTime * EASE_SPEED;
	}
	else
	{
		ease -= deltaTime * EASE_SPEED;
	}

	//	�C�[�W���O�p�ϐ��̃N�����v
	ease = min(max(0.0f, ease), 1.0f);
}

//	�{�^���̕`�揈��
void Button::Render()
{
	Vector2 sizeHalf = size / 2;

	//	�g���̕`��
	if (isFramelineActive)
	{
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, false);
	}

	//	�{�^���̔w�i��`��
	//	�{�^���̃^�C�v�ɂ���ăC�[�W���O��ω�����
	switch (easeType)
	{
		//	�����Ȃ�
	case Button::EaseType::Static:
		
		if (onMouse)
		{
			DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
				pos.x + sizeHalf.x, pos.y + sizeHalf.y,
				buttonColor, true);
		}
		break;

		//������E��
	case Button::EaseType::LeftToRight:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			(pos.x - sizeHalf.x) + size.x * Ease01(ease), pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	�E���獶��
	case Button::EaseType::RightToLeft:
		DrawBox((pos.x + sizeHalf.x) - size.x * Ease01(ease), pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	�ォ�牺
	case Button::EaseType::UpToDown:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, (pos.y - sizeHalf.y) + size.y * Ease01(ease),
			buttonColor, true);
		break;

		//	�������
	case Button::EaseType::DownToUp:
		DrawBox(pos.x - sizeHalf.x, (pos.y + sizeHalf.y) - size.y * Ease01(ease),
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	�O���璆�ցi�T�C�h�j
	case Button::EaseType::SideToCenter:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			(pos.x - sizeHalf.x) + sizeHalf.x * Ease01(ease), pos.y + sizeHalf.y,
			buttonColor, true);
		DrawBox((pos.x + sizeHalf.x) - sizeHalf.x * Ease01(ease), pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	������O�ցi�T�C�h�j
	case Button::EaseType::CenterToSide:
		DrawBox(pos.x - sizeHalf.x * Ease01(ease), pos.y - sizeHalf.y,
			pos.x, pos.y + sizeHalf.y,
			buttonColor, true);
		DrawBox(pos.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x * Ease01(ease), pos.y + sizeHalf.y,
			buttonColor, true);
		break;

		//	�O���璆�ցi�㉺�j
	case Button::EaseType::UpAndDownToCenter:
		DrawBox(pos.x - sizeHalf.x, pos.y - sizeHalf.y,
			pos.x + sizeHalf.x, (pos.y - sizeHalf.y) + sizeHalf.y * Ease01(ease),
			buttonColor, true);
		DrawBox(pos.x - sizeHalf.x, (pos.y + sizeHalf.y) - sizeHalf.y * Ease01(ease),
			pos.x + sizeHalf.x, pos.y + sizeHalf.y,
			buttonColor, true);
		break;
		
		//	������O�ցi�㉺�j
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

	//	�{�^���̃e�L�X�g��`��i���������j
	SetFontSize(textSize);
	DrawString(((screenSize.x - textWidth) / 2) + (pos.x - SCREEN_CENTER.x), pos.y - textSize / 2.0f, text, textColor);
	SetFontSize(saveFontSize);
}

void Button::Finalize()
{

}

//	���N���b�N�̎擾
bool Button::GetMouseLeftButton()
{
	//	���݂̃N���b�N���
	bool nowClick = (GetMouseInput() & MOUSE_INPUT_LEFT);

	//	1�t���[���O�ɃN���b�N����Ă��Ȃ��āA���N���b�N����Ă�����Atrue��Ԃ�
	if (nowClick == true && saveClick == false)
	{
		saveClick = nowClick;
		return true;
	}
	//	����ȊO��false��Ԃ�
	else if (nowClick == false && saveClick == true)
	{
		saveClick = false;
	}
	
	return false;
}

//	�{�^���̏������p�֐�
void Button::SetButton(Vector2 pos, Vector2 size, int buttonColor, const char* text, int textSize, int textColor, EaseType type)
{
	//	�e��ϐ���ݒ�
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

//	�{�^���̍��W��ݒ�
void Button::SetPos(Vector2 pos)
{
	this->pos = pos;
}

//	�{�^���̑傫����ݒ�
void Button::SetSize(Vector2 pos, Vector2 size)
{
	this->pos = pos;
	this->size = size;
}

//	�{�^���̔w�i�F��ݒ�
void Button::SetColor(int color)
{
	this->buttonColor = color;
}

//	�{�^���̃e�L�X�g��ݒ�
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

//	�{�^���̃t���[����ݒ�
void Button::SetFrameLine(bool active, int color)
{
	this->isFramelineActive = active;
	this->framelineColor = color;
}

//	�{�^���̃C�[�W���O�^�C�v��ݒ�
void Button::SetEaseType(EaseType type)
{
	this->easeType = type;
}

//	�{�^���̃g�O�����[�h�؂�ւ�
void Button::SetToggle(bool toggle)
{
	this->isToggle = toggle;
}

//	�{�^�����N���b�N���ꂽ���̕ϐ�
bool Button::GetIsPressed()
{
	return buttonPressed;
}

//	�{�^���p�C�[�W���O
float Button::Ease01(float x)
{
	double dx = (double)x;
	return (float)(dx < 0.5f ? 4 * dx * dx * dx : 1 - pow(-2 * dx + 2, 3) / 2);	
}

//	�{�^���p�C�[�W���O
float Button::Ease02(float x)
{
	double dx = (double)x;
	const double c1 = 1.70158f;
	const double c2 = c1 * 1.525f;

	return (float)(dx < 0.5
		? (pow(2.0 * dx, 2.0) * ((c2 + 1.0) * 2.0 * dx - c2)) / 2.0
		: (pow(2.0 * dx - 2.0, 2.0) * ((c2 + 1.0) * (dx * 2.0 - 2.0) + c2) + 2.0) / 2.0);
}