#ifndef _GAMETIME_HPP_
#define _GAMETIME_HPP_

#include "TimeSpan.hpp"

namespace Xna {
	class GameTime {
		TimeSpan totalGameTime{ TimeSpan::Zero };
		TimeSpan elapsedGameTime{ TimeSpan::Zero };
		bool isRunningSlowly{ false };

		GameTime();
		GameTime(TimeSpan totalGameTime, TimeSpan elapsedGameTime, bool isRunningSlowly = false);

	public:
		TimeSpan TotalGameTime() const;
		TimeSpan ElapsedGameTime() const;
		bool IsRunningSlowly() const;
	};
}

#endif