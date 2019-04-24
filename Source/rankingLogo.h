//=============================================================================
//
// �����L���O���S�̏��� [rankingLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _RANKINGLOGO_H_
#define _RANKINGLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_LOGO_NAME		"data/TEXTURE/RANKING/ranking.png"			// �`���[�g���A�����S�̃e�N�X�`����

//=========================
// �`���[�g���A�����S�N���X
//=========================
class CRankingLogo : public CLogo
{
public:
	CRankingLogo();															// �R���X�g���N�^
	~CRankingLogo();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CRankingLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �`���[�g���A�����S����������
	void Uninit(void);															// �`���[�g���A�����S�I������
	void Update(void);															// �`���[�g���A�����S�X�V����
	void Draw(void);															// �`���[�g���A�����S�`x�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif