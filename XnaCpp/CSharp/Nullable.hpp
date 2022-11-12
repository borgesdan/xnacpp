#ifndef _NULLABLE_HPP_
#define _NULLABLE_HPP_

namespace CSharp {	

	struct CSNullable {
		CSNullable() = default;

		bool HasValue() const {
			return _hasValue;
		}

	protected:
		bool _hasValue{ false };	
	};

	static const CSNullable csnull = CSNullable();	

	template <typename T> 
	struct Nullable : CSNullable {
		Nullable() = default;

		Nullable(CSNullable nullable) {}

		Nullable(T value) :
			_value(value) {
			_hasValue = true;
		}

		bool HasValue() const {
			return _hasValue;
		}

		T Value() const {
			return _value;
		}

	private:
		T _value;
	};
}

#endif