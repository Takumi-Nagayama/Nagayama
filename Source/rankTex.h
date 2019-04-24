//=============================================================================
//
// �����L���O�̃e�N�X�`���̏��� [rankTex.h]
// Author : ���R���
//
//=============================================================================
#ifndef _RANKTEX_H_
#define _RANKTEX_H_

#include "main.h"
#include "logo.h"

//=============================================================================
// �O���錾
//=============================================================================

//=====================
// ���U���g���S�N���X
//=====================
class CRankTex : public CLogo
{
public:
	CRankTex();																// �R���X�g���N�^
	~CRankTex();															// �f�X�g���N�^

	static HRESULT Load(void);												// �e�N�X�`���ǂݍ���
	static void Unload(void);												// �e�N�X�`�����

	static CRankTex *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �����L���O�̃e�N�X�`���𐶐�

	HRESULT Init(void);				// �����L���O�̃e�N�X�`������������
	void Uninit(void);														// �����L���O�̃e�N�X�`���I������
	void Update(void);														// �����L���O�̃e�N�X�`���X�V����
	void Draw(void);														// �����L���O�̃e�N�X�`���`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif