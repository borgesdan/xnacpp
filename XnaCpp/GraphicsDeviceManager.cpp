#include "GraphicsDeviceManager.hpp"

using std::make_shared;

//Constructor
namespace Xna {
	GraphicsDeviceManager::GraphicsDeviceManager(shared_ptr<Game> const& game) {
		//TODO: verificar exceção

		_game = game;
		_preferredBackBufferFormat = SurfaceFormat::Color;
		_preferredDepthStencilFormat = DepthFormat::Depth24;
		_synchronizedWithVerticalRetrace = true;

		//TODO: auto clientBounds = _game.Window().ClientBounds();
	}
}