#include "graph.h"
#include <algorithm>
#include <stdexcept>

Vertex::Vertex()
{
}

Vertex::~Vertex()
{
}
	
void Vertex::AddNeighbor(const SharedVertex& vertex)
{
	if(std::find(m_list.begin(), m_list.end(), vertex) == m_list.end())
		m_list.push_back(vertex);
	else
		throw std::invalid_argument("Vertex's been already inserted");
}

typename Vertex::Iterator Vertex::Begin()
{
	return m_list.begin();
}

typename Vertex::Iterator Vertex::End()
{
	return m_list.end();
}

typename Vertex::ConstIterator Vertex::CBegin()
{
	return m_list.cbegin();
}

typename Vertex::ConstIterator Vertex::CEnd()
{
	return m_list.cend();
}