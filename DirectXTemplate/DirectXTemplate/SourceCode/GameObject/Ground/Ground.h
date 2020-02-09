#ifndef GROUND_H
#define GROUND_H

#include "..\GameObject.h"

class CGround : public CGameObject	
{
private:
	const char* MODEL_NAME		= "Ground";	// モデル名.
	const float MODEL_SCALE		= 1.0f;		// モデルのサイズ.
	const float INIT_POSITION_Y = -0.001f;	// 初期座標y.
public:
	CGround();
	virtual ~CGround();

	// 更新関数.
	virtual void Update() override;
	// 当たり判定関数.
	virtual void Collision( pCollisionManager ) override;
	// 描画関数.
	virtual void Render( SCENE_INFO& ) override;

private:
	std::shared_ptr<CDX9StaticMesh>	m_StaticMesh;	// メッシュクラス.

};

#endif	// #ifndef GROUND_H.