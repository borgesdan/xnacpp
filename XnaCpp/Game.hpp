#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "TimeSpan.hpp"
#include <map>
#include <string>

namespace Xna {
	class Game {
		bool _initialized{ false };
		bool _isFixedTimeStep{ true };

		TimeSpan _targetElapsedTime{ TimeSpan::FromTicks(166667) };
		TimeSpan _inactiveSleepTime{ TimeSpan::FromSeconds(0.02) };
		TimeSpan _maxElapsedTime{ TimeSpan::FromMilliseconds(500) };

		bool _shouldExit;
		bool _suppressDraw;		
		
		std::map <std::string, std::string> launchParameters;

		Game();

	public:
		std::map <std::string, std::string> LaunchParameters() const;
		TimeSpan InactiveSleepTime() const;
		void InactiveSleepTime(TimeSpan const& value);
		TimeSpan MaxElapsedTime() const;
		void MaxElapsedTime(TimeSpan const& value);
		bool IsActive() const;
		bool IsMouseVisible() const;
		void IsMouseVisible(bool value);
		TimeSpan TargetElapsedTime() const;
		void TargetElapsedTime(TimeSpan const& value);
		bool IsFixedTimeStep() const;
		void IsFixedTimeStep(bool value) const;

		void Exit();
		void ResetElapsedTime();
		void SuppressDraw();
		void RunOneFrame();
		void Run();
	};
}

#endif // !_GAME_HPP_
