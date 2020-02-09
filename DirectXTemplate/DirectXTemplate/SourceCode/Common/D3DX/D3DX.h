#ifndef D3DX_H
#define D3DX_H

#include "..\..\Global.h"

class CD3DX
{
private: //----- 定数 ------.
	const float CLEAR_BACK_COLOR[4] = { 0.1f, 0.1f, 0.1f, 1.0f };	// バックカラー.

public: //----- 関数 ------.
	CD3DX();
	~CD3DX();

	// 作成関数.
	HRESULT Init( HWND hWnd );
	// 解放関数.
	HRESULT Destroy();

	// クリアバックバッファ.
	void ClearBackBuffer();
	// スワップチェーンプレゼント.
	void SwapChainPresent();

	// デバイス11の取得関数.
	static ID3D11Device*		GetDevice11() { return m_pDevice11; }
	// コンテキスト11の取得関数.
	static ID3D11DeviceContext*	GetContext11() { return m_pContext11; }
	// デバイス9の取得関数.
	static LPDIRECT3DDEVICE9	GetDevice9() { return m_pDevice9; }

private: //----- 関数 ------.
	// デバイス9の作成.
	HRESULT InitDevice9();
	// デバイス11の作成.
	HRESULT InitDevice11();
	// レンダーターゲットビューの作成.
	HRESULT InitTexRTV();
	// ステンシルビューの作成.
	HRESULT InitDSTex();
	// ビューポートの作成.
	HRESULT InitViewports();
	// ラスタライザの作成.
	HRESULT InitRasterizer();

private: //----- 変数 ------.
	HWND	m_hWnd;	// ウィンドウハンドル.

	static ID3D11Device*		m_pDevice11;	// デバイス11.
	static ID3D11DeviceContext*	m_pContext11;	// コンテキスト11.
	static LPDIRECT3DDEVICE9	m_pDevice9;		// デバイス9.

	IDXGISwapChain*			m_pSwapChain;			// スワップチェーン.

	ID3D11RenderTargetView*	m_pBackBuffer_TexRTV;	// レンダーターゲットビュー.
	ID3D11Texture2D*		m_pBackBuffer_DSTex;	// テクスチャー2D.
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;	// ステンシルビュー.
	
};

#endif	// #ifndef D3DX_H.