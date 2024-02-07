

template <typename val, typename val2>
class Node
{
public:
    val first;
    val2 second;
    Node<val,val2>* next_node;

    Node();
    explicit Node(val key, val2 v);
};

template <typename val, typename val2>
inline Node<val,val2>::Node()
{
    next_node = nullptr;
}

template <typename val, typename val2>
inline Node<val,val2>::Node(val key, val2 v)
{
    first = key;
    second = v;
    next_node = nullptr;
}

template <typename var_type, typename var_type2>
class Linked_list
{
    Node<var_type,var_type2>* head ;
    int list_size = 0;

public:
    Linked_list();
    void insertNode(var_type key, var_type2 data);
    bool is_empty();
    bool exists(var_type var);
    void deleteNode(var_type key);
    var_type2& find(var_type key);
    int size();
};


template<typename var_type, typename var_type2>
inline Linked_list<var_type, var_type2>::Linked_list()
{
    head = nullptr;
}

template<typename var_type, typename var_type2>
inline void Linked_list<var_type,var_type2>::insertNode(var_type key, var_type2 data)
{
    auto* temp = new Node<var_type,var_type2>(key, data);
    if (head == nullptr)
    {
        head = temp;
        list_size++;
        return;
    }

    Node<var_type,var_type2>* current = head;
    Node<var_type,var_type2>* tmp = nullptr;

    do
    {
        tmp = current;
        current = current->next_node;
    } while (current != nullptr);

    tmp->next_node = new Node<var_type,var_type2>;
    list_size++;
}

template<typename var_type, typename var_type2>
inline bool Linked_list<var_type,var_type2>::is_empty()
{
    return (head == nullptr);
}

template<typename var_type, typename var_type2>
inline bool Linked_list<var_type,var_type2>::exists(var_type var)
{
    Node<var_type,var_type2>* current = head;
    while (current != nullptr)
    {
        if (current->first == var) return true;
    }
    return false;
}


template<typename var_type, typename var_type2>
inline void Linked_list<var_type,var_type2>::deleteNode(var_type key)
{
    Node<var_type, var_type2>* current = head;
    Node<var_type, var_type2>* prev = nullptr;
    bool found = false;

    if (current == nullptr) {
        return;
    }

    do {
        if (current->first == key) {
            found = true;
            break;
        }

        prev = current;
        current = current->next_node;
    } while (current != nullptr);

    if (current == head) {
        prev = head;
        head = current->next_node;
        delete prev;
        return;
    }

    if (current->next_node == nullptr) {
        prev->next_node = nullptr;
        delete current;
        return;
    }

    prev->next_node = current->next_node;
    delete current;

    list_size--;
}

template<typename var_type, typename var_type2>
var_type2& Linked_list<var_type,var_type2>::find(var_type key)
{
    Node<var_type,var_type2>* itr = head;
    if (exists(key))
    {
        while (itr != nullptr)
        {
            if (itr->first == key)return itr->second;
            itr = itr->next_node;
        }
    }
    var_type2* b = new var_type2;
    return head->second;
}


template<typename var_type, typename var_type2>
int Linked_list<var_type,var_type2>::size()
{
    return list_size;
}


