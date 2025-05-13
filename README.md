# 🎮 [게임 서버 + 언리얼 엔진 연동]

## 📌 게임 개요
- **Target Platform:** Windows PC
- **Core Concept:** C++ + WinSock2 기반의 IOCP 네트워크 서버 프레임워크

## 🛠️ 개발 툴
- **Game Engine:** Unreal Engine 5.2
- **Development Language:** C/C++
- **Build Tool:** Visual Studio 2022
- **Protocol:** Protocol Buffers (protobuf)
- **Version Control:** Git + GitHub

## ⏳ 개발 기간
- **Start Date:** 2024-12 ~ 2025-03
- **Total Duration:** 3 months

## 👨‍👩‍👦 개발원
| Name      | Role              | GitHub                                 |
|-----------|-------------------|----------------------------------------|
| 장민석     | Client + Server Programmer | [hen0406@naver.com](https://github.com/MinSeok0406) |

## 🧩 주요 모듈 구성(GameServer)

| 모듈 이름                         | 설명 |
|----------------------------------|------|
| `GameServer`                     | 프로젝트의 진입점(Main 함수)이며 서버를 초기화하고 실행 |
| `GameSession`, `GameSessionManager` | 클라이언트 세션 관리 및 연결 상태 유지 |
| `ServerPacketHandler`           | 수신된 패킷을 분기하고 핸들링하는 핵심 로직 |
| `Room`                          | 유저 간 상호작용이 발생하는 공간으로, 룸/파티/매치 등의 개념 구현 |
| `ObjectUtils`                   | 게임 오브젝트 생성 및 유틸리티 처리 |
| `Protocol.pb`, `Struct.pb`, `Enum.pb` | protobuf로 정의된 메시지 구조로 클라이언트와 통신 |

## 🧩 주요 모듈 구성(ServerCore)

| 모듈 이름              | 설명 |
|------------------------|------|
| `IocpCore`, `IocpEvent` | IOCP 이벤트 수신 및 소켓 처리 |
| `Session`, `Listener`, `Service` | 클라이언트 연결 관리 및 이벤트 처리 |
| `BufferReader`, `BufferWriter` | 패킷 직렬화/역직렬화 |
| `RecvBuffer`, `SendBuffer`     | 고정 버퍼 기반 송수신 처리 |
| `Job`, `JobQueue`, `JobTimer`  | 비동기 작업 처리 및 지연 실행 |
| `ThreadManager`, `CoreTLS`     | 스레드 풀, TLS 기반 스레드 안정성 |
| `SocketUtils`, `LockQueue`     | 유틸리티 함수 및 멀티스레드 큐 |
| `Types`, `CoreMacro`, `CoreGlobal` | 전역 타입 정의 및 설정 |

## 🧩 언리얼 엔진 프로젝트 구성
| 모듈 이름                              | 설명 |
|---------------------------------------|------|
| `S1GameInstance`                      | 서버와의 TCP 연결 및 세션 관리를 담당하는 진입 지점 |
| `S1MyPlayer`                          | 플레이어 입력을 감지하고 서버로 명령을 전송 |
| `S1GameModeBase`                      | 게임 모드 설정과 월드 초기화 처리 |
| `ClientPacketHandler`                | 서버로부터 수신된 protobuf 메시지를 분기 처리 |
| `ProtobufCore`                        | Google Protocol Buffers 런타임 및 `.proto` 메시지 정의 포함 |
| `Protocol.pb`, `Struct.pb`, `Enum.pb`| 서버와 통신하는 메시지 형식을 정의한 protobuf 코드 |

## 🔗 클라이언트-서버 통신 흐름
[플레이어 입력]
    ↓
[S1MyPlayer.cpp]
    ↓
[Protobuf 메시지 생성]
    ↓
[소켓 송신 (S1GameInstance)]
    ↓
[ServerCore 기반 C++ 서버 수신 및 처리]
    ↓
[응답 메시지 수신]
    ↓
[ClientPacketHandler.cpp]
    ↓
[Unreal 내부 상태 업데이트]

## 🎯 기능 요약
- ✅ IOCP 기반 비동기 TCP 통신
- ✅ 비동기 네트워크 통신 구현
- ✅ Unreal Engine 클라이언트 연동 고려 설계
- ✅ 구조화된 모듈 설계로 확장성과 유지보수 용이

## 🧪 개선 및 제안
- 🔒 패킷 암호화/해싱 추가로 보안성 강화
- 📊 실시간 로깅 및 모니터링 시스템 도입
- 🌐 느린 빌드 속도와 메모리 과부화를 방지하기 위해 C++20 Module 도입 설계

## 📸 스크린샷
- 서버 연결 안했을 때
![서버 연결 안했을 때](https://github.com/user-attachments/assets/286ab0fc-e581-47de-9b92-0ed5c824fbee)
- 서버 작동한 모습
![서버 작동](https://github.com/user-attachments/assets/8ae83a50-b0d1-425e-b67a-aa4dfef481c9)
- 3명 연결 시도 성공
![3명 연결 시도](https://github.com/user-attachments/assets/5bdae48b-2e3b-47f3-a5da-67516ca6d355)

- 동기화 테스트
https://github.com/user-attachments/assets/302388f5-e677-46e3-9e09-ed9ca0ff2d04

