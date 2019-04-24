//=============================================================================
//
// �c�@���S�̏��� [lifeLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _LIFELOGO_H_
#define _LIFELOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LIFE_LOGO_NAME		"data/TEXTURE/UI/LIFE.png"			// �c�@���S�̃e�N�X�`����

//=========================
// �X�R�A���S�N���X
//=========================
class CLifeLogo : public CLogo
{
public:
	CLifeLogo();															// �R���X�g���N�^
	~CLifeLogo();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CLifeLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �u���b�N���S����������
	void Uninit(void);															// �u���b�N���S�I������
	void Update(void);															// �u���b�N���S�X�V����
	void Draw(void);															// �u���b�N���S�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif