#ifndef _TIMESPAN_HPP_
#define _TIMESPAN_HPP_

#include <stdint.h>
#include <limits>

namespace CSharp {
	struct TimeSpan {
	
		static constexpr int64_t TicksPerMillisecond = 10000;
		static constexpr int64_t TicksPerSecond = TicksPerMillisecond * 1000;
		static constexpr int64_t TicksPerMinute = TicksPerSecond * 60;
		static constexpr int64_t TicksPerHour = TicksPerMinute * 60;
		static constexpr int64_t TicksPerDay = TicksPerHour * 24;

		static const TimeSpan Zero;

		TimeSpan();
		TimeSpan(int64_t ticks);
		TimeSpan(int32_t hours, int32_t minutes, int32_t seconds);
		TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds);
		TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds);

		TimeSpan operator -(TimeSpan const& t);
		TimeSpan operator +(TimeSpan const& t);
		friend TimeSpan operator +(TimeSpan const& t1, TimeSpan const& t2);
		friend TimeSpan operator -(TimeSpan const& t1, TimeSpan const& t2);
		friend bool operator ==(TimeSpan const& t1, TimeSpan const& t2);
		friend bool operator !=(TimeSpan const& t1, TimeSpan const& t2);
		friend bool operator <(TimeSpan const& t1, TimeSpan const& t2);
		friend bool operator <=(TimeSpan const& t1, TimeSpan const& t2);
		friend bool operator >(TimeSpan const& t1, TimeSpan const& t2);
		friend bool operator >=(TimeSpan const& t1, TimeSpan const& t2);

		static int32_t Compare(TimeSpan const& t1, TimeSpan const& t2);
		static TimeSpan FromDays(double value);
		static TimeSpan FromHours(double value);
		static TimeSpan Interval(double value, int32_t scale);
		static TimeSpan FromMilliseconds(double value);
		static TimeSpan FromMinutes(double value);
		static TimeSpan FromSeconds(double value);
		static TimeSpan FromTicks(int64_t value);

		int64_t Ticks() const;
		int32_t Days() const;
		int32_t Hours() const;
		int32_t Milliseconds() const;
		int32_t Minutes() const;
		int32_t Seconds() const;
		double TotalDays() const;
		double TotalHours() const;
		double TotalMilliseconds() const;
		double TotalMinutes() const;
		double TotalSeconds() const;

		TimeSpan Add(TimeSpan const& ts) const;
		TimeSpan Duration() const;
		bool Equals(TimeSpan other) const;
		TimeSpan Negate() const;
		TimeSpan Subtract(TimeSpan const& ts) const;

	private:
		static constexpr double MillisecondsPerTick = 1.0 / TicksPerMillisecond;
		static constexpr double SecondsPerTick = 1.0 / TicksPerSecond;
		static constexpr double MinutesPerTick = 1.0 / TicksPerMinute;
		static constexpr double HoursPerTick = 1.0 / TicksPerHour;
		static constexpr double DaysPerTick = 1.0 / TicksPerDay;
		static constexpr int32_t MillisPerSecond = 1000;
		static constexpr int32_t MillisPerMinute = MillisPerSecond * 60;
		static constexpr int32_t MillisPerHour = MillisPerMinute * 60;
		static constexpr int32_t MillisPerDay = MillisPerHour * 24;
		static constexpr int64_t MaxSeconds = std::numeric_limits<int64_t>::max() / TicksPerSecond;
		static constexpr int64_t MinSeconds = std::numeric_limits<int64_t>::min() / TicksPerSecond;
		static constexpr int64_t MaxMilliSeconds = std::numeric_limits<int64_t>::max() / TicksPerMillisecond;
		static constexpr int64_t MinMilliSeconds = std::numeric_limits<int64_t>::min() / TicksPerMillisecond;
		static constexpr int64_t TicksPerTenthSecond = TicksPerMillisecond * 100;

		int64_t _ticks{ 0 };

		static int64_t TimeToTicks(int32_t const& hour, int32_t const& minute, int32_t const& second);
		static int64_t DayToTicks(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds);
	};
}

#endif
