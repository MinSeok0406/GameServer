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

// S1_API -> 클래스 명 앞에 꼭 붙여야 하는것
// 언리얼 엔진에서 C++ 클래스를 사용할 때 public FRunnable을 꼭 붙여야함
class S1_API RecvWorker : public FRunnable
{
public:
	RecvWorker(FSocket* Socket, TSharedPtr<class PacketSession> Session);
	~RecvWorker();

	// 반드시 선언해야 하는 3가지 가상함수
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;

	void Destroy();

private:
	// 내가 원하는 데이터의 크기 만큼을 담은 패킷을 가져올려는 함수
	bool ReceivePacket(TArray<uint8>& OutPacket);

	// 내가 원하는 패킷의 크기가 올 때까지 기다리겠다 라는 함수
	bool ReceiveDesiredBytes(uint8* Results, int32 Size);

protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket;
	TWeakPtr<class PacketSession> SessionRef;
};

// RecvWorker와 대칭적으로 이루는 클래스
class S1_API SendWorker : public FRunnable
{
public:
	SendWorker(FSocket* Socket, TSharedPtr<class PacketSession> Session);
	~SendWorker();

	// 반드시 선언해야 하는 3가지 가상함수
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