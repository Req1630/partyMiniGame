#ifndef GAME_H
#define GAME_H

#include "..\..\SceneBase\SceneBase.h"
#include "..\..\..\Collider\Colliders\Sphere\SphereModel.h"

class CStage;	// �X�e�[�W�N���X.
class CGround;	// �O���E���h�N���X.

class CPlayerManager;	// �v���C���[�N���X.
class CEnemyManager;	// �G�N���X.

namespace scene
{
	/**********************************
	*	�Q�[���V�[���N���X.
	*/
	class CGame : public CSceneBase
	{
	public:
		CGame( SCENE_INIT_INFO sceneInitInfo );
		virtual ~CGame();

		// �Ǎ��֐�.
		virtual void Load() override;
		// �X�V�֐�.
		virtual void Update() override;
		// �`��֐�.
		virtual void Render() override;

	private:
		std::shared_ptr<CStage>		m_pStage;	// �X�e�[�W�N���X.
		std::shared_ptr<CGround>	m_pGround;	// �O���E���h�N���X.

		std::shared_ptr<CPlayerManager>	m_pPlayerManager;	// �v���C���[�N���X.
		std::shared_ptr<CEnemyManager>	m_pEnemyManager;	// �G�N���X.
	};
};

#endif	// #ifndef GAME_H.