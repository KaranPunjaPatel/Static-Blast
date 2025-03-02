#pragma once

enum struct InputType { pressed, held, released };

namespace Graphics
{

	void Initialize();
	void Deinitialize();

	bool CheckKeyInput(char key, InputType type);
	bool UpdatedGameState();

	void Begin();
	void End();

	bool CheckWindowOpen();

	void HandleChanges();
	void HandleInput();

	void Draw();


};

