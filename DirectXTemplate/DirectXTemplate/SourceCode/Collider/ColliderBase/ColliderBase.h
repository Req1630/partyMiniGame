#ifndef COLLIDER_BASE_H
#define COLLIDER_BASE_H

#include "..\..\Global.h"

class CColliderBase
{
public: //------- �֐� -------.
	CColliderBase();
	virtual ~CColliderBase();

	// �����蔻��̕\��.
	virtual void DebugRender( std::shared_ptr<CCamera> camera ) = 0;

	// ���W�̎擾.
	D3DXVECTOR3 GetPosition() const { return (*m_pvPosition) + m_vAdjPosition; }
	// ���W�|�C���^�[�̐ݒ�.
	void SetPosition( D3DXVECTOR3* pvPosition ){ m_pvPosition = pvPosition; }
	// �����p�̍��W�̐ݒ�.
	void SetAdjPosition( const D3DXVECTOR3& pos ){ m_vAdjPosition = pos; }

	// ��]���̎擾.
	D3DXVECTOR3 GetRotation() const { return (*m_pvRotation); }
	// ��]���|�C���^�[�̐ݒ�.
	void SetRotation( D3DXVECTOR3* pvRotation ){ m_pvRotation = pvRotation; }

	// �T�C�Y�̎擾.
	float GetScale() const { return *m_pScale; }
	// �T�C�Y�|�C���^�[�̐ݒ�.
	void SetScale( float* pScale ){ m_pScale = pScale; }


protected: //------- �ϐ� -------.
	D3DXVECTOR3*	m_pvPosition;	// ���݂̍��W.
	D3DXVECTOR3		m_vAdjPosition;	// �����p�̍��W.
	D3DXVECTOR3*	m_pvRotation;	// ���݂̉�]���.
	float*			m_pScale;		// �T�C�Y.
};

#endif	// #ifndef COLLIDER_BASE_H.