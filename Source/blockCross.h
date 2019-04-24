//=============================================================================
//
// �u���b�N�̌����S�̏��� [blocCross.h]
// Author : ���R���
//
//=============================================================================
#ifndef _BLOCKCROSS_H_
#define _BLOCKCROSS_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCKCROSS_LOGO_NAME		"data/TEXTURE/UI/blockCross.png"			// �u���b�N�̌����S�̃e�N�X�`����

//=========================
// �X�R�A���S�N���X
//=========================
class CBlockCross : public CLogo
{
public:
	CBlockCross();															// �R���X�g���N�^
	~CBlockCross();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CBlockCross *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �u���b�N���S����������
	void Uninit(void);															// �u���b�N���S�I������
	void Update(void);															// �u���b�N���S�X�V����
	void Draw(void);															// �u���b�N���S�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif