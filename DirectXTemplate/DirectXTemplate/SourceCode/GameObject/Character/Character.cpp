#include "Character.h"
#include "..\..\Utility\FileManager\FileManager.h"

CCharacter::CCharacter()
	: m_ModelName			("")
	, m_SphereAdjPosition	{ 0.0f, 0.0f, 0.0f }
	, m_SphereRadius		( 0.0f )
{
}

CCharacter::~CCharacter()
{
}

// �L�����N�^�[�p�����[�^�̏�������.
void CCharacter::CharacterParameterWriting( 
	const CHARACTER_INFO& characterInfo,
	const std::string& characterName )
{
	std::string path = CHARACTER_PARAMETER_FILE_PATH;
	path += characterName + CHARACTER_PARAMETER_FILE_EXE;

	CFileManager::BinaryWriting( path, characterInfo );
}

// �L�����N�^�[�p�����[�^�̓ǂݍ���.
void CCharacter::CharacterParameterReading(
	CHARACTER_INFO& characterInfo,
	const std::string& characterName )
{
	std::string path = CHARACTER_PARAMETER_FILE_PATH;
	path += characterName + CHARACTER_PARAMETER_FILE_EXE;

	CFileManager::BinaryReading( path, characterInfo );
}

// �L�����N�^�[���̐ݒ�.
void CCharacter::SetCharacterParam( 
	const CHARACTER_INFO& playerInfo, 
	const std::string& modelName )
{
	m_vPosition			= playerInfo.vPosition;
	m_vRotation			= playerInfo.vRotation;
	m_ModelScale		= playerInfo.ModelScale;
	m_ModelName			= modelName;
	m_SphereAdjPosition = playerInfo.vSphereAdjPosition;
	m_SphereRadius		= playerInfo.SphereAdjRdius;
}