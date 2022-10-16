#include "Game.h"
#include "time.h"
#include "difine.h"
#include "Keyboard.h"
#include "SceneMgr.h"
#include "DxLib.h"

static int mImageHandle;    //�摜�n���h���i�[�p�ϐ�
static int hp = 200, hp_max = 200;
int white = GetColor(255, 255, 255);
int Score1;
int Score2;
int Score_all;
int save_time;
int time;
int Score_count = 0;

//������
void Game_Initialize() {
    mImageHandle = LoadGraph("images/Scene_Game.png");    //�摜�̃��[�h
}

//�I������
void Game_Finalize() {
    DeleteGraph(mImageHandle);    //�摜�̉��
}

//�X�V
void Game_Update() {
    if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
        SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
    }
}

//�`��
void Game_Draw() {
    DrawGraph(0, 0, mImageHandle, FALSE);

    time_init(); //���ԏ�����
    while (Score_count < 2) {
        ClearDrawScreen();                   //����ʂ̃f�[�^��S�č폜         // ���ׂẴL�[�̏�Ԃ𓾂�

        DrawFormatString(WINDOW_WIDTH / 2, 5, white, "�X�^�[�g�{�^���������Ă�������");

        if (Keyboard_Get(KEY_INPUT_V) == 1) {
                    time = GetNowCount(); //�o�ߎ��ԏ�����
                    while (1) {
                        ClearDrawScreen(); //��ʃN���A
                        save_time = 0 + (GetNowCount() - time) / 1000; //�o�ߎ��ԉ��Z
                        DrawFormatString(WINDOW_WIDTH / 2, 10, white, "�c�莞�ԁF%d",save_time);
                        if (Keyboard_Get(KEY_INPUT_SPACE) ==1 ) {
                            if (Score_count == 0) {
                                Score1 = save_time; //�o�ߎ��ԕۑ�
                            }

                            if (Score_count == 1) {
                                Score2 = save_time; //�o�ߎ��ԕۑ�
                            }
                            Score_count++; //����񐔉��Z
                            break; //���[�v����
                        }
                        ScreenFlip(); //��ʍX�V
                }
            }

        if (Score_count == 2) {
            break;
        }
        ScreenFlip();
    }
    Score_all = Score1 + Score2;
    DrawString(0, 0, "�Q�[���I���ł��B", GetColor(255, 255, 255));
    DrawFormatString(0, 20, white, "Score1 %d", Score1);
    DrawFormatString(0, 40, white, "Score2 %d", Score2);
    DrawFormatString(0, 60, white, "Score_all %d", Score_all);
    DrawString(0, 80, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}

