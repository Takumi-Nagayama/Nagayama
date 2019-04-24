//=============================================================================
//
// �Q�[���N���A���S�̏��� [gameclearLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _GAMECLEARLOGO_H_
#define _GAMECLEARLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMECLEAR_LOGO_NAME		"data/TEXTURE/RESULT/gameclear.png"			// �Q�[���N���A���S�̃e�N�X�`����

//=========================
// �Q�[���N���A���S�N���X
//=========================
class CGameClearLogo : public CLogo
{
public:
	CGameClearLogo();															// �R���X�g���N�^
	~CGameClearLogo();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CGameClearLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �Q�[���N���A���S����������
	void Uninit(void);															// �Q�[���N���A���S�I������
	void Update(void);															// �Q�[���N���A���S�X�V����
	void Draw(void);															// �Q�[���N���A���S�`x�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif