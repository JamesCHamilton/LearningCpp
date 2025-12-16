#include <iostream>
#include <string>
using namespace std;

template <typename T>
class MyVector{

private:
    T* data;
    int size;
    int capacity;

public:
    MyVector(){
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    ~MyVector(){
        delete[] data;
    }

    void push_back(const T& value){
        if(size == capacity){
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for(int i = 0; i < size; ++i){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }

    void pop_back(){
        if(size > 0){
            --size;
        }
    }

    T& operator[](int index){
        if(index < 0 || index >= size){
            throw out_of_range("Index out of range");
        }

        return data[index];
    }

    int getSize() const{
        return size;
    }

    int getCapacity() const{
        return capacity;
    }
};

int main(){

    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "Size: " << vec.getSize() << endl;
    cout << "Capacity: " << vec.getCapacity() << endl;
    cout << "Size before pop" << vec.getSize() << endl;

    for( int i = 0; i < vec.getSize(); i++){
        cout << "Element at index " << i << ": " << vec[i] << endl;
    }

    vec.pop_back();

    cout << "Size after pop: " << vec.getSize() << endl;
    cout << "Capacity after pop: " << vec.getCapacity() << endl;

    for (int i = 0; i < vec.getSize(); ++i) {
        cout << "Element at index " << i << ": " << vec[i] << endl;
    }

    return 0;
}