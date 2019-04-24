//=============================================================================
//
// �v���C���[�̎c�@���S�̏��� [playerCross.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PLAYERCROSS_H_
#define _PLAYERCROSS_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYERCROSS_LOGO_NAME		"data/TEXTURE/UI/playerCross.png"			// �v���C���[�̎c�@���S�̃e�N�X�`����

//=========================
// �X�R�A���S�N���X
//=========================
class CPlayerCross : public CLogo
{
public:
	CPlayerCross();															// �R���X�g���N�^
	~CPlayerCross();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CPlayerCross *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �u���b�N���S����������
	void Uninit(void);															// �u���b�N���S�I������
	void Update(void);															// �u���b�N���S�X�V����
	void Draw(void);															// �u���b�N���S�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif