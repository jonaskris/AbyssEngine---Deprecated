#pragma once

namespace abyssengine {
	namespace entitysystem {
		class BatchErasableUnit
		{
		private:
			bool erase = false;
		
		public:
			bool getErase() const
			{
				return erase;
			}

			void setErase(const bool& erase)
			{
				this->erase = erase;
			}
		};
	}
}