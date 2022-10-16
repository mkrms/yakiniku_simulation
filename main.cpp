#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

    SceneMgr_Initialize();

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

        Keyboard_Update();    //�L�[�{�[�h�̍X�V

        SceneMgr_Update();  //�X�V
        SceneMgr_Draw();    //�`��

    }

    SceneMgr_Finalize();
        
    DxLib_End(); // DX���C�u�����I������
    return 0;
}

/*
�V�X�e���t���[

�^�C�g�������[�h�I�����Q�[����ʁ����U���g���

�Q�[���t���[
�Q�[����ʕ\�����X�^�[�g�{�^���v�b�V�����Q�[���X�^�[�g
1.�X�^�[�g����̌o�ߎ��Ԏ擾/�Z���T�[�l�擾
2.�Z���T�[�l���؂�ւ��^�C�~���O�Ōo�ߎ��Ԏ擾
3.����̎��Ԃ���̍��َ擾���X�R�A
4.1-3��������x
5.�ŏI�X�R�A�v�Z

���U���g
�E1��ځE2��ڂ�1-3�X�R�A�A�S�̃X�R�A�\��
�E�X�R�A�Z�[�u���X�R�A�\�[�g
�E�����L���O�\��

*/