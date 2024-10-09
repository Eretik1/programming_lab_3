#include <iostream>

template <typename T>
class element1
{
public:
    T data;
    element1<T> *early = NULL, *next = NULL;
    element1(T value)
    {
        data = value;
        //std::cout << "+ " << data << std::endl;
    }
    element1() {
        //std::cout << "+ " << data << std::endl;
    }
    ~element1()
    {
        //std::cout << "-" << data << std::endl;
        if (next){
            delete next;
        }

    }
};

template <typename T>
class d_l_list
{
public:
    int size = 0;
    element1<T> *first = NULL, *last = NULL;
    d_l_list(T value)
    {
    }
    d_l_list() {}
    d_l_list(T value, d_l_list &&copy)
    {   
        size = copy.size;
        element1<T> *el = new element1<T>;
        element1<T> *el1 = copy.first;
        if(copy.first){
            first = el;
            el->data = el1->data;
            while (el1->next){
                element1<T> *el2 = new element1<T>;
                el->next = el2;
                el2->data = el1->next->data;
                el2->early = el;
                el = el2;
                el1 = el1->next;
            }
            last = el;
        }
    }
    ~d_l_list()
    {
        if (first){
            delete first;
        }
    }
    void push_back(int x)
    {
        element1<T> *newel = new element1<T>;
        newel->data = x;
        if (last)
        {
            last->next = newel;
            newel->early = last;
        }
        else
        {
            first = newel;
        }
        last = newel;
        size++;
        // std::cout << "+" << x << std::endl;
    }
    element1<T> *operator[](int index)
    {
        element1<T> *el;
        if (index >= 0 && index < size)
        {
            el = first;
            for (int i = 1; i <= index; i++)
            {
                el = el->next;
            }
        }
        return el;
    }
    d_l_list &operator=(const d_l_list &copy)
    {
        
        size = copy.size;
        element1<T> *el = new element1<T>;
        element1<T> *el1 = copy.first;
        if(copy.first){
            first = el;
            el->data = el1->data;
            while (el1->next){
                element1<T> *el2 = new element1<T>;
                el->next = el2;
                el2->data = el1->next->data;
                el2->early = el;
                el = el2;
                el1 = el1->next;
            }
            last = el;
        }
        return *this;
    }
    void print()
    {
        if (first)
        {
            element1<T> *el = first;
            std::cout << el->data << " ";
            while (el->next)
            {
                el = el->next;
                std::cout << el->data << " ";
            }
            std::cout << std::endl;
        }
    }
    void del(int index)
    {
        if (index == 0)
        {
            if (first)
            {
                element1<T> *el = first;
                if (first->next)
                {
                    first->next->early = NULL;
                }
                first = first->next;
                delete el;
            }
            size--;
        }
        else if (index == size - 1)
        {
            if (last)
            {
                element1<T> *el = last;
                if (last->early)
                {
                    last->early->next = NULL;
                }
                last = last->early;
                delete el;
            }
            size--;
        }
        else if (index > 0 && index < size)
        {
            element1<T> *el = first;
            for (int i = 1; i <= index; i++)
            {
                el = el->next;
            }
            el->early->next = el->next;
            el->next->early = el->early;
            el->next = NULL;
            delete el;
            size--;
        }
    }
    void insert(int index, int x)
    {
        if (index >= 0 && index < size)
        {
            element1<T> *el = first;
            for (int i = 1; i <= index; i++)
            {
                el = el->next;
            }
            element1<T> *newel = new element1<T>;
            newel->data = x;
            newel->early = el->early;
            newel->next = el;
            if (el->early)
            {
                el->early->next = newel;
            }
            el->early = newel;
            size++;
            if (index == 0)
            {
                first = newel;
            }
        }
    }
};

template <typename T>
class interator1{
    public:
    d_l_list<T> list;
    element1<T>* el;
    interator1(d_l_list<T> &con){
        list = con;
        el = list.first;
    }
    element1<T>* begin(){
        return list.first;
    }
    element1<T>* end(){
        return list.last;
    }
    interator1<T>& operator++(int){
        if(el->next){
            el = el->next;
        }
        return *this;
    }
        interator1<T>& operator--(int){
        if(el->early){
            el = el->early;
        }
        return *this;
    }
    T get(){
        return el->data;
    }
};

template <typename T>
class element2
{
public:
    T data;
    element2 *next = NULL;
    element2(T value)
    {
        data = value;
    }
    element2() {}
    ~element2()
    {
        // std::cout << "-" << data << std::endl;
        if (next)
        {
            delete next;
        }
    }
};

template <typename T>
class s_l_list
{
public:
    int size = 0;
    element2<T> *first = NULL;
    s_l_list(T value)
    {
    }
    s_l_list() {}
    s_l_list(T value, s_l_list &&copy)
    {
        size = copy.size;
        element2<T> *el = new element2<T>;
        element2<T> *el1 = copy.first;
        if(copy.first){
            first = el;
            el->data = el1->data;
            while (el1->next){
                element2<T> *el2 = new element2<T>;
                el->next = el2;
                el2->data = el1->next->data;
                el = el2;
                el1 = el1->next;
            }
        }
    }
    ~s_l_list()
    {
        if (first)
        {
            delete first;
        }
    }
    void push_back(T x)
    {
        if (first)
        {
            element2<T> *el = first;
            while (el->next)
            {
                el = el->next;
            }
            el->next = new element2<T>;
            el->next->data = x;
        }
        else
        {
            first = new element2<T>;
            first->data = x;
        }
        size++;
    }
    void print()
    {
        if (first)
        {
            element2<T> *el = first;
            std::cout << el->data << " ";
            while (el->next)
            {
                el = el->next;
                std::cout << el->data << " ";
            }
            std::cout << std::endl;
        }
    }
    element2<T> *operator[](int index)
    {
        element2<T> *el;
        if (index >= 0 && index < size)
        {
            el = first;
            for (int i = 1; i <= index; i++)
            {
                el = el->next;
            }
        }
        return el;
    }
    s_l_list &operator=(const s_l_list &copy)
    {
        size = copy.size;
        element2<T> *el = new element2<T>;
        element2<T> *el1 = copy.first;
        if(copy.first){
            first = el;
            el->data = el1->data;
            while (el1->next){
                element2<T> *el2 = new element2<T>;
                el->next = el2;
                el2->data = el1->next->data;
                el = el2;
                el1 = el1->next;
            }
        }
        return *this;
    }
    void del(int index)
    {
        if (index == 0 && first)
        {
            element2<T> *el = first;
            if (first->next)
            {
                first = first->next;
            }
            else
            {
                first = NULL;
            }
            el->next = NULL;
            delete el;
            size--;
        }
        else if (first && index >= 0 && index < size)
        {
            element2<T> *el = first;
            for (int i = 1; i < index; i++)
            {
                if (el->next)
                {
                    el = el->next;
                }
            }
            if (el->next)
            {
                element2<T> *el1 = el->next;
                el->next = el->next->next;
                el1->next = NULL;
                size--;
                delete el1;
            }
        }
    }
    void insert(int index, T x)
    {
        if (index == 0)
        {
            element2<T> *el = first;
            first = new element2<T>;
            first->data = x;
            first->next = el;
            size++;
            return;
        }
        if (index > 0 && index < size && first)
        {
            element2<T> *el = first;
            for (int i = 1; i < index; i++)
            {
                if (el->next)
                {
                    el = el->next;
                }
            }
            element2<T> *el1 = el->next;
            el->next = new element2<T>;
            el->next->data = x;
            size++;
            el->next->next = el1;
        }
    }
};

template <typename T>
class my_vector
{
public:
    T *data;
    int size = 0, capacity;
    my_vector(T value, int capacity = 20)
    {
        data = new T[20];
    }
    my_vector(int capacity = 20)
    {
        data = new T[20];
    }
    my_vector(T value,  my_vector &&copy)
    {
        T *newData = new T[copy.capacity];
        for(int i = 0; i < copy.size; i++){
            newData[i] = copy.data[i];
        }
        data = newData;
        size = copy.size;
        capacity = copy.capacity;
    }
    ~my_vector()
    {
        delete[] data;
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    void expansion()
    {
        capacity += capacity / 2;
        T *newdata = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            newdata[i] = data[i];
        }
        delete[] data;
        data = newdata;
    }
    void push_back(T x)
    {
        if (size < capacity)
        {
            data[size] = x;
        }
        else
        {
            this->expansion();
            data[size] = x;
        }
        size++;
    }
    int operator[](int index)
    {
        return data[index];
    }
    my_vector &operator=(const my_vector &copy)
    {
        T *newData = new T[copy.capacity];
        for(int i = 0; i < copy.size; i++){
            newData[i] = copy.data[i];
        }
        data = newData;
        size = copy.size;
        capacity = copy.capacity;
        return *this;
    }
    void del(int index)
    {
        for (int i = index; i < size; i++)
        {
            if (i + 1 < size)
            {
                data[i] = data[i + 1];
            }
        }
        size--;
    }
    void insert(int index, T x)
    {
        if (index >= 0 && index < size)
        {
            if (size + 1 > capacity)
            {
                this->expansion();
            }
            for (int i = size - 1; i >= index; i--)
            {
                data[i + 1] = data[i];
            }
            data[index] = x;
            size++;
        }
    }
};

/*/
template<typename T>
class iterator{
    public:
    T list;
    int type;
    iterator(T obj){
        list = obj;
        type = test(typeid(list).name());
    }
    int test(const char * typeName){
        const char name1[] {"8d_l_list"};
        const char name2[] {"8s_l_list"};
        const char name3[] {"9my_vector"};
        for(int i = 0; i < sizeof(name1)/sizeof(name1[0]) - 1; i++){
            if(name1[i] != typeName[i]){
                break;
            }
            if(i == sizeof(name1)/sizeof(name1[0]) - 2 ){
                return 1;
            }
        }
        for(int i = 0; i < sizeof(name2)/sizeof(name2[0]) - 1; i++){
            if(name2[i] != typeName[i]){
                break;
            }
            if(i == sizeof(name2)/sizeof(name2[0]) - 2 ){
                return 2;
            }
        }
        for(int i = 0; i < sizeof(name3)/sizeof(name3[0]) - 1; i++){
            if(name3[i] != typeName[i]){
                break;
            }
            if(i == sizeof(name3)/sizeof(name3[0]) - 2 ){
                return 3;
            }
        }        
        return 0;
    }
    void* begin(){
        void* res;
        if(type == 1 || type == 2){
            try{
                res = list.first;
            }
            catch(){
                std::cout << "+" << std::endl;
            }
        }
        if(type == 3){
            res = list.data[0];
        }
        return res;
    }
};
//*/



int main1()
{
    d_l_list<int> l;
    l.push_back(0);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);
    l.push_back(8);
    l.push_back(9);
    l.print();
    std::cout << l.size << std::endl;
    l.del(2);
    l.del(3);
    l.del(4);
    l.print();
    l.insert(0, 10);
    l.print();
    l.insert(4, 20);
    l.print();
    l.push_back(30);
    l.print();
    std::cout << std::endl;
    return 0;
}

int main2()
{
    s_l_list<int> l;
    l.push_back(0);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);
    l.push_back(8);
    l.push_back(9);
    l.print();
    std::cout << l.size << std::endl;
    l.del(2);
    l.del(3);
    l.del(4);
    l.print();
    l.insert(0, 10);
    l.print();
    l.insert(4, 20);
    l.print();
    l.push_back(30);
    l.print();
    std::cout << std::endl;
    return 0;
}

int main3()
{
    my_vector<int> l;
    l.push_back(0);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);
    l.push_back(8);
    l.push_back(9);
    l.print();
    std::cout << l.size << std::endl;
    l.del(2);
    l.del(3);
    l.del(4);
    l.print();
    l.insert(0, 10);
    l.print();
    l.insert(4, 20);
    l.print();
    l.push_back(30);
    l.print();
    std::cout << std::endl;
    return 0;
}

int main()
{
    main1();
    main2();
    main3();
    return 0;
}
