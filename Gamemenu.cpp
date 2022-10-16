#include "GameMenu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

const static int GAME_Y = 240;    //�u�Q�[���v������y�ʒu
//const static int GAME1_Y = 240;    //�u�Q�[���P�v������y�ʒu
//const static int GAME2_Y = 270;    //�u�Q�[���Q�v������y�ʒu
//const static int GAME3_Y = 300;    //�u�Q�[���Q�v������y�ʒu

typedef enum {
    eMenu_Game,
    //eMenu_Game1,        
    //eMenu_Game2,  
    //eMenu_Game3,

    eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Game;    //���݂̑I�����(�����̓Q�[���I��)

//�X�V
void GameMenu_Update() {
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
        NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
    }
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
        switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case eMenu_Game:
            SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
            break;
        /*
        case eMenu_Game1:
            SceneMgr_ChangeScene(eScene_Game1);//�V�[�����Q�[����ʂɕύX
            break;
        case eMenu_Game2:
            SceneMgr_ChangeScene(eScene_Game2);//�V�[����ݒ��ʂɕύX
            break;
        case eMenu_Game3:
            SceneMgr_ChangeScene(eScene_Game3);//�V�[����ݒ��ʂɕύX
            break;
        */
        }
    }
}

//�`��
void GameMenu_Draw() {
    DrawString(200, 150, "���[�h�Q�[���I����ʂł��B", GetColor(255, 255, 255));
    DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
    DrawString(280, GAME_Y, "�Q�[��1", GetColor(255, 255, 255));
    /*
    DrawString(280, GAME1_Y, "�Q�[��1", GetColor(255, 255, 255));
    DrawString(280, GAME2_Y, "�Q�[��2", GetColor(255, 255, 255));
    DrawString(280, GAME3_Y, "�Q�[��3", GetColor(255, 255, 255));
    */
    int y = 0;
    switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_Game://�Q�[���I�𒆂Ȃ�
        y = GAME_Y;    //�Q�[���̍��W���i�[
        break;
        /*
    case eMenu_Game1://�Q�[���I�𒆂Ȃ�
        y = GAME1_Y;    //�Q�[���̍��W���i�[
        break;
    case eMenu_Game2://�ݒ�I�𒆂Ȃ�
        y = GAME2_Y;    //�ݒ�̍��W���i�[
        break;
    case eMenu_Game3://�ݒ�I�𒆂Ȃ�
        y = GAME3_Y;    //�ݒ�̍��W���i�[
        break;
        */
    }
    DrawString(250, y, "��", GetColor(255, 255, 255));
}
