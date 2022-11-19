#include "Game.hpp"
#include "GameWindow.hpp";
#include "IGraphicsDeviceManager.hpp";
#include "GraphicsDeviceManager.hpp";
#include "Graphics/IGraphicsDeviceService.hpp";
#include "Graphics/GraphicsDevice.hpp";
#include "GameTime.hpp";

using std::shared_ptr;
using std::map;
using std::string;
using std::make_shared;

//public
namespace Xna {
	Game::Game() {
		_instance = make_shared<Game>(*this);
		//_services = new GameServiceContainer();
		//_components = new GameComponentCollection();
		//_content = new ContentManager(_services);

		//Platform = GamePlatform.PlatformCreate(this);
		//Platform.Activated += OnActivated;
		//Platform.Deactivated += OnDeactivated;
		//_services.AddService(typeof(GamePlatform), Platform);

		//FrameworkDispatcher.Update();

		//PlatformConstruct();
	}
}