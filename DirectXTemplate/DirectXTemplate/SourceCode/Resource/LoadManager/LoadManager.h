#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include "..\..\Global.h"
#include <thread>

/*********************************
*	�e���\�[�X�ނ̓ǂݍ��݂��܂Ƃ߂�N���X.
*		Load�摜�Ȃǂ̕\���������ɓ���Ă���������.
*/
class CLoadManager
{
public:
	CLoadManager();
	~CLoadManager();

	// �ǂݍ���.
	void Load( HWND hWnd, 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11, 
		LPDIRECT3DDEVICE9 pDevice9  );
	// �X���b�h�̉��.
	bool ThreadRelease();

private:
	std::thread m_Thread;		// �X���b�h.

	bool m_isLoadEnd;			// ���[�h���I��������.
	bool m_isThreadJoined;		// �X���b�h��������ꂽ��.
};

#endif	// #ifndef LOAD_MANAGER_H.