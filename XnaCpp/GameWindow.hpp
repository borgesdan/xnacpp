#ifndef _GAMEWINDOW_HPP_
#define _GAMEWINDOW_HPP_

#include <string>
#include "Rectangle.hpp"
#include "Point.hpp"

namespace Xna {
	
	class Game;

	class GameWindow {

	protected:
		bool _isBorderless{ false };
		bool _allowAltF4{ true };
		std::string _title;
		//TODO: MouseState MouseState;
		void OnActivated();
		void OnDeactivated();
		void OnOrientationChanged();
		void OnPaint();
		void OnScreenDeviceNameChanged();

	public:
		static GameWindow Create(Game const& game, int32_t width, int32_t height);

		virtual bool AllowUserResizing() const = 0;
		virtual void AllowUserResizing(bool value) = 0;
		virtual Rectangle ClientBounds() const = 0;
		virtual bool AllowAltF4() const;
		virtual void AllowAlfF4(bool value);
		virtual Point Position() const = 0;
		virtual void Position(Point const& value) = 0;
		//TODO: verificar IntPrt - virtual IntPtr Handle()  = 0;
		virtual std::string ScreenDeviceName() const = 0;
		std::string Title() const;
		void Title(std::string const& value);
		virtual bool IsBorderless() const;
		virtual void IsBorderless(bool value);
		virtual void SetTitle(std::string const& title) = 0;
		virtual void BeginScreenDeviceChange(bool willBeFullScreen) = 0;
		virtual void EndScreenDeviceChange(std::string const& screenDeviceName, int32_t clientWidth, int32_t clientHeight) = 0;
		void EndScreenDeviceChange(std::string const& screenDeviceName);
		void OnClientSizeChanged();
	};
}

#endif