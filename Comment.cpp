#include <iostream>

struct Item //элемент стека
{
    int value; //поле данных элемента
    Item* previous; //Указатель типа Item на предыдущее звено стека(для связывания элементов)
};

class Stack //класс стека
{
private:
    Item* top; //указатель на корневой эелемент стека(то есть самый первый)
    unsigned int size; // размер стека
    void clear(unsigned int); //закрытый метод для удаление элементов по индексу

public:
    Stack(); //конструктор, который просто все обнуляент
    Stack(Stack*); //конструктор копирования(для создания копии стека)
    void set(int, unsigned int); // метод для вставки элемента в стек
    int get(unsigned int); //для получения элемента по индексу
    ~Stack(); // деструктор обычный
    void push(const int); //добавление нового элемента в конец стека
    int pop(); //получение и удаления последнего элемента стека
    unsigned int getSize(); // возвращает размер стека
    void clear(); //удаляет весь стек
    int back(); // тоже что и pop только он не удаляет элемент
};

void merge(Stack& a, int n); //прототип функции

int main()
{
    int size = 16;
    Stack stack;
    for (int i = 0; i < size; i++)
    {
        stack.push(std::rand() % 10); // тут делаем стек. Заполяем его случайными значениями
    }
    std::cout << "before: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << stack.get(i) << " "; //показываем первоначальное состояние
    }
    merge(stack, size); // вызываем функцию сортировки
    std::cout << "\nafter: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << stack.get(i)<< " "; // показываем уже отсортированный стек
    }

}

void merge(Stack& a, int n) //первый аргумент ссылка на стек, второй размер
{
    int mid = n / 2;
    if (n % 2 == 1)
        mid++;
    int h = 1;
    Stack c;
    for (int i = 0; i < n; i++)
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

Stack::Stack(): top(nullptr), size(0){} // конструктор по умолчанию

Stack::Stack(Stack* baseStack) //конструктор копирования. Указатель принимает ссылку на стэк, из которого копируем
{
    size = baseStack->getSize(); // присвиваем новому стеку размер второго
    top = nullptr; // тут понятно
    if (size) //тут куча всякой херни происходит, которая все и копирует. разбираться в этой не надо.
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

void Stack::push(const int value) // добавление нового элемента в конец стека
{
    Item* newItem = new Item(); //создаем новый элемент и выделяем память
    newItem->previous = top; // присваиваем указателю previous нового элемента адрес на последний элемент стека(связываем элементы)
    newItem->value = value; //ну тут понятно
    top = newItem; //вверх стека становится указатель на новый эелемент
    size++;
}

int Stack::pop() // взятие последнего элемента
{
    Item* lastItem = top; // присваиваем новому указателю адрес последнего элемента
    top = lastItem->previous; //присваиваем вверху предпоследний элемент
    int lastvalue = lastItem->value; //переменной присваиваем значение элемента
    delete lastItem; // удаляем последний элемент стека
    size--;
    return lastvalue; // возвращаем значение последнего элемента
}

int Stack::back()
{
    return top->value; // смотрим что в конце
}

unsigned int Stack::getSize()
{
    return size;
}

void Stack::clear() // тут проходимся сверху вниз и удаляем все
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

void Stack::clear(unsigned int index) //тут удаляем эелементы до определенного элемента
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

int Stack::get(unsigned int index) // возвращаем элемент по индексу
{
    unsigned int size_ = this->size - index;
    Stack temp(this); // создаем копию стека
    int result = 0;
    for (size_t i = 0; i < size_; i++)
    {
        result = temp.pop(); // удаляем элементы до определенного элемента (из копии стека, чтоб оригинал не ломать)
    }
    return result; // ну и возвращаем

}

void Stack::set(int value, unsigned int index) // value это значение которое надо вставить
{
    Stack temp(this); //делаем копию
    int size_ = size - 1; // тут всякие манипуляции происходят которые сложно объяснить
    unsigned int firstsize = size - index;
    unsigned int secondsize = temp.size - firstsize + 1;
    clear(firstsize); // удаляем оригинальный стек до определенного элемента
    push(value); // вставляем новый элемент
    for (int i = secondsize; i <= size_; i++)
    {
        this->push(temp.get(i)); // а тут заполняем конец стека элементами из копии стека, чтобы восстановить то, что удалилось
    }
}

Stack::~Stack()
{
    clear();
}
