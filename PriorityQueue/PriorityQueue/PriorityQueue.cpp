// PriorityQueue.cpp :
// An example of a priority queue

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class PriorityQueue
{
private:
	struct Item
	{
		T value;
		float priority;

		Item(T _value, float _priority)
		{
			value = _value;
			priority = _priority;
		}
	};
	vector<Item> queue;

	int Parent(int index)
	{
		return (index - 1) / 2;
	}

	int ChildA(int index)
	{
		return 2 * index + 1;
	}

	int ChildB(int index)
	{
		return 2 * index + 2;
	}

	// Sift high priority items toward the root of the tree
	void SiftUp(int index)
	{
		while (index > 0)
		{
			int p = Parent(index);
			// only swap if parent is lower priority
			if (queue[p].priority < queue[index].priority)
			{
				Item tmp = queue[p];
				queue[p] = queue[index];
				queue[index] = tmp;
			}
			else
				break;
			index = p;
		}
	}

	// Sift low priority items toward the leafs of the tree
	void SiftDown(int index)
	{
		while (index < queue.size() - 1)
		{
			int a = ChildA(index);
			int b = ChildB(index);
			if (a >= queue.size())
				break;
			// swap with higher priority child;
			int si = a;
			if (b < queue.size() && queue[a].priority < queue[b].priority)
				si = b;
			// only swap if child priority is larger
			if (queue[si].priority > queue[index].priority)
			{
				Item tmp = queue[index];
				queue[index] = queue[si];
				queue[si] = tmp;
			}
			else
				break;
			index = si;
		}
	}

public:
	void Push(T input, float priority)
	{
		queue.push_back(Item(input, priority));
		SiftUp(queue.size() - 1);
	}

	T Pop()
	{
		if (queue.size() == 0)
			return NULL;
		// swap highest priority item with end of array
		Item tmp = queue[0];
		queue[0] = queue[queue.size() - 1];
		queue[queue.size() - 1] = tmp;
		// grab highest priority item and remove it from end of array
		Item item = queue.back();
		queue.pop_back();
		// Keep the heap sorted
		SiftDown(0);
		return item.value;
	}

	int Size()
	{
		return queue.size();
	}
};

int main()
{
	PriorityQueue<float> pq;

	for (int i = 0; i < 10; i++)
	{
		float num = (float)(rand()) * 100 / RAND_MAX;
		pq.Push(num, num);
	}
	while (pq.Size() > 0)
	{
		std::cout << pq.Pop() << ", ";
	}
}
