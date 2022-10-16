#include "GameMenu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

const static int GAME_Y = 240;    //「ゲーム」文字のy位置
//const static int GAME1_Y = 240;    //「ゲーム１」文字のy位置
//const static int GAME2_Y = 270;    //「ゲーム２」文字のy位置
//const static int GAME3_Y = 300;    //「ゲーム２」文字のy位置

typedef enum {
    eMenu_Game,
    //eMenu_Game1,        
    //eMenu_Game2,  
    //eMenu_Game3,

    eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Game;    //現在の選択状態(初期はゲーム選択中)

//更新
void GameMenu_Update() {
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
        NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
    }
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {//上キーが押されていたら
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
        switch (NowSelect) {//現在選択中の状態によって処理を分岐
        case eMenu_Game:
            SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
            break;
        /*
        case eMenu_Game1:
            SceneMgr_ChangeScene(eScene_Game1);//シーンをゲーム画面に変更
            break;
        case eMenu_Game2:
            SceneMgr_ChangeScene(eScene_Game2);//シーンを設定画面に変更
            break;
        case eMenu_Game3:
            SceneMgr_ChangeScene(eScene_Game3);//シーンを設定画面に変更
            break;
        */
        }
    }
}

//描画
void GameMenu_Draw() {
    DrawString(200, 150, "モードゲーム選択画面です。", GetColor(255, 255, 255));
    DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
    DrawString(280, GAME_Y, "ゲーム1", GetColor(255, 255, 255));
    /*
    DrawString(280, GAME1_Y, "ゲーム1", GetColor(255, 255, 255));
    DrawString(280, GAME2_Y, "ゲーム2", GetColor(255, 255, 255));
    DrawString(280, GAME3_Y, "ゲーム3", GetColor(255, 255, 255));
    */
    int y = 0;
    switch (NowSelect) {//現在の選択状態に従って処理を分岐
    case eMenu_Game://ゲーム選択中なら
        y = GAME_Y;    //ゲームの座標を格納
        break;
        /*
    case eMenu_Game1://ゲーム選択中なら
        y = GAME1_Y;    //ゲームの座標を格納
        break;
    case eMenu_Game2://設定選択中なら
        y = GAME2_Y;    //設定の座標を格納
        break;
    case eMenu_Game3://設定選択中なら
        y = GAME3_Y;    //設定の座標を格納
        break;
        */
    }
    DrawString(250, y, "■", GetColor(255, 255, 255));
}
