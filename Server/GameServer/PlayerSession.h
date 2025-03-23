#pragma once

class PlayerSession : public Session
{
public:
	PlayerSession();
	~PlayerSession();

	// 이벤트 핸들러
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnSend(uint32 sentBytes) override;
	virtual void OnRecv(BYTE* buffer, int32 len) override;

	inline void SetPlayerRef(weak_ptr<class Player> playerRef) { _playerRef = playerRef; }

private:
	std::shared_ptr<IOCPServer> _server;

	weak_ptr<class Player> _playerRef;
};

