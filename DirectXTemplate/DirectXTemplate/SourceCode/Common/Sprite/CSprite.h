#ifndef CSPRITE_UI_H
#define CSPRITE_UI_H

#include "..\Common.h"

/**************************************************
*	���ײ�UI�׽.
**/
class CSprite : public CCommon
{
	//======================================
	//	�\����.
	//======================================
	//�ݽ����ޯ̧�̱��ؑ��̒�`.
	//������ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		ALIGN16 D3DMATRIX	mW;				// ���[���h�s��.
		ALIGN16 D3DMATRIX	mWVP;
		ALIGN16 float		fViewPortWidth;	// �r���[�|�[�g��.
		ALIGN16 float		fViewPortHeight;// �r���[�|�[�g����.
		ALIGN16 float		fAlpha;			// �A���t�@�l(���߂Ŏg�p����).
		ALIGN16 D3DXVECTOR4 vColor;			// �J���[(RGBA�̌^�ɍ��킹��).
		ALIGN16 D3DXVECTOR2 vUV;			// UV���W.
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//���_���W.
		D3DXVECTOR2	Tex;	//ø������W.
	};
	// �������\����(float�^).
	struct WHDIZE_FLOAT
	{
		float w;
		float h;
	};
public:
	// �X�v���C�g�\����.
	struct SPRITE_STATE
	{
		WHDIZE_FLOAT	Disp;		// �\����,����.
		WHDIZE_FLOAT	Base;		// ���摜�̕�,����.
		WHDIZE_FLOAT	Stride;		// 1�R�}������̕�,����.
		D3DXVECTOR3		vPos;		// ���W.
		int				FrameNum;	// �t���[����.

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

	CSprite();	//�ݽ�׸�.
	CSprite( 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		const char* fileName, 
		const SPRITE_STATE& pSs );
	
	~CSprite();	//�޽�׸�.

	//������.
	HRESULT Init( 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, 
		const char* fileName, 
		const SPRITE_STATE& pSs );

	//���.
	void Release();

	//�����ݸޗp.
	void Render( const D3DXMATRIX& mView, const D3DXMATRIX& mProj );
	void RenderUI();
private:
	//����ލ쐬.
	HRESULT InitShader();
	//���ٍ쐬.
	HRESULT InitModel();
	// �e�N�X�`���쐬.
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
	//�����ق̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11VertexShader*		m_pVertexShaderUI;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer;	//�ݽ����ޯ̧.

	//�����ق��Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;	//���_�ޯ̧.
	ID3D11Buffer*			m_pVertexBufferUI;	//���_�ޯ̧.

	ID3D11SamplerState*		m_pSampleLinear;	//�����:ø����Ɋe��̨����������.
	ID3D11ShaderResourceView*	m_pTexture;		//ø���.

	int			m_AnimCount;	//����.
	D3DXVECTOR2	m_UV;		//ø���UV���W.


	SPRITE_STATE	m_SState;		// �X�v���C�g���.
	POINT			m_PatternNo;	// �p�^�[���ԍ�.
};


#endif	// #ifndef CSPRITE_UI_H.