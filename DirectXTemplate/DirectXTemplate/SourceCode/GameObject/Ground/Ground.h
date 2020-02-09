#ifndef GROUND_H
#define GROUND_H

#include "..\GameObject.h"

class CGround : public CGameObject	
{
private:
	const char* MODEL_NAME		= "Ground";	// ���f����.
	const float MODEL_SCALE		= 1.0f;		// ���f���̃T�C�Y.
	const float INIT_POSITION_Y = -0.001f;	// �������Wy.
public:
	CGround();
	virtual ~CGround();

	// �X�V�֐�.
	virtual void Update() override;
	// �����蔻��֐�.
	virtual void Collision( pCollisionManager ) override;
	// �`��֐�.
	virtual void Render( SCENE_INFO& ) override;

private:
	std::shared_ptr<CDX9StaticMesh>	m_StaticMesh;	// ���b�V���N���X.

};

#endif	// #ifndef GROUND_H.