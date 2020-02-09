#ifndef CAMERA_H
#define CAMERA_H

#include "..\Global.h"

//===========================.
//	�J�����N���X.
//===========================.
class CCamera
{
private: //------- �萔 -------.
	const float FLOAT_WND_W = static_cast<float>(WND_W);	// (float)��ʕ�.
	const float FLOAT_WND_H = static_cast<float>(WND_H);	// (float)��ʕ�.
	const D3DXVECTOR3 VIEW_UP_VECTOR	= { 0.0f, 1.0f, 0.0f };				// ������x�N�g��.
	const float INITIAL_VIEWING_ANGLE	= static_cast<float>(D3DX_PI/4.0);	// ��������p.
	const float SCREEN_ASPECT_RATIO		= FLOAT_WND_W/FLOAT_WND_H;			// ��ʃA�X�y�N�g��.
	const float INITIAL_MAX_CLIPPING_DISTANCE = 100.0f;						// �����ő�`�拗��.
	const float INITIAL_MIN_CLIPPING_DISTANCE = 0.1f;						// �����ŏ��`�拗��.

public: //------- �֐� -------.
	CCamera();
	virtual ~CCamera();

	// �J�����̍X�V����.
	void Update();
	// �r���[�s��A�v���W�F�N�V�����s��̏�����.
	void InitViewProj();

	// �r���[�s��擾�֐�.
	D3DXMATRIX GetViewMatrix() const { return m_ViewMatrix; }
	// �v���W�F�N�V�����s��擾�֐�.
	D3DXMATRIX GetProjMatrix() const { return m_ProjMatrix; }
	// �J�������W�擾�֐�.
	D3DXVECTOR3 GetPosition()		const { return m_vPosition; }
	// �J�����������W�擾�֐�.
	D3DXVECTOR3 GetLookPosition()	const { return m_vLookPosition; }
	// �J�������W�ݒ�֐�.
	void SetPosition( const D3DXVECTOR3& vPos )			{ m_vPosition = vPos; }
	// �J�����������W�ݒ�֐�.
	void SetLookPosition( const D3DXVECTOR3& vLookPos )	{ m_vLookPosition = vLookPos; }

	// �p����̃J�������̐ݒ�֐�.
	void SetCamera( std::shared_ptr<CCamera> camera );

protected: //------- �ϐ� -------.
	D3DXVECTOR3	m_vPosition;		// �J�����ʒu.
	D3DXVECTOR3	m_vLookPosition;	// �J���������ʒu.

private: //------- �ϐ� -------.
	D3DXMATRIX m_ViewMatrix;		// �r���[�s��.
	D3DXMATRIX m_ProjMatrix;		// �v���W�F�N�V�����s��.

	float m_ViewingAngle;			// ����p.
	float m_MaxClippingDistance;	// �ő�N���b�s���O����.
	float m_MinClippingDistance;	// �ŏ��N���b�s���O����.
};

#endif	// #ifndef CAMERA_H.