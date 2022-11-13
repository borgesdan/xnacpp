#ifndef _GAMEPLATFORM_HPP_
#define _GAMEPLATFORM_HPP_

#include <cstdint>
#include <string>
#include <memory>
#include "Game.hpp"
#include "GameWindow.hpp"
#include "GameTime.hpp"
#include "CSharp/TimeSpan.hpp"
#include "GameRunBehavior.hpp"
#include "Graphics/PresentationParameters.hpp"

namespace Xna {

	class GamePlatform {
	private:		
		bool _isActive;

	protected:
		Game _game;
		bool _isMouseVisible;
		std::unique_ptr<GameWindow> _window;
		CSharp::TimeSpan _inactiveSleepTime{ CSharp::TimeSpan::FromMilliseconds(20.0) };
		bool _needsToResetElapsedTime{ false };
		bool InFullScreenMode{ false };

		GamePlatform(Game const& game);
		~GamePlatform();
		
		virtual GameRunBehavior DefaultRunBehavior() const = 0;

		void RaiseAsyncRunLoopEnded();

	public:
		Game GetGame() const;
		bool IsActive() const;
		void IsActive(bool value);
		bool IsMouseVisible() const;
		void IsMouseVisible(bool value);
		GameWindow Window() const;
		void Window(GameWindow const& value);
		virtual void BeforeInitialize();
		virtual bool BeforeRun();
		virtual CSharp::TimeSpan TargetElapsedTimeChanging(CSharp::TimeSpan const& value);

		virtual void Exit() = 0;
		virtual void RunLoop() = 0;
		virtual void StartRunLoop() = 0;
		virtual void EnterFullScreen() = 0;
		virtual void ExitFullScreen() = 0;
		virtual void TargetElapsedTimeChanged() = 0;
		virtual void ResetElapsedTime() = 0;
		virtual void Present() = 0;
		virtual void OnIsMouseVisibleChanged() = 0;
		virtual void OnPresentationChanged(Graphics::PresentationParameters const& pp) = 0;
		virtual void BeginScreenDeviceChange(bool willBeFullScreen) = 0;
		virtual void EndScreenDeviceChange(std::string const& screenDeviceName, int32_t clientWidth, int32_t clientHeight) = 0;
		virtual bool BeforeUpdate(GameTime const& gameTime) = 0;
		virtual bool BeforeDraw(GameTime const& gameTime) = 0;
	};
}

#endif