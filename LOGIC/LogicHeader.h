#pragma once


#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X32\\ENGINED32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X32\\ENGINER32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X64\\ENGINED64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X64\\ENGINER64.lib")
#endif
#endif

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X32\\LOGICD32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X32\\LOGICR32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X64\\LOGICD64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X64\\LOGICR64.lib")
#endif
#endif


class LogicLibrary
{
public:
	static void Init();
};