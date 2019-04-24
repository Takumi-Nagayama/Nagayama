//=============================================================================
//
// �u���b�N�̐����� [NumBlock.h]
// Author : ���R���
//
//=============================================================================
#ifndef _NUMBLOCK_H_
#define _NUMBLOCK_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUMBLOCK	(2)	// �e�N�X�`���̐�
#define MAX_SET_BLOCK	(10)									// �u���b�N�ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CNumber;

//========================================
// �N���X�̒�`
//========================================
//=====================
// �u���b�N�̐��N���X
//=====================
class CNumBlock : public CScene
{
public:
	CNumBlock(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);	// �R���X�g���N�^
	~CNumBlock();													// �f�X�g���N�^

	static CNumBlock *Create(D3DXVECTOR3 pos, float fSize);

	HRESULT Init(void);							// �u���b�N�̐��̏���������
	void Uninit(void);							// �u���b�N�̐��̏I������
	void Update(void);							// �u���b�N�̐��̍X�V����
	void Draw(void);							// �u���b�N�̐��̕`�揈��

	void SetBlock(int nBlock);					// �u���b�N�̐��̐ݒ�
	int GetBlock(void);							// �u���b�N�̐��̎擾
	void AddBlock(int nValue);					// �u���b�N�̐����Z
	void SetColor(D3DXCOLOR color);				// �F�̐ݒ�

private:
	CNumber *m_apNumber[MAX_NUMBLOCK];
	D3DXVECTOR3 m_pos;
	int m_nNumBlock;
	float m_fSize;
};

#endif