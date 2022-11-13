#include "GameWindow.hpp"

using std::string;

namespace Xna {
	//GameWindow GameWindow::Create(Game const& game, int32_t width, int32_t height) {
		/*auto window = new MonoGame.Framework.WinFormsGameWindow((MonoGame.Framework.WinFormsGamePlatform)game.Platform);
		window.Initialize(width, height);

		return window;*/
	//}
}

//protected
namespace Xna {

	void GameWindow::OnActivated() {}
	
	void GameWindow::OnDeactivated() {}

	void GameWindow::OnPaint() {}

	void GameWindow::OnOrientationChanged() {
		//TODO: EventHelpers.Raise(this, OrientationChanged, EventArgs.Empty);
	}

	void GameWindow::OnScreenDeviceNameChanged() {
		//TODO:  EventHelpers.Raise(this, ScreenDeviceNameChanged, EventArgs.Empty);
	}
}

namespace Xna {

	bool GameWindow::AllowAltF4() const {
		return _allowAltF4;
	}
	
	void GameWindow::AllowAlfF4(bool value) {
		_allowAltF4 = value;
	}

	string GameWindow::Title() const {
		return _title;
	}

	void GameWindow::Title(string const& value) {
		if (_title != value) {
			SetTitle(value);
			_title = value;
		}
	}
	
	bool GameWindow::IsBorderless() const {
		return _isBorderless;
	}
	
	void GameWindow::IsBorderless(bool value) {
		_isBorderless = value;
	}

	void GameWindow::EndScreenDeviceChange(string const& screenDeviceName) {
		EndScreenDeviceChange(screenDeviceName, ClientBounds().Width, ClientBounds().Height);
	}

	void GameWindow::OnClientSizeChanged() {
		//TODO: EventHelpers.Raise(this, ClientSizeChanged, EventArgs.Empty);
	}	
}