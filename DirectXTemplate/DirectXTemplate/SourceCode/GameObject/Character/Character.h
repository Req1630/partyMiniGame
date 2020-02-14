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
	inline static const char* CHARACTER_PARAMETER_FILE_PATH = "Data\\GameText\\CharacterData\\";
	inline static const char* CHARACTER_PARAMETER_FILE_EXE = ".data";

public:
	CCharacter();
	virtual ~CCharacter();

	// �L�����N�^�[�p�����[�^�̏�������.
	static void CharacterParameterWriting( 
		const CHARACTER_INFO& characterInfo,
		const std::string& characterName );

	// �L�����N�^�[�p�����[�^�̓ǂݍ���.
	static void CharacterParameterReading( 
		CHARACTER_INFO& characterInfo,
		const std::string& characterName );

protected:
	// �ړ��֐�.
	virtual void Move() = 0;
};

#endif	// #ifndef CHARACTER_H.