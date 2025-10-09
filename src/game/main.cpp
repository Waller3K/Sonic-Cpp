#include <GameEngine.hpp>
#include <string>

#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "IDs.hpp"

int main()
{
	std::string gameName = "Sonic C++";

	GameEngine game({1920.0, 1080.0}, gameName);

	//Adds the menu Scene to the game engine's m_scenes vector with the correct ID
	auto menuScene = std::make_shared<MenuScene>(&game);
	game.addScene(static_cast<int>(SceneIDs::MENU), menuScene);

	auto gameScene = std::make_shared<GameScene>(&game);
	game.addScene(static_cast<int>(SceneIDs::GAME), gameScene);

	//Initializes the game engine and sets the default scene to the MenuScene
	game.init(static_cast<int>(SceneIDs::MENU));

		
	return 0;
}
