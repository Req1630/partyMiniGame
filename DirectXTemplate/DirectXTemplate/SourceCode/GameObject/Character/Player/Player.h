#ifndef PLAYER_H
#define PLAYER_H

#include "..\Character.h"
struct PLAYER_INFO;

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
	virtual void Collision( pCollisionManager ) override;
	// �`��֐�.
	virtual void Render( SCENE_INFO& ) override;

	// ����֐�.
	void Control();
	// �v���C���[�l���̐ݒ�.
	void SetPlayerNumber( const int& playerNumber );

	// �v���C���[���̐ݒ�.
	void SetPlayerParam( const PLAYER_INFO& playerInfo, const std::string& modelName );

private:
	// �ړ��֐�.
	virtual void Move() override;
	// �X�e�[�W�O�ɍs���Ȃ��悤�ɂ���.
	void OutsideMove();

private:
	std::shared_ptr<CDX9StaticMesh> m_pStaticMesh;	// ���b�V���N���X.
	D3DXVECTOR2	m_MoveVector;		// �ړ��p�x�N�g��.
	D3DXVECTOR2 m_MovePower;		// �ړ���.
	int m_PlayerNumber;				// �v���C���[�l��.
	std::string m_ModelName;		// ���f����.
	D3DXVECTOR3 m_SphereAdjPosition;// �X�t�B�A�̓����蔻����W.
	float m_SphereRadius;			// �X�t�B�A�̓����蔻�蔼�a.
};

#endif	// #ifndef PLAYER_H.