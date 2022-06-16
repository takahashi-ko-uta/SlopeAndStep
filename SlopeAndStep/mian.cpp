#include "DxLib.h"
#include <cmath>
#include <iostream>
#include <math.h>

#include "Collision.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�X���[�v�ƒi���̎���";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 600;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0, 0, 0);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	Line line
	{
		0,600,600,0
	};

	Circle circle//�{��
	{
		200,300,50,
		0,0
	};

	Circle circle2//���̈ړ��p
	{
		200,300,50,
		0,0
	};

	Line floor//��
	{
		0,500,600,500
	};

	Line step//�i��
	{
		300,500,600,500
	};

	Point point
	{
		0,
		0
	};


	float speed = 3.0f;

	int scene = 0;//0 = �΂߈ړ�,1 = �i��

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����


		switch (scene)
		{
			case 0:
#pragma region �΂߈ړ�
				//�X�V����
#pragma region �~�̈ړ�
				if (keys[KEY_INPUT_W] == 1)//��
				{
					circle2.posY -= speed;
				}
				else if (keys[KEY_INPUT_S] == 1)//��
				{
					circle2.posY += speed;
				}
				else if (keys[KEY_INPUT_A] == 1)//��
				{
					circle2.posX -= speed;
				}
				else if (keys[KEY_INPUT_D] == 1)//�E
				{
					circle2.posX += speed;
				}
				circle2.flag1 = LineAndCircleCollision(line, circle2);


				if (circle2.flag1 == 1)
				{
					circle2.posX = circle.posX;
					circle2.posY = circle.posY;
					if (keys[KEY_INPUT_S] == 1)//��
					{
						circle2.posX -= speed;
						circle2.posY += speed;
					}
					else if (keys[KEY_INPUT_D] == 1)//�E
					{
						circle2.posX += speed;
						circle2.posY -= speed;
					}
					circle2.flag1 = LineAndCircleCollision(line, circle2);
				}
				if (circle2.flag1 == 0)
				{
					circle.posX = circle2.posX;
					circle.posY = circle2.posY;
				}
#pragma endregion
				//�V�[���؂�ւ�
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					scene = 1;
					//���Z�b�g
					circle.posX = 200;
					circle.posY = 300;
				}

				//�`�揈��
				DrawLine(line.StartX, line.StartY, line.EndX, line.EndY, GetColor(255, 255, 255));
				if (circle2.flag1 == 1)
				{
					DrawCircle(circle.posX, circle.posY, circle.radius, GetColor(255, 0, 0), false);
				}
				else
				{
					DrawCircle(circle.posX, circle.posY, circle.radius, GetColor(255, 255, 255), false);
				}
#pragma endregion
				break;
			case 1:
#pragma region �i��
				//�X�V����
#pragma region �~�̈ړ�

				if (keys[KEY_INPUT_W] == 1)//��
				{
					circle2.posY -= speed;
				}
				else if (keys[KEY_INPUT_S] == 1)//��
				{
					circle2.posY += speed;
				}
				else if (keys[KEY_INPUT_A] == 1)//��
				{
					circle2.posX -= speed;
				}
				else if (keys[KEY_INPUT_D] == 1)//�E
				{
					circle2.posX += speed;

				}

				point.posX = step.StartX;
				point.posY = step.StartY;

				circle2.flag1 = LineAndCircleCollision(floor, circle2);
				circle2.flag2 = LineAndCircleCollision(step, circle2);
				circle2.flag3 = PointAndCircleCollision(point, circle2);


				if (circle2.flag1 == 1 || circle2.flag2 == 1 || circle2.flag3 == 1)
				{
					circle2.posX = circle.posX;
					circle2.posY = circle.posY;
					if (circle2.flag3 == 1)//�i���ɓ��������Ƃ�
					{
						if (keys[KEY_INPUT_D] == 1)
						{
							if (-circle2.radius / 2 <=
								step.StartY - (circle2.posY + circle2.radius))//�~��1/4�̍����ƒi���̍������r
							{
								circle2.posY += step.StartY - (circle2.posY + circle2.radius);
							}
						}
					}
				}
				if (circle2.flag1 == 0 || circle2.flag2 == 0 || circle2.flag3 == 0)
				{
					circle.posX = circle2.posX;
					circle.posY = circle2.posY;
				}




#pragma endregion

#pragma region �i���̈ړ�
				if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0)
				{
					step.StartY -= 25;
					step.EndY -= 25;
				}
				else if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0)
				{
					step.StartY += 25;
					step.EndY += 25;
				}
#pragma endregion
				//�V�[���؂�ւ�
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					scene = 0;
					//���Z�b�g
					circle2.posX = 200;
					circle2.posY = 300;
					line.EndX = 600;
					line.EndY = 0;
				}
				//�`�揈��
				DrawLine(floor.StartX, floor.StartY, floor.EndX, floor.EndY, GetColor(255, 255, 255));//��
				DrawLine(step.StartX, step.StartY, step.EndX, step.EndY, GetColor(255, 255, 255));//�i��
				DrawLine(step.StartX, step.StartY, 300, 500, GetColor(255, 255, 255));//�i��
				DrawCircle(circle.posX, circle.posY, circle.radius, GetColor(255, 255, 255), false);

				DrawFormatString(10, 30, GetColor(255, 255, 255), "flag3:%d", circle2.flag3);
				DrawFormatString(10, 50, GetColor(255, 255, 255), "%f", -circle2.radius / 2);
				DrawFormatString(10, 70, GetColor(255, 255, 255), "%f", step.StartY - (circle2.posY + circle2.radius));
				DrawFormatString(10, 90, GetColor(255, 255, 255), "%f", (circle2.posY + circle2.radius));
#pragma endregion
				break;
		}








		//�f�o�b�N
		if (scene == 0)
		{
			DrawFormatString(10, 10, GetColor(255, 255, 255), "�΂߈ړ�");
		}
		else
		{
			DrawFormatString(10, 10, GetColor(255, 255, 255), "�i��");
		}



		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}