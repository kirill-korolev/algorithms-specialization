#ifndef graph_h
#define graph_h

#include <iterator>
#include <list>
#include <memory>

struct Vertex;
using SharedVertex = std::shared_ptr<Vertex>;

template <class Key>
struct KVertex;

template <class Key>
using SharedKVertex = std::shared_ptr<KVertex<Key>>;

struct Vertex
{
	using Iterator = typename std::list<SharedVertex>::iterator;
	using ConstIterator = typename std::list<SharedVertex>::const_iterator;

	Vertex();
	~Vertex();
	
	void AddNeighbor(const SharedVertex& vertex);

	Iterator Begin();
	Iterator End();
	ConstIterator CBegin();
	ConstIterator CEnd();

	template <class... Args>
	static SharedVertex Create(Args&&... args);
private:
	std::list<SharedVertex> m_list;
};

template <class Key>
struct KVertex: Vertex
{
	using Vertex::Vertex;

	KVertex(Key&& key);
	~KVertex();

	Key& GetKey();

	template <class... Args>
	static SharedKVertex<Key> Create(Args&&... args);
private:
	Key m_key;
};

template <class... Args>
SharedVertex Vertex::Create(Args&&... args)
{
	return std::make_shared<Vertex>(std::forward<Args>(args)...);
}

template <class Key>
KVertex<Key>::KVertex(Key&& key): Vertex()
{
	m_key = std::move(key);
}

template <class Key>
KVertex<Key>::~KVertex()
{

}

template <class Key>
Key& KVertex<Key>::GetKey()
{
	return m_key;
}

template <class Key>
template <class... Args>
SharedKVertex<Key> KVertex<Key>::Create(Args&&... args)
{
	return std::make_shared<KVertex<Key>>(std::forward<Args>(args)...);
}

#endif