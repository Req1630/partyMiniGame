#include "XinputConfig.h"
#include "..\FileManager\FileManager.h"

CXInputConfig::CXInputConfig()
	: m_Button		()
	, m_ButtonList	( Max )
{
	// �e�{�^���̏�����.
	m_ButtonList[A] = m_Button[A] = XINPUT_GAMEPAD_A;
	m_ButtonList[B] = m_Button[B] = XINPUT_GAMEPAD_B;
	m_ButtonList[X] = m_Button[X] = XINPUT_GAMEPAD_X;
	m_ButtonList[Y] = m_Button[Y] = XINPUT_GAMEPAD_Y;
	m_ButtonList[Left]	= m_Button[Left]	= XINPUT_GAMEPAD_LEFT_SHOULDER;
	m_ButtonList[Right]	= m_Button[Right]	= XINPUT_GAMEPAD_RIGHT_SHOULDER;

	// �t�@�C������ǂݍ��񂾃{�^���̐ݒ�.
	FileReading();
}

CXInputConfig::~CXInputConfig()
{
	m_ButtonList.clear();
	m_Button.clear();
}

//------------------------------.
// �{�^���̐ݒ�.
//------------------------------.
void CXInputConfig::SetButton( enBUTTON_LIST before, enBUTTON_LIST after )
{
	// �e�������{�^���̍ő��葽����ΏI��.
	if( before >= Max ) return;
	if( after >= Max ) return;
	// ����{�^���ɐݒ�.
	m_Button[before] = m_ButtonList[after];
}

//------------------------------.
// �t�@�C���̓ǂݍ���.
//------------------------------.
std::vector<std::string> CXInputConfig::FileReading()
{
	std::vector<std::string> readList;	// �Ǎ��p�̃��X�g.
	// �t�@�C���̓Ǎ�.
	readList = CFileManager::TextLoading( FILE_PATH );

	// �ǂݍ��񂾃T�C�Y���Ȃ���ΏI��.
	if( readList.empty() == true ) return readList;

	// �e�{�^���ɓǂݍ��񂾃{�^����ݒ�.
	for( size_t i = 0; i < readList.size(); i+=2 ){
		// �ǂݍ��񂾃T�C�Y���{�^���̃��X�g��葽���̂Ŋ����Ă�����.
		int index = (i+1)/2;
		enBUTTON_LIST no	= static_cast<enBUTTON_LIST>(i/2);
		enBUTTON_LIST temp	= static_cast<enBUTTON_LIST>(std::stoi(readList[i+1]));
		m_ButtonList[index] = m_Button[no] = temp;
	}

	return readList;
}