#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H

#include <string>
#include <sstream>

#include "..\Common.h"

class CDebugTextShader;

// �f�o�b�O�e�L�X�g�N���X.
class CDebugText : public CCommon
{
private:
	const float DIMENSION		= 12.0f;
	const float WDIMENSION		= 10.0f;
	const float TEX_DIMENSION	= 128.0f;

public:
	CDebugText();	// �R���X�g���N�^
	~CDebugText();	// �f�X�g���N�^.

	// �C���X�^���X�̎擾.
	static CDebugText* GetInstance();

	// �������֐�.
	static HRESULT Init( 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		float Scale, 
		D3DXVECTOR4 vColor );
	// ���W�̐ݒ�.
	static void SetPosition( const D3DXVECTOR3& vPos ){ GetInstance()->m_vPos = vPos; }

	// �`��֐�(�ψ���).
	template<class... T1>
	static void Render( const T1&... t1 )
	{
		std::string Text = GetInstance()->initstring(t1...);
		GetInstance()->Render( Text );
	}
	// �`��֐�.
	void Render( const std::string& stext );
	
	// �T�C�Y�̎擾.
	static float GetScale(){ return GetInstance()->m_fScale*10.0f; };
private:
	// �t�H���g�����_�����O�֐�.
	void RenderFont( int FontIndex, float x, float y );
	// ���f���̍쐬.
	HRESULT InitModel();
	// �T���v���̍쐬.
	HRESULT InitSampleLinear();
	// �e�N�X�`���쐬.
	HRESULT InitTexture();

	template <class T>
	std::string to_std_string(const T& x)
	{
		std::stringstream ss;
		ss << x;
		return ss.str();
	}
	template<class T1, class... T2>
	std::string initstring( const T1& t1, const T2&... t2 )
	{
		std::string s = to_std_string(t1);
		return s + initstring(t2...);
	}
	template<class T1>
	std::string initstring( const T1& t1 )
	{
		std::string s = to_std_string(t1);
		return s;
	}

private:
	ID3D11Buffer*				m_pVertexBuffer[100];	// ���_�o�b�t�@.
	ID3D11SamplerState*			m_pSampleLinear;		// �T���v��:�e�N�X�`���Ɋe��t�B���^��������.
	ID3D11ShaderResourceView*	m_pAsciiTexture;		// �e�N�X�`��.

	std::unique_ptr<CDebugTextShader> m_pShader;		// �V�F�[�_�[.

	float		m_fKerning[100];	// �J�[�j���O.
	D3DXVECTOR4	m_vColor;			// �F.

private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CDebugText( const CDebugText & )				= delete;
	CDebugText& operator = ( const CDebugText & )	= delete;
	CDebugText( CDebugText && )						= delete;
	CDebugText& operator = ( CDebugText && )		= delete;
};

#endif // #ifndef CDEBUG_TEXT_H.