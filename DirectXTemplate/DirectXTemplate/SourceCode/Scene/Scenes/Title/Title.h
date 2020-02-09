#ifndef TITLE_H
#define TITLE_H

#include "..\..\SceneBase\SceneBase.h"

namespace scene
{
	/**********************************
	*	タイトルシーンクラス.
	*/
	class CTitle : public CSceneBase
	{
	public:
		CTitle( SCENE_INIT_INFO sceneInitInfo );
		virtual ~CTitle();

		// 読込関数.
		virtual void Load() override;
		// 更新関数.
		virtual void Update() override;
		// 描画関数.
		virtual void Render() override;
	private:
		std::shared_ptr<CDX9StaticMesh>	m_pStaticMesh;
	};
};

#endif	// #ifndef TITLE_H.