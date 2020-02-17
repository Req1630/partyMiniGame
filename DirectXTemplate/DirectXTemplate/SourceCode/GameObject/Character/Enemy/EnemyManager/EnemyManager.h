#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "..\EnemyBase.h"

#include <vector>

class CEnemyManager
{
	typedef scene::CSceneBase::SCENE_INIT_INFO SCENE_INFO;
	typedef std::shared_ptr<CCollsionManager> pCollisionManager;

private:
	const char* ENEMY_DIRECTION_TEXT_PATH = "Data\\GameText\\Enemy\\EnemyDirection.txt";
	const char* ENEMY_INIT_POS_TEXT_PATH = "Data\\GameText\\Enemy\\EnemyInitPos.txt";

public:
	CEnemyManager();
	~CEnemyManager();

	// �X�V�֐�.
	void Update();
	// �����蔻��֐�.
	void Collision( pCollisionManager );
	// �`��֐�.
	void Render( SCENE_INFO& );

	// �G�擾�֐�.
	std::shared_ptr<CGameObject> GetEnemy( const int index ) const;
	// �G���X�g�T�C�Y�擾�֐�.
	int GetEnemySize() const { return m_pEnemyList.size(); }

private:
	// �G�̍쐬.
	void EnemyCreating();
	// �������̓ǂݍ���.
	void DirectionInfoReading();
	// �������W�̓ǂݍ���.
	void InitPositionReading();

private:
	std::vector<std::shared_ptr<CEnemyBase>> m_pEnemyList;	// �G���X�g.
	std::vector<float> m_DirectionList;	// �����̃��X�g.
	std::vector<float> m_InitPosList;	// �������W�̃��X�g.
	int m_GameCount;				// �Q�[���J�E���g.
};

#endif	// #ifndef ENEMY_MANAGER_H.