#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

struct vertex;
typedef std::shared_ptr<vertex> shared_vertex;

struct vertex
{

	vertex(unsigned int label=0): label(label){}

	vertex(const shared_vertex& shared)
	{
		neighbors.push_back(shared);
	}

	unsigned int label;
	std::list<shared_vertex> neighbors;
};

bool is_connected_impl(const shared_vertex& u, const shared_vertex& v, std::set<int>& visited)
{
	if(!u || !v)
		return false;
	if(u->label == v->label)
		return true;

	visited.insert(u->label);

	for(const auto& neighbor: u->neighbors)
	{
		if(visited.find(neighbor->label) == visited.end())
			if(is_connected_impl(neighbor, v, visited))
				return true;
	}
	
	return false;
}

bool is_connected(const shared_vertex& u, const shared_vertex& v)
{
	std::set<int> visited;
	return is_connected_impl(u, v, visited);
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t n, m;
	std::cin >> n >> m;

	std::unordered_map<uint, shared_vertex> vertices(n);
	int u, v;

	for(size_t i = 0; i < m; ++i)
	{
		std::cin >> u >> v;

		auto uit = vertices.find(u);
		auto vit = vertices.find(v);

		shared_vertex ux, vx;

		if(uit == vertices.end())
			ux = std::make_shared<vertex>(u);
		else
			ux = uit->second;

		if(vit == vertices.end())
			vx = std::make_shared<vertex>(v);
		else
			vx = vit->second;

		ux->neighbors.push_back(vx);
		vx->neighbors.push_back(ux);

		vertices[u] = ux;
		vertices[v] = vx;
	}

	std::cin >> u >> v;

	size_t label = 0;
	size_t size = vertices.size();

	for(size_t i = 0; i < n - size; ++i)
	{	
		do
		{
			++label;
		} while(vertices.find(label) != vertices.end());

		auto vx = std::make_shared<vertex>(label);
		vertices[label] = vx;
	}

	std::cout << is_connected(vertices.find(u)->second, vertices.find(v)->second) << std::endl;

	return 0;
}