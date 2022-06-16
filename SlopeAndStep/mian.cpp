#include "DxLib.h"
#include <cmath>
#include <iostream>
#include <math.h>

#include "Collision.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "スロープと段差の実装";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 600;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0, 0, 0);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	Line line
	{
		0,600,600,0
	};

	Circle circle//本体
	{
		200,300,50,
		0,0
	};

	Circle circle2//仮の移動用
	{
		200,300,50,
		0,0
	};

	Line floor//床
	{
		0,500,600,500
	};

	Line step//段差
	{
		300,500,600,500
	};

	Point point
	{
		0,
		0
	};


	float speed = 3.0f;

	int scene = 0;//0 = 斜め移動,1 = 段差

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理


		switch (scene)
		{
			case 0:
#pragma region 斜め移動
				//更新処理
#pragma region 円の移動
				if (keys[KEY_INPUT_W] == 1)//上
				{
					circle2.posY -= speed;
				}
				else if (keys[KEY_INPUT_S] == 1)//下
				{
					circle2.posY += speed;
				}
				else if (keys[KEY_INPUT_A] == 1)//左
				{
					circle2.posX -= speed;
				}
				else if (keys[KEY_INPUT_D] == 1)//右
				{
					circle2.posX += speed;
				}
				circle2.flag1 = LineAndCircleCollision(line, circle2);


				if (circle2.flag1 == 1)
				{
					circle2.posX = circle.posX;
					circle2.posY = circle.posY;
					if (keys[KEY_INPUT_S] == 1)//下
					{
						circle2.posX -= speed;
						circle2.posY += speed;
					}
					else if (keys[KEY_INPUT_D] == 1)//右
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
				//シーン切り替え
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					scene = 1;
					//リセット
					circle.posX = 200;
					circle.posY = 300;
				}

				//描画処理
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
#pragma region 段差
				//更新処理
#pragma region 円の移動

				if (keys[KEY_INPUT_W] == 1)//上
				{
					circle2.posY -= speed;
				}
				else if (keys[KEY_INPUT_S] == 1)//下
				{
					circle2.posY += speed;
				}
				else if (keys[KEY_INPUT_A] == 1)//左
				{
					circle2.posX -= speed;
				}
				else if (keys[KEY_INPUT_D] == 1)//右
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
					if (circle2.flag3 == 1)//段差に当たったとき
					{
						if (keys[KEY_INPUT_D] == 1)
						{
							if (-circle2.radius / 2 <=
								step.StartY - (circle2.posY + circle2.radius))//円の1/4の高さと段差の高さを比較
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

#pragma region 段差の移動
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
				//シーン切り替え
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					scene = 0;
					//リセット
					circle2.posX = 200;
					circle2.posY = 300;
					line.EndX = 600;
					line.EndY = 0;
				}
				//描画処理
				DrawLine(floor.StartX, floor.StartY, floor.EndX, floor.EndY, GetColor(255, 255, 255));//床
				DrawLine(step.StartX, step.StartY, step.EndX, step.EndY, GetColor(255, 255, 255));//段差
				DrawLine(step.StartX, step.StartY, 300, 500, GetColor(255, 255, 255));//段差
				DrawCircle(circle.posX, circle.posY, circle.radius, GetColor(255, 255, 255), false);

				DrawFormatString(10, 30, GetColor(255, 255, 255), "flag3:%d", circle2.flag3);
				DrawFormatString(10, 50, GetColor(255, 255, 255), "%f", -circle2.radius / 2);
				DrawFormatString(10, 70, GetColor(255, 255, 255), "%f", step.StartY - (circle2.posY + circle2.radius));
				DrawFormatString(10, 90, GetColor(255, 255, 255), "%f", (circle2.posY + circle2.radius));
#pragma endregion
				break;
		}








		//デバック
		if (scene == 0)
		{
			DrawFormatString(10, 10, GetColor(255, 255, 255), "斜め移動");
		}
		else
		{
			DrawFormatString(10, 10, GetColor(255, 255, 255), "段差");
		}



		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}