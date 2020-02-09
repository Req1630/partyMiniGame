#ifndef SPHERE_COLLISION_H
#define SPHERE_COLLISION_H

#include "..\..\ColliderBase\ColliderBase.h"

class CSphereModel;

class CSphereCollision : public CColliderBase
{
public:  //------- �֐� -------.
	CSphereCollision();
	virtual ~CSphereCollision();

	// ���f���̔��a�̍쐬.
	HRESULT InitModelRadius( LPD3DXMESH pMesh );
	// �����蔻��̕\��.
	virtual void DebugRender( std::shared_ptr<CCamera> camera ) override;

	// �F��ς��邩�ǂ���.
	void SetChangeColor( const bool& changed );
	// ���a�̎擾.
	float GetRadius() const { return m_Radius; }
	// �����p�̋��̔��a�̐ݒ�.
	void SetAdjRadius( const float& radius ){ m_AdjRadius = radius; }

private: //------- �ϐ� -------.
	float m_Radius;		// ���̂̔��a.
	float m_AdjRadius;	// �����p�̋��̔��a.
#ifdef _DEBUG
	std::unique_ptr<CSphereModel> m_pDebugSphere;	// �f�o�b�O�p�̋���.
	static bool m_IsRender;	// �`�悷�邩�ǂ���.
#endif	// #ifdef _DEBUG.
};

#endif	// #ifndef SPHERE_COLLISION_H.