#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <array>

using std::cout, std::cin, std::endl;

namespace zen::corex {
    /**
     * @brief A dynamic array container with automatic memory management
     * 
     * @tparam T The type of elements stored in the array
     * 
     * The Array class provides a flexible container that dynamically grows
     * and shrinks as elements are added or removed. It offers:
     * - Dynamic memory management using std::unique_ptr
     * - Construction from std::vector and std::array
     * - Element access with bounds checking
     * - Various manipulation operations (add, remove, reverse, etc.)
     * - Conversion to other container types
     * 
     * Example usage:
     * @code
     * zen::corex::Array<int> numbers;
     * numbers.add(10);
     * numbers.add(20);
     * int value = numbers[0];  // value = 10
     * @endcode
     */
    template <typename T>
    class Array {
        private:
            std::unique_ptr<T[]> data;  ///< Underlying dynamic array storage
            size_t size;                 ///< Current number of elements

        public:
            /**
             * @brief Constructs an empty array
             * 
             * Creates an array with no elements. The internal data pointer
             * is set to nullptr and size is set to 0.
             * 
             * @post data == nullptr && size == 0
             */
            Array() : data(nullptr), size(0) {}

            /**
             * @brief Constructs an array from a std::vector
             * 
             * @param items Vector containing elements to initialize the array with
             * 
             * Creates a new array containing a copy of all elements from the
             * provided vector. The order of elements is preserved.
             * 
             * @complexity O(n) where n is the size of the vector
             */
            Array(const std::vector<T>& items) {
                data = std::make_unique<T[]>(items.size());
                size = items.size();

                for (size_t i = 0; i < items.size(); i++) {
                    data[i] = items[i];
                }
            }

            /**
             * @brief Constructs an array from a std::array with type checking
             * 
             * @tparam A The type of elements in the source array
             * @tparam length The size of the source array
             * @param items std::array containing elements to initialize the array with
             * 
             * Creates a new array from a std::array. This constructor performs
             * compile-time type checking to ensure type safety.
             * 
             * @throws std::invalid_argument if type A doesn't match template type T
             * 
             * @complexity O(n) where n is the array length
             */
            template <typename A, size_t length>
            Array(const std::array<A, length>& items) {
                if constexpr (!std::is_same_v<A, T>) {
                    throw std::invalid_argument("type of array is not match with class type");
                }

                data = std::make_unique<T[]>(length);
                size = length;

                for (size_t i = 0; i < items.size(); i++) {
                    data[i] = items[i];
                }
            }

            /**
             * @brief Move constructor
             * 
             * @param other The array to move resources from
             * 
             * Transfers ownership of the internal data from another array
             * to this newly constructed array. The source array is left in
             * a valid but unspecified state.
             * 
             * @complexity O(1)
             * @noexcept
             */
            Array(Array&& other) noexcept : data(std::move(other.data)), size(other.size) {}

            /**
             * @brief Accesses element at specified index with bounds checking
             * 
             * @param index Position of the element to access (0-based)
             * @return T& Reference to the element at the specified index
             * 
             * Provides non-const access to elements.
             * 
             * @throws std::out_of_range if index is greater than or equal to size
             * 
             * @complexity O(1)
             */
            T& operator[](size_t index) {
                if (index >= size) {
                    throw std::out_of_range("Index out of range");
                }

                return data[index];
            }

            /**
             * @brief Const version of element access operator
             * 
             * @param index Position of the element to access (0-based)
             * @return const T& Const reference to the element at the specified index
             * 
             * Provides const access to elements.
             * 
             * @throws std::out_of_range if index is greater than or equal to size
             * 
             * @complexity O(1)
             */
            const T& operator[](size_t index) const {
                if (index >= size) {
                    throw std::out_of_range("Index out of range");
                }
                
                return data[index];
            }

            /**
             * @brief Copy assignment operator
             * 
             * @param input Source array to copy from
             * @return Array& Reference to this array after assignment
             * 
             * Performs a deep copy of the source array. If the source array
             * is the same as this array, no operation is performed.
             * 
             * @complexity O(n) where n is the size of the input array
             */
            Array& operator=(const Array<T>& input) {
                if (this != &input) {
                    clear();
        
                    for (size_t i = 0; i < input.size; i++) {
                        add(input.data[i]);
                    }
                }

                return *this;
            }

            /**
             * @brief Equality comparison operator
             * 
             * @param input Array to compare with
             * @return true If arrays have the same size and all elements are equal
             * @return false Otherwise
             * 
             * @complexity O(n) where n is the size of the arrays
             */
            bool operator==(const Array<T>& input) const {
                if (input.size != size) {
                    return false;
                }

                for (size_t i = 0; i < input.size; i++) {
                    if (data[i] != input[i]) {
                        return false;
                    }
                }

                return true;
            }

            /**
             * @brief Inequality comparison operator
             * 
             * @param input Array to compare with
             * @return true If arrays differ in size or any element
             * @return false If arrays are identical
             * 
             * @complexity O(n) where n is the size of the arrays
             */
            bool operator!=(const Array<T>& input) const {
                if (input.size != size) {
                    return true;
                }

                for (size_t i = 0; i < input.size; i++) {
                    if (data[i] != input[i]) {
                        return true;
                    }
                }

                return false;      
            }

            /**
             * @brief Concatenation operator
             * 
             * @param input Array to append
             * @return Array New array containing elements from both arrays
             * 
             * Creates a new array that contains all elements from this array
             * followed by all elements from the input array.
             * 
             * @complexity O(n + m) where n and m are sizes of the arrays
             */
            Array operator+(const Array<T>& input) const {
                Array result;

                for (size_t i = 0; i < size; ++i) {
                    result.add(data[i]);
                }
        
                for (size_t i = 0; i < input.size; ++i) {
                    result.add(input.data[i]);
                }
        
                return result;
            }

            /**
             * @brief In-place concatenation operator
             * 
             * @param input Array containing elements to append
             * @return Array& Reference to this array after concatenation
             * 
             * Appends all elements from the input array to the end of this array.
             * 
             * @complexity O(n + m) where n and m are sizes of the arrays
             */
            Array& operator+=(const Array<T>& input) {
                if (input.size == 0) {
                     return *this;
                }
    
                if (size == 0) {
                    data = std::make_unique<T[]>(input.size);
                    size = input.size;

                    for (size_t i = 0; i < size; ++i) {
                        data[i] = input.data[i];
                    }

                    return *this;
                }
    
                size_t newSize = size + input.size;
                auto newData = std::make_unique<T[]>(newSize);
    
                for (size_t i = 0; i < size; ++i) {
                    newData[i] = data[i];
                }
    
                for (size_t i = 0; i < input.size; ++i) {
                    newData[size + i] = input.data[i];
                }
    
                data = std::move(newData);
                size = newSize;
    
                return *this;
            }

            /**
             * @brief Adds an element to the end of the array
             * 
             * @param input Element to add
             * 
             * Appends the specified element to the end of the array. The array
             * size increases by 1.
             * 
             * @complexity O(n) due to reallocation
             */
            void add(const T& input) {
                auto newData = std::make_unique<T[]>(size + 1);
                for (size_t i = 0; i < size; ++i) {
                    newData[i] = data[i];
                }
    
                newData[size] = input;
                data = std::move(newData);
                size++;
            }

            /**
             * @brief Removes the first occurrence of a specified element
             * 
             * @param input Element to remove
             * @throws std::runtime_error if the element is not found in the array
             * 
             * Searches for the first occurrence of the specified element and
             * removes it by shifting all subsequent elements left by one position.
             * The array size decreases by 1.
             * 
             * @complexity O(n)
             */
            void remove(const T& input) {
                bool found = false;

                for (size_t i = 0; i < size; i++) {
                    if (data[i] == input) {
                        found = true;

                        for (size_t j = i; j < size - 1; j++) {
                            data[j] = std::move(data[j + 1]);
                        }

                        size--;
                        break;
                    }   
                }

                if (!found) {
                    throw std::runtime_error("the key is not in the array");
                }
            }

            /**
             * @brief Removes all elements from the array
             * 
             * Resets the array to an empty state. The internal data pointer
             * is set to nullptr and size is set to 0.
             * 
             * @post data == nullptr && size == 0
             * 
             * @complexity O(1)
             */
            void clear() {
                data = nullptr;
                size = 0;
            }

            /**
             * @brief Reverses the order of elements in the array
             * 
             * Rearranges the elements so that the first element becomes the last,
             * the second becomes the second-last, and so on.
             * 
             * @complexity O(n)
             */
            void reverse() {
                auto newData = std::make_unique<T[]>(size);
                for (size_t i = 0; i < size; i++) {
                    newData[i] = data[size - i - 1];
                }

                data = std::move(newData);
            }

            /**
             * @brief Copies elements to a raw array
             * 
             * @param array Destination raw array
             * @param size Number of elements to copy
             * @throws std::logic_error if requested size exceeds array size
             * 
             * Copies the first 'size' elements from this array into the
             * provided raw array. The destination array must have sufficient
             * capacity.
             * 
             * @complexity O(n) where n is the number of elements to copy
             */
            void toArray(T* array, size_t size) const {
                if (size > this->size) {
                    throw std::logic_error("size of array is larger than number of items in this array");
                }

                for (size_t i = 0; i < size; i++) {
                    array[i] = data[i];
                }
            }

            /**
             * @brief Checks if an element exists in the array
             * 
             * @param input Element to search for
             * @return true If the element is found
             * @return false Otherwise
             * 
             * @complexity O(n)
             */
            bool contains(const T& input) const {
                for (size_t i = 0; i < size; i++) {
                    if (data[i] == input) {
                        return true;
                    }
                }

                return false;
            }

            /**
             * @brief Checks if the array is empty
             * 
             * @return true If the array has no elements
             * @return false If the array contains at least one element
             * 
             * @complexity O(1)
             */
            bool isEmpty() const {
                return size == 0;
            }

            /**
             * @brief Counts occurrences of a specific element
             * 
             * @param key Element to count
             * @return size_t Number of occurrences of the element
             * 
             * @complexity O(n)
             */
            size_t count(const T& key) const {
                size_t foundItems = 0;

                for (size_t i = 0; i < size; i++) {
                    if (data[i] == key) {
                        foundItems++;
                    }
                }

                return foundItems;
            }

            /**
             * @brief Returns the current number of elements
             * 
             * @return size_t Size of the array
             * 
             * @complexity O(1)
             */
            size_t getSize() const {
                return size;
            }

            /**
             * @brief Converts the array to a std::vector
             * 
             * @return std::vector<T> Vector containing all elements
             * 
             * Creates a new vector containing a copy of all elements
             * from this array. The order of elements is preserved.
             * 
             * @complexity O(n)
             */
            std::vector<T> toVector() const {
                std::vector<T> items;
                items.reserve(size);
                
                for (size_t i = 0; i < size; i++) {
                    items.push_back(data[i]);
                }

                return items;
            }
    };
}