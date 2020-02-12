#ifndef STAGE_H
#define STAGE_H

#include "..\GameObject.h"

class CStage : public CGameObject	
{
private:
	const char* MODEL_NAME = "Stage";	// ���f����.
	const float MODEL_SCALE = 2.0f;		// ���f���̃T�C�Y.

public:
	CStage();
	virtual ~CStage();

	// �X�V�֐�.
	virtual void Update() override;
	// �����蔻��֐�.
	virtual void Collision( pGameObject ) override;
	// �`��֐�.
	virtual void Render( SCENE_INFO& ) override;

private:
	std::shared_ptr<CDX9StaticMesh>	m_StaticMesh;	// ���b�V���N���X.

};

#endif	// #ifndef STAGE_H.