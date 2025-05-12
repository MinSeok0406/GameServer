// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "S1.h"

class FSocket;

struct S1_API FPacketHeader
{
	FPacketHeader() : PacketSize(0), PacketID(0)
	{

	}

	FPacketHeader(uint16 PacketSize, uint16 PacketID) : PacketSize(PacketSize), PacketID(PacketID)
	{

	}

	friend FArchive& operator<<(FArchive& Ar, FPacketHeader& Header)
	{
		Ar << Header.PacketSize;
		Ar << Header.PacketID;
		return Ar;
	}

	uint16 PacketSize;
	uint16 PacketID;
};

// S1_API -> Ŭ���� �� �տ� �� �ٿ��� �ϴ°�
// �𸮾� �������� C++ Ŭ������ ����� �� public FRunnable�� �� �ٿ�����
class S1_API RecvWorker : public FRunnable
{
public:
	RecvWorker(FSocket* Socket, TSharedPtr<class PacketSession> Session);
	~RecvWorker();

	// �ݵ�� �����ؾ� �ϴ� 3���� �����Լ�
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;

	void Destroy();

private:
	// ���� ���ϴ� �������� ũ�� ��ŭ�� ���� ��Ŷ�� �����÷��� �Լ�
	bool ReceivePacket(TArray<uint8>& OutPacket);

	// ���� ���ϴ� ��Ŷ�� ũ�Ⱑ �� ������ ��ٸ��ڴ� ��� �Լ�
	bool ReceiveDesiredBytes(uint8* Results, int32 Size);

protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket;
	TWeakPtr<class PacketSession> SessionRef;
};

// RecvWorker�� ��Ī������ �̷�� Ŭ����
class S1_API SendWorker : public FRunnable
{
public:
	SendWorker(FSocket* Socket, TSharedPtr<class PacketSession> Session);
	~SendWorker();

	// �ݵ�� �����ؾ� �ϴ� 3���� �����Լ�
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;

	bool SendPacket(SendBufferRef SendBuffer);

	void Destroy();

private:
	bool SendDesiredBytes(uint8* Buffer, int32 Size);

protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket;
	TWeakPtr<class PacketSession> SessionRef;
};