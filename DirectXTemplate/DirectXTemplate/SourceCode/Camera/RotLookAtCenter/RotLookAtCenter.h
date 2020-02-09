#ifndef ROTATION_LOOK_AT_CENTER_CAMERA_H
#define ROTATION_LOOK_AT_CENTER_CAMERA_H

#include "..\Camera.h"

class CRotLookAtCenter : public CCamera
{
private: //------ �萔 -------.
	const float DEFAULT_LENGTH			= 20.0f;	// �J�����ʒu�ƒ����ʒu�̋���.
	const float DEFAULT_HORIZONTAL_MAX	= 360.0f;	// ����]�̍ő�T�C�Y.
	const float DEFAULT_HORIZONTAL_MIN	= 0.0f;		// ����]�̍ŏ��T�C�Y.
	const float DEFAULT_VERTICAL_MAX	= 90.0f;	// �c��]�̍ő�T�C�Y.
	const float DEFAULT_VERTICAL_MIN	= 0.0f;		// �c��]�̍ŏ��T�C�Y.

public:  //------ �֐� -------.
	CRotLookAtCenter();
	virtual ~CRotLookAtCenter();

	// �I�u�W�F�N�g���𒍎��ɉ�].
	void RotationLookAtObject( const D3DXVECTOR3& vLookPos );

	// �������̉�].
	void DegreeHorizontalMove( const float& movePower );
	// �c�����̉�].
	void DegreeVerticalMove( const float& movePower );
	// ���W�A���̎擾�֐�.
	float GetRadianX() const { return m_vDegree.x; }

	// �J�����ƒ����_�̒����ݒ�.
	void SetLength( const float& length );
	// �������̍ő�A�ŏ��̐ݒ�.
	void SetHorizontalDegree( const float& max, const float& min );
	// �c�����̍ő�A�ŏ��̐ݒ�.
	void SetVerticalDegree( const float& max, const float& min );

private: //------ �ϐ� -------.
	D3DXVECTOR2 m_vDegree;	// �J�����̊p�x.
	float m_Length;			// �J�����ƒ����_�̒���.
	float m_HorizontalMax;	// �������̍ő�T�C�Y.
	float m_HorizontalMin;	// �������̍ŏ��T�C�Y.
	float m_VerticalMax;	// �c�����̍ő�T�C�Y.
	float m_VerticalMin;	// �c�����̍ŏ��T�C�Y.
};

#endif	// #ifndef ROTATION_LOOK_AT_CENTER_CAMERA_H.