#ifndef CONTROLLER_EDIT_H
#define CONTROLLER_EDIT_H

#include "..\..\Utility\ImGuiManager\ImGuiManager.h"
#include "..\..\Utility\XInput\XInput.h"

#include <filesystem>

namespace fs = std::filesystem;

class CControllerEdit
{
private:
	const ImVec2 WINDOW_SIZE		= { 250.0f, 300.0f };	// �E�B���h�E�T�C�Y.
	const ImVec2 RENDER_POSITION	= { 10.0f, 20.0f };		// �`����W.
	const char* BUTTON_ITEMS[6]		= { "A", "B", "X", "Y", "Left", "Right" };

public:
	CControllerEdit();
	~CControllerEdit();

	// �`��֐�.
	void Render();

private:
	// ���x���̕`��.
	void LabelRender( const int& index );

	// �{�^���ݒ�̌���.
	void ButtonSettingDetermination();

	// �t�@�C���̓ǂݍ���.
	void FileReading();
	// �t�@�C���̏�������.
	void FileWriting();

private:
	std::vector<fs::path> m_LabelList;
	std::vector<CXInput::enBUTTON_LIST> m_ItemList;
};

#endif	// #ifndef CONTROLLER_EDIT_H.