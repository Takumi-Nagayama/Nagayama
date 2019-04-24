//=============================================================================
//
// �w�i���S�̏��� [logoBack.h]
// Author : ���R���
//
//=============================================================================
#ifndef _LOGOBACK_H_
#define _LOGOBACK_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOGOBACK_NAME		"data/TEXTURE/logoBack001.png"			// �w�i���S�̃e�N�X�`����

//=========================
// �`���[�g���A�����S�N���X
//=========================
class CLogoBack : public CLogo
{
public:
	CLogoBack();															// �R���X�g���N�^
	~CLogoBack();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CLogoBack *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �`���[�g���A�����S����������
	void Uninit(void);															// �`���[�g���A�����S�I������
	void Update(void);															// �`���[�g���A�����S�X�V����
	void Draw(void);															// �`���[�g���A�����S�`x�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif