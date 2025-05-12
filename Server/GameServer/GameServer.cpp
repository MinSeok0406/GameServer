#include "pch.h"
#include <iostream>
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
//#include "ClientPacketHandler.h"
#include <tchar.h>
#include "Job.h"
#include "Protocol.pb.h"
#include "Room.h"

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(ServerServiceRef& service)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		// 네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해)
		service->GetIocpCore()->Dispatch(10);

		// 예약된 일감 처리
		ThreadManager::DistributeReservedJobs();

		// 글로벌 큐
		ThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	ServerPacketHandler::Init();

	ServerServiceRef service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		make_shared<IocpCore>(),
		[=]() { return make_shared<GameSession>(); }, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

	cout << "Listening..." << endl;

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([&service]()
			{
				DoWorkerJob(service);
			});
	}

	// Main Thread
	//DoWorkerJob(service);

	GRoom->DoAsync(&Room::UpdateTick);

	while (true)
	{
		//Protocol::S_CHAT pkt;
		//pkt.set_msg("HelloWorld");
		//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt); // -> 직렬화 단계

		//GSessionManager.Broadcast(sendBuffer);
		this_thread::sleep_for(1s);
		
	}

	// TemplateID -> 아이템의 데이터 시트 고유 아이디, 아이템
	// DbID -> Db에서 보이는 고유 아이디, 아이템, 몬스터X
	// GameID -> 몬스터같은 개념에게 상태 변화를 주고 싶을 때 찾는 아이디

	{
		Protocol::ObjectInfo* obj = new Protocol::ObjectInfo();
		//p->CopyFrom(); -> 객체가 가지고 있는 데이터를 전부 다 복사

		Protocol::S_ENTER_GAME pkt;
		pkt.set_allocated_player(obj); // -> 자동으로 메모리를 해제해준다
		pkt.release_player(); // -> 메모리를 해제 안시켜주고 남겨준다
	}

	// --------------------------------------------

	{
		Protocol::S_LOGIN pkt;

		// 플레이어 3명을 만들어서 x좌표를 10으로 만듦
		for (int32 i = 0; i < 3; i++)
		{
			Protocol::PosInfo* pos = new Protocol::PosInfo();
			pos->set_x(10);
			// auto *p
			Protocol::ObjectInfo* obj = pkt.add_players();
			obj->set_allocated_pos_info(pos);
		}

		for (int32 i = 0; i < pkt.players_size(); i++)
		{
			// i번째 플레이어의 정보를 가져와줌
			const Protocol::ObjectInfo& obj = pkt.players(i);
		}

		// 사용 가능
		for (auto& p : pkt.players())
		{

		}
	}
	

	GThreadManager->Join();
}