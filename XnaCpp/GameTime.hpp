#ifndef _GAMETIME_HPP_
#define _GAMETIME_HPP_

#include "CSharp/TimeSpan.hpp"

namespace Xna {
	class GameTime {
		CSharp::TimeSpan totalGameTime{ CSharp::TimeSpan::Zero };
		CSharp::TimeSpan elapsedGameTime{ CSharp::TimeSpan::Zero };
		bool isRunningSlowly{ false };

		GameTime();
		GameTime(CSharp::TimeSpan totalGameTime, CSharp::TimeSpan elapsedGameTime, bool isRunningSlowly = false);

	public:
		CSharp::TimeSpan TotalGameTime() const;
		CSharp::TimeSpan ElapsedGameTime() const;
		bool IsRunningSlowly() const;
	};
}

#endif