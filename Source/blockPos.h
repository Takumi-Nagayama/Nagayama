//=============================================================================
//
// �u���b�N�̏o���ʒu�\������ [blockPos.h]
// Author : ���R���
//
//=============================================================================
#ifndef _BLOCKPOS_H_
#define _BLOCKPOS_H_

#include "main.h"
#include "scene.h"
#include "polygon.h"

//*********************************************************************
// �u���b�N�̏o���ʒu�\���N���X�̒�`
//*********************************************************************
class CBlockPos : public  CPolygon
{
public:

	CBlockPos();
	~CBlockPos();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CBlockPos *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, D3DXCOLOR col);
	static HRESULT Load(void);
	static void UnLoad(void);

	//�����o�ϐ�
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9			m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	float								m_Height;

	D3DXVECTOR3							m_pos;							//�ʒu
	D3DXVECTOR3							m_rot;							//����
	D3DXCOLOR							m_col;
	D3DXMATRIX							m_mtxWorld;						//���[���h�}�g���b�N�X
	float								m_fWidth, m_fDepth;				//���@���s��
};

#endif
