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
            // ��ȯ�ϸ� ID�� ���� (currentID�� �������� ��ȯ)
            uint32 id = (currentID + i) % (MAX_ID);

            // ID�� ��� ������ ���� ��� �Ҵ�
            if (!usedIDs.test(id)) {
                usedIDs.set(id);  // �ش� ID�� ��� ������ ǥ��
                currentID = id + 1;  // ���� ���� ��ġ�� ����
                return id;
            }
        }

        // ��� ID�� ��� ���� ��� ���ܸ� �߻���ų �� ����
        throw std::runtime_error("No available IDs");
    }

    // Release an ID when it is no longer in use
    void ReleaseID(uint32 id) 
    {
        usedIDs.reset(id);  // ID�� �̻�� ���·� ǥ��
    }

private:
    std::bitset<MAX_ID> usedIDs;        // ID ��� ���¸� �����ϴ� ��Ʈ��
    uint32 currentID = 0;               // �������� ������ ID�� ������
};

