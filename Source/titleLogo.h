//=============================================================================
//
// �^�C�g�����S�̏��� [titleLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_LOGO_NAME			"data/TEXTURE/TITLE/title001.png"		// �^�C�g�����S�̃e�N�X�`����

//=====================
// �^�C�g�����S�N���X
//=====================
class CTitleLogo : public CLogo
{
public:
	CTitleLogo();																// �R���X�g���N�^
	~CTitleLogo();																// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CTitleLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init();																// �^�C�g�����S����������
	void Uninit(void);															// �^�C�g�����S�I������
	void Update(void);															// �^�C�g�����S�X�V����
	void Draw(void);															// �^�C�g�����S�`x�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif