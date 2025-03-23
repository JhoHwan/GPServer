#pragma once
#include <bitset>
#include <stdint.h>

class IDGenerator
{
public:
    static constexpr uint32 MAX_ID = 4294967295;

    // Generate a unique ID
    uint32 GenerateID() 
    {
        for (uint32 i = 0; i < MAX_ID; ++i) {
            // 순환하며 ID를 생성 (currentID를 기준으로 순환)
            uint32 id = (currentID + i) % (MAX_ID);

            // ID가 사용 중이지 않은 경우 할당
            if (!usedIDs.test(id)) {
                usedIDs.set(id);  // 해당 ID를 사용 중으로 표시
                currentID = id + 1;  // 다음 생성 위치를 갱신
                return id;
            }
        }

        // 모든 ID가 사용 중인 경우 예외를 발생시킬 수 있음
        throw std::runtime_error("No available IDs");
    }

    // Release an ID when it is no longer in use
    void ReleaseID(uint32 id) 
    {
        usedIDs.reset(id);  // ID를 미사용 상태로 표시
    }

private:
    std::bitset<MAX_ID> usedIDs;        // ID 사용 상태를 추적하는 비트셋
    uint32 currentID = 0;               // 다음으로 생성할 ID의 시작점
};

