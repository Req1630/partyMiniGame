#include "Main.h"

#include <fstream>
#include <sstream>

#include "..\Common\D3DX\D3DX.h"
#include "..\Utility\FrameRate\FrameRate.h"
#include "..\Camera\Camera.h"
#include "..\Common\DebugText\DebugText.h"
#include "..\Scene\Scenes\SceneList.h"
#include "..\Resource\LoadManager\LoadManager.h"
#include "..\Utility\XInput\XInput.h"
#include "..\Utility\FileManager\FileManager.h"
#include "..\Utility\ImGuiManager\ImGuiManager.h"

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

CMain::CMain()
	: m_hWnd			( nullptr )
	, m_pD3DX			( std::make_unique<CD3DX>() )
	, m_pDevice11		( nullptr )
	, m_pContext11		( nullptr )
	, m_pDevice9		( nullptr )
	, m_pFrameRate		( std::make_unique<CFrameRate>() )
	, m_pCamera			( std::make_shared<CCamera>() )
	, m_Light			()
	, m_pSceneManager	( std::make_shared<scene::CSceneManager>() )
	, m_pLoadManager	( std::make_unique<CLoadManager>() )
{
	//ﾗｲﾄ情報.
	m_Light.vPos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);	//ﾗｲﾄ位置.
	m_Light.vDir = D3DXVECTOR3(1.5f, 1.0f, -1.0f);	//ﾗｲﾄ方向.
	D3DXMatrixIdentity(&m_Light.mRot);				//ﾗｲﾄ回転行列.
	m_Light.fIntensity = 5.0f;						//ﾗｲﾄ強度(明るさ).

	// カメラの初期化.
	m_pCamera->SetPosition( D3DXVECTOR3( 0.0f, 12.0f, 10.0f ) );		// 座標.
	m_pCamera->SetLookPosition( D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) );	// 視点座標.

	scene::CSceneBase::SCENE_INIT_INFO sceneInfo;
	sceneInfo.pSceneManager	= m_pSceneManager;
	sceneInfo.pCamera		= m_pCamera;
	sceneInfo.pLight		= &m_Light;

	m_pSceneManager->Push( std::make_shared<scene::CGame>(sceneInfo));
}

CMain::~CMain()
{
}

//====================================.
//	初期化関数.
//====================================.
HRESULT CMain::Init()
{
	if( FAILED( m_pD3DX->Init( m_hWnd ) )) return E_FAIL;

	m_pDevice11		= m_pD3DX->GetDevice11();
	m_pContext11	= m_pD3DX->GetContext11();
	m_pDevice9		= m_pD3DX->GetDevice9();
	
	CImGuiManager::Init( m_hWnd, m_pDevice11, m_pContext11 );

	return S_OK;
}

//====================================.
//	解放関数.
//====================================.
void CMain::Destroy()
{
	m_pSceneManager->StackRelease();

	CImGuiManager::Release();

	m_pDevice11		= nullptr;
	m_pContext11	= nullptr;
	m_pDevice9		= nullptr;

	m_pD3DX->Destroy();
}

//====================================.
//	読み込み関数.
//====================================.
HRESULT CMain::Load()
{
	CDebugText::Init( m_pDevice11, m_pContext11, 40.0f, D3DXVECTOR4( 1.0f, 0.0f, 0.0f, 1.0f ) );
	m_pLoadManager->Load( m_hWnd, m_pDevice11, m_pContext11, m_pDevice9 );

	return S_OK;
}

//====================================.
//	更新処理.
//====================================.
void CMain::Update()
{
	CXInput::StatsUpdate();

	m_pSceneManager->Load();
	m_pCamera->Update();
	m_pSceneManager->Update();
}

//====================================.
//	描画処理.
//====================================.
void CMain::Render()
{
	m_pD3DX->ClearBackBuffer();
	m_pCamera->InitViewProj();

	CDebugText::SetPosition( D3DXVECTOR3( 5.0f, 5.0f, 0.0f ) );
	CDebugText::Render( "FPS : ", (int)m_pFrameRate->GetFPS() );
	// 各シーンの表示.
	m_pSceneManager->Render();

	m_pD3DX->SwapChainPresent();
}

//====================================.
//	解放関数.
//====================================.
void CMain::Loop()
{
	Load();	// 読み込み関数.

	// メッセージループ.
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof(msg) );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE )){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
			if( m_pLoadManager->ThreadRelease() == true ){
				Update();
				Render();
			}
			// フレームレートの待機処理.
			m_pFrameRate->Wait();
		}
	}
}

//====================================.
// ウィンドウ初期化関数.
//====================================.
HRESULT CMain::InitWindow( HINSTANCE hInstance )
{
	ReadWindowInfo();

	// ウィンドウの定義.
	WNDCLASSEX wc = {};
	UINT windowStyle = CS_HREDRAW | CS_VREDRAW;

	wc.cbSize			= sizeof(wc);
	wc.style			= windowStyle;
	wc.lpfnWndProc		= WndProc;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon( nullptr, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( nullptr, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( LTGRAY_BRUSH );
	wc.lpszClassName	= APP_NAME.c_str();
	wc.hIconSm			= LoadIcon( nullptr, IDI_APPLICATION );

	// ウィンドウクラスをWindowsに登録.
	if( !RegisterClassEx( &wc ) ){
		ERROR_MESSAGE( "ウィンドウクラスの登録に失敗" );
		return E_FAIL;
	}

	// ウィンドウの作成.
	m_hWnd = CreateWindow(
		APP_NAME.c_str(),		// アプリ名.
		WND_TITLE.c_str(),		// ウィンドウタイトル.
		WS_OVERLAPPEDWINDOW,	// ウィンドウ種別(普通).
		0, 0,					// 表示位置x,y座標.
		WND_W, WND_H,			// ウィンドウ幅,高さ.
		nullptr,				// 親ウィンドウハンドル..
		nullptr,				// メニュー設定.
		hInstance,				// インスタンス番号.
		nullptr );				// ウィンドウ作成時に発生するイベントに渡すデータ.
	if( !m_hWnd ){
		ERROR_MESSAGE( "ウィンドウクラス作成失敗" );
		return E_FAIL;
	}

	// ウィンドウの表示.
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

//====================================.
// ウィンドウ情報読み込み.
//====================================.
void CMain::ReadWindowInfo()
{
	std::vector<std::string> readList = CFileManager::TextLoading( WINDOW_INFO_TEXT_PATH );

	if( readList.empty() == true ){
		ERROR_MESSAGE("リストが空でした.");
		return;
	}

	WND_TITLE = readList[0];
	APP_NAME = readList[1];
}