#ifndef ENEMY_TYPE_H
#define ENEMY_TYPE_H

// �G�̎��.
enum class enENEMY_TYPE
{
	None,		// �����Ȃ�.
	
	RUN = None,	// ����.
	SHOOT,		// ����.

	Max,		// �ő�.
};

// �G���ǂ̕����Ɉړ����邩.
enum class enENEMY_DIRECTION
{
	None,		// �����Ȃ�.

	UP = None,	// �����.
	DOWN,		// ������.
	RIGHT,		// �E����.
	LEFT,		// ������.

	Max,		// �ő�.
};

#endif	// #ifndef ENEMY_TYPE_H.