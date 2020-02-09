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

		// �Ǎ��֐�,
		void Load();
		// �X�V�֐�.
		void Update();
		// �`��֐�.
		void Render();

		// �V�[����ǉ�����.
		void Push( std::shared_ptr<CSceneBase> pScenebase );
		// �V�[�������o��.
		void Pop();
		// �V�[�������o��.
		void TwoPop();
		// �V�[����؂�ւ���.
		void Change( std::shared_ptr<CSceneBase> pScenebase );
		// ���݃X�^�b�N���Ă���V�[�������ׂĎ��o��.
		void StackRelease();

	private:
		// �G�f�B�b�g�V�[���ɕύX.
		void ScenePushEditor();

	private:
		std::stack<std::shared_ptr<CSceneBase>> m_pStackScene;	// �X�^�b�N�V�[��.
	};
};	// namespace scene.
#endif // #ifndef SCENE_MANAGER_H.