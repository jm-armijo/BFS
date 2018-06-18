#include <queue>
#include <set>

#include "Node.hpp"

template <typename T>
std::vector<Step> BSF(const std::shared_ptr<Node<T>> first, const std::shared_ptr<Node<T>> goal)
{
    std::queue<std::shared_ptr<Node<T>>> to_visit;
    to_visit.push(first);

    std::set<std::shared_ptr<Node<T>>> opened;
    opened.insert(first);

    std::vector<Step> response;
    while(to_visit.size() > 0) {
        const std::shared_ptr<Node<T>> curr = to_visit.front();
        to_visit.pop();

        if (curr->isValidSolution(goal)) {
            response = curr->getPath();
            break;
        }

        // Get next possible nodes to explore
        std::vector<std::shared_ptr<Node<T>>> next_nodes = curr->getNextNodes(goal);

        // Enqueue found nodes to visit later only if not opened already
        std::for_each(next_nodes.begin(), next_nodes.end(), [&](const std::shared_ptr<Node<T>> next_node){
            if (std::find(opened.begin(), opened.end(), next_node) == opened.end()) {
                opened.insert(next_node);
                to_visit.push(std::move(next_node));
            }
        });
    }

    return response;
}


int main()
{
    //Node<std::string> first ({"V1", "S1", "S1", "S1", "J1", "S1", "S1", "S1", "V2", "G1", "P1", "P1", "V2", "V2", "P1", "A1", "V2", "M1", "M1", "M1", "", "", "", ""});
    //Node<std::string> goal  ({"S1", "S1", "S1", "S1", "S1", "S1", "S1", "S1", "V1", "M1", "M1", "M1", "J1", "K1", "G2", "G1", "P1", "A1", "V2", "V2", "P1", "P1", "V2", "V2"});

    std::shared_ptr<Node<int>> first(new Node<int>({1, 2, 3, 0, 0}));
    std::shared_ptr<Node<int>> goal (new Node<int>({2, 3, 1, 2, 2}));
    std::vector<Step> path = BSF(first, goal);

    first->print();
    std::for_each(path.begin(), path.end(), [](Step& step){ step.print();});
    goal->print();

    return 0;
}
