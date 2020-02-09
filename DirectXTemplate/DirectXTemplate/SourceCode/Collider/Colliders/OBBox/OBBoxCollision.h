#ifndef OBBOX_COLLISION_H
#define OBBOX_COLLISION_H

#include "..\..\ColliderBase\ColliderBase.h"

class CBoxModel;

class COBBoxCollision : public CColliderBase
{
public: //------ �֐� -------.
	COBBoxCollision();
	virtual ~COBBoxCollision();

	// ���f���̃{�b�N�X�̍쐬.
	HRESULT InitModelBox( LPD3DXMESH pMesh );
	// �����蔻��̕\��.
	virtual void DebugRender( std::shared_ptr<CCamera> camera ) override;

	// �F��ς��邩�ǂ���.
	void SetChangeColor( const bool& changed );
	
	// �����x�N�g���擾�֐�.
	D3DXVECTOR3 GetDirection( const int& index );
	// �����̎擾�֐�.
	D3DXVECTOR3 GetLength(){ return m_vLength; }
	// �{�b�N�X�̒����p�����ݒ�.
	void SetAdjLength( const D3DXVECTOR3& length ){ m_vAdjLength = length; }

private: //----- �ϐ� ------.
	D3DXVECTOR3 m_vDirection[3];// �����x�N�g��.
	D3DXVECTOR3 m_vLength;		// ����.
	D3DXVECTOR3 m_vAdjLength;	// �����p�̒���.
#ifdef _DEBUG
	std::unique_ptr<CBoxModel> m_pDebugBox;	// �f�o�b�O�p�{�b�N�X���f��.
	static bool m_IsRender;	// �`�悷�邩�ǂ���.
#endif	// #ifdef _DEBUG.
};

#endif	// #ifndef OBBOX_COLLISION_H.