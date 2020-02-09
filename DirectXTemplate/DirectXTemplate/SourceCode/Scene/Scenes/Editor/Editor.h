#ifndef EDITOR_H
#define EDITOR_H

#include "..\..\SceneBase\SceneBase.h"

class CControllerEdit;
class CCharacterEdit;
class CStage;	// �X�e�[�W�N���X.
class CGround;	// �O���E���h�N���X.

namespace scene
{
	/**********************************
	*	�Q�[���V�[���N���X.
	*/
	class CEditor : public CSceneBase
	{
	public:
		CEditor( SCENE_INIT_INFO sceneInitInfo );
		virtual ~CEditor();

		// �Ǎ��֐�.
		virtual void Load() override;
		// �X�V�֐�.
		virtual void Update() override;
		// �`��֐�.
		virtual void Render() override;

	private:
		// ���݂̃V�[�������o��.
		void ScenePop();

	private:
		std::shared_ptr<CStage>		m_pStage;	// �X�e�[�W�N���X.
		std::shared_ptr<CGround>	m_pGround;	// �O���E���h�N���X.

		std::unique_ptr<CControllerEdit> m_pControllerEdit;
		std::unique_ptr<CCharacterEdit> m_pCharacterEdit;
	};
};	// namespace scene.

#endif	// #ifndef EDITOR_H.