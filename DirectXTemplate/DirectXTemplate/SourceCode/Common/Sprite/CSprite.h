#ifndef CSPRITE_UI_H
#define CSPRITE_UI_H

#include "..\Common.h"

/**************************************************
*	ｽﾌﾟﾗｲﾄUIｸﾗｽ.
**/
class CSprite : public CCommon
{
	//======================================
	//	構造体.
	//======================================
	//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧのｱﾌﾟﾘ側の定義.
	//※ｼｪｰﾀﾞ内のｺﾝｽﾀﾝﾄﾊﾞｯﾌｧと一致している必要あり.
	struct SHADER_CONSTANT_BUFFER
	{
		ALIGN16 D3DMATRIX	mW;				// ワールド行列.
		ALIGN16 D3DMATRIX	mWVP;
		ALIGN16 float		fViewPortWidth;	// ビューポート幅.
		ALIGN16 float		fViewPortHeight;// ビューポート高さ.
		ALIGN16 float		fAlpha;			// アルファ値(透過で使用する).
		ALIGN16 D3DXVECTOR4 vColor;			// カラー(RGBAの型に合わせる).
		ALIGN16 D3DXVECTOR2 vUV;			// UV座標.
	};
	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//頂点座標.
		D3DXVECTOR2	Tex;	//ﾃｸｽﾁｬ座標.
	};
	// 幅高さ構造体(float型).
	struct WHDIZE_FLOAT
	{
		float w;
		float h;
	};
public:
	// スプライト構造体.
	struct SPRITE_STATE
	{
		WHDIZE_FLOAT	Disp;		// 表示幅,高さ.
		WHDIZE_FLOAT	Base;		// 元画像の幅,高さ.
		WHDIZE_FLOAT	Stride;		// 1コマ当たりの幅,高さ.
		D3DXVECTOR3		vPos;		// 座標.
		int				FrameNum;	// フレーム数.

		enum enSPRITE_STATE
		{
			None,

			enDisp_w = 0,
			enDisp_h,
			enBase_w,
			enBase_h,
			enStride_w,
			enStride_h,
			envPos_x,
			envPos_y,
			envPos_z,
			enFrameNum,

			MAX = enFrameNum,
		};
	};

	CSprite();	//ｺﾝｽﾄﾗｸﾀ.
	CSprite( 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		const char* fileName, 
		const SPRITE_STATE& pSs );
	
	~CSprite();	//ﾃﾞｽﾄﾗｸﾀ.

	//初期化.
	HRESULT Init( 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, 
		const char* fileName, 
		const SPRITE_STATE& pSs );

	//解放.
	void Release();

	//ﾚﾝﾀﾞﾘﾝｸﾞ用.
	void Render( const D3DXMATRIX& mView, const D3DXMATRIX& mProj );
	void RenderUI();
private:
	//ｼｪｰﾀﾞ作成.
	HRESULT InitShader();
	//ﾓﾃﾞﾙ作成.
	HRESULT InitModel();
	// テクスチャ作成.
	HRESULT CreateTexture( const char* fileName, ID3D11ShaderResourceView** pTexture );
	HRESULT InitVertex( ID3D11Buffer** ppVertxtBuffer, VERTEX* pVertex );
	HRESULT InitSample();
	HRESULT InitVertexLayout( ID3DBlob* pCompiledShader );
	HRESULT InitConstantBuffer( ID3D11Buffer** ppConstantBuffer, UINT size );

	int myGcd( int t, int t2)
	{
		if( t2 == 0 ) return t;
		return myGcd( t2, t % t2 );
	}
private:
	//↓ﾓﾃﾞﾙの種類ごとに用意.
	ID3D11VertexShader*		m_pVertexShader;	//頂点ｼｪｰﾀﾞ.
	ID3D11VertexShader*		m_pVertexShaderUI;	//頂点ｼｪｰﾀﾞ.
	ID3D11InputLayout*		m_pVertexLayout;	//頂点ﾚｲｱｳﾄ.
	ID3D11PixelShader*		m_pPixelShader;		//ﾋﾟｸｾﾙｼｪｰﾀﾞ.
	ID3D11Buffer*			m_pConstantBuffer;	//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧ.

	//↓ﾓﾃﾞﾙごとに用意.
	ID3D11Buffer*			m_pVertexBuffer;	//頂点ﾊﾞｯﾌｧ.
	ID3D11Buffer*			m_pVertexBufferUI;	//頂点ﾊﾞｯﾌｧ.

	ID3D11SamplerState*		m_pSampleLinear;	//ｻﾝﾌﾟﾗ:ﾃｸｽﾁｬに各種ﾌｨﾙﾀをかける.
	ID3D11ShaderResourceView*	m_pTexture;		//ﾃｸｽﾁｬ.

	int			m_AnimCount;	//ｶｳﾝﾀ.
	D3DXVECTOR2	m_UV;		//ﾃｸｽﾁｬUV座標.


	SPRITE_STATE	m_SState;		// スプライト情報.
	POINT			m_PatternNo;	// パターン番号.
};


#endif	// #ifndef CSPRITE_UI_H.