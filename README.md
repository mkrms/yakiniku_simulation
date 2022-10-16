# yakiniku_simulation

2022/10/16 - first commit & push
system flow construction

## next goal (to next commiy about 10/17-10/22)

* 定数格納ファイルの作成・整理
* ウィンドウサイズ最適化
* マイコンとの連携
* ゲームモード多様化
* ビジュアル整備

## bag fix goal
* 時間に関するバグ(time initialize)
* キーボード入力に対するバグ(入力待機時間の設定)
* システム的に脆弱な部分の修正
  * 例外処理
  * エラー処理
 
## 2022/10/17 中間報告書で使えそうなネタ

### 今完成してるゲームフローの根幹

* スタートボタン V
* ストップボタン SPACE
* 時間経過を2回計測→スコア

```c++
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
```

### ヘッダー・ソースファイルで分けることで、関数の呼び出しが容易になる
* これを徹底することで、読みやすいコードが書ける
* difineとかで定義する部分をヘッダーファイルにまとめて呼び出すと便利
* 定数・時間処理・各計算処理・キーボードの処理などで分けて記載するとなおよし

```c++
#pragma once

void Config_Initialize();//初期化
void Config_Finalize();//終了処理
void Config_Update();//更新
void Config_Draw();//描画

```

```c++
nclude "Config.h"
#include "SceneMgr.h"
#include "DxLib.h"

static int mImageHandle;    //画像ハンドル格納用変数

//初期化
void Config_Initialize() {
    mImageHandle = LoadGraph("images/Scene_Config.png");//画像のロード
}

//終了処理
void Config_Finalize() {
    DeleteGraph(mImageHandle);//画像の解放
}

//更新
void Config_Update(){
    if(CheckHitKey(KEY_INPUT_ESCAPE)!=0){//Escキーが押されていたら
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
    }
}

//描画
void Config_Draw(){
    DrawGraph(0, 0, mImageHandle, FALSE);
    DrawString(0, 0,"設定画面です。",GetColor(255,255,255));
    DrawString(0,20,"Escキーを押すとメニュー画面に戻ります。",GetColor(255,255,255));
}
```

### タイトル画面・モード選択画面での選択処理

* それぞれの項目のY座標を決定させる
* enumで項目の数・種類を定義
* 上キー・下キーが押されると、「選択状態の切り替え」が行われる
* 「選択状態が○○ならシーンを○○に変更」という処理がおこなわれる
* 選択状態に応じたy座標を取得することで複雑な処理をすることなくキーボードでの選択が可能(追記もしやすい・例外処理しなくていい)

```c++
const static int GAMEMENU_Y   = 240;    //「ゲーム」文字のy位置
const static int CONFIG_Y = 270;    //「設定」文字のy位置

typedef enum{
    eMenu_GameMenu,        //ゲーム
    eMenu_Config,    //設定

    eMenu_Num,        //本項目の数
} eMenu ;

static int NowSelect = eMenu_GameMenu;    //現在の選択状態(初期はゲーム選択中)

static int mImageHandle;    //画像ハンドル格納用変数

//初期化
void Menu_Initialize() {
    mImageHandle = LoadGraph("images/Scene_Menu.png");    //画像のロード
}

//終了処理
void Menu_Finalize() {
    DeleteGraph(mImageHandle);    //画像の解放
}

//更新
void Menu_Update(){
    if(Keyboard_Get(KEY_INPUT_DOWN)==1){//下キーが押されていたら
        NowSelect = (NowSelect+1)%eMenu_Num;//選択状態を一つ下げる
    }
    if(Keyboard_Get(KEY_INPUT_UP)==1){//上キーが押されていたら
        NowSelect = (NowSelect+(eMenu_Num-1))%eMenu_Num;//選択状態を一つ上げる
    }
    if(Keyboard_Get(KEY_INPUT_RETURN)==1){//エンターキーが押されたら
        switch(NowSelect){//現在選択中の状態によって処理を分岐
        case eMenu_GameMenu://ゲーム選択中なら
            SceneMgr_ChangeScene(eScene_GameMenu);//シーンをゲーム画面に変更
            break;
        case eMenu_Config://設定選択中なら
            SceneMgr_ChangeScene(eScene_Config);//シーンを設定画面に変更
            break;
        }
    }
}

//描画
void Menu_Draw(){
    DrawGraph(0, 0, mImageHandle, FALSE);
    DrawString(200, 150,     "メニュー画面です。",GetColor(255,255,255));
    DrawString(200, 170,     "上下キーを押し、エンターを押して下さい。",GetColor(255,255,255));
    DrawString(280, GAMEMENU_Y,  "ゲーム開始",GetColor(255,255,255));
    DrawString(280, CONFIG_Y,"設定",GetColor(255,255,255));
    int y=0;
    switch(NowSelect){//現在の選択状態に従って処理を分岐
    case eMenu_GameMenu://ゲーム選択中なら
        y=GAMEMENU_Y;    //ゲームの座標を格納
        break;
    case eMenu_Config://設定選択中なら
        y=CONFIG_Y;    //設定の座標を格納
        break;
    }
    DrawString(250, y, "■", GetColor(255,255,255));
}
```
### シーン切り替え処理

* case文でシーンの切り替えをおこなっている
* ヘッダーファイルでそれぞれのシーン(eScene)を定義・参照


```c++
void SceneMgr_Update(){
    if (mNextScene != eScene_None) {    //次のシーンがセットされていたら
        SceneMgr_FinalizeModule(mScene);//現在のシーンの終了処理を実行
        mScene = mNextScene;    //次のシーンを現在のシーンセット
        mNextScene = eScene_None;    //次のシーン情報をクリア
        SceneMgr_InitializeModule(mScene);    //現在のシーンを初期化
    }
    switch(mScene){       //シーンによって処理を分岐
    case eScene_Menu:    //現在の画面がメニューなら
        Menu_Update();   //メニュー画面の更新処理をする
        break;//以下略
    case eScene_GameMenu:
        GameMenu_Update();
        break;
    case eScene_Config:
        Config_Update();
        break;
    case eScene_Game:
        Game_Update();
        break;
    /*
    case eScene_Game1:
        Game1_Update();
        break;
    case eScene_Game2:
        Game2_Update();
        break;
    case eScene_Game3:
        Game3_Update();
        break;
    */


    }
}

//描画
void SceneMgr_Draw() {
    switch (mScene) {      //シーンによって処理を分岐
    case eScene_Menu:   //現在の画面がメニュー画面なら
        Menu_Draw();    //メニュー画面の描画処理をする
        break;//以下略
    case eScene_GameMenu:
        GameMenu_Draw();
        break;
    case eScene_Config:
        Config_Draw();
        break;
    case eScene_Game:
        Game_Draw();
        break;
        /*
    case eScene_Game1:
        Game1_Draw();
        break;
    case eScene_Game2:
        Game2_Draw();
        break;
    case eScene_Game3:
        Game3_Draw();
        break;
        */
    }
}
```
