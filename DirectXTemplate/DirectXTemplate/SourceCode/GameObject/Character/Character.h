#ifndef CHARACTER_H
#define CHARACTER_H

#include "..\GameObject.h"

// �v���C���[���.
struct CHARACTER_INFO
{
	D3DXVECTOR3	vPosition;			// ���W.
	D3DXVECTOR3	vRotation;			// ��].
	float		ModelScale;			// ���f���X�P�[��.
	D3DXVECTOR3	vSphereAdjPosition;	// �X�t�B�A�̒����p���W.
	float		SphereAdjRdius;		// �X�t�B�A�̒����p���a.

	CHARACTER_INFO()
		: vPosition				{ 0.0f, 0.0f, 0.0f }
		, vRotation				{ 0.0f, 0.0f, 0.0f }
		, ModelScale			( 1.0f )
		, vSphereAdjPosition	{ 0.0f, 0.0f, 0.0f }
		, SphereAdjRdius		( 0.0f )
	{}
};

class CCharacter : public CGameObject
{
public:
	CCharacter();
	virtual ~CCharacter();

protected:
	// �ړ��֐�.
	virtual void Move() = 0;
};

#endif	// #ifndef CHARACTER_H.