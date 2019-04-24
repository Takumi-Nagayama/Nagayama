//=============================================================================
//
// �i���o�[���� [number.h]
// Author : ���R���
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	SCORE_NAME	"data/TEXTURE/number_02.png"		// �X�R�A�̃e�N�X�`����

//========================================
// �N���X�̒�`
//========================================
//=====================
// �i���o�[�N���X
//=====================
class CNumber
{
public:
	CNumber();												// �R���X�g���N�^
	~CNumber();												// �f�X�g���N�^

	static HRESULT Load(void);								// �e�N�X�`���ǂݍ���
	static void UnLoad(void);								// �e�N�X�`�����

	static CNumber *Create(D3DXVECTOR3 pos, float fSize);	// �i���o�[�̐���

	HRESULT Init(D3DXVECTOR3 pos, float fSize);				// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V
	void Draw(void);										// �`��
	void SetNumber(int nNumber);							// �e�N�X�`���ݒ�
	void SetColor(D3DXCOLOR color);							// �F�̐ݒ�

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;					// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;
};

#endif