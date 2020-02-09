#ifndef BOX_MODEL_H
#define BOX_MODEL_H

#include "..\..\..\Common\Common.h"

class CSimpleShader;

class CBoxModel : public CCommon
{
private: //------- �萔 -------.
	const D3DXVECTOR4 MODEL_COLOR			= { 0.0f, 0.0f, 1.0f, 1.0f };	// ���f���̐F.
	const D3DXVECTOR4 MODEL_CHANGE_COLOR	= { 1.0f, 0.0f, 0.0f, 1.0f };	// ���f���̐F.

public: //------- �֐� -------.
	CBoxModel();
	virtual ~CBoxModel();

	// ������.
	HRESULT Init( const D3DXVECTOR3& vMaxPoint, const D3DXVECTOR3& vMinPoint );
	// �`��.
	void Render( std::shared_ptr<CCamera> camera );
	// �F��ς���.
	void ChangeColor( const bool& changed ){ m_IsColorChanged = changed; }

private: //------- �֐� -------.
		 // WVP Matrix�̍쐬.
	D3DXMATRIX CreateWVPMatrix( std::shared_ptr<CCamera> camera, D3DXMATRIX& mWVP );
	// ���f���̍쐬.
	HRESULT InitModel( const D3DXVECTOR3& vMaxPoint, const D3DXVECTOR3& vMinPoint );

private: //------- �ϐ� -------.
	std::unique_ptr<CSimpleShader>	m_pSimpleShader;	// �V���v���V�F�[�_.
	ID3D11Buffer*					m_pVertexBuffer;	// ���_�o�b�t�@.
	ID3D11Buffer*					m_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@.

	bool m_IsColorChanged;	// �F���ς�������ǂ���.
};

#endif	// #ifndef BOX_MODEL_H.