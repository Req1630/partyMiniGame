#ifndef TOON_H
#define TOON_H

#include "..\..\Common.h"

// �g�D�[���V�F�[�_�[�N���X.
class CToon
{
	inline static const char* SHADER_FIEL_PATH		= "Data\\";
	inline static const char* SHADER_ENTRY_POINT	= "Data\\";
	inline static const char* SHADER_MODEL			= "Data\\";
public:
	CToon();
	~CToon();

private:
	HRESULT InitShader();
	HRESULT InitVertexShader();
	HRESULT InitVertexLayout( ID3DBlob* pCompiledShader );

private:
	struct CBUFFER
	{
		D3DXMATRIX	mW;			// ���[���h�s��.
		D3DXMATRIX	mWVP;		// ���[���h����ˉe�܂ł̕ϊ��s��.
		D3DXVECTOR4 vLightDir;	// ���C�g����.
	};

	ID3D11Device*			m_pDevice11;

	ID3D11VertexShader*		m_pVertexShader;	// ���_�V�F�[�_�[.
	ID3D11InputLayout*		m_pVertexLayout;	// ���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;		// �s�N�Z���V�F�[�_�[.

	ID3D11ShaderResourceView*	m_pToonTexture;
};

#endif	// #ifndef TOON_H.