#include "pch.h"


#ifdef FlatBuffer

class CustomAllocator : public flatbuffers::Allocator {
public:
	explicit CustomAllocator(uint8_t* buffer, size_t size)
		: buffer_(buffer), capacity_(size), offset_(0) {
	}

	// 메모리 할당
	uint8_t* allocate(size_t size) override {
		if (offset_ + size > capacity_) {
			throw std::runtime_error("CustomAllocator: Out of memory!");
		}
		uint8_t* allocated = buffer_ + offset_;
		offset_ += size;
		return allocated;
	}

	// 메모리 해제 (FlatBuffers에서는 일반적으로 필요 없음)
	void deallocate(uint8_t* p, size_t size) override {
		// CustomAllocator는 메모리 해제를 처리하지 않음
	}

	// 현재 오프셋 반환
	size_t get_offset() const { return offset_; }

private:
	uint8_t* buffer_; // 사용자가 제공한 메모리 버퍼
	size_t capacity_; // 버퍼 크기
	size_t offset_;   // 현재 오프셋
};

template<typename T>
struct is_std_vector : std::false_type {};

template<typename T, typename Alloc>
struct is_std_vector<std::vector<T, Alloc>> : std::true_type {};

template<typename... Args>
auto transformArgs(flatbuffers::FlatBufferBuilder& builder, Args&&... args) {
	return std::make_tuple(
		[&]() -> decltype(auto) {
			if constexpr (std::is_same_v<std::decay_t<Args>, std::string> || std::is_same_v<std::decay_t<Args>, const char*>) {
				// std::string or const char* -> FlatBuffers의 string
				return builder.CreateString(args);
			}
			else if constexpr (is_std_vector<std::decay_t<Args>>::value) {
				// std::vector<T> -> FlatBuffers의 Vector<T>
				using ElementType = typename std::decay_t<Args>::value_type;
				return builder.CreateVector(args);
			}
			else {
				// 다른 타입은 그대로 반환
				return std::forward<Args>(args);
			}
		}()...
			);
}

template<typename Ret, typename... FuncArgs, typename... Args>
shared_ptr<SendBuffer> SerializeFlatBuffer(Flatbuffer::PacketContent type, flatbuffers::Offset<Ret>(*func)(flatbuffers::FlatBufferBuilder&, FuncArgs...), Args&&... args)
{
	std::vector<BYTE> vec(128);

	BYTE* buf = vec.data();

	CustomAllocator allocator(buf, 128);

	flatbuffers::FlatBufferBuilder builder(128, &allocator);

	auto transformedArgs = transformArgs(builder, std::forward<Args>(args)...);

	auto message = std::apply([&](auto&&... transformed) {
		return func(builder, std::forward<decltype(transformed)>(transformed)...);
		}, transformedArgs);


	auto packet = Flatbuffer::CreatePacket(builder, type, message.Union());

	builder.Finish(packet);

	PacketHeader* header = reinterpret_cast<PacketHeader*>(builder.GetBufferPointer() - sizeof(PacketHeader));

	header->packetType = PacketType::GC_SendPlayerInfo;
	header->packetSize = builder.GetSize() + sizeof(PacketHeader);

	shared_ptr<SendBuffer> sendbuffer = make_shared<SendBuffer>(header->packetSize);
	sendbuffer->CopyData(header, header->packetSize);

	return sendbuffer;
}

void TestFlatBuffer()
{
	uint16_t id = 12;
	string name = "Cho";

	vector<uint16> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	auto sendbuffer = SerializeFlatBuffer(Flatbuffer::PacketContent_S_Test2, Flatbuffer::CreateS_Test2, id, "Cho", vec);
	auto buffer = sendbuffer->Buffer();

	// 역직렬화
	PacketHeader* recvHeader = reinterpret_cast<PacketHeader*>(buffer);
	auto type = recvHeader->id;
	auto size = recvHeader->size;

	auto recvPacket = Flatbuffer::GetPacket(&recvHeader[1]);

	auto message = recvPacket->content_as_S_Test2();
	auto newid = message->id();
	string newName = message->name()->str();
	for (auto num : *message->ids())
	{
		cout << num << " ";
	}
}
#endif