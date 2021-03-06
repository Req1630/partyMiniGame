#ifndef COMMON_H
#define COMMON_H

#include "..\Global.h"

class CCommon
{
public:
	enum class enRS_STATE
	{
		None,	// 正背面描画.
		Back,	// 背面を描画しない.
		Front,	// 正面を描画しない.
		Wire,	// ワイヤーフレーム描画.

		Max,
	};
public:
	CCommon();
	virtual ~CCommon();

	// 座標の設定.
	void SetPosition( const D3DXVECTOR3& vPos ){ m_vPos = vPos; }
	// 回転情報の設定.
	void SetRotation( const D3DXVECTOR3& vRot ){ m_vRot = vRot; }
	// サイズの設定.
	void SetScale( const float& fScale ){ m_fScale = fScale; }
	// アルファ値の設定.
	void SetAlpha( const float& fAlpha ){ m_fAlpha = fAlpha; }

	// ブレンドを有効:無効に設定する.
	void SetBlend( bool EnableAlpha );
	// アルファカバレージを有効:無効に設定する.
	void SetCoverage( bool EnableCoverage );
	// 深度テストを有効:無効に設定する.
	void SetDeprh( bool flag );
	// ラスタライザステート設定.
	void SetRasterizerState( const enRS_STATE& rsState );

protected:
	// デバイスの取得、各情報の初期化.
	HRESULT InitPram( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );

private:
	// ブレンド作成.
	HRESULT InitBlend();
	// 深度テスト作成.
	HRESULT InitDeprh();
	// ラスタライザステート作成.
	HRESULT InitRasterizerState();
private:
	ID3D11DepthStencilState*	m_pDepthStencilState;		// デプスステンシル有効.
	ID3D11DepthStencilState*	m_pDepthStencilStateOff;	// デプスステンシル無効.

	ID3D11BlendState*			m_pAlphaBlend;				// アルファブレンド有効.
	ID3D11BlendState*			m_pNoAlphaBlend;			// アルファブレンド無効.
	ID3D11BlendState*			m_pAlphaToCoverage;			// アルファカバレージ有効.

	ID3D11RasterizerState*		m_pRsSoldAndNone;	// ソリッドAnd正背面描画.
	ID3D11RasterizerState*		m_pRsSoldAndBack;	// ソリッドAnd背面を描画しない.
	ID3D11RasterizerState*		m_pRsSoldAndFront;	// ソリッドand正面を描画しない.
	ID3D11RasterizerState*		m_pRsWireFrame;		// ワイヤーフレーム描画.
protected:
	ID3D11Device*			m_pDevice11;	// デバイスオブジェクト.
	ID3D11DeviceContext*	m_pContext11;	// デバイスコンテキスト.

	D3DXVECTOR3 m_vPos;		// 座標情報.
	D3DXVECTOR3 m_vRot;		// 回転情報.
	float		m_fScale;	// スケール情報.
	float		m_fAlpha;	// アルファ値.
};

#endif	// #ifndef COMMON_H.