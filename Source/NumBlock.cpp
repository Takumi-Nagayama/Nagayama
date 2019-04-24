//=============================================================================
//
// �u���b�N�̐����� [NumBlock.cpp]
// Author : ���R���
//
//=============================================================================
#include "NumBlock.h"
#include "manager.h"
#include "number.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
//int CNumBlock::m_nScore = 0;
//CNumber *CNumBlock::m_apNumber[MAX_NUMBLOCK] = {};

//=============================================================================
// �X�R�A�̐�������
//=============================================================================
CNumBlock *CNumBlock::Create(D3DXVECTOR3 pos, float fSize)
{
	CNumBlock *pNumber = NULL;

	if (pNumber == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pNumber = new CNumBlock;

		if (pNumber != NULL)
		{
			pNumber->m_pos = pos;
			pNumber->m_fSize = fSize;
			pNumber->Init();
		}
	}

	return pNumber;
}

//=============================================================================
// �X�R�A�N���X�̃R���X�g���N�^
//=============================================================================
CNumBlock::CNumBlock(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	for (int nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		m_apNumber[nCntScore] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumBlock = 10;
}

//=============================================================================
// �X�R�A�N���X�̃f�X�g���N�^
//=============================================================================
CNumBlock::~CNumBlock()
{
}

//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CNumBlock::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SCORE);

	for (int nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		m_apNumber[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x - nCntScore * 60, m_pos.y, 0.0f), m_fSize);
	}

	m_nNumBlock = 0;

	AddBlock(10);

	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CNumBlock::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMBLOCK; nCntBg++)
	{
		if (m_apNumber[nCntBg] != NULL)
		{
			m_apNumber[nCntBg]->Uninit();

			// ���������J��
			delete m_apNumber[nCntBg];
			m_apNumber[nCntBg] = NULL;
		}
	}

	// �X�R�A���̂̉��
	Release();
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CNumBlock::Update(void)
{

}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CNumBlock::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMBLOCK; nCntBg++)
	{
		if (m_apNumber[nCntBg] != NULL)
		{
			m_apNumber[nCntBg]->Draw();
		}
	}
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CNumBlock::AddBlock(int nValue)
{
	int nAnswer = 1;
	int nCntScore;
	int nScore;

	m_nNumBlock += nValue;

	for (nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		// �X�R�A��\�����邽�߂̌v�Z
		nScore = m_nNumBlock % (nAnswer * 10) / nAnswer;

		m_apNumber[nCntScore]->SetNumber(nScore);

		nAnswer *= 10;
	}

}

//=============================================================================
// �X�R�A�̐ݒ菈��
//=============================================================================
void CNumBlock::SetBlock(int nBlock)
{
	m_nNumBlock = nBlock;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int CNumBlock::GetBlock(void)
{
	return m_nNumBlock;
}

//=============================================================================
// �X�R�A�̐F�̐ݒ菈��
//=============================================================================
void CNumBlock::SetColor(D3DXCOLOR color)
{
	for (int nCntScore = 0; nCntScore < MAX_NUMBLOCK; nCntScore++)
	{
		m_apNumber[nCntScore]->SetColor(color);
	}
}