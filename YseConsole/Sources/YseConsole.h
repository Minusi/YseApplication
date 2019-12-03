#pragma once
#include <memory>

class UpdateDelegate;
class ConsoleRender;
class Console;
class MainLoop;
class StateManager;


/*
 *	YseProgram is represented for Console Application. Main purpose of
 *	class is abstraction about 'console program'.
 */
class YseProgram
{
public:
	/* Default Constructor and Destructor */
	YseProgram() = default;
	~YseProgram() = default;
		
	YseProgram(const YseProgram& other) = delete;
	YseProgram(YseProgram&& other) = delete;
	const YseProgram& operator=(const YseProgram& other) = delete;

	/* exit program if not valid*/
	static YseProgram* ValidateProgram(YseProgram* InProgram);

	/* Start Yse console application. Used for Application Main Entry. */
	void Start();

private:
	/* Initialize console application */
	void Init();

	/* Clean up consle application and exit. */
	void Close();



public:
	/* getter function */
	UpdateDelegate* OnUpdateDelegate() const;
	ConsoleRender* GetConsoleRender() const;
	Console* GetConsole() const;

private:
	/* flag to check program is already initialized */
	bool bProgramInit;

	/* console object */
	std::unique_ptr<Console> uConsole;

	/* supports Loop. don't access this directly
	 * alternatively, use UpdateDelegate to register loop */
	std::unique_ptr<MainLoop> uMainLoop;

	/* program state manager */
	std::unique_ptr<StateManager> uStateManager;
};

extern YseProgram* gYseProgram;
