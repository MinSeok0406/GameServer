# 🎮 Project Title: [게임 서버 + 언리얼 엔진 연동]

## 📌 Game Overview
- **Target Platform:** Windows PC
- **Core Concept:** C++ + WinSock2 기반의 IOCP 네트워크 서버 프레임워크

## 🛠️ Development Tools
- **Game Engine:** Unreal Engine 5.2
- **Development Language:** C/C++
- **Version Control:** Git + GitHub

## ⏳ Development Timeline
- **Start Date:** 2024-12 ~ 2025-03
- **Total Duration:** 3 months

## 👨‍👩‍👦 Development Team
| Name      | Role              | GitHub                                 |
|-----------|-------------------|----------------------------------------|
| 장민석     | Client + Server Programmer | [hen0406@naver.com](https://github.com/MinSeok0406) |

## 🧩 주요 모듈 구성

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

## 🎯 Features
- ✅ IOCP 기반 비동기 TCP 통신
- ✅ 비동기 네트워크 통신 구현
- ✅ Unreal Engine 클라이언트 연동 고려 설계
- ✅ 구조화된 모듈 설계로 확장성과 유지보수 용이

## 🧪 개선 및 제안
- 🔒 패킷 암호화/해싱 추가로 보안성 강화
- 📊 실시간 로깅 및 모니터링 시스템 도입
- 🌐 느린 빌드 속도와 메모리 과부화를 방지하기 위해 C++20 Module 도입 설

## 📸 Screenshots
- 서버 연결 안했을 때
![서버 연결 안했을 때](https://github.com/user-attachments/assets/286ab0fc-e581-47de-9b92-0ed5c824fbee)
- 서버 작동한 모습
![서버 작동](https://github.com/user-attachments/assets/8ae83a50-b0d1-425e-b67a-aa4dfef481c9)
- 3명 연결 시도 성공
![3명 연결 시도](https://github.com/user-attachments/assets/5bdae48b-2e3b-47f3-a5da-67516ca6d355)

- 동기화 테스트
https://github.com/user-attachments/assets/302388f5-e677-46e3-9e09-ed9ca0ff2d04

