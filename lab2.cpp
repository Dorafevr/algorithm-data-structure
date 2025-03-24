 //как оценивать сложность алгоритма?
//сколько операции выполнится в зависимости от кол-ва элементов в массиве
//время и кол-во операции пропорциональны
#include <iostream>
#include <array>
#include <vector>
#include <span>
#include <algorithm>
#include <chrono>

struct SearchResult {
    bool isElementFound;
    size_t foundIndex;
};
SearchResult linearSearch(std::span<int> arr, int elementToFind)
{
    for (size_t i = 0; i < arr.size(); i++) 
    {
        if (arr[i]== elementToFind)  
        { 
            return { true , i};
        }
    }
    return { false, 0 };
}
SearchResult binarySearch(std::span<int> arr, int elementToFind)
{
    const SearchResult elementNotFoundResult = {0, false};

    if (arr.empty())
    {
        return elementNotFoundResult;
    }
    if (arr[0] > elementToFind)
    {
        return elementNotFoundResult;
    }

    size_t indexLow = 0;
    size_t indexHigh = arr.size() - 1;

    while (indexLow <= indexHigh)
    {
        size_t currentIndex = (indexHigh - indexLow) / 2 + indexLow;
        int currentElement = arr[currentIndex];

        if (elementToFind > currentElement)
        {
            indexLow = currentIndex + 1;
        }
        else if (elementToFind < currentElement)
        {
            indexHigh = currentIndex - 1;
        }
        else  
        {
            return { true, currentIndex};
        }
    }

    return elementNotFoundResult;
}

struct Node
{
    int value;
    Node* left;
    Node* right;
};

struct BinarySearchTree
{
    Node* root;
};

Node* find(BinarySearchTree tree, int value)
{
    Node* currentNode = tree.root;
    while (currentNode != nullptr)
    {
        if (currentNode->value == value)
        {
            
            break;
        }
        else if (value < currentNode->value)
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
    }

    return currentNode;
}

Node* addNode(BinarySearchTree* tree, int value)
{
    Node* node = new Node;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;

    if (tree->root == nullptr)
    {
        tree->root = node;
        return node;
    }

    Node* currentNode = tree->root;
    while (true)
    {
        if (value > currentNode->value)
        {
            if (currentNode->right != nullptr)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode->right = node;
                break;
            }
        }
        else
        {
            if (currentNode->left != nullptr)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode->left = node;
                break;
            }
        }
    }
    return node;
}
void test(std::span<int> arr, int target) {
    auto measureTime = [](auto searchFunction, std::span<int> arr, int target, const std::string& name) {
          auto start = std::chrono::high_resolution_clock::now();
          SearchResult result = searchFunction(arr, target);
          auto end = std::chrono::high_resolution_clock::now();
          
          if (result.isElementFound) {
              std::cout  <<"\n"<< name << ": Element found at index" << result.foundIndex
                        << " in " << std::chrono::duration<double>(end - start).count();
          } else {
              std::cout <<"\n"<< name << ": Element not found in "
                        << std::chrono::duration<double>(end - start).count();
          }
      };
  
      measureTime(linearSearch, arr, target, "Linear Search");
      measureTime(binarySearch, arr, target, "Binary Search");
   
  }
  
int main()
{
    std::vector<int> sortedArray = {1, 3, 5, 7, 9, 11, 13, 15};
    std::vector<int> reverseSortedArray = {15, 13, 11, 9, 7, 5, 3, 1};
    std::vector<int> randomArray = {7, 1, 9, 3, 5, 15, 11, 13};

    std::cout << " sorted array:";
    test (sortedArray, 7);

    std::cout << "\nreverse array:";
    test(reverseSortedArray, 11);

    std::cout << "\nrandom array:";
    test(randomArray, 15);
 
    std::array arr = {1, 5, 7, 10, 15, 32, 89};
    SearchResult result = binarySearch(arr, 0);

    if (result.isElementFound)
    {
        std::cout << "\nElement found at index " << result.foundIndex;
    }
    else
    {
        std::cout << "\nElement not found.";
    }

    std::array<int, 6> values{1, 5, 3, 4, 9, 7};
    BinarySearchTree tree;
    tree.root = nullptr;

    for (size_t i = 0; i < values.size(); i++)
    {
        int currentValue = values[i];
        addNode(&tree, currentValue);
    }

    Node* node = find(tree, 5);
    if (node == nullptr)
    {
        std::cout << "Node not found";
    }
    if (node->left != nullptr)
    {
        std::cout << node->left->value;
    }
    if (node->right != nullptr)
    {
        std::cout << node->right->value;
    }

    return 0;
}
