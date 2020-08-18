#pragma once
#include "pch.h"

class Animation
{
private:
	vector<POINT> vecFrameList; // key frame ��ġ ����Ʈ
	vector<int> vecPlayList;	// �÷��� ����Ʈ

	int frameCount;		// ��ü ������ ��
	int frameWidth;		// ������ ����ũ��
	int frameHeight;	// ������ ����ũ��

	bool isLoop;		// �ݺ� �Ǵ��� ����
	int nowPlayIdx;		// ���� �÷��� ������ �ε���
	bool isPlaying;		// ���� �÷��� ������ ����

	float keyFrameUpdateTime;	// ������Ʈ ���� �ð�
	float accumulateTime;		// ���� ����
public:
	Animation();
	~Animation();

	HRESULT Init(int totalwidth, int totalHeight, int frameWidth, int frameHeight);
	void SetPlayFrame(bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int startFrame, int endFrame, bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int* arr, int arrLength, bool isReverse = FALSE, bool isLoop = FALSE);
	// FALSE�� false�� �ǹ̻� ������ ���� �������� ���
	// BOOL �̳� bool�� �ǹ̻� ������ ~
	void UpdateKeyFrame(float dt);

	void SetUpdateTime(float fps) { keyFrameUpdateTime = 1.0f / fps; }

	POINT GetFramePos() { return vecFrameList[vecPlayList[nowPlayIdx]]; }
	int GetNowPlayIdx() { return nowPlayIdx; }

	void Start();
	void Stop();
	void Pause();
	void Resume();
};

