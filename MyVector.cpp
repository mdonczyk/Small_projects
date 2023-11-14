/* my implementation of vector
Implement vector (similar to std::vector). It should grow dynamically as needed. It should store int (or use templates) and implement:
    a. push_back operation
    b. copy/move constructors. Copy assigment operator.
    c. make it work with range loop/algorithms. How to sort it from greatest to smallest using std::sort 
*/

#include <algorithm>
#include <cstring>
#include <iostream>

template <typename T>
class MyVector{
    public:
        // default constructor
        MyVector(size_t capacity=2) : 
                capacity_(capacity) {
            std::cout<<"Constructor called"<<std::endl;
            vec_ = new T[capacity_];
        }

        // destructor
        ~MyVector() {
            std::cout<<"Destructor called"<<std::endl;
            delete[] vec_;
        }

        // copy constructor (deep copy)
        MyVector(const MyVector& other_vec) :
                size_(other_vec.size_),
                capacity_(other_vec.capacity_) {
            std::cout<<"Copy Constructor called"<<std::endl;
            vec_ = new T[size_];
            memcpy(vec_, other_vec.vec_, sizeof(T)*size_);
        }

        //move constructor
         MyVector(MyVector&& other_vec) noexcept :
                size_(std::move(other_vec.size_)),
                capacity_(std::move(other_vec.capacity_)) {
            std::cout<<"Move Constructor called"<<std::endl;
            vec_ = std::move(other_vec.vec_);
            other_vec.vec_ = nullptr;
        }

        // copy assignment
        MyVector& operator= (const MyVector& other_vec) {
            std::cout<<"Copy Assignment called"<<std::endl;
            // detect self assignment
            if (&other_vec != this) {
                delete[] vec_;
                size_ = other_vec.size_;
                capacity_ = other_vec.capacity_;
                vec_ = new T[size_];
                memcpy(vec_, other_vec.vec_, sizeof(T)*size_);
            }
            return *this;
        }

        //move assignment
        MyVector& operator= (MyVector&& other_vec) noexcept {
            std::cout<<"Move Assignment called"<<std::endl;
            // detect self assignment
            if (&other_vec != this) {
                delete[] vec_;
                size_ = std::move(other_vec.size_);
                capacity_ = std::move(other_vec.capacity_);
                vec_ = std::move(other_vec.vec_);
                other_vec.vec_ = nullptr;
            }
            return *this;
        }

        void push_back(const T& val) noexcept {
            if (size_ == capacity_) {
               resize();
            }
            vec_[size_] = val;
            size_++;
        }

        constexpr size_t size() const noexcept {
            return size_;
        }

        constexpr size_t capacity() const noexcept {
            return capacity_;
        }

        // for accessing MyVector elements:
        T& operator[] (size_t index) { return vec_[index]; };
        const T& operator[] (size_t index) const { return vec_[index]; };

        // used for for range loops:
        constexpr T* begin() const noexcept {
            return vec_;
        }

        constexpr T* end() const noexcept {
            return vec_ + size();
        }

     private:
        size_t size_{0};
        size_t capacity_{0};
        T* vec_{nullptr};

        void resize() {
            capacity_*=2;
            T* temp_vec = new T[capacity_];
            memcpy(temp_vec, vec_, sizeof(T)*size_);
            delete[] vec_;
            vec_ = temp_vec;
        }
        
        friend std::ostream& operator<< (std::ostream& os, const MyVector& my_vec) {
            for (auto const& element : my_vec) {
                os << element << " ";
            }
            return os;
        }
};

int main() {
    MyVector<int> vector1;
    vector1.push_back(1);
    vector1.push_back(2);
    vector1.push_back(3);
    vector1.push_back(4);

    std::cout<< vector1 << std::endl;

    vector1[2] = 8;

    std::cout<< vector1 << std::endl;

    MyVector<int> vector2(vector1);
    MyVector<int> vector3;

    vector2 = vector1;

    vector3.push_back(9);
    vector3.push_back(6);
    vector3.push_back(5);
    vector3.push_back(7);

    vector2 = std::move(vector3);
    MyVector<int> vector4(std::move(vector2));

    std::cout << vector4 << std::endl;

    // sort from greatest to smallest
    std::sort(vector4.begin(), vector4.end(), std::greater<int>());

    std::cout << vector4 << std::endl;

    return 0;
}