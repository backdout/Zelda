#include "Animation.h"

Animation::Animation()
	:frameCount(0)
	, frameWidth(0)
	, frameHeight(0)
	, isLoop(false)
	, nowPlayIdx(0)
	, isPlaying(false)	// {}�ȿ� ���ֳ� �ۿ� ���ֳ� ��ǻ� ���� ���� ����
	, keyFrameUpdateTime(0)
	, accumulateTime(0.0f)
{
}

Animation::~Animation()
{
}

HRESULT Animation::Init(int totalwidth, int totalHeight, int frameWidth, int frameHeight)
{
	// ���� ������ ��
	int frameWidthCount = totalwidth / frameWidth;
	// ���� ������ ��
	int frameHeightCount = totalHeight / frameHeight;
	// ��ü ������ ��
	frameCount = frameWidthCount * frameHeightCount;

	// ������ ��ġ ����Ʈ ����
	vecFrameList.clear();
	vecFrameList.resize(frameCount);

	for (int i = 0; i < frameHeightCount; i++)
	{
		for (int j = 0; j < frameWidthCount; j++)
		{

			vecFrameList[i * frameWidthCount + j].x = j * frameWidth;
			vecFrameList[i * frameWidthCount + j].y = i * frameHeight;

			/*
			POINT framePos;

			framePos.x = j * frameWidth;
			framePos.y = i * frameHeight;

			vecFrameList[i * frameWidthCount + j] = framePos;

			���Ʒ� �Ѵ� ����

			vecFrameList[i * frameWidthCount + j].x = j * frameWidth;
			vecFrameList[i * frameWidthCount + j].y = i * frameHeight;

			vecFrameList[i * frameWidthCount + j] = framePos;
			*/
		}
	}
	// �⺻ �÷��� ����Ʈ ����

	return E_NOTIMPL;
}

void Animation::SetPlayFrame(bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		// ������
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);	// pushback���� �ε��� ��ȣ�� ���� ����. �÷��̸���Ʈ 0������ 11������ ����Ǵ°�
		}
		// ������
		for (int i = frameCount - 1; i > 0; i--)
		{
			vecPlayList.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);
		}
	}
}

void Animation::SetPlayFrame(int startFrame, int endFrame, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	// startFrame �� 0���� ũ�ų� ���� endFrame�� ������ Frame���� �۰ų� ���� ��
	// startFrame = 8 endFrame = 3 �� ���
	if (startFrame == endFrame)	// �����Ǿ��ִ� �ִϸ��̼�
	{
		Stop();					// ��ž�Լ� ȣ���ѵڿ�
		return;					// ���� ��Ų��.
	}

	if (startFrame > endFrame)	// ù������ ���������� Ŭ��
	{
		if (isReverse)
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}
			for (int i = 0; i <= endFrame; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = endFrame; i >= 0; i--)
			{
				vecPlayList.push_back(i);
			}
			for (int i = frameCount - 1; i >= startFrame; i--)
			{
				vecPlayList.push_back(i);
			}
		}
		else
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}
			for (int i = 0; i <= endFrame; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
	else
	{
		if (isReverse)
		{
			// ������
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);	// pushback���� �ε��� ��ȣ�� ���� ����. �÷��̸���Ʈ 0������ 11������ ����Ǵ°�
			}
			// ������
			for (int i = endFrame - 1; i > startFrame; i--)
			{
				vecPlayList.push_back(i);
			}
		}
		else
		{									// + 1�� ����� endFrame���� ������.
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
}

void Animation::SetPlayFrame(int * arr, int arrLength, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}
		for (int i = arrLength - 1; i >= 0; i--)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
}

void Animation::UpdateKeyFrame(float dt)
{
	if (isPlaying)
	{
		accumulateTime += dt;

		if (accumulateTime >= keyFrameUpdateTime)
		{
			nowPlayIdx++;

			if (nowPlayIdx >= vecPlayList.size())	// �����س��� �ִϸ��̼��� �� ��������
			{
				//������ ��
				if (isLoop)
				{
					nowPlayIdx = 0;
				}
				else
				{
					nowPlayIdx--;
					isPlaying = false;
				}
			}
			accumulateTime -= keyFrameUpdateTime;
			//accumulateTime -= 0.0f;	�ڼ��� ó���� ��������
		}
	}

}

void Animation::Start()
{
	nowPlayIdx = 0;
	isPlaying = true;
}

void Animation::Stop()
{
	nowPlayIdx = 0;
	isPlaying = false;
}

void Animation::Pause()
{
	isPlaying = false;
}

void Animation::Resume()
{
	isPlaying = true;
}