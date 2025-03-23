#pragma once

#ifndef PCH_H
#define PCH_H

#include "CorePch.h"
#include "ServerPch.h"

#ifdef _DEBUG
#pragma comment(lib,"libprotobufd.lib")
#else
#pragma comment(lib,"libprotobuf.lib")
#endif // DEBUG

#endif //PCH_H
