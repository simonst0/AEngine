#pragma once
#include <vector>

template<class T>
class Factory
{
public:
	Factory<T>(const int size)
	{
		allocated = new T[size];
		allocationSize = size;
		claimedAllocations = 0;
	}

	~Factory<T>() { delete[] allocated; }

	T* GetNew()
	{
		if (claimedAllocations >= allocationSize)
			return nullptr;		
		T* New = allocated + claimedAllocations;
		objects.push_back(New);
		claimedAllocations++;
		return New;
	}

	std::vector<T*> GetInitializedObjects() { return objects; }

protected:
	T* allocated;
	int allocationSize;
	int claimedAllocations = 0;
	std::vector<T*> objects;

};