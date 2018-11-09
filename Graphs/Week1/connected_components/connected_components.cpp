#include <iostream>
#include <list>
#include <memory>
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

typedef unsigned int uint;

void explore(std::pair<const uint, shared_vertex> vpair, std::vector<bool>& visited)
{
	visited[vpair.first] = true;

	for(const auto& vertex: vpair.second->neighbors)
	{
		if(!visited[vertex->label])
			explore(std::make_pair(vertex->label, vertex), visited);
	}
}

uint get_components(std::unordered_map<uint, shared_vertex>& vertices)
{
	std::vector<bool> visited(vertices.size(), false);
	uint components = 0;

	for(auto& pair: vertices)
	{
		if(!visited[pair.first])
		{
			explore(pair, visited);
			++components;
		}
	}

	return components;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t n, m;
	std::cin >> n >> m;

	std::unordered_map<uint, shared_vertex> vertices(n);

	for(size_t i = 0; i < m; ++i)
	{
		int u, v;
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

	std::cout << get_components(vertices) << std::endl;

	return 0;
}