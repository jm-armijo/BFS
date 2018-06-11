#include <queue>
#include <set>

#include "Node.hpp"

template <typename T>
std::vector<Step> BSF(const Node<T>& first, const Node<T>& goal)
{
    std::queue<Node<T>> to_visit;
    to_visit.push(first);

    std::set<Node<T>> opened;
    opened.insert(first);

    std::vector<Step> response;
    while(to_visit.size() > 0) {
        Node<T> curr = to_visit.front();
        to_visit.pop();

        if (curr.isValidSolution(goal)) {
            response = curr.getPath();
            break;
        }

        // Get next possible nodes to explore
        std::vector<Node<T>> next_nodes = curr.getNextNodes(goal);

        // Enqueue found nodes to visit later only if not opened already
        std::for_each(next_nodes.begin(), next_nodes.end(), [&](Node<T>& next_node){
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

    Node<int> first({1, 2, 3, 0, 0});
    Node<int> goal ({2, 3, 1, 2, 2});
    std::vector<Step> path = BSF(first, goal);

    first.print();
    std::for_each(path.begin(), path.end(), [](Step& step){ step.print();});
    goal.print();

    return 0;
}
