#ifndef graph_alg
#define graph_alg

#include "graph.h"
#include <set>
#include <stack>

template <class Functor>
inline void Explore(const SharedVertex& vertex, Functor functor)
{
	std::set<uintptr_t> visited;
	std::stack<SharedVertex> stack;

	stack.push(vertex);

	while(!stack.empty())
	{
		auto v = stack.top();
		stack.pop();

		visited.insert((uintptr_t)v.get());
		functor(v);

		for(auto u = v->CBegin(); u != v->CEnd(); ++u)
		{
			if(visited.find((uintptr_t)u->get()) == visited.end())
			{
				stack.push(*u);
			}
		}
	}
}

#endif