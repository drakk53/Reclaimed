#include <Windows.h>
#include <Psapi.h>

/*
Required to meet the requirements for the custom DLL import
of the ms30.dll. This could be removed from the executable
but it can provide a useful point of reference when debugging
NOTE: This will require custom setup of the import desctiptors
for the ms30.dll
Pretty sure that this doesn't cause any issues either, but
just in case lets return the correct value for this function.
NOTE: Yes this is terrible but nobody helped me on discord
either.. RIP
*/
#undef GetProcessMemoryInfo
extern "C" __declspec(dllexport) BOOL GetProcessMemoryInfo(
	_In_  HANDLE                   Process,
	_Out_ PPROCESS_MEMORY_COUNTERS ppsmemCounters,
	_In_  DWORD                    cb
) {
	return K32GetProcessMemoryInfo(Process, ppsmemCounters, cb);
}
