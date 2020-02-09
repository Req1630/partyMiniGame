#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <string>

#include "..\Global.h"

//-------------------------.
//	前方宣言.
class CD3DX;
class CFrameRate;
class CLoadManager;
namespace scene { class CSceneManager; }
//-------------------------.

/**************************************************
*	ﾒｲﾝｸﾗｽ.
**/
class CMain
{
	std::string WND_TITLE;
	std::string APP_NAME;
	const char* WINDOW_INFO_TEXT_PATH = "Data\\WindowInfo.txt";
public:
	CMain();
	~CMain();
	// ウィンドウ初期化関数.
	HRESULT InitWindow( HINSTANCE hInstance );

	// メッセージループ.
	void Loop();

	HRESULT Init();
	void Destroy();

private:
	// 更新処理.
	void Update();
	// 描画処理.
	void Render();

	// メッシュの読み込み関数.
	HRESULT Load();

	// ウィンドウ情報読み込み.
	void ReadWindowInfo();

private:
	HWND m_hWnd;

	std::unique_ptr<CD3DX>		m_pD3DX;		// DirectX関係.
	// Dx11.
	ID3D11Device*				m_pDevice11;	// デバイス "11".
	ID3D11DeviceContext*		m_pContext11;	// コンテキスト "11".
	// Dx9.
	LPDIRECT3DDEVICE9			m_pDevice9;		// デバイス "9".

	std::unique_ptr<CFrameRate>	m_pFrameRate;	// フレームレート.
	std::shared_ptr<CCamera>	m_pCamera;		// カメラクラス.

	LIGHT m_Light;	// ライト情報.

	std::shared_ptr<scene::CSceneManager>	m_pSceneManager;
	std::unique_ptr<CLoadManager>	m_pLoadManager;
};

#endif	// #ifndef MAIN_H.
