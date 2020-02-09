#ifndef EDITOR_H
#define EDITOR_H

#include "..\..\SceneBase\SceneBase.h"

class CControllerEdit;
class CCharacterEdit;
class CStage;	// ステージクラス.
class CGround;	// グラウンドクラス.

namespace scene
{
	/**********************************
	*	ゲームシーンクラス.
	*/
	class CEditor : public CSceneBase
	{
	public:
		CEditor( SCENE_INIT_INFO sceneInitInfo );
		virtual ~CEditor();

		// 読込関数.
		virtual void Load() override;
		// 更新関数.
		virtual void Update() override;
		// 描画関数.
		virtual void Render() override;

	private:
		// 現在のシーンを取り出す.
		void ScenePop();

	private:
		std::shared_ptr<CStage>		m_pStage;	// ステージクラス.
		std::shared_ptr<CGround>	m_pGround;	// グラウンドクラス.

		std::unique_ptr<CControllerEdit> m_pControllerEdit;
		std::unique_ptr<CCharacterEdit> m_pCharacterEdit;
	};
};	// namespace scene.

#endif	// #ifndef EDITOR_H.