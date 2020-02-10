#ifndef GAME_H
#define GAME_H

#include "..\..\SceneBase\SceneBase.h"
#include "..\..\..\Collider\Colliders\Sphere\SphereModel.h"

class CStage;	// ステージクラス.
class CGround;	// グラウンドクラス.

class CPlayerManager;	// プレイヤークラス.
class CEnemyManager;	// 敵クラス.

namespace scene
{
	/**********************************
	*	ゲームシーンクラス.
	*/
	class CGame : public CSceneBase
	{
	public:
		CGame( SCENE_INIT_INFO sceneInitInfo );
		virtual ~CGame();

		// 読込関数.
		virtual void Load() override;
		// 更新関数.
		virtual void Update() override;
		// 描画関数.
		virtual void Render() override;

	private:
		std::shared_ptr<CStage>		m_pStage;	// ステージクラス.
		std::shared_ptr<CGround>	m_pGround;	// グラウンドクラス.

		std::shared_ptr<CPlayerManager>	m_pPlayerManager;	// プレイヤークラス.
		std::shared_ptr<CEnemyManager>	m_pEnemyManager;	// 敵クラス.
	};
};

#endif	// #ifndef GAME_H.