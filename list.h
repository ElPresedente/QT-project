#ifndef LIST_H
#define LIST_H
#include <cstddef>

template<typename T>
class List
{
private:
    struct Node;
public:
    List(){
        head = nullptr;
        tail = nullptr;
        m_length = 0;
    };
    ~List(){
        Node *node;
        Node *currnode = head;
        while(currnode != nullptr){
            node = currnode;
            currnode = node->nextNode;
            delete node;
        }
    };

    class Iterator{
        friend class List;
    public:
        Iterator() : m_node(nullptr) { };

        Iterator& operator++(){
            m_node = m_node->nextNode;
            return *this;
        }
        Iterator& operator++(int){
            m_node = m_node->nextNode;
            return *this;
        }

        operator T(){
            return m_node->data;
        }

        T& operator=(Iterator iterator){
            return iterator.m_node.data;
        }

        bool operator==(const Iterator& iterator){
            //if(this == &iterator){
            //    return true;
            //}
            return m_node == iterator.m_node;
        }

        bool operator!=(const Iterator& iterator){
            return !(operator==(iterator));
        }

        bool operator==(const Node& node){
            if(this->m_node == node){
                return true;
            }
            return m_node == node;
        }

        bool operator!=(const Node& node){
            return m_node != node;
        }

    private:
        Node* m_node;
        Iterator(Node* node){
            m_node = node;
        };
    };

    void push_back(const T& item){
        if(m_length == 0){
            Node *node = new Node();
            node->data = item;
            node->nextNode = nullptr;
            head = tail = node;
        }
        else if(m_length == 1){
            Node *node = new Node();
            node->data = item;
            node->nextNode = nullptr;
            head->nextNode = node;
            tail = node;
        }
        else{
            Node *node = new Node();
            node->data = item;
            node->nextNode = nullptr;
            tail->nextNode = node;
            tail = node;
        }
        m_length++;
    }
    void push_front(const T& item){
        if(m_length == 0){
            Node *node = new Node();
            node->data = item;
            node->nextNode = nullptr;
            tail = node;
            head = node;
        }
        else if(m_length == 1){
            Node *node = new Node();
            node->data = item;
            node->nextNode = tail;
            head = node;
        }
        else{
            Node *node = new Node();
            node->data = item;
            node->nextNode = head;
            head = node;
        }
        m_length++;
    }

    void append(const T& item){
        push_back(item);
    };

    void remove(Iterator iterator){
        if(m_length == 0){
            return;
        }
        else if(m_length == 1 && iterator.m_node == head){
            delete head;
            head = tail = nullptr;
            return;
        }

        if(iterator == begin()){
            Node* nextnode = iterator.m_node->nextNode;
            delete head;
            head = nextnode;
        }
        else if(iterator == end()){
            List<T>::Iterator i = begin();
            for(; i.m_node->nextNode != iterator.m_node; i++);
            delete tail;
            tail = i.m_node;
        }
        else{
            List<T>::Iterator i = begin();
            for(; i.m_node->nextNode != iterator.m_node; i++);
            i.m_node->nextNode = iterator.m_node->nextNode;
            delete iterator.m_node;
        }
        m_length--;
    }

    void removeAt(int itemNum){
        if(m_length < itemNum){
            return;
        }
        auto i = begin();
        for(int j = 0; j<itemNum; j++, i++);
        remove(i);
        return;
    }

    T at(int itemNum){
        if(m_length < itemNum){
            return;
        }
        auto i = begin();
        for(int j = 0; j<itemNum; j++, i++);
        return i.m_node->data;
    }

    Iterator begin(){
        return Iterator(head);
    }
    Iterator end()  {
        return Iterator(tail);
    }

    size_t length(){
        return m_length;
    }
    size_t size(){
        return m_length;
    };

private:
    struct Node{
        T data;
        Node* nextNode;
    };
    Node* head;
    Node* tail;
    size_t m_length;
};

#endif // LIST_H
