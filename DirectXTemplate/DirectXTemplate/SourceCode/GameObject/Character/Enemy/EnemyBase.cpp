#include "EnemyBase.h"

CEnemyBase::CEnemyBase()
	: m_AttackCount		( 0 )
	, m_isAssailable	( false )
{
}

CEnemyBase::~CEnemyBase()
{
}

//--------------------------.
// �U���ł��邩�ǂ���.
//--------------------------.
bool CEnemyBase::IsAssailable( const int& gameCount )
{
	// �Q�[���J�E���g���A�^�b�N�J�E���g��菭�Ȃ���ΏI��.
	if( m_AttackCount >= gameCount ) return false;

	// ������� true �����ďI��.
	return m_isAssailable = true;
}