#include <iostream>
#include <ctime>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <type_traits>

// Enumeration for searching values in the list
enum FiLa
{
	FIRST, // First occurrence
	LAST   // Last occurrence
};

// Enumeration for sorting the list
enum AsDe
{
	ASCENDING, // Ascending order
	DESCENDING  // Descending order
};

// Enumeration for finding min/max values
enum MiMa
{
	MIN, // Find minimum value
	MAX   // Find maximum value
};

// Enumeration for list output format
enum VeHo
{
	VERTICAL, // Vertical output
	HORIZONTAL // Horizontal output
};

// Enumeration for finding average value
enum FSS
{
	Fast_Slow, // Fast-slow pointer method
	SizeFM      // Size-based average calculation
};

template <typename T>
class List
{
public:
	List(); // Constructor
	~List(); // Destructor

    // Method prototypes
    void push_back(T data);
    void pop_back();
    void clear();
    void push_front(T data);
    void pop_front();
    void insert(int index, T data);
    void removeAt(int index);
    void reverse();
    void primDisplay(VeHo type);
    void infDisplay();
    void DisplayInfo();
    int FindByValueINDEX(const T value, FiLa find);
    void DeleteByValue(const T value, FiLa find);
    void RandomFill(T start, T end, bool repeat);
    void Initialize_Fill(int size, T value);
    void Sort(AsDe type);
    void Mesh();
    T MinMax(MiMa type);
    void SaveData_F(std::string path);
    void Clear_F(std::string path);
    void Remove_F(std::string path);
    void ImportData_F(std::string path);
    void DeleteAll(T value);
    void Cutter(int startIndex, int lastIndex);
    void Swap(int firstIndex, int secondIndex);
    T GetDataByIndex(int index);

    int& GetSize() { return this->Size; } // Size getter
    bool isEmpty() { return Size == 0; } // Check if list is empty
    bool isThere(T value) // Check element existence
    {
        if (isEmpty())
        {
            throw std::out_of_range("List is empty! Cannot find element in empty list.\n");
        }

        Node* current = head;

        for (int i = 0; i < this->Size; i++)
        {
            if (current->data == value)
            {
                return true;
            }
            current = current->pNext;
        }
        return false;
    }

    T& operator [] (const int index); // Subscript operator overload

    // Copy constructor
    List(const List<T>& other) : Size(0), head(nullptr), tail(nullptr)
    {
        if (other.head == nullptr)
        {
            return;
        }

        Node* current = other.head;

        for (int i = 0; i < other.Size; i++)
        {
            push_back(current->data);
            current = current->pNext;
        }
    }

private:
    class Node
    {
    public:
        T data;
        Node* pNext;
        Node* pPrev;
        Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };
public:
    class Iterator
    {
    public:
        Iterator(Node* ptr) : current(ptr) {}
        T& operator*()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            return current->data;
        }

        T* operator->()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            return &(current->data);
        }

        Iterator& operator++()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            current = current->pNext;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            current = current->pPrev;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }

    private:
        Node* current;
    };
    class const_Iterator
    {
    public:
        const_Iterator(Node* ptr) : current(ptr) {}

        const T& operator*()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            return current->data;
        }

        const T* operator->()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            return &(current->data);
        }

        const_Iterator& operator++()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            current = current->pNext;
            return *this;
        }

        const_Iterator operator++(int)
        {
            const_Iterator temp = *this;
            ++(*this);
            return temp;
        }

        const_Iterator& operator--()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            current = current->pPrev;
            return *this;
        }

        const_Iterator operator--(int)
        {
            const_Iterator temp = *this;
            --(*this);
            return temp;
        }

        const bool operator==(const const_Iterator& other) const { return current == other.current; }
        const bool operator!=(const const_Iterator& other) const { return current != other.current; }

    private:
        Node* current;
    };
    class reverse_Iterator
    {
    public:
        reverse_Iterator(Node* ptr) : current(ptr) {}

        T& operator*()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            return current->data;
        }

        T* operator->()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            return &(current->data);
        }

        reverse_Iterator& operator++()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            current = current->pPrev;
            return *this;
        }

        reverse_Iterator operator++(int)
        {
            reverse_Iterator temp = *this;
            --(*this);
            return temp;
        }

        reverse_Iterator& operator--()
        {
            if (current == nullptr)
            {
                throw std::out_of_range("Iterator out of bounds!");
            }
            current = current->pNext;
            return *this;
        }

        reverse_Iterator operator--(int)
        {
            reverse_Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const reverse_Iterator& other) const { return current == other.current; }
        bool operator!=(const reverse_Iterator& other) const { return current != other.current; }

    private:
        Node* current;
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    const_Iterator cbegin() { return const_Iterator(head); }
    const_Iterator cend() { return const_Iterator(nullptr); }

    reverse_Iterator rbegin() { return reverse_Iterator(tail); }
    reverse_Iterator rend() { return reverse_Iterator(nullptr); }

    Node* GetHead() { return this->head; }
    Node* GetTail() { return this->tail; }

    Node* GetMiddle(FSS type)
    {
        if (isEmpty())
        {
            throw std::out_of_range("List is empty! Cannot find element.\n");
        }

        Node* current = this->head;

        if (type == Fast_Slow)
        {
            Node* fast = this->head;

            while (fast != nullptr && fast->pNext != nullptr)
            {
                current = current->pNext;
                fast = fast->pNext->pNext;
            }
        }
        else
        {
            int TempSize = Size / 2;

            for (int i = 0; i < TempSize; i++)
            {
                current = current->pNext;
            }
        }

        return current;
    }

    Node* FindByValueADRESS(const T value, FiLa find)
    {
        if (isEmpty())
        {
            throw std::out_of_range("List is empty! Cannot find element.\n");
        }
        if (find == FIRST)
        {
            Node* current = head;

            for (int i = 0; i < this->Size; i++)
            {
                if (current->data == value)
                {
                    return current;
                }
                current = current->pNext;
            }
            return nullptr;
        }
        else if (find == LAST)
        {
            Node* current = tail;

            for (int i = this->Size; i >= 0; i--)
            {
                if (current->data == value)
                {
                    return current;
                }
                current = current->pPrev;
            }
            return nullptr;
        }
    }

    void Split(int& otherSIZE, Node* otherHEAD, Node* otherTAIL)
    {
        if (otherSIZE <= 0) { return; }

        if (isEmpty())
        {
            head = otherHEAD;
            tail = otherTAIL;
        }
        else
        {
            tail->pNext = otherHEAD;
            otherHEAD->pPrev = tail;
            tail = otherTAIL;
        }

        Size += otherSIZE;
        otherSIZE = 0;
    }
private:
    int Size;
    Node* head;
    Node* tail;

protected:
    Node* GetElByIndex(int index)
    {
        if (isEmpty())
        {
            throw std::out_of_range("List is empty! Cannot find element.\n");
        }
        else if (index >= Size || index < 0)
        {
            throw std::out_of_range("Invalid index!\n");
        }
        Node* current;

        if (index <= Size / 2)
        {
            current = this->head;

            for (int i = 0; i < Size; i++)
            {
                if (i == index)
                {
                    return current;
                }
                current = current->pNext;
            }
        }
        else
        {
            current = this->tail;

            for (int i = Size - 1; i >= 0; i--)
            {
                if (i == index)
                {
                    return current;
                }
                current = current->pPrev;
            }
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////***

int main()
{
    setlocale(LC_ALL, "ru"); // Set locale for Russian characters
    srand(unsigned(time(NULL))); // Initialize random generator

    List<int> myList;
    std::string path = "MyFile.txt";
    std::ifstream fin;
    fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    // Initialize and fill list
    myList.Initialize_Fill(10, 0);
    myList.RandomFill(0, 10, true);

    

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////***

template<typename T>
List<T>::List()
{
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::removeAt(int index)
{
    if (index == 0)
    {
        pop_front();
        return;
    }
    else if (index == Size - 1)
    {
        pop_back();
        return;
    }

    Node* toDelete = GetElByIndex(index);
    toDelete->pPrev->pNext = toDelete->pNext;
    toDelete->pNext->pPrev = toDelete->pPrev;

    delete toDelete;
    Size--;
}

template<typename T>
void List<T>::reverse()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot reverse.\n");
    }
    Node* current = head;
    Node* temp = nullptr;

    tail = head;

    while (current != nullptr)
    {
        temp = current->pPrev;
        current->pPrev = current->pNext;
        current->pNext = temp;

        current = current->pPrev;
    }

    if (temp != nullptr)
    {
        head = temp->pPrev;
    }
}

template<typename T>
void List<T>::primDisplay(VeHo type)
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot display.\n");
    }
    Node* current = this->head;

    if (type == HORIZONTAL)
    {
        for (int i = 0; i < this->Size; i++)
        {
            std::cout << current->data;
            (i == this->Size - 1) ? std::cout << ". " : std::cout << ", ";
            current = current->pNext;
        }
        std::cout << std::endl;
    }
    else if (type == VERTICAL)
    {
        for (int i = 0; i < this->Size; i++)
        {
            std::cout << "Index: " << i << "\tElement : " << current->data << std::endl;
            current = current->pNext;
        }
        std::cout << std::endl;
    }
}

template<typename T>
void List<T>::infDisplay()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot display.\n");
    }
    if (Size == 1)
    {
        std::cout << "Index: 0" << "\tElement : " << this->head << "\tADRESS: " << &this->head << "\tWhat: head, tail";
    }
    else
    {
        Node* current = this->head;

        for (int i = 0; i < this->Size; i++)
        {
            std::cout << "Index: " << i << "\tElement : " << current->data << "\tADRESS: " << &current->data << "\tWhat: ";

            if (current == head)
            {
                std::cout << "head" << std::endl;
            }
            else if (current == tail)
            {
                std::cout << "tail" << std::endl;
            }
            else
            {
                std::cout << "regular element" << std::endl;
            }
            current = current->pNext;
        }
    }
    std::cout << std::endl;
}

template<typename T>
void List<T>::DisplayInfo()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot display info.\n");
    }
    else
    {
        std::cout << "List element count: " << this->Size << std::endl << std::endl;
        std::cout << "Head address: " << this->head << std::endl;
        std::cout << "Head value: " << this->head->data << std::endl << std::endl;
        std::cout << "Tail address: " << this->tail << std::endl;
        std::cout << "Tail value: " << this->tail->data << std::endl << std::endl;
    }
}

template<typename T>
int List<T>::FindByValueINDEX(const T value, FiLa find)
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot find element.\n");
    }
    if (find == FIRST)
    {
        Node* current = head;
        for (int i = 0; i < this->Size; i++)
        {
            if (current->data == value)
            {
                return i;
            }
            current = current->pNext;
        }
        return -1;
    }
    else if (find == LAST)
    {
        Node* current = tail;

        for (int i = this->Size - 1; i >= 0; i--)
        {
            if (current->data == value)
            {
                return i;
            }
            current = current->pPrev;
        }
        return -1;
    }
}

template<typename T>
void List<T>::DeleteByValue(const T value, FiLa find)
{
    if (find == FIRST)
    {
        int index = FindByValueINDEX(value, FIRST);
        if (index == -1)
        {
            throw std::out_of_range("Element not found in list.\n");
        }
        else if (index == 0)
        {
            pop_front();
        }
        else if (index == this->Size - 1)
        {
            pop_back();
        }
        else
        {
            Node* current = GetElByIndex(index);
            current->pPrev->pNext = current->pNext;
            current->pNext->pPrev = current->pPrev;
            delete current;
            Size--;
        }
    }
    else if (find == LAST)
    {
        int index = FindByValueINDEX(value, LAST);

        if (index == -1)
        {
            throw std::out_of_range("Element not found in list");
        }
        else if (index == 0)
        {
            pop_front();
        }
        else if (index == this->Size - 1)
        {
            pop_back();
        }
        else
        {
            Node* current = GetElByIndex(index);
            current->pPrev->pNext = current->pNext;
            current->pNext->pPrev = current->pPrev;
            delete current;
            Size--;
        }
    }
}

template<typename T>
void List<T>::RandomFill(T start, T end, bool repeat)
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot fill.\n");
    }
    if (start > end)
    {
        T temp = start;
        start = end;
        end = temp;
    }

    if (!repeat)
    {
        if (end - start + 1 < this->Size)
        {
            throw std::out_of_range("Insufficient range for unique values.\n");
        }
        else
        {
            Node* current = this->head;
            T* arr = new T[this->Size];

            for (int i = 0; i < this->Size; i++)
            {
                arr[i] = current->data;
                current = current->pNext;
            }

            current = this->head;

            for (int i = 0; i < this->Size; )
            {
                bool have = false;
                int random = start + rand() % (end - start + 1);
                for (int y = 0; y < i; y++)
                {
                    if (arr[y] == random)
                    {
                        have = true;
                        break;
                    }
                }
                if (!have)
                {
                    current->data = random;
                    arr[i] = random;
                    current = current->pNext;
                    i++;
                }
            }
            delete[] arr;
        }
    }
    else
    {
        Node* current = this->head;

        for (int i = 0; i < Size; i++)
        {
            current->data = start + rand() % (end - start + 1);
            current = current->pNext;
        }
    }
}

template<typename T>
void List<T>::Initialize_Fill(int size, T value)
{
    for (int i = 0; i < size; i++)
    {
        push_back(value);
    }
}

template<typename T>
void List<T>::Sort(AsDe type)
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot sort.\n");
    }
    Node* current = this->head;
    int unsorted_limit = Size - 1;
    int counter;

    if (type == ASCENDING)
    {
        do
        {
            counter = 0;
            current = this->head;

            for (int i = 0; i < unsorted_limit; i++)
            {
                if (current->data > current->pNext->data)
                {
                    T temp = current->data;
                    current->data = current->pNext->data;
                    current->pNext->data = temp;

                    counter++;
                }
                current = current->pNext;
            }
            if (counter != 0) { unsorted_limit--; }

        } while (counter != 0);
    }

    else if (type == DESCENDING)
    {
        do
        {
            counter = 0;
            current = this->head;

            for (int i = 0; i < unsorted_limit; i++)
            {
                if (current->data < current->pNext->data)
                {
                    T temp = current->data;
                    current->data = current->pNext->data;
                    current->pNext->data = temp;

                    counter++;
                }
                current = current->pNext;
            }
            if (counter != 0) { unsorted_limit--; }

        } while (counter != 0);
    }
}

template<typename T>
void List<T>::Mesh()
{
    if (Size <= 1) return;
    Node** arr = new Node * [Size];
    Node* current = head;

    for (int i = 0; i < Size; i++)
    {
        arr[i] = current;
        current = current->pNext;
    }

    for (int i = Size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(arr[i]->data, arr[j]->data);
    }

    delete[] arr;
}

template<typename T>
T List<T>::MinMax(MiMa type)
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot find min/max.\n");
    }
    Node* current = this->head;

    if (type == MIN)
    {
        T minValue = current->data;

        for (int i = 0; i < this->Size; i++)
        {
            if (current->data < minValue)
            {
                minValue = current->data;
            }
            current = current->pNext;
        }
        return minValue;
    }
    else if (type == MAX)
    {
        T maxValue = current->data;

        for (int i = 0; i < this->Size; i++)
        {
            if (current->data > maxValue)
            {
                maxValue = current->data;
            }
            current = current->pNext;
        }
        return maxValue;
    }
}

template<typename T>
void List<T>::SaveData_F(std::string path)
{
    std::ofstream fout;
    try
    {
        fout.open(path, std::ofstream::app);

        if (!fout.is_open())
        {
            throw std::ifstream::failure("Failed to open file.");
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    Node* current = this->head;

    for (int i = 0; i < this->Size; i++)
    {
        fout << current->data << std::endl;
        current = current->pNext;
    }

    fout.close();
}

template<typename T>
void List<T>::Clear_F(std::string path)
{
    std::ofstream fout;
    try
    {
        fout.open(path, std::ofstream::out | std::ofstream::trunc);

        if (!fout.is_open())
        {
            throw std::ifstream::failure("Failed to open file.");
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    fout.close();
}

template<typename T>
void List<T>::Remove_F(std::string path)
{
    const char* INNERPATH = path.c_str();
    try
    {
        remove(INNERPATH);
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    catch (const std::ifstream::failure& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::cerr << "Error code: " << ex.code() << std::endl;
    }
}

template<typename T>
void List<T>::ImportData_F(std::string path)
{
    std::ifstream fin;
    try
    {
        fin.open(path, std::ifstream::in);

        if (!fin.is_open())
        {
            throw std::ios_base::failure("Failed to open file.");
        }

        T value;

        while (fin >> value)
        {
            if (std::is_same<T, decltype(value)>::value)
            {
                push_back(value);
            }
            else
            {
                std::cerr << "Error: Data type mismatch!" << std::endl;
                break;
            }
        }
    }
    catch (const std::ios_base::failure& ex)
    {
        std::cerr << "IO Error: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    fin.close();
}

template<typename T>
void List<T>::DeleteAll(T value)
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->pNext;
        if (current->data == value)
        {
            if (current == head)
            {
                pop_front();
            }
            else if (current == tail)
            {
                pop_back();
            }
            else
            {
                current->pPrev->pNext = current->pNext;
                current->pNext->pPrev = current->pPrev;
                delete current;
                Size--;
            }
        }
        current = next;
    }
}

template<typename T>
void List<T>::Cutter(int startIndex, int lastIndex)
{
    if (startIndex < 0 || lastIndex >= Size || startIndex > lastIndex)
    {
        throw std::out_of_range("Invalid indices for slicing.\n");
    }
    Node* current = this->head;
    int counter = this->Size - 1;

    for (int i = 0; i < startIndex; i++)
    {
        current = current->pNext;
        pop_front();
    }

    this->head = current;
    current = this->tail;

    for (; counter > lastIndex; counter--)
    {
        current = current->pPrev;
        pop_back();
    }

    this->tail = current;
}

template<typename T>
void List<T>::Swap(int firstIndex, int secondIndex)
{
    Node* current = GetElByIndex(firstIndex);
    Node* current2 = GetElByIndex(secondIndex);
    T temp = current->data;
    current->data = current2->data;
    current2->data = temp;
}

template<typename T>
T List<T>::GetDataByIndex(int index)
{
    return GetElByIndex(index)->data;
}

template<typename T>
void List<T>::insert(int index, T data)
{
    if (index == 0)
    {
        push_front(data);
        return;
    }
    else if (index == Size)
    {
        push_back(data);
        return;
    }
    Node* previous = GetElByIndex(index - 1);

    Node* newNode = new Node(data, previous->pNext, previous);
    previous->pNext = newNode;
    newNode->pNext->pPrev = newNode;

    Size++;
}

template<typename T>
void List<T>::pop_front()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot pop.\n");
    }
    else
    {
        if (this->Size == 1)
        {
            pop_back();
        }
        else
        {
            this->head = head->pNext;
            Node* toDelete = head->pPrev;
            head->pPrev = nullptr;
            toDelete->pNext = nullptr;

            delete toDelete;
            Size--;
        }
    }
}

template<typename T>
void List<T>::push_front(T data)
{
    Node* newNode = new Node(data);
    if (isEmpty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->pNext = head;
        head->pPrev = newNode;
        head = newNode;
    }
    Size++;
}

template<typename T>
void List<T>::pop_back()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty! Cannot pop.\n");
    }
    else
    {
        Node* toDelete = this->tail;
        this->tail = toDelete->pPrev;
        toDelete->pNext = nullptr;
        toDelete->pPrev = nullptr;

        delete toDelete;
        Size--;
    }
}

template<typename T>
void List<T>::clear()
{
    if (!isEmpty())
    {
        while (!isEmpty())
        {
            pop_back();
        }
        this->head = nullptr;
        this->tail = nullptr;
    }
}

template<typename T>
void List<T>::push_back(T data)
{
    if (this->head == nullptr)
    {
        Node* newNode = new Node(data);
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        Node* newNode = new Node(data, nullptr, this->tail);
        Node* oldNode = newNode->pPrev;
        oldNode->pNext = newNode;

        this->tail = newNode;
    }

    Size++;
}

template<typename T>
T& List<T>::operator[](const int index)
{
    return GetElByIndex(index)->data;
}
