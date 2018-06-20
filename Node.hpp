#ifndef JM_SEARCH_NODE
#define JM_SEARCH_NODE

#include <cassert>
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

class Step {
private:
    int m_from;
    int m_to;
public:
    Step(int i, int j);
    void print() const;
    int getFromIdx() const;
    int getToIdx() const;
};


template <typename T>
class Node {
private:
    std::vector<T> m_values;
    std::vector<Step> m_path;
    T m_def_val;

    std::shared_ptr<Node<T>> getNextNode (const Step& step) const;
    bool isInPosition(int idx, const Node<T>* goal) const;

public:
    Node(const std::vector<T>& values, const std::vector<Step>& path = {});
    bool operator<(const Node<T>& n) const;
    bool operator==(const Node<T>& n) const;
    std::vector<Step> getPath() const;
    bool isValidSolution(const Node<T>* n) const;
    std::vector<std::shared_ptr<Node<T>>> getNextNodes(const Node<T>* goal) const;
    void print() const;
};

Step::Step(int i, int j) : m_from(i), m_to(j) {}

void Step::print() const
{
    std::cout << m_from << " --> " << m_to << std::endl;
}

int Step::getFromIdx() const
{
    return m_from;
}

int Step::getToIdx() const
{
    return m_to;
}


template <typename T>
std::shared_ptr<Node<T>> Node<T>::getNextNode (const Step& step) const
{
    // Cannot use make_shared here because that would create a circular dependency.
    std::shared_ptr<Node<T>> n(new Node<T>(m_values, m_path));
    std::swap(n->m_values[step.getFromIdx()], n->m_values[step.getToIdx()]);
    n->m_path.push_back(step);
    return n;
}

template <typename T>
bool Node<T>::isInPosition(int idx, const Node<T>* goal) const
{
    return (m_values[idx] == m_def_val || m_values[idx] == goal->m_values[idx]);
}

template <typename T>
Node<T>::Node(const std::vector<T>& values, const std::vector<Step>& path) :
        m_values(values),
        m_path(path)
{
    static T x;
    m_def_val = x;
}

template <typename T>
bool Node<T>::operator<(const Node<T>& n) const
{
    return (m_values < n.m_values);
}

template <typename T>
bool Node<T>::operator==(const Node<T>& n) const
{
    assert(m_values.size() == n.m_values.size());
    return std::equal(m_values.begin(), m_values.end(), n.m_values.begin());
}

template <typename T>
std::vector<Step> Node<T>::getPath() const
{
    return m_path;
}

template <typename T>
void Node<T>::print() const
{
    std::for_each(m_values.begin(), m_values.end(), [](T val){std::cout << "'" << val << "' ";});
    std::cout << std::endl;
}

template <typename T>
bool Node<T>::isValidSolution(const Node<T>* n) const
{
    assert(m_values.size() == n->m_values.size());

    for (unsigned i {0}; i<m_values.size(); ++i) {
        if (m_values[i] != m_def_val && m_values[i] != n->m_values[i]) {
            return false;
        }
    }

    return true;
}

template <typename T>
std::vector<std::shared_ptr<Node<T>>> Node<T>::getNextNodes(const Node<T>* goal) const
{
    std::vector<std::shared_ptr<Node<T>>> next_nodes;
    for (unsigned i {0}; i<m_values.size(); ++i) {

        // We'll try to move the value only if not already on it's final position
        if (isInPosition(i, goal)) {
            continue;
        }

        for (unsigned j {0}; j<m_values.size(); ++j) {
            // value being moved is not a default
            // value is being moved to final position
            // final position is available
            if (m_values[i] != m_def_val && m_values[i] == goal->m_values[j] && m_values[j] == m_def_val) {
                const std::shared_ptr<Node<T>> next = getNextNode(Step(i, j));
                next_nodes.push_back(next);
            }
        }
    }

    return next_nodes;
}

#endif // JM_SEARCH_NODE
