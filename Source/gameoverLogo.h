//=============================================================================
//
// �Q�[���I�[�o�[���S�̏��� [gameoverLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _GAMEOVERLOGO_H_
#define _GAMEOVERLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMEOVER_LOGO_NAME		"data/TEXTURE/RESULT/gameover.png"			// �Q�[���I�[�o�[���S�̃e�N�X�`����

//=========================
// �Q�[���I�[�o�[���S�N���X
//=========================
class CGameOverLogo : public CLogo
{
public:
	CGameOverLogo();															// �R���X�g���N�^
	~CGameOverLogo();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CGameOverLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �Q�[���I�[�o�[���S����������
	void Uninit(void);															// �Q�[���I�[�o�[���S�I������
	void Update(void);															// �Q�[���I�[�o�[���S�X�V����
	void Draw(void);															// �Q�[���I�[�o�[���S�`x�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif