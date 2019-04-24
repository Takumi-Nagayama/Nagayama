//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.h]
// Author : ���R���
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define IRON_FILE_GAME	"data\\TEXT\\modelIron.txt"	// �ݒu�������f���������o���e�L�X�g
#define WOOD_FILE_GAME	"data\\TEXT\\modelWood.txt"	// �ݒu�������f���������o���e�L�X�g

//=============================================================================
// �O���錾
//=============================================================================
//class CRenderer;
class CInputKeyboard;
class CScore;
class CNumBlock;
class CLife;

//=============================================================================
// �N���X�̒�`
//=============================================================================
//=====================
// �}�l�[�W���N���X
//=====================
class CTutorial
{
public:
	CTutorial();	// �R���X�g���N�^
	~CTutorial();	// �f�X�g���N�^

	static CTutorial *Create();		// �`���[�g���A���𐶐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *GetScore(void);
	static CNumBlock *GetNumBlock(void);
	static CLife *GetLife(void);

	void LoadIronBlock(void);								// �S�u���b�N�̓ǂݍ���
	void LoadWoodBlock(void);								// �؃u���b�N�̓ǂݍ���
	
private:
	static CScore *m_pScore;
	static CNumBlock *m_pNumBlock;
	static CLife *m_pLife;
};

#endif