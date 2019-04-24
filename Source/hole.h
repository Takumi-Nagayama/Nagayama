//=============================================================================
//
// ���̏��� [hole.h]
// Author : ���R���
//
//=============================================================================
#ifndef _HOLE_H_
#define _HOLE_H_

#include "main.h"
#include "polygon.h"
#include "scene3D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_DEBRIS		"data/TEXTURE/woodDebris.png"	// �؂̔j�Ђ̃e�N�X�`��
#define EFFECT_STAR_NAME	"data/TEXTURE/effect001.jpg"	// ���G�t�F�N�g�̃e�N�X�`����

//========================================
// �N���X�̒�`
//========================================
//=====================
// ���N���X
//=====================
class CHole : public CPolygon
{
public:
	CHole();	// �R���X�g���N�^
	~CHole();	// �f�X�g���N�^

	HRESULT Init(void);	// ������������
	void Uninit(void);	// ���I������
	void Update(void);	// ���X�V����
	void Draw(void);	// ���`�揈��

	static CHole *Create(D3DXVECTOR3 pos, float fDepth, float fWifth);	// �I�u�W�F�N�g�̐���
	static HRESULT Load(void);	// �e�N�X�`���ǂݍ���
	static void Unload(void);	// �e�N�X�`�����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nLife;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
};

#endif