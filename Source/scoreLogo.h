//=============================================================================
//
// �X�R�A���S�̏��� [scoreLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SCORELOGO_H_
#define _SCORELOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_LOGO_NAME		"data/TEXTURE/UI/SCORE.png"			// �`���[�g���A�����S�̃e�N�X�`����

//=========================
// �X�R�A���S�N���X
//=========================
class CScoreLogo : public CLogo
{
public:
	CScoreLogo();															// �R���X�g���N�^
	~CScoreLogo();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CScoreLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �X�R�A���S����������
	void Uninit(void);															// �X�R�A���S�I������
	void Update(void);															// �X�R�A���S�X�V����
	void Draw(void);															// �X�R�A���S�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif