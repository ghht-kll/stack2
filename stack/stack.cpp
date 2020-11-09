#include <iostream>

struct Item
{
    int value;
    Item* previous;
};

class Stack
{
private:
    Item* top;
    unsigned int size;
    void clear(unsigned int);
    
public:
    Stack();
    Stack(Stack*);
    void set(int, unsigned int);
    int get(unsigned int);
    ~Stack();
    void push(const int);
    int pop();
    unsigned int getSize();
    void clear();
    void sort(int N);
    int back();
};

void merge(Stack& a, int n);

int main()
{
    int size = 16;
    Stack stack;
    for (size_t i = 0; i < size; i++)
    {
        stack.push(std::rand() % 10);
    }
    std::cout << "before: ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << stack.get(i) << " ";
    }
    merge(stack, size);
    std::cout << "\nafter: ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << stack.get(i)<< " ";
    }
    
}

void merge(Stack& a, int n)
{
    int mid = n / 2; 
    if (n % 2 == 1)
        mid++;
    int h = 1; 
    Stack c;
    for (size_t i = 0; i < n; i++)
        c.push(0);
  
    int step;
    while (h < n)
    {
        step = h;
        int i = 0;   
        int j = mid; 
        int k = 0;  
        while (step <= mid)
        {
            while ((i < step) && (j < n) && (j < (mid + step)))
            {
                if (a.get(i) < a.get(j))
                {
                    c.set(a.get(i), k);
                    i++; k++;
                }
                else {
                    c.set(a.get(j), k);
                    j++; k++;
                }
            }
            while (i < step)
            { 
                c.set(a.get(i), k);
                i++; k++;
            }
            while ((j < (mid + step)) && (j < n))
            {  
                c.set(a.get(j), k);
                j++; k++;
            }
            step = step + h; 
        }
        h = h * 2;
        for (i = 0; i < n; i++)
            a.set(c.get(i), i);
    }
}

Stack::Stack(): top(nullptr), size(0){}

Stack::Stack(Stack* baseStack)
{
    size = baseStack->getSize();
    top = nullptr;
    if (size)
    {
        Item* itemFromSource = baseStack->top;
        Item* itemPrevious = new Item();
        itemPrevious->previous = nullptr;
        itemPrevious->value = itemFromSource->value;
        top = itemPrevious;
        for (unsigned int i = size - 1; i > 0; --i)
        {
            itemFromSource = itemFromSource->previous;
            Item* itemCurrent = new Item();
            itemCurrent->previous = nullptr;
            itemCurrent->value = itemFromSource->value;
            itemPrevious->previous = itemCurrent;;
            itemPrevious = itemCurrent;
        }
    }
}

void Stack::push(const int value)
{
    Item* newItem = new Item();
    newItem->previous = top;
    newItem->value = value;
    top = newItem;
    size++;
}

int Stack::pop()
{
    Item* lastItem = top;
    top = lastItem->previous;
    int lastvalue = lastItem->value;
    delete lastItem;
    size--;
    return lastvalue;
}

int Stack::back()
{
    return top->value;
}

unsigned int Stack::getSize()
{
    return size;
}

void Stack::clear()
{
    Item* currentItem;
    for (unsigned int i = size; i > 0; --i)
    {
        currentItem = top;
        top = currentItem->previous;
        delete currentItem;
    }
    size = 0;
}

void Stack::clear(unsigned int index)
{
    Item* currentItem;
    for (unsigned int i = 0; i < index; i++)
    {
        currentItem = top;
        top = currentItem->previous;
        delete currentItem;
    }
    this->size -= index;
}

int Stack::get(unsigned int index)
{
    unsigned int size_ = this->size - index;
    Stack temp(this);
    int result = 0;
    for (size_t i = 0; i < size_; i++)
    {
        result = temp.pop();
    }
    return result;

}

void Stack::set(int value, unsigned int index)
{
    Stack temp(this);
    int sss = size - 1;
    unsigned int firstsize = size - index;
    unsigned int secondsize = temp.size - firstsize + 1;
    clear(firstsize);
    push(value);
    for (size_t i = secondsize; i <= sss; i++)
    {
        this->push(temp.get(i));
    }
}

void Stack::sort(int N)
{
    int s, f, d, i, j, g, k, p;
    s = 1;

    do
    {
        s = 1 - s;
        d = 1;
        f = 1;

        if (s == 0)
        {
           
            i = 1;
            j = N;
            k = N + 1;
            g = 2 * N;
        }
        else
        {
           
            i = N + 1;
            j = 2 * N;
            k = 1;
            g = N;
        }
        while (i != j)//
        {
           
            // if(K[i]<K[j])
            if (get(i) > get(j))
            {
               
                // R[k] = R[j];
                set(k, get(j));
                k = k + d;
                j = j - 1;

                // if (!(K[j+1]<=K[j]))
                if (get(j + 1) <= get(j))
                {
                   
                }
                else
                {
                   
                    do
                    {
                        // R[k]=R[i];
                        set(k, get(i));
                        k = k + d;
                        i = i + 1;
                    }
                    // while(!K[i-1]>=K[i]);
                    while (get(i - 1) < get(i));

                    f = 0;
                    d = -d;
                    p = k;
                    k = g;
                    g = p;
                }
            }
            else
            {
               
                // R[k]=R[i];
                set(k, get(i));
                k = k + d;
                i = i + 1;
                // if(K[i-1]<=K[i])
                if (get(i - 1) <= get(i))
                {
                   
                }
                else
                {
                   
                    do
                    {
                        // R[k] = R[j];
                        set(k, get(j));
                        k = k + d;
                        j = j - 1;
                    }
                    // while(K[j+1]>=K[j]);
                    while (get(j + 1) < get(j));
                    f = 0;
                    d = -d;
                    p = k;
                    k = g;
                    g = p;

                }
            }
        }
        //R[k]=R[i];
        set(k, get(i));
    } while (f != 1);


    if (s == 0)
    {
       
        for (int i = 1; i <= N; i++)
        {
           
            // R[i] = R[i+n];
            set(i, get(i + N));
        }

    }

    int size_1 = size;
    for (int i = 1; i <= size_1; i++)
    {
        if (i <= size / 2)
        {
           
           // Add(Del());
            set(pop(),i);
        }
        else
        {
           
            pop();
        }
    }
}
Stack::~Stack()
{
    clear();
}
