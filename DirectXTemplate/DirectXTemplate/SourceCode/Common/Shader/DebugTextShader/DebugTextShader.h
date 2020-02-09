#ifndef DEBUG_TEXT_SHADER_H
#define DEBUG_TEXT_SHADER_H

#include "..\ShaderBase.h"

class CDebugTextShader : public CShaderBase
{
private: //------ �萔 ------.
	const char* SHADER_NAME = "Data\\Shader\\DebugText.hlsl";	// �V�F�[�_�[�t�@�C��.

public: //------ �\���� ------.
	// �R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_�[���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct C_BUFFER
	{
		D3DXMATRIX	mWVP;		// ���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.
		D3DXVECTOR4 vColor;		// �J���[(RGBA�̌^�ɍ��킹��).
		D3DXVECTOR4 fAlpha;		// �A���t�@�l(x �̂ݎg�p).
	};
	// ���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	// ���_���W.
		D3DXVECTOR2	Tex;	// �e�N�X�`�����W.
	};
public: //------ �֐� ------.
	CDebugTextShader();
	virtual ~CDebugTextShader();
	// ������.
	virtual HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 ) override;
	// ���.
	virtual HRESULT Release() override;

	// �R���X�^���g�o�b�t�@�Ƀf�[�^��n��.
	void SetConstantBufferData( const D3DXMATRIX& mWVP, const D3DXVECTOR4& color );
	// �e��V�F�[�_�̐ݒ�.
	void ShaderSet( ID3D11Buffer* pVertexBuffer, ID3D11SamplerState* pSampleLinear, ID3D11ShaderResourceView* pAsciiTexture );

private: //------ �֐� ------.
	// �V�F�[�_�[�쐬.
	virtual HRESULT InitShader() override;
};

#endif	// #ifndef DEBUG_TEXT_SHADER_H.