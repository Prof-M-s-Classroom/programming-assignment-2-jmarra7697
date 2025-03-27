#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "Node.h"
#include "Story.h"

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;
    std::unordered_map<int, Node<T>*> eventMap;

public:
    // TODO: Constructor
    GameDecisionTree() : root(nullptr) {}

    // Destructor
    ~GameDecisionTree() {
        deleteTree(root);
    }

    // Helper function to delete entire tree if needed
    void deleteTree(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        std::ifstream file(filename);
        if (!std::filesystem::exists(filename)) {
            std::cerr << "File " << filename << " does not exist." << std::endl;
            return;
        }
        if (!file.is_open()) {
            std::cerr << "File " << filename << " could not be opened." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream iss(line);
            std::string eventStr, descStr, leftStr, rightStr;

            // parses the line using the specified delimiter
            std::getline(iss, eventStr, delimiter);
            std::getline(iss, descStr, delimiter);
            std::getline(iss, leftStr, delimiter);
            std::getline(iss, rightStr);

            // Converts strings into proper types
            int eventNum = std::stoi(eventStr);
            int leftEventNum = std::stoi(leftStr);
            int rightEventNum = (rightStr.empty()) ? -1 : std::stoi(rightStr);

            T storyData(descStr, eventNum, leftEventNum, rightEventNum);
            Node<T>* newNode = new Node<T>(storyData);

            // stores index in event map
            eventMap[eventNum] = newNode;

            // if this is first node, then set the root to NewNode<T>
            if (root == nullptr) {
                root = new Node<T>();
            }
        }
        connectNodes();
        }

    // helper function that will connect nodes based on certain event numbers
    void connectNodes() {
        for (auto& pair : eventMap) {
            Node<T>* currentNode = pair.second;
            // connects left child
            if (currentNode->data.leftEventNumber != -1) {
                currentNode->left = eventMap[currentNode->data.leftEventNumber];
            }
            if (currentNode->data.rightEventNumber != -1) {
                currentNode->right = eventMap[currentNode->data.rightEventNumber];
            }
        }
    }
    // Function to start the game and traverse the tree based on user input
    void playGame() {
        // if there is no root, then the game ends by default
        if (root == nullptr) {
            std::cerr << "Game is empty." << std::endl;
            return;
        }
        Node<T>* currentNode = root;
        while (currentNode != nullptr) {
            // display current active event
            std::cout << "\n" << currentNode->data.description << std::endl;

            // checks if this is a state where the story ends and there are no more paths
            if (currentNode->left == nullptr && currentNode->right == nullptr) {
                std::cout << "Your story has ended. Try and find more paths in the other choices!" << std::endl;
                break;
            }

            // allows user to make their path choice only if left and right node are not null
            int choice = -1;
            if (currentNode-> left != nullptr && currentNode->right != nullptr) {
                while (choice != 1 && choice != 2) {
                    std::cout << "Enter choice 1 or 2: ";
                    std::cin >> choice;
                }
                // moves to whatever path is chosen
                currentNode = (choice == 1) ? currentNode->left : currentNode->right;
                // if only the left path is available
            } else if (currentNode->left != nullptr) {
                currentNode = currentNode->left;
                // if only the right path is available
            } else if (currentNode->right != nullptr) {
                currentNode = currentNode->right;
            }

        }

    }
};

#endif // GAMEDECISIONTREE_H
