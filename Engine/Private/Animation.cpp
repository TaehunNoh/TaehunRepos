#include "..\Public\Animation.h"

#include "Channel.h"
#include "Model.h"
#include "Bone.h"

CAnimation::CAnimation()
{
}

CAnimation::CAnimation(const CAnimation& rhs)
	: m_dDuration(rhs.m_dDuration)
	, m_dTickPerSecond(rhs.m_dTickPerSecond)
	, m_dTimeAcc(rhs.m_dTimeAcc)
	, m_isFinish(rhs.m_isFinish)
	, m_iNumChannels(rhs.m_iNumChannels)
	, m_Channels(rhs.m_Channels)
	, m_iCurrentKeyFrames(rhs.m_iCurrentKeyFrames)
{
	for (auto& pChannel : m_Channels)
		Safe_AddRef(pChannel);

	strcpy_s(m_szName, rhs.m_szName);
}

HRESULT CAnimation::Initialize(ifstream* pFin, CModel* pModel)
{
	_uint iSize = { 0 };
	pFin->read(reinterpret_cast<char*>(&iSize), sizeof(_uint));
	pFin->read(m_szName, iSize);
	strcat_s(m_szName, "\0");
	pFin->read(reinterpret_cast<char*>(&m_dDuration), sizeof(_double));
	pFin->read(reinterpret_cast<char*>(&m_dTickPerSecond), sizeof(_double));
	pFin->read(reinterpret_cast<char*>(&m_iNumChannels), sizeof(_uint));

	m_iCurrentKeyFrames.resize(m_iNumChannels);
	
	for (_uint i = 0; i < m_iNumChannels; i++)
	{
		iSize = { 0 };
		pFin->read(reinterpret_cast<char*>(&iSize), sizeof(_uint));
		char szName[MAX_PATH] = { "" };
		pFin->read(szName, iSize);
		strcat_s(szName, "\0");

		//이 애니메이션에서 움직이는 뼈와 이름이 같은 모델의 뼈를 찾아 pBone에 저장
		CBone * pBone = pModel->Get_Bone(szName);

		CChannel* pChannel = CChannel::Create(pFin, szName, pModel->Get_BoneIndex(pBone->Get_Name()));
		if (nullptr == pChannel)
			return E_FAIL;

		m_Channels.emplace_back(pChannel);
	}

	return S_OK;
}

void CAnimation::Invalidate_TransformationMatrices(CModel* pModel, _double dTimeDelta)
{
	m_isFinish = false;

	/* 현재 재생되는 애니메이션 */
	m_dTimeAcc += m_dTickPerSecond * dTimeDelta;

	if (m_dDuration <= m_dTimeAcc)
	{
		// 전체 재생시간보다 누적시간이 커졌다 == 애니메이션이 끝났다
		m_isFinish = true;
		m_dTimeAcc = 0.0;
	}

	_uint	iIndex = { 0 };
	for (auto& pChannel : m_Channels)
	{
		//이 애니메이션에서 움직이는 뼈들의 상태를 시간에 맞게 갱신한다.
		pChannel->Invalidate(pModel, m_iCurrentKeyFrames[iIndex++], m_dTimeAcc);
	}
}

CAnimation* CAnimation::Create(ifstream* pFin, class CModel* pModel)
{
	CAnimation* pInstance = new CAnimation();

	if (FAILED(pInstance->Initialize(pFin, pModel)))
	{
		MSG_BOX("Failed to Created : CAnimation");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}

void CAnimation::Free()
{
	for (auto& pChannel : m_Channels)
		Safe_Release(pChannel);

	m_Channels.clear();
}
