//=============================================================================
//
// �u���b�N���S�̏��� [blocLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _BLOCKLOGO_H_
#define _BLOCKLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK_LOGO_NAME		"data/TEXTURE/UI/BLOCK.png"			// �u���b�N���S�̃e�N�X�`����

//=========================
// �X�R�A���S�N���X
//=========================
class CBlockLogo : public CLogo
{
public:
	CBlockLogo();															// �R���X�g���N�^
	~CBlockLogo();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CBlockLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �u���b�N���S����������
	void Uninit(void);															// �u���b�N���S�I������
	void Update(void);															// �u���b�N���S�X�V����
	void Draw(void);															// �u���b�N���S�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif