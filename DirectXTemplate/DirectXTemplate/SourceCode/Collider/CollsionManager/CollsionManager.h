#ifndef COLLSION_MANAGER_H
#define COLLSION_MANAGER_H

#include "..\..\Global.h"

class CSphereCollision;
class COBBoxCollision;

//----------------------------------.
//	�����蔻��}�l�[�W���[�N���X.
//	 �e�I�u�W�F�N�g�͂��̃N���X���g�p����.
//----------------------------------.
class CCollsionManager
{
	typedef std::shared_ptr<CSphereCollision> pSphereCollision;
	typedef std::shared_ptr<COBBoxCollision> pOBBoxCollision;

public: //------ �֐� -------.
	CCollsionManager();
	~CCollsionManager();

	// ������.
	HRESULT Init( LPD3DXMESH pMesh, D3DXVECTOR3* pPos, D3DXVECTOR3* pRot, float* pScale );
	// �f�o�b�O�p�`��.
	void DebugRender( std::shared_ptr<CCamera> camera );

	/*
	//- �����蔻��֐� -.
	*/

	// �X�t�B�A���m�̓����蔻��.
	bool IsShereToShere( pSphereCollision pSphere );
	// OBB���m�̓����蔻��.
	bool IsOBBToOBB( pOBBoxCollision pOBBox );

	/*
	//- �擾�֐� -.
	*/

	// �X�t�B�A�擾�֐�.
	pSphereCollision GetSphere() const { return m_pSphere; }
	// �{�b�N�X�擾�֐�.
	pOBBoxCollision GetOBB() const { return m_pOBBox; }

	/*
	//- �����p�֐� -.
	*/

	// �X�t�B�A�̒����p���W�ݒ�.
	void SetSphereAdjPosition( const D3DXVECTOR3& pos );
	// �X�t�B�A�̒����p���a�ݒ�.
	void SetSphereAdjRadius( const float& radius );
	// �{�b�N�X�̒����p���W�ݒ�.
	void SetBoxAdjPosition( const D3DXVECTOR3& pos );
	// �{�b�N�X�̒����p�����ݒ�.
	void SetBoxAdjLength( const D3DXVECTOR3& length );

private: //------ �ϐ� -------.
	pSphereCollision m_pSphere;	// �X�t�B�A.
	pOBBoxCollision m_pOBBox;	// �{�b�N�X.
};

#endif	// #ifndef COLLSION_MANAGER_H.