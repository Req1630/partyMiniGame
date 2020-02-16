#ifndef PLAYER_H
#define PLAYER_H

#include "..\Character.h"

class CPlayer : public CCharacter
{
private:
	const float MOVE_DIVISION		= 600000.0f;// �ړ����x.
	const float OUTSIDE_STAGE_VALUE	= 3.5f;		// �X�e�[�W�O�̒l.

public:
	CPlayer();
	virtual ~CPlayer();

	// �X�V�֐�.
	virtual void Update() override;
	// �����蔻��֐�.
	virtual void Collision( pGameObject ) override;
	// �`��֐�.
	virtual void Render( SCENE_INFO& ) override;

	// �v���C���[���m�̓����蔻��.
	void PlayerToCollision( pGameObject );

	// ����֐�.
	void Control();
	// �v���C���[�l���̐ݒ�.
	void SetPlayerNumber( const int& playerNumber );

private:
	// �ړ��֐�.
	virtual void Move() override;
	// �X�e�[�W�O�ɍs���Ȃ��悤�ɂ���.
	void OutsideMove();

private:
	std::shared_ptr<CDX9StaticMesh> m_pStaticMesh;	// ���b�V���N���X.
	D3DXVECTOR2	m_MoveVector;		// �ړ��p�x�N�g��.
	D3DXVECTOR2 m_MovePower;		// �ړ���.
	int			m_PlayerNumber;		// �v���C���[�l��.
};

#endif	// #ifndef PLAYER_H.