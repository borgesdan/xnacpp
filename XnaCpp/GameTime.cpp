#include "GameTime.hpp"

using CSharp::TimeSpan;

namespace Xna {
	GameTime::GameTime() {}
	GameTime::GameTime(TimeSpan totalGameTime, TimeSpan elapsedGameTime, bool isRunningSlowly) :
		totalGameTime(totalGameTime), elapsedGameTime(elapsedGameTime), isRunningSlowly(isRunningSlowly) {}

	TimeSpan GameTime::TotalGameTime() const {
		return totalGameTime;
	}

	TimeSpan GameTime::ElapsedGameTime() const {
		return elapsedGameTime;
	}

	bool GameTime::IsRunningSlowly() const {
		return isRunningSlowly;
	}
}