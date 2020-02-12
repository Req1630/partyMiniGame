#ifndef STAGE_H
#define STAGE_H

#include "..\GameObject.h"

class CStage : public CGameObject	
{
private:
	const char* MODEL_NAME = "Stage";	// モデル名.
	const float MODEL_SCALE = 2.0f;		// モデルのサイズ.

public:
	CStage();
	virtual ~CStage();

	// 更新関数.
	virtual void Update() override;
	// 当たり判定関数.
	virtual void Collision( pGameObject ) override;
	// 描画関数.
	virtual void Render( SCENE_INFO& ) override;

private:
	std::shared_ptr<CDX9StaticMesh>	m_StaticMesh;	// メッシュクラス.

};

#endif	// #ifndef STAGE_H.