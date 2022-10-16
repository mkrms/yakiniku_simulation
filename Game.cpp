#include "Game.h"
#include "time.h"
#include "difine.h"
#include "Keyboard.h"
#include "SceneMgr.h"
#include "DxLib.h"

static int mImageHandle;    //画像ハンドル格納用変数
static int hp = 200, hp_max = 200;
int white = GetColor(255, 255, 255);
int Score1;
int Score2;
int Score_all;
int save_time;
int time;
int Score_count = 0;

//初期化
void Game_Initialize() {
    mImageHandle = LoadGraph("images/Scene_Game.png");    //画像のロード
}

//終了処理
void Game_Finalize() {
    DeleteGraph(mImageHandle);    //画像の解放
}

//更新
void Game_Update() {
    if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
    }
}

//描画
void Game_Draw() {
    DrawGraph(0, 0, mImageHandle, FALSE);

    time_init(); //時間初期化
    while (Score_count < 2) {
        ClearDrawScreen();                   //裏画面のデータを全て削除         // すべてのキーの状態を得る

        DrawFormatString(WINDOW_WIDTH / 2, 5, white, "スタートボタンを押してください");

        if (Keyboard_Get(KEY_INPUT_V) == 1) {
                    time = GetNowCount(); //経過時間初期化
                    while (1) {
                        ClearDrawScreen(); //画面クリア
                        save_time = 0 + (GetNowCount() - time) / 1000; //経過時間加算
                        DrawFormatString(WINDOW_WIDTH / 2, 10, white, "残り時間：%d",save_time);
                        if (Keyboard_Get(KEY_INPUT_SPACE) ==1 ) {
                            if (Score_count == 0) {
                                Score1 = save_time; //経過時間保存
                            }

                            if (Score_count == 1) {
                                Score2 = save_time; //経過時間保存
                            }
                            Score_count++; //測定回数加算
                            break; //ループ抜け
                        }
                        ScreenFlip(); //画面更新
                }
            }

        if (Score_count == 2) {
            break;
        }
        ScreenFlip();
    }
    Score_all = Score1 + Score2;
    DrawString(0, 0, "ゲーム終了です。", GetColor(255, 255, 255));
    DrawFormatString(0, 20, white, "Score1 %d", Score1);
    DrawFormatString(0, 40, white, "Score2 %d", Score2);
    DrawFormatString(0, 60, white, "Score_all %d", Score_all);
    DrawString(0, 80, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}

