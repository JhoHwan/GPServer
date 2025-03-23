#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(uint32 bufferSize) 
	: _maxDataSize(bufferSize), _bufferSize(bufferSize * BUFFER_COUNT), _writePos(0), _readPos(0)
{
	_buffer.resize(_bufferSize);
}

bool RecvBuffer::OnWirte(uint32 size)
{
	if (size > Capacity())
	{
		return false;
	}

	_writePos += size;
	return true;
}

bool RecvBuffer::OnRead(uint32 size)
{
	if (size > DataSize())
	{
		return false;
	}

	_readPos += size;
	return true;
}

void RecvBuffer::Clean()
{
	auto dataSize = DataSize();
	
	if (dataSize == 0)
	{
		_readPos = 0;
		_writePos = 0;
	}
	else
	{
		// ���� ������ ���� 1�� ũ�� �̸��̸�, �����͸� ������ �����.
		if (Capacity() < _maxDataSize)
		{
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}
	}
}

