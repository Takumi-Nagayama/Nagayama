//=============================================================================
//
// �`���[�g���A���Ŏg�����S�̏��� [tutorialLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _TUTORIALLOGO_H_
#define _TUTORIALLOGO_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\move.png"		// �ړ����@�̃e�N�X�`����
#define JUMP_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\jump.png"		// �W�����v���@�̃e�N�X�`����
#define SET_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\set.png"		// �ݒu���@�̃e�N�X�`����
#define DESTROY_TEXTURE_NAME		"data\\TEXTURE\\TUTORIAL\\destroy.png"	// �j����@�̃e�N�X�`����
#define END_TEXTURE_NAME			"data\\TEXTURE\\TUTORIAL\\end.png"		// �I���̃e�N�X�`����
#define NUM_VTX						(4)										// ���_�̐�

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CTutorialLogo : public CPolygon
{
public:
	typedef enum
	{// �v���C���[�̏��
		TYPE_MOVE = 0,	// �ړ����@�̃e�N�X�`��
		TYPE_JUMP,		// �W�����v���@�̃e�N�X�`��
		TYPE_SET,		// �ݒu���@�̃e�N�X�`��
		TYPE_DESTROY,	// �j����@�̃e�N�X�`��
		TYPE_END,		// �I���̃e�N�X�`��
		TYPE_MAX		// �e�N�X�`���̎�ނ̑���
	} TEX_TYPE;

	CTutorialLogo();											// �R���X�g���N�^
	~CTutorialLogo();										// �f�X�g���N�^

	HRESULT Init(void);							// �`���[�g���A���Ŏg�����S����������
	void Uninit(void);							// �`���[�g���A���Ŏg�����S�I������
	void Update(void);							// �`���[�g���A���Ŏg�����S�X�V����
	void Draw(void);							// �`���[�g���A���Ŏg�����S�`�揈��

	static CTutorialLogo *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, TEX_TYPE type);			// �I�u�W�F�N�g�̐���
	static HRESULT Load(void);	// �e�N�X�`���ǂݍ���
	static void Unload(void);	// �e�N�X�`�����

private:
	static LPDIRECT3DTEXTURE9		m_apTexture[TYPE_MAX];					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;					// ���[���h�}�g���b�N�X
	TEX_TYPE				m_Type;
};

#endif