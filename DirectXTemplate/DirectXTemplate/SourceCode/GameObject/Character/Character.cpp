#include "Character.h"
#include "..\..\Utility\FileManager\FileManager.h"

CCharacter::CCharacter()
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