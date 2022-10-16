#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

const static int GAMEMENU_Y   = 240;    //�u�Q�[���v������y�ʒu
const static int CONFIG_Y = 270;    //�u�ݒ�v������y�ʒu

typedef enum{
    eMenu_GameMenu,        //�Q�[��
    eMenu_Config,    //�ݒ�

    eMenu_Num,        //�{���ڂ̐�
} eMenu ;

static int NowSelect = eMenu_GameMenu;    //���݂̑I�����(�����̓Q�[���I��)

static int mImageHandle;    //�摜�n���h���i�[�p�ϐ�

//������
void Menu_Initialize() {
    mImageHandle = LoadGraph("images/Scene_Menu.png");    //�摜�̃��[�h
}

//�I������
void Menu_Finalize() {
    DeleteGraph(mImageHandle);    //�摜�̉��
}

//�X�V
void Menu_Update(){
    if(Keyboard_Get(KEY_INPUT_DOWN)==1){//���L�[��������Ă�����
        NowSelect = (NowSelect+1)%eMenu_Num;//�I����Ԃ��������
    }
    if(Keyboard_Get(KEY_INPUT_UP)==1){//��L�[��������Ă�����
        NowSelect = (NowSelect+(eMenu_Num-1))%eMenu_Num;//�I����Ԃ���グ��
    }
    if(Keyboard_Get(KEY_INPUT_RETURN)==1){//�G���^�[�L�[�������ꂽ��
        switch(NowSelect){//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case eMenu_GameMenu://�Q�[���I�𒆂Ȃ�
            SceneMgr_ChangeScene(eScene_GameMenu);//�V�[�����Q�[����ʂɕύX
            break;
        case eMenu_Config://�ݒ�I�𒆂Ȃ�
            SceneMgr_ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
            break;
        }
    }
}

//�`��
void Menu_Draw(){
    DrawGraph(0, 0, mImageHandle, FALSE);
    DrawString(200, 150,     "���j���[��ʂł��B",GetColor(255,255,255));
    DrawString(200, 170,     "�㉺�L�[�������A�G���^�[�������ĉ������B",GetColor(255,255,255));
    DrawString(280, GAMEMENU_Y,  "�Q�[���J�n",GetColor(255,255,255));
    DrawString(280, CONFIG_Y,"�ݒ�",GetColor(255,255,255));
    int y=0;
    switch(NowSelect){//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_GameMenu://�Q�[���I�𒆂Ȃ�
        y=GAMEMENU_Y;    //�Q�[���̍��W���i�[
        break;
    case eMenu_Config://�ݒ�I�𒆂Ȃ�
        y=CONFIG_Y;    //�ݒ�̍��W���i�[
        break;
    }
    DrawString(250, y, "��", GetColor(255,255,255));
}
