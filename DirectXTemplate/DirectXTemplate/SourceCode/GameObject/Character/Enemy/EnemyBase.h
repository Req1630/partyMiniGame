#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "..\Character.h"

class CEnemyBase : public CCharacter
{
public:
	CEnemyBase();
	virtual ~CEnemyBase();

	// �o���ł��邩�ǂ���.
	bool IsAppearance( const int& gameCount );
	// �o���J�E���g�̐ݒ�.
	void SetAppearanceCount( const int& appearanceCount ){ m_AppearanceCount = appearanceCount; }

protected:
	int m_AppearanceCount;	// �o���J�E���g.
	int m_AttackCount;		// �U���J�E���g.
	bool m_isAssailable;	// �U���ł��邩.
};

#endif	// #ifndef ENEMY_BASE_H.