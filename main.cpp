#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

    SceneMgr_Initialize();

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){//画面更新 & メッセージ処理 & 画面消去

        Keyboard_Update();    //キーボードの更新

        SceneMgr_Update();  //更新
        SceneMgr_Draw();    //描画

    }

    SceneMgr_Finalize();
        
    DxLib_End(); // DXライブラリ終了処理
    return 0;
}

/*
システムフロー

タイトル→モード選択→ゲーム画面→リザルト画面

ゲームフロー
ゲーム画面表示→スタートボタンプッシュ→ゲームスタート
1.スタートからの経過時間取得/センサー値取得
2.センサー値が切り替わるタイミングで経過時間取得
3.既定の時間からの差異取得→スコア
4.1-3をもう一度
5.最終スコア計算

リザルト
・1回目・2回目の1-3スコア、全体スコア表示
・スコアセーブ→スコアソート
・ランキング表示

*/