#ifndef _CONTENTTYPEREADER_HPP_
#define _CONTENTTYPEREADER_HPP_

#include <typeinfo>
#include <type_traits>

namespace Xna {
	namespace Content {
		class ContentTypeReader {
		private:
			type_info& _targeType;

		public:
			virtual bool CanDeserializeIntoExistingObject();

		};
	}
}

#endif