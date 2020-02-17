#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "..\Character.h"

class CEnemyBase : public CCharacter
{
public:
	CEnemyBase();
	virtual ~CEnemyBase();

	// 出現できるかどうか.
	bool IsAppearance( const int& gameCount );
	// 出現カウントの設定.
	void SetAppearanceCount( const int& appearanceCount ){ m_AppearanceCount = appearanceCount; }

protected:
	int m_AppearanceCount;	// 出現カウント.
	int m_AttackCount;		// 攻撃カウント.
	bool m_isAssailable;	// 攻撃できるか.
};

#endif	// #ifndef ENEMY_BASE_H.