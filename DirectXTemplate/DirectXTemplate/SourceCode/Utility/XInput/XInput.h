/**
* @file XInput.h
* @brief This is Use Xinput Controller file.
* @author Fukuta
* @date 2019/11/09
* @details Xinput���g�p���邽�߂̃N���X�ł�.
**/
#ifndef XINPUT_H
#define XINPUT_H

#include "XinputConfig.h"

static const int IDLE_THUMB_MAX		=  10000;	//!< �X�e�B�b�N�̗V��.
static const int IDLE_THUMB_MIN		= -10000;	//!< �X�e�B�b�N�̗V��.
static const int IDLE_TIGGER_MAX	=  100;		//!< �g���K�[�{�^���̗V��.

/**
* @brief XInput Class(Singleton).
*
* @details �o�C�u���[�V�����@�\�ȊO�̋@�\�͂��Ă܂�.
*/
class CXInput : public CXInputConfig
{
	const int FOUR_LIMITED_CONTROLLER = 4;	//!< �ڑ��R���g���[���̍ő吔.
	
	enum enBUTTON_STATE
	{
		enNOT_PUSHING		= 0,		//!< �����Ă��Ȃ����.

		enPRESSED_MOMENT	= 1 << 0,	//!< �������u��.
		enPRESS_AND_HOLD	= 1 << 1,	//!< ���������Ă���.
		enSEPARATED			= 1 << 2,	//!< ���������.
	};
public:
	/**
	* @brief �R���X�g���N�^.
	*/
	CXInput();
	/**
	* @brief �f�X�g���N�^.
	*/
	~CXInput();

	/**
	* @fn static void StatsUpdate()
	* @brief �R���g���[���[�̏�Ԃ��X�V.
	* @details ���t���[�����ɍX�V���邱��.
	*/
	static void StatsUpdate();

	/**
	* @fn static int GetConnectCount()
	* @return int ���݂̃R���g���[���[�̐ڑ���.
	* @brief �R���g���[���[�̐ڑ����Ă��鐔���擾.
	*/
	static int GetConnectCount(){ return GetInstance()->m_ConnectedCount; }
	
	/**
	* @fn static bool A_Button( const int& connectNum = 0 )
	* @brief A �{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE A_Button( const int& connectNum = 0 );

	/**
	* @fn static bool B_Button( const int& connectNum = 0 )
	* @brief B �{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE B_Button( const int& connectNum = 0 );

	/**
	* @fn static bool X_Button( const int& connectNum = 0 )
	* @brief X �{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE X_Button( const int& connectNum = 0 );

	/**
	* @fn static bool Y_Button( const int& connectNum = 0 )
	* @brief Y �{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE Y_Button( const int& connectNum = 0 );

	/**
	* @fn static bool DPadUp( const int& connectNum = 0 )
	* @brief ��{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE DPadUp( const int& connectNum = 0 );

	/**
	* @fn static bool DPadDown( const int& connectNum = 0 )
	* @brief ���{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE DPadDown( const int& connectNum = 0 );

	/**
	* @fn static bool DPadLEFT( const int& connectNum = 0 )
	* @brief ���{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE DPadLEFT( const int& connectNum = 0 );

	/**
	* @fn static bool DPadRIGHT( const int& connectNum = 0 )
	* @brief �E�{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE DPadRIGHT( const int& connectNum = 0 );

	/**
	* @fn static SHORT LThumbX_Axis( const int& connectNum = 0 )
	* @brief L�X�e�B�b�N��X���̒l���擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return SHORT �X�e�B�b�N�̌X���̒l.
	*/
	static SHORT LThumbX_Axis( const int& connectNum = 0 );

	/**
	* @fn static SHORT LThumbY_Axis( const int& connectNum = 0 )
	* @brief L�X�e�B�b�N��Y���̒l���擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return SHORT �X�e�B�b�N�̌X���̒l.
	*/
	static SHORT LThumbY_Axis( const int& connectNum = 0 );

	/**
	* @fn static SHORT RThumbX_Axis( const int& connectNum = 0 )
	* @brief R�X�e�B�b�N��X���̒l���擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return SHORT �X�e�B�b�N�̌X���̒l.
	*/
	static SHORT RThumbX_Axis( const int& connectNum = 0 );

	/**
	* @fn static SHORT RThumbY_Axis( const int& connectNum = 0 )
	* @brief R�X�e�B�b�N��Y���̒l���擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return SHORT �X�e�B�b�N�̌X���̒l.
	*/
	static SHORT RThumbY_Axis( const int& connectNum = 0 );

	/**
	* @fn static bool LThumb_Button( const int& connectNum = 0 )
	* @brief L�X�e�B�b�N�{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE LThumb_Button( const int& connectNum = 0 );

	/**
	* @fn static bool RThumb_Button( const int& connectNum = 0 )
	* @brief R�X�e�B�b�N�{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE RThumb_Button( const int& connectNum = 0 );

	/**
	* @fn static INT LTrigger( const int& connectNum = 0 )
	* @brief L�g���K�[�̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return INT �g���K�[�̉������ݒl.
	*/
	static INT LTrigger( const int& connectNum = 0 );

	/**
	* @fn static INT RTrigger( const int& connectNum = 0 )
	* @brief R�g���K�[�̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return INT �g���K�[�̉������ݒl.
	*/
	static INT RTrigger( const int& connectNum = 0 );

	/**
	* @fn static bool L_Button( const int& connectNum = 0 )
	* @brief L �{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE L_Button( const int& connectNum = 0 );

	/**
	* @fn static bool R_Button( const int& connectNum = 0 )
	* @brief R �{�^���̏�Ԃ��擾.
	* @param connectNum  �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE R_Button( const int& connectNum = 0 );

	/**
	* @fn static bool Start_Button( const int& connectNum = 0 )
	* @brief �X�^�[�g �{�^���̏�Ԃ��擾.
	* @param connectNum �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE Start_Button( const int& connectNum = 0 );

	/**
	* @fn static bool Back_Button( const int& connectNum = 0 )
	* @brief �o�b�N �{�^���̏�Ԃ��擾.
	* @param connectNum �g�p�������R���g���[���[�̎w�� �����w�肵�Ȃ��ꍇ�� 0 �Œ�.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	static enBUTTON_STATE Back_Button( const int& connectNum = 0 );

	// �{�^���̐ݒ�.
	static void SetButton( enBUTTON_LIST before, enBUTTON_LIST after )
	{ GetInstance()->CXInputConfig::SetButton( before, after ); }

	// �{�^���t�@�C���̓ǂݍ���.
	static std::vector<std::string> FileReading()
	{ return GetInstance()->CXInputConfig::FileReading(); }

private:
	/**
	* @fn void ConnectCheck( const int& connectNum )
	* @brief �ڑ��̐����m�F �N���X���Ŏg�p.
	* @param connectNum �w�肵���R���g���[���[.
	*/
	void ConnectCheck( const int& connectNum );

	/**
	* @fn bool IsButtonInput( const int& connectNum, const DWORD& button_mask )
	* @brief �{�^���n�̏�Ԃ��擾 �N���X���Ŏg�p.
	* @param connectNum �w�肵���R���g���[���[.
	* @param button_mask �w�肵�����{�^��.
	* @return bool ������Ă����� true�B������Ă��Ȃ������� false.
	*/
	bool IsButtonInput( const int& connectNum, const DWORD& button_mask );

	/**
	* @fn enBUTTON_STATE ButtonInputState( const int& connectNum, const DWORD& button_mask )
	* @brief �{�^���n�̓��͏�Ԃ��擾 �N���X���Ŏg�p.
	* @param connectNum �w�肵���R���g���[���[.
	* @param button_mask �w�肵�����{�^��.
	* @return enBUTTON_STATE �{�^���̓��͏��(�������u�ԂȂ�)��Ԃ�.
	*/
	enBUTTON_STATE ButtonInputState( const int& connectNum, const DWORD& button_mask );

	/**
	* @fn static CXInput* GetInstance()
	* @brief ���g�̃N���X���쐬�A�擾.
	* @return CXInput* �쐬���ꂽ���g��Ԃ�.
	*/
	static CXInput* GetInstance()
	{
		static std::unique_ptr<CXInput> pInstance = std::make_unique<CXInput>();
		return pInstance.get();
	}

private:
	std::vector<XINPUT_STATE> m_State;	//!< �ڑ������R���g���[���[�̏��.
	int m_ConnectedCount;				//!< �ڑ������R���g���[���[�̐�.

	std::vector<std::unordered_map<INT, enBUTTON_STATE>> m_ButtonStateList;	//!< ���͂��ꂽ�{�^���̏��.

	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CXInput( const CXInput & )				= delete;
	CXInput( CXInput && )					= delete;
	CXInput& operator = ( const CXInput & )	= delete;
	CXInput& operator = ( CXInput && )		= delete;
};


#endif	// #ifndef XINPUT_H.