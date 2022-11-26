#ifndef _CONTENTREADER_HPP_
#define _CONTENTREADER_HPP_

#include <memory>

namespace Xna {
	namespace Content {

		class ContentManager;

		class ContentReader {
		private:

		public:
			ContentReader();

			void InitializeTypeReaders();

			template <typename T>
			std::shared_ptr<T> ReadAsset();
			
			template <typename T>
			std::shared_ptr<T> ReadAsset(T const& existingInstance);
		};
	}
}

#endif