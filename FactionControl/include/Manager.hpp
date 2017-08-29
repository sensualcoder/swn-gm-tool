#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>

namespace SwnGmTool
{
    template<class T>
    class Manager
    {
        public:
            Manager();
            ~Manager();

            void Add(T);
            void Remove(int);
            T GetItem(int);
            std::vector<T> GetList();
            void ClearList();

        private:
            std::vector<T> List;
    };

    template<class T>
    Manager<T>::Manager()
    {
    }

    template<class T>
    Manager<T>::~Manager()
    {
        this->ClearList();
    }

    template<class T>
    void Manager<T>::Add(T item)
    {
        this->List.push_back(item);
    }

    template<class T>
    void Manager<T>::Remove(int index)
    {
        this->List.erase(this->List.begin() + index);
    }

    template<class T>
    T Manager<T>::GetItem(int index)
    {
        return this->List[index];
    }

    template<class T>
    std::vector<T> Manager<T>::GetList()
    {
        return this->List;
    }

    template<class T>
    void Manager<T>::ClearList()
    {
        this->List.clear();
    }
}

#endif
