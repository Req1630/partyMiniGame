#include "Main.h"
#include <Windows.h>

#include "..\Utility\ImGuiManager\ImGuiManager.h"

// ImGuiで使用.
extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND, UINT, WPARAM, LPARAM );

int WINAPI WinMain( 
	HINSTANCE hInstance, 
	HINSTANCE hInstancePrev, 
	LPSTR pCmdLine, 
	int nCmdShow )
{
#ifdef _DEBUG
	// メモリリーク検出
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif	// #ifdef _DEBUG.

	std::unique_ptr<CMain> pMain = std::make_unique<CMain>();

	if( pMain == nullptr ) return 0;

	// ウィンドウの作成.
	if( FAILED( pMain->InitWindow( hInstance ) )) return 0;
	// メイン初期化処理.
	if( FAILED( pMain->Init() )) return 0;

	// メインループ.
	pMain->Loop();

	// メイン解放処理.
	pMain->Destroy();

	return 0;
}

LRESULT CALLBACK WndProc(
	HWND hWnd, 
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam )
{
	if( ImGui_ImplWin32_WndProcHandler( hWnd, uMsg, wParam, lParam ) )
		return true;
	IMGUI_API
	switch( uMsg ){
	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		//ｷｰ別の処理.
		switch( static_cast<char>(wParam) ){
		case VK_ESCAPE:	//ESCｷｰ.
#ifdef _DEBUG
			if( MessageBox( nullptr, "ゲームを終了しますか？", "警告", MB_YESNO ) == IDYES ){ 
				PostQuitMessage(0); 
			}
			break;
#endif	// #ifdef _DEBUG.
		}
		break;

	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}