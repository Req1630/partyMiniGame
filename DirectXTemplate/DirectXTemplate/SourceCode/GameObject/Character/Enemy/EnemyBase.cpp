#include "EnemyBase.h"

CEnemyBase::CEnemyBase()
	: m_AppearanceCount	( 0 )
	, m_AttackCount		( 0 )
	, m_isAssailable	( false )
{
}

CEnemyBase::~CEnemyBase()
{
}

//--------------------------.
// �o���ł��邩�ǂ���.
//--------------------------.
bool CEnemyBase::IsAppearance( const int& gameCount )
{
	// �Q�[���J�E���g���o���J�E���g��菭�Ȃ���ΏI��.
	if( m_AppearanceCount >= gameCount ) return false;

	// ������� true �����ďI��.
	return m_isAssailable = true;
}