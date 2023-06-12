#include "MagicalContainer.hpp"
#include <stdexcept>

using namespace std;
namespace ariel
{    
    void MagicalContainer::addElement(int elem)
    {
        elements.push_back(elem);
        MagicalContainer::sortElements();
    }
    

    const std::vector<int> &MagicalContainer::getElements() const
    {
        return elements;
    }
    int MagicalContainer::size() const
    {
        return elements.size();
    }
    int MagicalContainer::getSize() const
    {
        return elements.size();
    }
    void MagicalContainer::removeElement(int elem)
    {
        bool tmp = false;
        for (auto it = elements.begin(); it != elements.end(); ++it)
        {
            
            if (*it == elem)
            {
                elements.erase(it);
                tmp = true;
                break;
            }
        }
        if(tmp == false){
                throw std::runtime_error("Element not found in container");
            
        }
    }

}