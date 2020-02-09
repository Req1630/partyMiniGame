#ifndef XINPUT_CONFIG_H
#define XINPUT_CONFIG_H

#include <Windows.h>
#include <Xinput.h>
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

#pragma comment( lib, "xinput.lib" )

/*********************************:
*	Xinput�ݒ�N���X.
*		(�p�������Ďg�p).
*/
class CXInputConfig
{
public:
	inline static const char* FILE_PATH = "Data\\Config\\controller.txt";	// �R���g���[���[�̃t�@�C���p�X.

public:
	// �{�^�����X�g.
	enum enBUTTON_LIST
	{
		None,
		
		A = 0,
		B,
		X,
		Y,
		Left,
		Right,

		Max,
	};

public:
	CXInputConfig();
	virtual ~CXInputConfig();

	// �{�^���̐ݒ�.
	void SetButton( enBUTTON_LIST before, enBUTTON_LIST after );

	// �t�@�C���̓ǂݍ���.
	std::vector<std::string> FileReading();

protected:
	std::unordered_map<enBUTTON_LIST, DWORD> m_Button;	// ���肳�ꂽ�{�^��.
	std::vector<DWORD>	m_ButtonList;	// �{�^���̃��X�g.
};

#endif	// #ifndef XINPUT_CONFIG_H.