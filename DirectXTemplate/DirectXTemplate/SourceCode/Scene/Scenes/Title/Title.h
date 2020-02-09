#ifndef TITLE_H
#define TITLE_H

#include "..\..\SceneBase\SceneBase.h"

namespace scene
{
	/**********************************
	*	�^�C�g���V�[���N���X.
	*/
	class CTitle : public CSceneBase
	{
	public:
		CTitle( SCENE_INIT_INFO sceneInitInfo );
		virtual ~CTitle();

		// �Ǎ��֐�.
		virtual void Load() override;
		// �X�V�֐�.
		virtual void Update() override;
		// �`��֐�.
		virtual void Render() override;
	private:
		std::shared_ptr<CDX9StaticMesh>	m_pStaticMesh;
	};
};

#endif	// #ifndef TITLE_H.