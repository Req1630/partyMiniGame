#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "..\SceneBase\SceneBase.h"

namespace scene
{
	class CSceneManager
	{	
	public:
		CSceneManager();
		~CSceneManager();

		// 読込関数,
		void Load();
		// 更新関数.
		void Update();
		// 描画関数.
		void Render();

		// シーンを追加する.
		void Push( std::shared_ptr<CSceneBase> pScenebase );
		// シーンを取り出す.
		void Pop();
		// シーンを二つ取り出す.
		void TwoPop();
		// シーンを切り替える.
		void Change( std::shared_ptr<CSceneBase> pScenebase );
		// 現在スタックしているシーンをすべて取り出す.
		void StackRelease();

	private:
		// エディットシーンに変更.
		void ScenePushEditor();

	private:
		std::stack<std::shared_ptr<CSceneBase>> m_pStackScene;	// スタックシーン.
	};
};	// namespace scene.
#endif // #ifndef SCENE_MANAGER_H.