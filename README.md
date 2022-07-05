# DxLib_Button
DxLibで使用できるシンプルなボタンクラス

# Requirement
「DxLib」が必須です。

# Usage

## 1.インスタンスを作る
~~~
#include Button.h
#include Vector2.h

Button button;
~~~
ヘッダファイルをインクルードして、インスタンスを作ります。  
またVector2.hをインクルードして使用できるようにします。ボタンの座標や大きさの指定に使用しています。

## 2.Initializeを実行する
~~~
//  ボタンの初期化
button.Initialize(Vector2(800, 600));
~~~
イニシャライズを実行します。
このときの引数は「画面のサイズ（px）」です。

## 3.SetButtonを実行する
~~~
//	ボタンの基本設定
button.SetButton(Vector2(400, 300), Vector2(600, 100), GetColor(255, 0, 0), 
    "TestButton", 100, GetColor(255, 255, 255), Button::EaseType::OutToCenter);
~~~
ボタンの基本的な設定となるSetButtonを実行します。
このときの引数は「画面上の座標(px)、ボタンの横幅と縦幅(px)、ボタンの背景色、ボタン上のテキスト、テキストサイズ、テキストの色、イージングタイプ」です。
イージングに関しては下記をご覧ください。

## 4.Updateを実行する
~~~
Vector2 mousePos;
GetMousePoint(&mousePos.x, &mousePos.y);

button.Update(deltaTime, moousePos);
~~~
ループの中でUpdateを実行します。このときの引数は「前フレームからの経過時間、マウスカーソルの座標」です。

## 5.Renderを実行する
~~~
button.Render();
~~~
ループの中でRenderを実行します。ただそれだけです。

## 6.入力を取って完成
~~~
if(button.GetIsPressed())
{
  //ここにボタンを押されたときの処理を記述
}
~~~
GetisPressed関数を使うことで、ボタンがクリックされたかを得ることができます。戻り値はbool型です。  
あとはif文に使うなどしてボタンが押された際の処理を記述するだけです。
基本的な設定は以上になります。以下はその他の細かい設定になっています。


## 7.その他の設定

### SetToggle
~~~
button.SetToggle(true);
~~~
ボタンを切り替えモードに設定します。このときの引数は「切り替えモードを有効にするか」のbool型です。GetIsPressedの戻り値が一度押すとtrue、もう一度押すとfalseになるモードです。

### SetFrameLine
~~~
button.SetFrameLine(true, GetColor(255, 0, 0));
~~~
ボタンの背景に枠線を描画するかを設定します。このときの引数は「描画するか、色」です。ボタンの位置を明確に提示する際や、デバッグなどにお使いください。

# Easing
ボタンの上にカーソルが乗るとイージングを使用したアニメーションが再生されます。今回は5つのタイプを用意してみました。
SetButton関数や、SetEaseType関数を使用して、好みのアニメーションを設定してください。

## Static
![bandicam 2022-07-05 22-55-44-370_1](https://user-images.githubusercontent.com/76957710/177347138-90d1b7f7-3a8f-42c9-85eb-980448653f2a.gif)  
クリックした瞬間に色が変わるだけのモードです。

## LeftToRight
![bandicam 2022-07-05 22-56-05-175_1](https://user-images.githubusercontent.com/76957710/177347129-7a32cd2a-9f1b-4d89-9b54-8634603d1281.gif)  
左から右にかけてアニメーションします。

## RightToLeft
![bandicam 2022-07-05 22-56-24-843_1](https://user-images.githubusercontent.com/76957710/177347128-badbe578-9d80-48a8-8c20-dd2d8f869ed8.gif)  
右から左にかけてアニメーションします。

## CenterToOut
![bandicam 2022-07-05 22-56-44-754_1](https://user-images.githubusercontent.com/76957710/177347124-d2ad220f-b6a2-49e4-adb4-a10bbe340717.gif)  
中から外へ向けてアニメーションします。

## OutToCenter
![bandicam 2022-07-05 22-57-02-619_1](https://user-images.githubusercontent.com/76957710/177347109-1387ac92-3343-4ab7-8695-d6c4673a1f3e.gif)  
外から中へ向けてアニメーションします。

その他アニメーションを作成することもできます。Button.cppの中に処理が記載されていますのでご活用ください。
