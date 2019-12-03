#pragma once
#include <string>
#include <tchar.h>

/* "Configuration.h is represented for global value for
 * simplicity of configuring variout variable */


namespace APP
{
	/* Console Configuration */
	const std::wstring DefaultConsoleTitle = L"YseConsoleApplication";
	const int DefaultConsoleWidth = 400;
	const int DefaultConsoleHeight = 400;
	const float DefaultFrameRate = 30.0f;

	/* Render Configuration */
	const char DefaultDecoration = '=';

#ifdef _DEBUG
	namespace DEBUG
	{
		/* Debug console configuration */
		const std::wstring DebugConsoleTitle = L"YseDebugConsole";
		TCHAR Command[];
	};
#endif // _DEBUG
};