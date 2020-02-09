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
	//ײď��.
	m_Light.vPos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);	//ײĈʒu.
	m_Light.vDir = D3DXVECTOR3(1.5f, 1.0f, -1.0f);	//ײĕ���.
	D3DXMatrixIdentity(&m_Light.mRot);				//ײĉ�]�s��.
	m_Light.fIntensity = 5.0f;						//ײċ��x(���邳).

	// �J�����̏�����.
	m_pCamera->SetPosition( D3DXVECTOR3( 0.0f, 12.0f, 10.0f ) );		// ���W.
	m_pCamera->SetLookPosition( D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) );	// ���_���W.

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
//	�������֐�.
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
//	����֐�.
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
//	�ǂݍ��݊֐�.
//====================================.
HRESULT CMain::Load()
{
	CDebugText::Init( m_pDevice11, m_pContext11, 40.0f, D3DXVECTOR4( 1.0f, 0.0f, 0.0f, 1.0f ) );
	m_pLoadManager->Load( m_hWnd, m_pDevice11, m_pContext11, m_pDevice9 );

	return S_OK;
}

//====================================.
//	�X�V����.
//====================================.
void CMain::Update()
{
	CXInput::StatsUpdate();

	m_pSceneManager->Load();
	m_pCamera->Update();
	m_pSceneManager->Update();
}

//====================================.
//	�`�揈��.
//====================================.
void CMain::Render()
{
	m_pD3DX->ClearBackBuffer();
	m_pCamera->InitViewProj();

	CDebugText::SetPosition( D3DXVECTOR3( 5.0f, 5.0f, 0.0f ) );
	CDebugText::Render( "FPS : ", (int)m_pFrameRate->GetFPS() );
	// �e�V�[���̕\��.
	m_pSceneManager->Render();

	m_pD3DX->SwapChainPresent();
}

//====================================.
//	����֐�.
//====================================.
void CMain::Loop()
{
	Load();	// �ǂݍ��݊֐�.

	// ���b�Z�[�W���[�v.
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
			// �t���[�����[�g�̑ҋ@����.
			m_pFrameRate->Wait();
		}
	}
}

//====================================.
// �E�B���h�E�������֐�.
//====================================.
HRESULT CMain::InitWindow( HINSTANCE hInstance )
{
	ReadWindowInfo();

	// �E�B���h�E�̒�`.
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

	// �E�B���h�E�N���X��Windows�ɓo�^.
	if( !RegisterClassEx( &wc ) ){
		ERROR_MESSAGE( "�E�B���h�E�N���X�̓o�^�Ɏ��s" );
		return E_FAIL;
	}

	// �E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(
		APP_NAME.c_str(),		// �A�v����.
		WND_TITLE.c_str(),		// �E�B���h�E�^�C�g��.
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E���(����).
		0, 0,					// �\���ʒux,y���W.
		WND_W, WND_H,			// �E�B���h�E��,����.
		nullptr,				// �e�E�B���h�E�n���h��..
		nullptr,				// ���j���[�ݒ�.
		hInstance,				// �C���X�^���X�ԍ�.
		nullptr );				// �E�B���h�E�쐬���ɔ�������C�x���g�ɓn���f�[�^.
	if( !m_hWnd ){
		ERROR_MESSAGE( "�E�B���h�E�N���X�쐬���s" );
		return E_FAIL;
	}

	// �E�B���h�E�̕\��.
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

//====================================.
// �E�B���h�E���ǂݍ���.
//====================================.
void CMain::ReadWindowInfo()
{
	std::vector<std::string> readList = CFileManager::TextLoading( WINDOW_INFO_TEXT_PATH );

	if( readList.empty() == true ){
		ERROR_MESSAGE("���X�g����ł���.");
		return;
	}

	WND_TITLE = readList[0];
	APP_NAME = readList[1];
}