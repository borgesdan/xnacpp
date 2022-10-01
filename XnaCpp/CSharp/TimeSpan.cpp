#include "TimeSpan.hpp"

using std::numeric_limits;

namespace CSharp {
	const TimeSpan TimeSpan::Zero = TimeSpan();

	//----- Constructors -----

	TimeSpan::TimeSpan() {}

	TimeSpan::TimeSpan(int64_t ticks) :
		_ticks(ticks) {}

	TimeSpan::TimeSpan(int32_t hours, int32_t minutes, int32_t seconds) :
		_ticks(TimeToTicks(hours, minutes, seconds)) {}

	TimeSpan::TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds) :
		_ticks(DayToTicks(days, hours, minutes, seconds, 0)) {}

	TimeSpan::TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds) :
		_ticks(DayToTicks(days, hours, minutes, seconds, milliseconds)) {}

	//----- Operators -----
	TimeSpan TimeSpan::operator- (TimeSpan const& t) {
		return TimeSpan(-t._ticks);
	}

	TimeSpan TimeSpan::operator+ (TimeSpan const& t) {
		return t;
	}

	TimeSpan operator+ (TimeSpan const& t1, TimeSpan const& t2) {
		return t1.Add(t2);
	}
	
	TimeSpan operator- (TimeSpan const& t1, TimeSpan const& t2) {
		return t1.Subtract(t2);
	}

	bool operator== (TimeSpan const& t1, TimeSpan const& t2) {
		return t1._ticks == t2._ticks;
	}
	
	bool operator!= (TimeSpan const& t1, TimeSpan const& t2) {
		return t1._ticks != t2._ticks;
	}

	bool operator< (TimeSpan const& t1, TimeSpan const& t2) {
		return t1._ticks < t2._ticks;
	}

	bool operator<= (TimeSpan const& t1, TimeSpan const& t2) {
		return t1._ticks <= t2._ticks;
	}

	bool operator> (TimeSpan const& t1, TimeSpan const& t2) {
		return t1._ticks > t2._ticks;
	}

	bool operator>= (TimeSpan const& t1, TimeSpan const& t2) {
		return t1._ticks >= t2._ticks;
	}

	//---- Static Functions -----

	int32_t TimeSpan::Compare(TimeSpan const& t1, TimeSpan const& t2) {
		if (t1._ticks > t2._ticks) 
			return 1;

		if (t1._ticks < t2._ticks) 
			return -1;
		
		return 0;
	}

	TimeSpan TimeSpan::FromDays(double value) {
		return Interval(value, MillisPerDay);
	}

	TimeSpan TimeSpan::FromHours(double value) {
		return Interval(value, MillisPerHour);
	}

	TimeSpan TimeSpan::Interval(double value, int32_t scale) {
		double tmp = value * scale;
		double millis = tmp + (value >= 0 ? 0.5 : -0.5);
		
		return TimeSpan(static_cast<int64_t>(millis) * TicksPerMillisecond);
	}

	TimeSpan TimeSpan::FromMilliseconds(double value) {
		return Interval(value, 1);
	}

	TimeSpan TimeSpan::FromMinutes(double value) {
		return Interval(value, MillisPerMinute);
	}

	TimeSpan TimeSpan::FromSeconds(double value) {
		return Interval(value, MillisPerSecond);
	}

	TimeSpan TimeSpan::FromTicks(int64_t value) {
		return TimeSpan(value);
	}	

	//----- Functions -----

	int64_t TimeSpan::Ticks() const { return _ticks; }
	
	int32_t TimeSpan::Days() const { return static_cast<int32_t>(_ticks / TicksPerDay); }
	
	int32_t TimeSpan::Hours() const { return static_cast<int32_t>((_ticks / TicksPerHour) % 24);  }
	
	int32_t TimeSpan::Milliseconds() const { return static_cast<int32_t>((_ticks / TicksPerMillisecond) % 1000); }
	
	int32_t TimeSpan::Minutes() const { return static_cast<int32_t>((_ticks / TicksPerMinute) % 60); }
	
	int32_t TimeSpan::Seconds() const { return static_cast<int32_t>((_ticks / TicksPerSecond) % 60); }
	
	double TimeSpan::TotalDays() const { return static_cast<double>(_ticks) * DaysPerTick; }
	
	double TimeSpan::TotalHours() const { return static_cast<double>(_ticks) * HoursPerTick; }
	
	double TimeSpan::TotalMilliseconds() const {
		double temp = static_cast<double>(_ticks) * MillisecondsPerTick;
		
		if (temp > MaxMilliSeconds)
			return  static_cast<double>(MaxMilliSeconds);

		if (temp < MinMilliSeconds)
			return  static_cast<double>(MinMilliSeconds);

		return temp;
	}
	
	double TimeSpan::TotalMinutes() const { return static_cast<double>(_ticks) * MinutesPerTick; }
	
	double TimeSpan::TotalSeconds() const { return static_cast<double>(_ticks) * SecondsPerTick; }

	TimeSpan TimeSpan::Add(TimeSpan const& ts) const {
		int64_t result = _ticks + ts._ticks;

		return TimeSpan(result);
	}

	TimeSpan TimeSpan::Duration() const {
		return TimeSpan(_ticks >= 0 ? _ticks : -_ticks);
	}

	bool TimeSpan::Equals(TimeSpan other) const {
		return _ticks == other._ticks;
	}

	TimeSpan TimeSpan::Negate() const {
		return TimeSpan(-_ticks);
	}

	TimeSpan TimeSpan::Subtract(TimeSpan const& ts) const {
		int64_t result = _ticks - ts._ticks;
		return TimeSpan(result);
	}

	//----- Private -----

	int64_t TimeSpan::TimeToTicks(int32_t const& hour, int32_t const& minute, int32_t const& second) {
		int64_t totalSeconds =
			static_cast<int64_t>(hour) * 3600 +
			static_cast<int64_t>(minute) * 60 +
			static_cast<int64_t>(second);		

		return totalSeconds * TicksPerSecond;
	}

	int64_t TimeSpan::DayToTicks(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds) {
		int64_t totalMilliSeconds =
			(static_cast<int64_t>(days) * 3600 * 24 +
				static_cast<int64_t>(hours) * 3600 +
				static_cast<int64_t>(minutes) * 60 + seconds) * 1000 + milliseconds;		

		return totalMilliSeconds * TicksPerMillisecond;
	}
}