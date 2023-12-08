#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ranges>
#include <string_view>
#include <thread>
#include <numeric>


using namespace std;

class Node
{
    Node * leftNode;
    Node * rightNode;
    

    Node(){}

    public:
    string name;
    Node(string name) : name(name) { leftNode = nullptr; rightNode = nullptr;}    
    void setLeftNode(Node *lNode);
    void setRightNode(Node *rNode);
    Node* getNextNode(char direction);
    Node* getThis();
    void printNodes();
};

void Node::setLeftNode(Node *lNode)
{
    if(nullptr == lNode)
        cout << "Trying to set null left node to: " << this->name << endl;
    if(nullptr == leftNode)
    {
        leftNode = lNode;
    }
    else
        cout << "Node: " << leftNode->name << " already set." << endl;
}

void Node::setRightNode(Node *rNode)
{
    if(nullptr == rNode)
        cout << "Trying to set null right node to: " << this->name << endl;
    if(nullptr == rightNode)
    {
        rightNode = rNode;
    }
    else
        cout << "Node: " << rightNode->name << " already set." << endl;
}

Node* Node::getNextNode(char direction)
{
    if('L' == direction)
        return leftNode;
    if('R' == direction)
        return rightNode;

    cout << "invalid direction" << endl;

    return nullptr;
}

Node* Node::getThis()
{
    return this;
}

void Node::printNodes()
{
    if(nullptr != leftNode)
        cout << "Node: " << name << " Left Node: " << leftNode->name << endl;
    if(nullptr != rightNode)
        cout << "Node: " << name << " Right Node: " << rightNode->name << endl;
}

array<bool,6> finished = {false, false, false, false, false, false};
array<int,6> ghostSteps{0};


int main()
{
    vector<Node> map;
    vector<Node>::iterator mapIter;
    string directionString;

    std::ifstream ifs;
    std::string str;

/* //test
    directionString = "LLR";
    map.emplace_back(Node("AAA"));
    map.emplace_back(Node("BBB"));
    map.emplace_back(Node("ZZZ"));

   
    mapIter = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "AAA"; });
//    if(nullptr != mapIter)
    {
       vector<Node>::iterator tempNode = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "BBB"; }); 
       mapIter->setLeftNode(tempNode->getThis());
       mapIter->setRightNode(tempNode->getThis());
    }

    mapIter = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "BBB"; });
//    if(nullptr != mapIter)
    {
       vector<Node>::iterator tempNode = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "AAA"; }); 
       mapIter->setLeftNode(tempNode->getThis());
       tempNode = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "ZZZ"; }); 
       mapIter->setRightNode(tempNode->getThis());
    }

    mapIter = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "ZZZ"; });
//    if(nullptr != mapIter)
    {
       vector<Node>::iterator tempNode = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "ZZZ"; }); 
       mapIter->setLeftNode(tempNode->getThis());
       tempNode = find_if(map.begin(), map.end(), [](Node temp){ return temp.name == "ZZZ"; }); 
       mapIter->setRightNode(tempNode->getThis());
    }

    for(Node node : map)
    {
        node.printNodes();
    }
*/

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day8.txt", std::ios::in);
    
    if(ifs)
    {
        getline(ifs, directionString);
        while(!ifs.eof())
        { 
            getline(ifs, str);
            if(!str.empty())
            {
                //first three chars are the name
                //vector<Node>::iterator tempNode;
                string nodeName = str.substr(0,3);
                map.emplace_back(Node(nodeName));
            }
        }
        ifs.clear();
        ifs.seekg(0);
        getline(ifs, str);
        int idx = 0;
        while(!ifs.eof())
        {            
            getline(ifs, str); 
            if(!str.empty())
            {
                int pos = str.find('(');
                vector<Node>::iterator tempNode;
                string nodeName = str.substr(pos+1, 3);
                tempNode = find_if(map.begin(), map.end(), [&](Node temp){ return temp.name == nodeName; }); 
                map.at(idx).setLeftNode(tempNode->getThis());
                nodeName = str.substr(pos+6, 3);
                tempNode = find_if(map.begin(), map.end(), [&](Node temp){ return temp.name == nodeName; }); 
                map.at(idx).setRightNode(tempNode->getThis());
                idx++;
            }
        }
        vector<Node>::iterator startNode = map.begin();
        
        bool allPathsFound = false;
//        int totalSteps = 0;
/*
        while(startNode != map.end())
        {
            startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
            if(startNode == map.end())
            {
              //  allPathsFound = true;
                break;
            }
            startNode++;
            totalSteps++;
        }
*/


    array<Node*,6> startNodes;
        startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
        startNodes[0] = startNode->getThis();
        startNode++;
        startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
        startNodes[1] = startNode->getThis();
        startNode++;
        startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
        startNodes[2] = startNode->getThis();
        startNode++;
        startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
        startNodes[3] = startNode->getThis();
        startNode++;
        startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
        startNodes[4] = startNode->getThis();
        startNode++;
        startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
        startNodes[5] = startNode->getThis();

    auto iterateNodes = [&](Node* startNode,  int pathIdx) 
    {
        bool isEndFound = false;
        Node* nextNode = startNode;
        
        while(!isEndFound)
        {
            for(char direction : directionString)
            {
                nextNode = nextNode->getNextNode(direction);
                ghostSteps[pathIdx]++;
                if(nextNode->name[2] == 'Z')
                {
                    isEndFound = true;
                    break;
                }
            }
        }
    };

    for(int i = 0; i < 6; i++)
        iterateNodes(startNodes[i],i);

    for(auto steps : ghostSteps)
        cout << steps << endl;

    long long totalSteps = lcm(ghostSteps[0], ghostSteps[1]);
    for(int i = 2; i < ghostSteps.size(); i++)
    {
        totalSteps = lcm(totalSteps, ghostSteps[i]);
    }



/*
        bool isEndFound = false;
        while(!isEndFound)
        {
            for(char direction : directionString)
            {
            //    for(int i = 0; i < 6; i++)
            //        startNodes[i] = iterateNodes(startNodes[i],direction,i);
                totalSteps++;

                isEndFound = true;
                for(bool done : finished)
                {
                    if(!done)
                    {
                        isEndFound = false;
                        break;
                    }
                }
                if(isEndFound)
                    break;
                for(bool& done : finished)
                    done = false;
            }
        }

*/
/*
        while(!allPathsFound)
        {
            startNode = find_if(startNode, map.end(), [](Node temp){ return temp.name[2] == 'A'; });
            if(startNode == map.end())
            {
                allPathsFound = true;
                break;
            }
            bool isEndFound = false;
            int steps = 0;
            Node* nextNode = startNode->getThis();
            while(!isEndFound)
            {
                for(char direction : directionString)
                {
                    nextNode = nextNode->getNextNode(direction);
                    steps++;
                    if(nextNode->name[2] == 'Z')
                    {
                        isEndFound = true;
                        break;
                    }
                }
            }
            totalSteps += steps;
            startNode++;
        }
*/
        cout << "Number of steps: " << totalSteps << endl;
      //  cout << "Found: " << mapIter->name << endl;
    }
    return 0;
}