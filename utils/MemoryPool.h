#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <functional>

namespace core
{
	template <typename TObject, std::size_t TInitSize =100>
	class MemoryPool
	{
	public:
		using ObjectPtr = std::unique_ptr<TObject, std::function<void (TObject*)>>;

		MemoryPool()
		{
			mFreeMemVctr.reserve(TInitSize);
			allocateMemory();
		}

		~MemoryPool()
		{
			for(auto& lMem : mFreeMemVctr)
			{
				std::free(lMem);
			}

			mFreeMemVctr.clear();
		}

		//can not make copy of Memory Pool
		MemoryPool(const MemoryPool&) = delete;
		MemoryPool& operator=(const MemoryPool&) = delete;

		//allow move construction
		MemoryPool(const MemoryPool&& lRHS)
		{
			mFreeMemVctr = std::move(lRHS.mFreeMemVctr);
		}

		MemoryPool& operator=(const MemoryPool&& lRHS)
		{
			if(this!= lRHS)
			{
				mFreeMemVctr = std::move(lRHS.mFreeMemVctr);
			}

			return *this;
		}

		template<typename... Args>
		ObjectPtr allocateObject(Args&&... lObjectArgs)
		{
			//once all memory is taken, increase available by memory slots
		    // vector will increase its size by reallocating memory . New available slots will depend on load factor.
		    //So filling up the pool will cause heap allocation for vector an obect
			if(mFreeMemVctr.empty())
			{
				mFreeMemVctr.emplace_back(reinterpret_cast<TObject*>(std::malloc(sizeof(TObject))));
			}

			auto* lMemory = mFreeMemVctr.back();
			mFreeMemVctr.pop_back();

			return ObjectPtr(new (lMemory) TObject(std::forward<Args>(lObjectArgs)...), [this](TObject* lObjPtr)
								{
									//destructor call is required
									lObjPtr->~TObject();

									mFreeMemVctr.push_back(lObjPtr);
								}
							);
		}

		size_t getCapacity()const { return mFreeMemVctr.capacity();}

		size_t getAvailable()const { return mFreeMemVctr.size(); }

	private:
		std::vector<TObject*> mFreeMemVctr;

		void allocateMemory()
		{
			for(auto idx = 0; idx< TInitSize ; ++idx)
			{
				TObject* lNewMemPtr = reinterpret_cast<TObject*>(std::malloc(sizeof(TObject)));
				mFreeMemVctr.emplace_back(lNewMemPtr);
			}
		}

	};
}




