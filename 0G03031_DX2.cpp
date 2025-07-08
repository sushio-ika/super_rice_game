#include "DxLib.h"
#include <time.h>

#define LIMIT 60 
#define CUS_NUM 8

typedef enum {
	eScene_Game,//ゲーム画面
	eScene_Title,
} eScene;

static int Scene = eScene_Title;    //現在の画面(シーン)

//シーンを更新する
void UpdateScene() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
		Scene = eScene_Game;
	}
}

//メニュー画面
void Title() {
	int back = LoadGraph("背景.png");
	int maku = LoadGraph("垂れ幕.png");

	//画面の大きさ設定
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);


	//文字設定
	ChangeFont("BIZ UDPゴシック");
	SetFontSize(64);

	DrawExtendGraph(0, 0, 1280,720, back, TRUE);
	DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

	DrawString(435, 200, "STOP!米騒動", GetColor(210, 210, 210));
	DrawString(428, 200, "STOP!米騒動", GetColor(0, 0, 0));
	DrawString(646, 200, "米", GetColor(255, 160, 16));

	SetFontSize(32);
	DrawString(420, 300, "決して米を2個以上買わすな！", GetColor(0,0,0));

	DrawString(425, 500, "スペースキーでゲームスタート", GetColor(0, 0, 0));

	DrawBox(505, 560, 780, 610, GetColor(0, 0, 0), FALSE);
	DrawString(515, 570, "PRESS SPACE", GetColor(0, 0, 0));

	ScreenFlip();
}

void Game() {

	int customer[CUS_NUM];
	int angry[CUS_NUM];
	int funny[CUS_NUM];
	int flag[CUS_NUM] = { 0,0,0,0,0,0,0 };
	int buy[CUS_NUM] = { 0,0,0,0,0,0,0 };
	int comment[8];
	int mouse, arm, rice, back, hukuro, monitor, counter, reji, pi, maku, nezu, shopman, end_back, tentyo;
	int x, y, i, n;
	int sinrai, hyouban, good, bad;
	int star;
	unsigned int wh, bla, red, gre, blu, lblu;
	int orgnl_time, atime;
	int bgm;

	//画面の大きさ設定
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);

	//文字設定
	SetFontSize(64);	//頻繁に呼ぶ場合、CreateFontToHandle
	ChangeFont("メイリオ");


	//変数初期化
	customer[0] = LoadGraph("ばあちゃん.png");
	customer[1] = LoadGraph("買い物女性.png");
	customer[2] = LoadGraph("父親と子供.png");
	customer[3] = LoadGraph("母親と子供.png");
	customer[4] = LoadGraph("女性.png");
	customer[5] = LoadGraph("男性.png");
	customer[6] = LoadGraph("母.png");
	customer[7] = LoadGraph("じいちゃん.png");

	angry[0] = LoadGraph("ばあちゃんおこ.png");
	angry[1] = LoadGraph("女性おこ.png");
	angry[2] = LoadGraph("メガネ.png");
	angry[3] = LoadGraph("女性おこ.png");
	angry[4] = LoadGraph("女性おこ.png");
	angry[5] = LoadGraph("男性おこ.png");
	angry[6] = LoadGraph("母おこ.png");
	angry[7] = LoadGraph("じいちゃんおこ.png");

	funny[0] = LoadGraph("ばあちゃんにやり.png");
	funny[1] = LoadGraph("女性にやり.png");
	funny[2] = LoadGraph("父親にやり.png");
	funny[3] = LoadGraph("女性にやり.png");
	funny[4] = LoadGraph("女性にやり.png");
	funny[5] = LoadGraph("男性にやり.png");
	funny[6] = LoadGraph("母にやり.png");
	funny[7] = LoadGraph("じいちゃんにやり.png");

	comment[0] = LoadGraph("comment (1).png");
	comment[1] = LoadGraph("comment (2).png");
	comment[2] = LoadGraph("comment (3).png");
	comment[3] = LoadGraph("comment (4).png");
	comment[4] = LoadGraph("comment (5).png");
	comment[5] = LoadGraph("comment (6).png");
	comment[6] = LoadGraph("comment (7).png");
	comment[7] = LoadGraph("comment (8).png");

	hukuro = LoadGraph("武器.png");
	arm = LoadGraph("腕.png");
	rice = LoadGraph("米.png");
	back = LoadGraph("背景.png");
	monitor = LoadGraph("モニター.png");
	counter = LoadGraph("レジカウンター.png");
	reji = LoadGraph("POSレジ.png");
	pi = LoadGraph("ピッ.png");
	maku = LoadGraph("垂れ幕.png");
	nezu = LoadGraph("マウス.png");
	shopman = LoadGraph("店員.png");
	end_back = LoadGraph("rice.png");
	tentyo = LoadGraph("店長.png");

	bgm = LoadSoundMem("MusMus-BGM-173.mp3");

	wh = GetColor(255, 255, 255);	//白
	bla = GetColor(0, 0, 0);		//黒
	red = GetColor(255, 0, 0);		//赤
	gre = GetColor(0, 150, 0);		//緑
	blu = GetColor(0, 0, 255);		//青
	lblu = GetColor(80, 208, 255);
	
	orgnl_time = GetNowCount();

	sinrai = 0;
	hyouban = 0;
	good = 0;
	bad = 0;

	DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
	DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

	DrawBox(0, 100, 1280, 200, wh, TRUE);
	DrawString(450, 127, "09:00 開店！", bla);

	WaitTimer(1800);
	
	SetVolumeMusic(100);
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK, TRUE);
	//メインループ
	while (1)
	{
		
		//終了時処理
		if (LIMIT - ((GetNowCount() - orgnl_time) / 1000) <= 0) {
			SetFontSize(64);
			ClearDrawScreen();

			DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
			DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

			DrawBox(0, 100, 1280, 200, wh, TRUE);
			DrawString(450, 127, "21:00 閉店！", bla);

			WaitTimer(1800);

			ClearDrawScreen();

			DrawExtendGraph(0, 0, 1280, 720, back, TRUE);

			DrawString(515, 127, "成果発表", bla);

			WaitTimer(1000);

			star = (double)good / (good + bad) * 5;

			for (i = 1; i <= 5; i++) {
				DrawString(i * 100 + 310, 250, "☆", gre, TRUE);
			}
			for (i = 1; i <= star; i++) {
				DrawString(i * 100 + 310, 250, "★", gre, TRUE);
				WaitTimer(500);
			}

			SetFontSize(32);
			DrawFormatString(597, 350, bla, "星%dつ", star);

			WaitTimer(1000);

			DrawBox(230, 400, 1030, 590, bla, FALSE);

			SetFontSize(28);

			switch (star) {
			case 0:
				DrawString(250, 450, "店長からのお言葉：クビです。", bla);
				break;
			case 1:
				DrawString(250, 450, "店長からのお言葉：クレーム殺到してます。", bla);
				break;
			case 2:
				DrawString(250, 450, "店長からのお言葉：新人だからまだセーフ", bla);
				break;
			case 3:
				DrawString(250, 450, "店長からのお言葉：そこそこです。", bla);
				break;
			case 4:
				DrawString(250, 450, "店長からのお言葉：優秀です。", bla);
				break;
			case 5:
				DrawString(250, 450, "店長からのお言葉：素晴らしい接客です。", bla);
				break;
			}

			if (hyouban >= 150||sinrai>=150) {
				DrawString(250, 500, "お客様からのお言葉：すごい店員さんがいた！", bla);
			}	
			else if (hyouban <= 30) {
				DrawString(235, 500, "お客様からのお言葉：2個購入している人がいた…", bla);
			}
			else if (sinrai >= 100) {
				DrawString(250, 500, "お客様からのお言葉：2個購入しようとした人に注意していた。", bla);
			}
			

			ScreenFlip();

			break;
		}


		SetFontSize(28);
		ClearDrawScreen();	//画面に描かれているものをすべて消す

		DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
		DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

		DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
		DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
		DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
		DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

		DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
		DrawFormatString(1030, 254, lblu, "信頼度%3d%%", sinrai);
		DrawFormatString(1030, 304, lblu, "評判　%3d%%", hyouban);

		if (LIMIT - ((GetNowCount() - orgnl_time) / 1000) <= 15) {
			DrawBox(20, 20, 280, 70, wh, TRUE);
			DrawString(33, 32, "閉店まであと少し", red);
		}

		WaitTimer(1000);

		srand((unsigned int)time(NULL));
		i = rand() % CUS_NUM;	//客をランダムに選択
		n = rand() % 4;			//米二個持ちのランダム数

		//客出現
		if (n == 3) {
			//米二個持ち
			x = -350;
			while (x <= 400) {
				ClearDrawScreen();
				DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
				DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

				DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);	//客
				DrawExtendGraph(x + 100, 300, x + 300, 500, rice, TRUE);	//米1
				DrawExtendGraph(x + 200, 300, x + 400, 500, rice, TRUE);	//米2

				DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
				DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
				DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
				DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

				DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
				DrawFormatString(1030, 254, lblu, "信頼度%3d%%", sinrai);
				DrawFormatString(1030, 304, lblu, "評判　%3d%%", hyouban);

				x += 10;

				ScreenFlip();

				WaitTimer(20);
			}
		}
		else {
			//米一個
			x = -350;
			while (x <= 400) {
				ClearDrawScreen();
				DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
				DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

				DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);	//客
				DrawExtendGraph(x + 100, 300, x + 300, 500, rice, TRUE);	//米

				DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
				DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
				DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
				DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

				DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
				DrawFormatString(1030, 254, lblu, "信頼度%3d%%", sinrai);
				DrawFormatString(1030, 304, lblu, "評判　%3d%%", hyouban);

				x += 10;

				ScreenFlip();

				WaitTimer(20);
			}
		}

		//客ごとのレジに来た回数カウント
		switch (i) {
		case 0: {
			flag[0]++;
			break;
		}
		case 1: {
			flag[1]++;
			break;
		}
		case 2: {
			flag[2]++;
			break;
		}
		case 3: {
			flag[3]++;
			break;
		}
		case 4: {
			flag[4]++;
			break;
		}
		case 5: {
			flag[5]++;
			break;
		}
		case 6: {
			flag[6]++;
			break;
		}
		case 7: {
			flag[7]++;
		}
		}

		//セリフと操作
		DrawBox(100, 500, 700, 600, wh, TRUE);
		DrawBox(820, 500, 1260, 700, wh, TRUE);

		DrawString(200, 535, "いらっしゃいませー", bla);
		DrawString(980, 555, "左クリック：米回収", bla);
		DrawString(980, 605, "右クリック：お会計", bla);

		SetFontSize(16);
		DrawString(126, 580, "あなた", TRUE);

		DrawExtendGraph(110, 510, 180, 575, shopman, TRUE);
		DrawExtendGraph(850, 525, 950, 675, nezu, TRUE);
		ScreenFlip();


		atime = GetNowCount();

		//マウスクリック入力待ちループ
		while (1) {
			mouse = GetMouseInput();
			SetFontSize(28);

			//左クリック
			if (mouse & MOUSE_INPUT_LEFT) {	//米を奪い取る処理

				orgnl_time -= atime - GetNowCount();

				//店員が腕を伸ばす
				y = 1000;
				while (y >= 800) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					DrawExtendGraph(400, 100, 750, 500, customer[i], TRUE);

					if (n == 3) {	//米2個持ち
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
						DrawExtendGraph(600, 300, 800, 500, rice, TRUE);	//米2
					}
					else {	//1個
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
					}

					DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
					DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
					DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
					DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

					DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
					DrawFormatString(1030, 254, lblu, "信頼度%3d%%", sinrai);
					DrawFormatString(1030, 304, lblu, "評判　%3d%%", hyouban);

					DrawExtendGraph(600, y, 800, y - 400, arm, TRUE);
					y -= 40;

					ScreenFlip();

					WaitTimer(30);

				}


				SetFontSize(512);

				//客を帰らせた結果
				if (flag[i] > 1) {	//来店2回目以降
					if (buy[i] == 0) {	//購入経験無し
						sinrai -= 10;
						hyouban -= 10;
						bad++;

						DrawString(415, 99, "×", blu);
					}
					else {	//購入経験あり
						sinrai += 15;
						hyouban += 5;
						good++;

						DrawString(384, 99, "〇", red);
					}
				}
				else {	//初来店
					if (n == 3) {	//2個持ち
						sinrai += 15;
						hyouban += 5;
						good++;
						flag[i] = 0;

						DrawString(384, 99, "〇", red);
					}
					else {	//1個
						sinrai -= 5;
						hyouban -= 10;
						bad++;
						flag[i] = 0;

						DrawString(415, 99, "×", blu);
					}
				}
				ScreenFlip();

				WaitTimer(500);
				SetFontSize(28);

				//客が帰る処理
				x = 400;
				while (x >= -350) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					if (flag[i] > 1) {	//来店2回目以降
						if (buy[i] == 0) {	//購入経験なし
							DrawExtendGraph(x, 100, x + 350, 500, angry[i], TRUE);
						}
						else {	//購入経験あり
							DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);
						}
					}
					else {	//初来店
						if (n == 3) {	//2個持ち
							DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);
						}
						else {	//1個
							DrawExtendGraph(x, 100, x + 350, 500, angry[i], TRUE);
						}
					}

					x -= 10;

					DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
					DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
					DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
					DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

					DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);

					if (n == 3) {	//2個持ち
						DrawExtendGraph(600, y, 800, y - 400, arm, TRUE);
						DrawExtendGraph(600, y - 500, 800, y - 300, rice, TRUE);
						DrawExtendGraph(700, y - 500, 900, y - 300, rice, TRUE);
					}
					else {	//1個
						DrawExtendGraph(600, y, 800, y - 400, arm, TRUE);
						DrawExtendGraph(550, y - 500, 750, y - 300, rice, TRUE);
					}

					y += 20;

					DrawBox(800, 20, 1250, 135, wh, TRUE);

					DrawExtendGraph(802, 25, 850, 120, tentyo, TRUE);

					if (flag[i] > 1) {	//来店2回目以降
						if (buy[i] == 0) {	//購入経験なし
							DrawString(1030, 279, "評価DOWN…", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[0], TRUE);
						}
						else {	//購入経験あり
							DrawString(1060, 279, "評価UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[1], TRUE);
						}
					}
					else {	//初来店
						if (n == 3) {	//2個持ち
							DrawString(1060, 279, "評価UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[2], TRUE);
						}
						else {	//1個
							DrawString(1030, 279, "評価DOWN…", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[3], TRUE);
						}
					}

					//セリフと操作
					DrawBox(100, 500, 950, 600, wh, TRUE);

					DrawString(200, 535, "一家族につき1つまでとなっておりますー", bla);

					DrawExtendGraph(110, 510, 180, 575, shopman, TRUE);


					ScreenFlip();

					WaitTimer(20);
				}

				break;
			}
			//右クリック
			else if (mouse & MOUSE_INPUT_RIGHT) {	//通す処理

				orgnl_time -= atime - GetNowCount();

				//袋を渡す処理
				y = 1000;
				while (y >= 600) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					DrawExtendGraph(400, 100, 750, 500, customer[i], TRUE);

					if (n == 3) {	//米2個持ち
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
						DrawExtendGraph(600, 300, 800, 500, rice, TRUE);	//米2
					}
					else {	//1個
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
					}

					DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
					DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
					DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
					DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

					DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
					DrawFormatString(1030, 254, lblu, "信頼度%3d%%", 0 + sinrai);
					DrawFormatString(1030, 304, lblu, "評判　%3d%%", 0 + hyouban);

					DrawExtendGraph(600, y - 250, 800, y, hukuro, TRUE);
					y -= 20;

					ScreenFlip();

					WaitTimer(20);

				}

				SetFontSize(512);

				//客が購入した結果
				if (flag[i] >= 1) {	//来店2回目以降
					if (buy[i] == 0) {	//購入無し
						hyouban += 15;
						sinrai += 5;
						good++;

						DrawString(384, 99, "〇", red);
					}
					else {	//購入あり
						hyouban -= 10;
						sinrai -= 10;
						bad++;

						DrawString(415, 99, "×", blu);
					}
				}
				else {	//初来店
					if (n == 3) {	//2個持ち
						hyouban -= 10;
						sinrai -= 5;
						bad++;

						DrawString(415, 99, "×", blu);
					}
					else {	//1個
						hyouban += 15;
						sinrai += 5;
						good++;

						DrawString(384, 99, "〇", red);
					}
				}

				ScreenFlip();

				WaitTimer(500);
				SetFontSize(28);

				//お会計の処理
				x = 0;
				while (x <= 1200) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					if (flag[i] > 1) {	//来店2回目以降
						if (buy[i] == 0) {	//購入経験なし
							DrawExtendGraph(x + 400, 100, x + 750, 500, customer[i], TRUE);
						}
						else {	//購入経験あり
							DrawExtendGraph(x + 400, 100, x + 750, 500, funny[i], TRUE);
						}
					}
					else {	//初来店
						if (n == 3) {	//米2個持ち
							DrawExtendGraph(x + 400, 100, x + 750, 500, funny[i], TRUE);
						}
						else {	//1個
							DrawExtendGraph(x + 400, 100, x + 750, 500, customer[i], TRUE);
						}
					}

					if (n == 3) {	//米2個持ち
						DrawExtendGraph(x + 500, 300, x + 700, 500, rice, TRUE);
						DrawExtendGraph(x + 600, 300, x + 800, 500, rice, TRUE);
					}
					else {	//1個
						DrawExtendGraph(x + 600, 300, x + 800, 500, rice, TRUE);
					}

					x += 10;

					DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
					DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
					DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
					DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

					DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);

					DrawBox(800, 20, 1250, 135, wh, TRUE);

					DrawExtendGraph(802, 25, 850, 120, tentyo, TRUE);

					if (flag[i] > 1) {	//来店2回目以降
						if (buy[i] == 0) {	//購入経験なし
							DrawString(1060, 279, "評価UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[4], TRUE);
						}
						else {	//購入経験あり
							DrawString(1030, 279, "評価DOWN…", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[5], TRUE);
						}
					}
					else {	//初来店
						if (n == 3) {	//米2個持ち
							DrawString(1030, 279, "評価DOWN…", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[6], TRUE);
						}
						else {	//1個
							DrawString(1060, 279, "評価UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[7], TRUE);
						}
					}

					//セリフと操作
					DrawBox(100, 500, 750, 600, wh, TRUE);

					DrawString(200, 535, "ありがとうございましたー", bla);

					DrawExtendGraph(110, 510, 180, 575, shopman, TRUE);

					buy[i]++;

					ScreenFlip();

					WaitTimer(20);

				}
				break;
			}
			else continue;
		}


		if (ProcessMessage() == -1) break;

		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

	}
	WaitTimer(4000);

	DxLib_End();				// ＤＸライブラリ使用の終了処理
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DXLib初期化
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//現在のシーンにあった処理をする
		case eScene_Title://現在のシーンがメニューなら
			Title();//メニュー画面
			break;
		case eScene_Game://現在のシーンがゲームなら
			Game();//ゲーム画面
			break;
		}

		UpdateScene();//シーンを更新する

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
