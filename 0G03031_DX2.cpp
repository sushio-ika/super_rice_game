#include "DxLib.h"
#include <time.h>

#define LIMIT 60 
#define CUS_NUM 8

typedef enum {
	eScene_Game,//�Q�[�����
	eScene_Title,
} eScene;

static int Scene = eScene_Title;    //���݂̉��(�V�[��)

//�V�[�����X�V����
void UpdateScene() {
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
		Scene = eScene_Game;
	}
}

//���j���[���
void Title() {
	int back = LoadGraph("�w�i.png");
	int maku = LoadGraph("���ꖋ.png");

	//��ʂ̑傫���ݒ�
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);


	//�����ݒ�
	ChangeFont("BIZ UDP�S�V�b�N");
	SetFontSize(64);

	DrawExtendGraph(0, 0, 1280,720, back, TRUE);
	DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

	DrawString(435, 200, "STOP!�đ���", GetColor(210, 210, 210));
	DrawString(428, 200, "STOP!�đ���", GetColor(0, 0, 0));
	DrawString(646, 200, "��", GetColor(255, 160, 16));

	SetFontSize(32);
	DrawString(420, 300, "�����ĕĂ�2�ȏ㔃�킷�ȁI", GetColor(0,0,0));

	DrawString(425, 500, "�X�y�[�X�L�[�ŃQ�[���X�^�[�g", GetColor(0, 0, 0));

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

	//��ʂ̑傫���ݒ�
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);

	//�����ݒ�
	SetFontSize(64);	//�p�ɂɌĂԏꍇ�ACreateFontToHandle
	ChangeFont("���C���I");


	//�ϐ�������
	customer[0] = LoadGraph("�΂������.png");
	customer[1] = LoadGraph("����������.png");
	customer[2] = LoadGraph("���e�Ǝq��.png");
	customer[3] = LoadGraph("��e�Ǝq��.png");
	customer[4] = LoadGraph("����.png");
	customer[5] = LoadGraph("�j��.png");
	customer[6] = LoadGraph("��.png");
	customer[7] = LoadGraph("���������.png");

	angry[0] = LoadGraph("�΂�����񂨂�.png");
	angry[1] = LoadGraph("��������.png");
	angry[2] = LoadGraph("���K�l.png");
	angry[3] = LoadGraph("��������.png");
	angry[4] = LoadGraph("��������.png");
	angry[5] = LoadGraph("�j������.png");
	angry[6] = LoadGraph("�ꂨ��.png");
	angry[7] = LoadGraph("��������񂨂�.png");

	funny[0] = LoadGraph("�΂������ɂ��.png");
	funny[1] = LoadGraph("�����ɂ��.png");
	funny[2] = LoadGraph("���e�ɂ��.png");
	funny[3] = LoadGraph("�����ɂ��.png");
	funny[4] = LoadGraph("�����ɂ��.png");
	funny[5] = LoadGraph("�j���ɂ��.png");
	funny[6] = LoadGraph("��ɂ��.png");
	funny[7] = LoadGraph("���������ɂ��.png");

	comment[0] = LoadGraph("comment (1).png");
	comment[1] = LoadGraph("comment (2).png");
	comment[2] = LoadGraph("comment (3).png");
	comment[3] = LoadGraph("comment (4).png");
	comment[4] = LoadGraph("comment (5).png");
	comment[5] = LoadGraph("comment (6).png");
	comment[6] = LoadGraph("comment (7).png");
	comment[7] = LoadGraph("comment (8).png");

	hukuro = LoadGraph("����.png");
	arm = LoadGraph("�r.png");
	rice = LoadGraph("��.png");
	back = LoadGraph("�w�i.png");
	monitor = LoadGraph("���j�^�[.png");
	counter = LoadGraph("���W�J�E���^�[.png");
	reji = LoadGraph("POS���W.png");
	pi = LoadGraph("�s�b.png");
	maku = LoadGraph("���ꖋ.png");
	nezu = LoadGraph("�}�E�X.png");
	shopman = LoadGraph("�X��.png");
	end_back = LoadGraph("rice.png");
	tentyo = LoadGraph("�X��.png");

	bgm = LoadSoundMem("MusMus-BGM-173.mp3");

	wh = GetColor(255, 255, 255);	//��
	bla = GetColor(0, 0, 0);		//��
	red = GetColor(255, 0, 0);		//��
	gre = GetColor(0, 150, 0);		//��
	blu = GetColor(0, 0, 255);		//��
	lblu = GetColor(80, 208, 255);
	
	orgnl_time = GetNowCount();

	sinrai = 0;
	hyouban = 0;
	good = 0;
	bad = 0;

	DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
	DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

	DrawBox(0, 100, 1280, 200, wh, TRUE);
	DrawString(450, 127, "09:00 �J�X�I", bla);

	WaitTimer(1800);
	
	SetVolumeMusic(100);
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK, TRUE);
	//���C�����[�v
	while (1)
	{
		
		//�I��������
		if (LIMIT - ((GetNowCount() - orgnl_time) / 1000) <= 0) {
			SetFontSize(64);
			ClearDrawScreen();

			DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
			DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

			DrawBox(0, 100, 1280, 200, wh, TRUE);
			DrawString(450, 127, "21:00 �X�I", bla);

			WaitTimer(1800);

			ClearDrawScreen();

			DrawExtendGraph(0, 0, 1280, 720, back, TRUE);

			DrawString(515, 127, "���ʔ��\", bla);

			WaitTimer(1000);

			star = (double)good / (good + bad) * 5;

			for (i = 1; i <= 5; i++) {
				DrawString(i * 100 + 310, 250, "��", gre, TRUE);
			}
			for (i = 1; i <= star; i++) {
				DrawString(i * 100 + 310, 250, "��", gre, TRUE);
				WaitTimer(500);
			}

			SetFontSize(32);
			DrawFormatString(597, 350, bla, "��%d��", star);

			WaitTimer(1000);

			DrawBox(230, 400, 1030, 590, bla, FALSE);

			SetFontSize(28);

			switch (star) {
			case 0:
				DrawString(250, 450, "�X������̂����t�F�N�r�ł��B", bla);
				break;
			case 1:
				DrawString(250, 450, "�X������̂����t�F�N���[���E�����Ă܂��B", bla);
				break;
			case 2:
				DrawString(250, 450, "�X������̂����t�F�V�l������܂��Z�[�t", bla);
				break;
			case 3:
				DrawString(250, 450, "�X������̂����t�F���������ł��B", bla);
				break;
			case 4:
				DrawString(250, 450, "�X������̂����t�F�D�G�ł��B", bla);
				break;
			case 5:
				DrawString(250, 450, "�X������̂����t�F�f���炵���ڋq�ł��B", bla);
				break;
			}

			if (hyouban >= 150||sinrai>=150) {
				DrawString(250, 500, "���q�l����̂����t�F�������X�����񂪂����I", bla);
			}	
			else if (hyouban <= 30) {
				DrawString(235, 500, "���q�l����̂����t�F2�w�����Ă���l�������c", bla);
			}
			else if (sinrai >= 100) {
				DrawString(250, 500, "���q�l����̂����t�F2�w�����悤�Ƃ����l�ɒ��ӂ��Ă����B", bla);
			}
			

			ScreenFlip();

			break;
		}


		SetFontSize(28);
		ClearDrawScreen();	//��ʂɕ`����Ă�����̂����ׂď���

		DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
		DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

		DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
		DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
		DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
		DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

		DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
		DrawFormatString(1030, 254, lblu, "�M���x%3d%%", sinrai);
		DrawFormatString(1030, 304, lblu, "�]���@%3d%%", hyouban);

		if (LIMIT - ((GetNowCount() - orgnl_time) / 1000) <= 15) {
			DrawBox(20, 20, 280, 70, wh, TRUE);
			DrawString(33, 32, "�X�܂ł��Ə���", red);
		}

		WaitTimer(1000);

		srand((unsigned int)time(NULL));
		i = rand() % CUS_NUM;	//�q�������_���ɑI��
		n = rand() % 4;			//�ē�����̃����_����

		//�q�o��
		if (n == 3) {
			//�ē����
			x = -350;
			while (x <= 400) {
				ClearDrawScreen();
				DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
				DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

				DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);	//�q
				DrawExtendGraph(x + 100, 300, x + 300, 500, rice, TRUE);	//��1
				DrawExtendGraph(x + 200, 300, x + 400, 500, rice, TRUE);	//��2

				DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
				DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
				DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
				DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

				DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
				DrawFormatString(1030, 254, lblu, "�M���x%3d%%", sinrai);
				DrawFormatString(1030, 304, lblu, "�]���@%3d%%", hyouban);

				x += 10;

				ScreenFlip();

				WaitTimer(20);
			}
		}
		else {
			//�Ĉ��
			x = -350;
			while (x <= 400) {
				ClearDrawScreen();
				DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
				DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

				DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);	//�q
				DrawExtendGraph(x + 100, 300, x + 300, 500, rice, TRUE);	//��

				DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
				DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
				DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
				DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

				DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
				DrawFormatString(1030, 254, lblu, "�M���x%3d%%", sinrai);
				DrawFormatString(1030, 304, lblu, "�]���@%3d%%", hyouban);

				x += 10;

				ScreenFlip();

				WaitTimer(20);
			}
		}

		//�q���Ƃ̃��W�ɗ����񐔃J�E���g
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

		//�Z���t�Ƒ���
		DrawBox(100, 500, 700, 600, wh, TRUE);
		DrawBox(820, 500, 1260, 700, wh, TRUE);

		DrawString(200, 535, "��������Ⴂ�܂��[", bla);
		DrawString(980, 555, "���N���b�N�F�ĉ��", bla);
		DrawString(980, 605, "�E�N���b�N�F����v", bla);

		SetFontSize(16);
		DrawString(126, 580, "���Ȃ�", TRUE);

		DrawExtendGraph(110, 510, 180, 575, shopman, TRUE);
		DrawExtendGraph(850, 525, 950, 675, nezu, TRUE);
		ScreenFlip();


		atime = GetNowCount();

		//�}�E�X�N���b�N���͑҂����[�v
		while (1) {
			mouse = GetMouseInput();
			SetFontSize(28);

			//���N���b�N
			if (mouse & MOUSE_INPUT_LEFT) {	//�Ă�D����鏈��

				orgnl_time -= atime - GetNowCount();

				//�X�����r��L�΂�
				y = 1000;
				while (y >= 800) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					DrawExtendGraph(400, 100, 750, 500, customer[i], TRUE);

					if (n == 3) {	//��2����
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
						DrawExtendGraph(600, 300, 800, 500, rice, TRUE);	//��2
					}
					else {	//1��
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
					}

					DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
					DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
					DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
					DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

					DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
					DrawFormatString(1030, 254, lblu, "�M���x%3d%%", sinrai);
					DrawFormatString(1030, 304, lblu, "�]���@%3d%%", hyouban);

					DrawExtendGraph(600, y, 800, y - 400, arm, TRUE);
					y -= 40;

					ScreenFlip();

					WaitTimer(30);

				}


				SetFontSize(512);

				//�q���A�点������
				if (flag[i] > 1) {	//���X2��ڈȍ~
					if (buy[i] == 0) {	//�w���o������
						sinrai -= 10;
						hyouban -= 10;
						bad++;

						DrawString(415, 99, "�~", blu);
					}
					else {	//�w���o������
						sinrai += 15;
						hyouban += 5;
						good++;

						DrawString(384, 99, "�Z", red);
					}
				}
				else {	//�����X
					if (n == 3) {	//2����
						sinrai += 15;
						hyouban += 5;
						good++;
						flag[i] = 0;

						DrawString(384, 99, "�Z", red);
					}
					else {	//1��
						sinrai -= 5;
						hyouban -= 10;
						bad++;
						flag[i] = 0;

						DrawString(415, 99, "�~", blu);
					}
				}
				ScreenFlip();

				WaitTimer(500);
				SetFontSize(28);

				//�q���A�鏈��
				x = 400;
				while (x >= -350) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					if (flag[i] > 1) {	//���X2��ڈȍ~
						if (buy[i] == 0) {	//�w���o���Ȃ�
							DrawExtendGraph(x, 100, x + 350, 500, angry[i], TRUE);
						}
						else {	//�w���o������
							DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);
						}
					}
					else {	//�����X
						if (n == 3) {	//2����
							DrawExtendGraph(x, 100, x + 350, 500, customer[i], TRUE);
						}
						else {	//1��
							DrawExtendGraph(x, 100, x + 350, 500, angry[i], TRUE);
						}
					}

					x -= 10;

					DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
					DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
					DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
					DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

					DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);

					if (n == 3) {	//2����
						DrawExtendGraph(600, y, 800, y - 400, arm, TRUE);
						DrawExtendGraph(600, y - 500, 800, y - 300, rice, TRUE);
						DrawExtendGraph(700, y - 500, 900, y - 300, rice, TRUE);
					}
					else {	//1��
						DrawExtendGraph(600, y, 800, y - 400, arm, TRUE);
						DrawExtendGraph(550, y - 500, 750, y - 300, rice, TRUE);
					}

					y += 20;

					DrawBox(800, 20, 1250, 135, wh, TRUE);

					DrawExtendGraph(802, 25, 850, 120, tentyo, TRUE);

					if (flag[i] > 1) {	//���X2��ڈȍ~
						if (buy[i] == 0) {	//�w���o���Ȃ�
							DrawString(1030, 279, "�]��DOWN�c", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[0], TRUE);
						}
						else {	//�w���o������
							DrawString(1060, 279, "�]��UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[1], TRUE);
						}
					}
					else {	//�����X
						if (n == 3) {	//2����
							DrawString(1060, 279, "�]��UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[2], TRUE);
						}
						else {	//1��
							DrawString(1030, 279, "�]��DOWN�c", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[3], TRUE);
						}
					}

					//�Z���t�Ƒ���
					DrawBox(100, 500, 950, 600, wh, TRUE);

					DrawString(200, 535, "��Ƒ��ɂ�1�܂łƂȂ��Ă���܂��[", bla);

					DrawExtendGraph(110, 510, 180, 575, shopman, TRUE);


					ScreenFlip();

					WaitTimer(20);
				}

				break;
			}
			//�E�N���b�N
			else if (mouse & MOUSE_INPUT_RIGHT) {	//�ʂ�����

				orgnl_time -= atime - GetNowCount();

				//�܂�n������
				y = 1000;
				while (y >= 600) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					DrawExtendGraph(400, 100, 750, 500, customer[i], TRUE);

					if (n == 3) {	//��2����
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
						DrawExtendGraph(600, 300, 800, 500, rice, TRUE);	//��2
					}
					else {	//1��
						DrawExtendGraph(500, 300, 700, 500, rice, TRUE);
					}

					DrawExtendGraph(0, 150, 1280, 720, counter, TRUE);
					DrawExtendGraph(970, 150, 1270, 550, monitor, TRUE);
					DrawExtendGraph(650, 100, 1050, 500, reji, TRUE);
					DrawExtendGraph(100, 100, 500, 500, pi, TRUE);

					DrawFormatString(205, 205, blu, "%02d:00", 9 + ((GetNowCount() - orgnl_time) / 1000) / 5);
					DrawFormatString(1030, 254, lblu, "�M���x%3d%%", 0 + sinrai);
					DrawFormatString(1030, 304, lblu, "�]���@%3d%%", 0 + hyouban);

					DrawExtendGraph(600, y - 250, 800, y, hukuro, TRUE);
					y -= 20;

					ScreenFlip();

					WaitTimer(20);

				}

				SetFontSize(512);

				//�q���w����������
				if (flag[i] >= 1) {	//���X2��ڈȍ~
					if (buy[i] == 0) {	//�w������
						hyouban += 15;
						sinrai += 5;
						good++;

						DrawString(384, 99, "�Z", red);
					}
					else {	//�w������
						hyouban -= 10;
						sinrai -= 10;
						bad++;

						DrawString(415, 99, "�~", blu);
					}
				}
				else {	//�����X
					if (n == 3) {	//2����
						hyouban -= 10;
						sinrai -= 5;
						bad++;

						DrawString(415, 99, "�~", blu);
					}
					else {	//1��
						hyouban += 15;
						sinrai += 5;
						good++;

						DrawString(384, 99, "�Z", red);
					}
				}

				ScreenFlip();

				WaitTimer(500);
				SetFontSize(28);

				//����v�̏���
				x = 0;
				while (x <= 1200) {
					ClearDrawScreen();

					DrawExtendGraph(0, 0, 1280, 720, back, TRUE);
					DrawExtendGraph(850, 30, 1050, 300, maku, TRUE);

					if (flag[i] > 1) {	//���X2��ڈȍ~
						if (buy[i] == 0) {	//�w���o���Ȃ�
							DrawExtendGraph(x + 400, 100, x + 750, 500, customer[i], TRUE);
						}
						else {	//�w���o������
							DrawExtendGraph(x + 400, 100, x + 750, 500, funny[i], TRUE);
						}
					}
					else {	//�����X
						if (n == 3) {	//��2����
							DrawExtendGraph(x + 400, 100, x + 750, 500, funny[i], TRUE);
						}
						else {	//1��
							DrawExtendGraph(x + 400, 100, x + 750, 500, customer[i], TRUE);
						}
					}

					if (n == 3) {	//��2����
						DrawExtendGraph(x + 500, 300, x + 700, 500, rice, TRUE);
						DrawExtendGraph(x + 600, 300, x + 800, 500, rice, TRUE);
					}
					else {	//1��
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

					if (flag[i] > 1) {	//���X2��ڈȍ~
						if (buy[i] == 0) {	//�w���o���Ȃ�
							DrawString(1060, 279, "�]��UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[4], TRUE);
						}
						else {	//�w���o������
							DrawString(1030, 279, "�]��DOWN�c", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[5], TRUE);
						}
					}
					else {	//�����X
						if (n == 3) {	//��2����
							DrawString(1030, 279, "�]��DOWN�c", blu);
							DrawExtendGraph(860, 35, 1230, 115, comment[6], TRUE);
						}
						else {	//1��
							DrawString(1060, 279, "�]��UP!", red);
							DrawExtendGraph(860, 35, 1230, 115, comment[7], TRUE);
						}
					}

					//�Z���t�Ƒ���
					DrawBox(100, 500, 750, 600, wh, TRUE);

					DrawString(200, 535, "���肪�Ƃ��������܂����[", bla);

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

		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

	}
	WaitTimer(4000);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DXLib������
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		switch (Scene) {//���݂̃V�[���ɂ���������������
		case eScene_Title://���݂̃V�[�������j���[�Ȃ�
			Title();//���j���[���
			break;
		case eScene_Game://���݂̃V�[�����Q�[���Ȃ�
			Game();//�Q�[�����
			break;
		}

		UpdateScene();//�V�[�����X�V����

	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
