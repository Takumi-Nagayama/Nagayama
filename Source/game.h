//=============================================================================
//
// �Q�[������ [game.h]
// Author : ���R���
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CInputKeyboard;
class CDebugProc;
class CScene3D;
class CPlayer;
class CScore;
class CNumBlock;
class CLife;

//=============================================================================
// �N���X�̒�`
//=============================================================================
//=====================
// �Q�[���N���X
//=====================
class CGame
{
public:
	CGame();	// �R���X�g���N�^
	~CGame();	// �f�X�g���N�^

	static CGame *Create();		// �Q�[���𐶐�
	HRESULT Init(void);			// �Q�[���̏�����
	void Uninit(void);			// �Q�[���̏I������
	void Update(void);			// �Q�[���̍X�V����
	void Draw(void);			// �Q�[���̕`��
	static CScore *GetScore(void);
	static CNumBlock *GetNumBlock(void);
	static CLife *GetLife(void);

	void LoadCoin(void);				// �R�C���̓ǂݍ���
	void LoadTexture(void);				// �e�N�X�`���̓ǂݍ���
	void UnLoadTexture(void);			// �e�N�X�`���̊J��
	void LoadModel(void);				// ���f���̓ǂݍ���
	void UnLoadModel(void);				// ���f���̊J��
	void LoadMat(void);					// �}�e���A���̓ǂݍ���
	void UnLoadMat(void);				// �}�e���A���̊J��
	void BlockCreate(void);				// �u���b�N�̐���
	void FieldCreate(void);				// �t�B�[���h�̐���

private:
	static CScore *m_pScore;
	static CNumBlock *m_pNumBlock;
	static CLife *m_pLife;
};

#endif