#pragma once

namespace abyssengine {
	namespace utils {
		/*
			Counter used to give Types a unique identifier.
		*/
		class TypeIdentifierCounter
		{
			template <typename Type>
			friend struct TypeIdentifier;

			static inline size_t counter = 1;
		};

		/*
			Identifies a Type with a unique identifier.
		*/
		template <typename Type>
		struct TypeIdentifier
		{
		private:
			static inline size_t identifier = 0;
		public:
			static size_t getIdentifier() {

				if (identifier == 0)
					identifier = TypeIdentifierCounter::counter++;
				return identifier;
			};
		};
	}
}