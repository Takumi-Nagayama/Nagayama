//=============================================================================
//
// �v���X�G�j�[�{�^���̏��� [pressAnyButton.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PRESSANYBUTTON_H_
#define _PRESSANYBUTTON_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BUTTON_LOGO_NAME		"data/TEXTURE/UI/PressAnyButton.png"			// �v���X�G�j�[�{�^�����S�̃e�N�X�`����
#define BUTTON_LOGO_NAME01		"data/TEXTURE/UI/enter.png"					// �G���^�[�{�^�����S�̃e�N�X�`����

//=========================
// �v���X�G�j�[�{�^�����S�N���X
//=========================
class CPressAnyButton : public CLogo
{
public:
	typedef enum
	{// �v���C���[�̏��
		TYPE_ANY = 0,	// �ʏ���
		TYPE_ENTER,		// �ړ����
		TYPE_MAX		// ���S�̎�ނ̑���
	} LOGOTYPE;

	CPressAnyButton();															// �R���X�g���N�^
	~CPressAnyButton();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CPressAnyButton *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LOGOTYPE type);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �v���X�G�j�[�{�^�����S����������
	void Uninit(void);															// �v���X�G�j�[�{�^�����S�I������
	void Update(void);															// �v���X�G�j�[�{�^�����S�X�V����
	void Draw(void);															// �v���X�G�j�[�{�^�����S�`x�揈��

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];
	LOGOTYPE m_type;
	int	m_nCntEnter;
	float m_fEnterTimer;
	bool m_bPress;
};

#endif