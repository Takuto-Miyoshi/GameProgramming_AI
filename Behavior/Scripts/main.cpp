#include "Definiton.h"
#include "DxLib.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ) {
    SetOutApplicationLogValidFlag( FALSE );
    SetGraphMode( window::WIDTH, window::HEIGHT, 32, 60 );
    ChangeWindowMode( true );
    if ( DxLib_Init() == -1 ) return -1;
    SetDrawScreen( DX_SCREEN_BACK );

    while ( true ) {
        // 画面をクリア
        ClearDrawScreen();
        clsDx();

        // いろいろ処理

        // 終了条件
        if ( ProcessMessage() < 0 ) break;
        if ( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;

        // 表示
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}