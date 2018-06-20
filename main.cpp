#include <queue>
#include <set>

#include "Node.hpp"

template <typename T>
std::vector<Step> BFS(const std::shared_ptr<T> first, const std::shared_ptr<T> goal)
{
    std::queue<std::shared_ptr<T>> to_visit;
    to_visit.push(first);

    std::set<std::shared_ptr<T>> opened;
    opened.insert(first);

    std::vector<Step> response;
    while(to_visit.size() > 0) {
        const std::shared_ptr<T> curr = to_visit.front();
        to_visit.pop();

        if (curr->isValidSolution(goal.get())) {
            response = curr->getPath();
            break;
        }

        // Get next possible nodes to explore
        std::vector<std::shared_ptr<T>> next_nodes = curr->getNextNodes(goal.get());

        // Enqueue found nodes to visit later only if not opened already
        std::for_each(next_nodes.begin(), next_nodes.end(), [&](std::shared_ptr<T> next_node){
            // Dereferencing in lambda to compare actual objects and not pointers to them
            auto is_match = [&](std::shared_ptr<T> n) {return *(next_node.get()) == *(n.get());};
            if (std::find_if(opened.begin(), opened.end(), is_match) == opened.end()) {
                opened.insert(next_node);
                to_visit.push(std::move(next_node));
            }
        });
    }

    return response;
}


int main()
{
    // std::string example
    std::shared_ptr<Node<std::string>> first = std::make_shared<Node<std::string>>(std::vector<std::string>{"V1", "S1", "S1", "S1", "J1", "S1", "S1", "S1", "V2", "G1", "P1", "P1", "V2", "V2", "P1", "A1", "V2", "M1", "M1", "M1", "", "", "", ""});
    std::shared_ptr<Node<std::string>> goal  = std::make_shared<Node<std::string>>(std::vector<std::string>{"S1", "S1", "S1", "S1", "S1", "S1", "S1", "S1", "V1", "M1", "M1", "M1", "J1", "K1", "G2", "G1", "P1", "A1", "V2", "V2", "P1", "P1", "V2", "V2"});

    //// int example
    //std::shared_ptr<Node<int>> first = std::make_shared<Node<int>>(std::vector<int>{1, 2, 3, 0, 0});
    //std::shared_ptr<Node<int>> goal  = std::make_shared<Node<int>>(std::vector<int>{2, 3, 1, 2, 2});

    std::vector<Step> path = BFS(first, goal);

    first->print();
    std::for_each(path.begin(), path.end(), [](Step& step){ step.print();});
    goal->print();

    return 0;
}
