#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#if defined(ESP32) || defined(ESP8266)
#include <functional>
#endif

template <typename T>
class ArrayList {
public:
    class Iterator {
    public:
        Iterator(T* ptr)
            : m_Ptr(ptr) {}

        Iterator operator++() {
            ++m_Ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++m_Ptr;
            return tmp;
        }

        Iterator operator--() {
            --m_Ptr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --m_Ptr;
            return tmp;
        }

        Iterator operator+(const int& n) {
            return Iterator(m_Ptr + n);
        }

        Iterator operator-(const int& n) {
            return Iterator(m_Ptr - n);
        }

        Iterator& operator+=(const int& n) {
            m_Ptr += n;
            return *this;
        }

        Iterator& operator-=(const int& n) {
            m_Ptr -= n;
            return *this;
        }

        bool operator==(const Iterator& other) {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const Iterator& other) const {
            return m_Ptr != other.m_Ptr;
        }

        T& operator[](const int& n) {
            return *(m_Ptr + n);
        }

        T& operator*() const {
            return *m_Ptr;
        }

        T* operator->() const {
            return m_Ptr;
        }

    private:
        T* m_Ptr;
    };

    /**
     * @brief Create empty ArrayList.
     *
     */
    ArrayList()
        : m_Data(NULL),
        m_Size(0),
        m_Capacity(0) {
        _reallocate(2);
    }

    /**
     * @brief Create ArrayList from another ArrayList.
     *
     * @param other is the ArrayList to copy from.
     */
    ArrayList(const ArrayList& other)
        : ArrayList() {
        if (_reallocate(other.m_Capacity)) {
            m_Size = other.m_Size;
            const size_t size = m_Size * sizeof(T);
            memcpy(m_Data, other.m_Data, size);
        }
    }

    /**
     * @brief Create ArrayList from another ArrayList.
     *
     * @param other is the ArrayList to move from.
     */
    ArrayList(ArrayList&& other) noexcept
        : ArrayList() {
        _swap(other);
    }

    /**
     * @brief Create ArrayList from an array.
     *
     * @param arr is the array to copy from.
     * @param len is the length of the array.
     */
    ArrayList(T arr[], size_t len)
        : m_Data(NULL),
        m_Size(0),
        m_Capacity(0) {
        if (_reallocate(len + len / 2)) {
            for (size_t i = 0; i < len; i++) {
                add(arr[i]);
            }
        }
    }

    /**
     * @brief Create ArrayList from a variadic arguments.
     *
     * @tparam Args must be the same type as T.
     * @param args is the variadic arguments.
     */
    template <typename... Args>
    ArrayList(Args... args)
        : ArrayList() {
        if (_reallocate(sizeof...(args) + sizeof...(args) / 2)) {
            int dummy[] = { (add(args), 0)... };
            (void)dummy;
        }
    }

    ~ArrayList() {
        _deallocate();
    }

    /**
     * @brief Add an element to the end of the ArrayList.
     *
     * @param element is the element to add.
     * @return true if the element was added successfully.
     */
    bool add(const T& element) {
        if (m_Size >= m_Capacity) {
            if (!_reallocate(m_Capacity + m_Capacity / 2)) return false;
        }
        m_Data[m_Size] = element;
        m_Size++;
        return true;
    }

    /**
     * @brief Add an element to the end of the ArrayList.
     *
     * @param element is the element to add.
     * @return true if the element was added successfully.
     */
    bool add(T&& element) {
        if (m_Size >= m_Capacity) {
            if (!_reallocate(m_Capacity + m_Capacity / 2)) return false;
        }
        m_Data[m_Size] = element;
        m_Size++;
        return true;
    }

    /**
     * @brief Add from another ArrayList to the end of this ArrayList.
     *
     * @param other is the ArrayList to add from.
     * @return true if the element was added successfully.
     */
    bool addAll(const ArrayList& other) {
        if (m_Size + other.m_Size >= m_Capacity) {
            if (!_reallocate(m_Capacity + other.m_Capacity)) return false;
        }
        for (size_t i = 0; i < other.m_Size; i++) {
            m_Data[m_Size + i] = other.m_Data[i];
        }
        m_Size += other.m_Size;
        return true;
    }

    /**
     * @brief Resize the ArrayList to a new size.
     *
     * @param newSize is the new size of the ArrayList.
     */
    void resize(const size_t& newSize) {
        _reallocate(newSize);
    }

    /**
     * @brief Remove an element from the ArrayList.
     *
     * @param element is the element to remove.
     */
    void remove(const T& element) {
        removeAt(indexOf(element));
    }

    /**
     * @brief Remove an element from the ArrayList.
     *
     * @param index is the index of the element to remove.
     */
    void removeAt(size_t index) {
        if (index < 0) return;
        m_Size--;
        for (size_t i = index; i < m_Size; i++) {
            m_Data[i] = m_Data[i + 1];
        }
    }

#if defined(ESP32) || defined(ESP8266)
    /**
     * @brief Remove elements from the ArrayList that match the predicate.
     *
     * @param predicate is the predicate to match.
     */
    void removeIf(std::function<bool(T)> predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) {
                removeAt(i);
                i--;
            }
        }
    }
#else
    /**
     * @brief Remove elements from the ArrayList that match the predicate.
     *
     * @param predicate is the predicate to match.
     */
    template <typename Callable>
    void removeIf(Callable predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) {
                removeAt(i);
                i--;
            }
        }
    }
#endif

    /**
     * @brief Check if the ArrayList contains an element.
     *
     * @param element is the element to check for.
     * @return true if the element is in the ArrayList.
     */
    bool contains(const T& element) {
        for (size_t i = 0; i < m_Size; i++) {
            if (m_Data[i] == element) return true;
        }
        return false;
    }

#if defined(ESP32) || defined(ESP8266)
    /**
     * @brief Check if the ArrayList contains an element that matches the predicate.
     *
     * @param predicate is the predicate to match.
     * @return true if the element is in the ArrayList.
     */
    bool contains(std::function<bool(T)> predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) return true;
        }
        return false;
    }
#else
    /**
     * @brief Check if the ArrayList contains an element that matches the predicate.
     *
     * @param predicate is the predicate to match.
     * @return true if the element is in the ArrayList.
     */
    template <typename Callable>
    bool contains(Callable predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) return true;
        }
        return false;
    }
#endif

    /**
     * @brief Get the index of the first element that matches the element.
     *
     * @param element is the element to match.
     * @return the index of the first element that matches the element.
     */
    int indexOf(const T& element) {
        for (size_t i = 0; i < m_Size; i++) {
            if (m_Data[i] == element) return i;
        }
        return -1;
    }

#if defined(ESP32) || defined(ESP8266)
    /**
     * @brief Get the index of the first element that matches the predicate.
     *
     * @param predicate is the predicate to match.
     * @return the index of the first element that matches the predicate.
     */
    int indexOf(std::function<bool(T)> predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) return i;
        }
        return -1;
    }

    void clear() {
        _deallocate();
        _reallocate(2);
    }
#else
    /**
     * @brief Get the index of the first element that matches the predicate.
     *
     * @param predicate is the predicate to match.
     * @return the index of the first element that matches the predicate.
     */
    template <typename Callable>
    int indexOf(Callable predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) return i;
        }
        return -1;
    }

    void clear() {
        _deallocate();
        _reallocate(2);
    }
#endif

    /**
     * @brief Get the element at the specified index.
     * If the index is out of bounds, the default value is returned.
     *
     * @param index is the index of the element to get.
     * @param defaultValue is the default value to return if the index is out of bounds.
     * @return the element at the specified index.
     */
    const T get(const size_t& index, const T& defaultValue) const {
        if (index >= m_Size) {
            return defaultValue;
        }
        return m_Data[index];
    }

    /**
     * @brief Get the element at the specified index.
     * If the index is out of bounds, the default value is returned.
     *
     * @param index is the index of the element to get.
     * @param defaultValue is the default value to return if the index is out of bounds.
     * @return the element at the specified index.
     */
    T get(const size_t& index, const T& defaultValue) {
        if (index >= m_Size) return const_cast<T&>(defaultValue);
        return m_Data[index];
    }

    /**
     * @brief Get the reference to the element at the specified index.
     *
     * @param index is the index of the element to get.
     * @return the reference to the element at the specified index.
     */
    const T& operator[](const size_t& index) const {
        return m_Data[index];
    }

    /**
     * @brief Get the reference to the element at the specified index.
     *
     * @param index is the index of the element to get.
     * @return the reference to the element at the specified index.
     */
    T& operator[](const size_t& index) {
        return m_Data[index];
    }

    ArrayList& operator=(const ArrayList& other) {
        m_Size = 0;
        if (_reallocate(other.m_Capacity)) {
            m_Size = other.m_Size;
            const size_t size = m_Size * sizeof(T);
            memcpy(m_Data, other.m_Data, size);
        }
        return *this;
    }

    ArrayList& operator=(ArrayList&& other) noexcept {
        _swap(other);
        return *this;
    }

#if defined(ESP32) || defined(ESP8266)
    /**
     * @brief Iterate over the ArrayList and call the predicate for each element.
     *
     * @param predicate is the predicate to call for each element.
     */
    void forEach(std::function<bool(T&, size_t)> predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (!predicate(m_Data[i], i)) break;
        }
    }
#else
    /**
     * @brief Iterate over the ArrayList and call the predicate for each element.
     *
     * @param predicate is the predicate to call for each element.
     */
    template <typename Callable>
    void forEach(Callable predicate) {
        for (size_t i = 0; i < m_Size; i++) {
            if (!predicate(m_Data[i], i)) break;
        }
    }
#endif

#if defined(ESP32) || defined(ESP8266)
    /**
     * @brief Map the ArrayList to a new ArrayList.
     *
     * @tparam E is the type of the new ArrayList.
     * @param predicate is the predicate to call for each element.
     * @return The new ArrayList.
     */
    template <typename E = T>
    ArrayList<E> map(std::function<E(T&, size_t)> predicate) {
        ArrayList<E> buffer;
        for (size_t i = 0; i < m_Size; i++) {
            buffer.add(predicate(m_Data[i], i));
        }
        return buffer;
    }
#else
    /**
     * @brief Map the ArrayList to a new ArrayList.
     *
     * @tparam E is the type of the new ArrayList.
     * @param predicate is the predicate to call for each element.
     * @return The new ArrayList.
     */
    template <typename E = T, typename Callable>
    ArrayList<E> map(Callable predicate) {
        ArrayList<E> buffer;
        for (size_t i = 0; i < m_Size; i++) {
            buffer.add(predicate(m_Data[i], i));
        }
        return buffer;
    }
#endif

#if defined(ESP32) || defined(ESP8266)
    /**
     * @brief Filter the ArrayList to a new ArrayList based on the predicate.
     *
     * @param predicate is the predicate to call for each element.
     * @return The filtered ArrayList.
     */
    ArrayList filter(std::function<bool(T&)> predicate) {
        ArrayList buffer;
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) buffer.add(m_Data[i]);
        }
        return buffer;
    }
#else
    /**
     * @brief Filter the ArrayList to a new ArrayList based on the predicate.
     *
     * @param predicate is the predicate to call for each element.
     * @return The filtered ArrayList.
     */
    template <typename Callable>
    ArrayList filter(Callable predicate) {
        ArrayList buffer;
        for (size_t i = 0; i < m_Size; i++) {
            if (predicate(m_Data[i])) buffer.add(m_Data[i]);
        }
        return buffer;
    }
#endif

#if defined(ESP32) || defined(ESP8266)
    /**
     * @brief Sort the ArrayList based on the predicate.
     *
     * @param predicate is the predicate to call for each element.
     */
    void sort(std::function<bool(T&, T&)> predicate) {
        for (size_t i = 1; i < m_Size; i++) {
            for (size_t j = i; j > 0 && predicate(m_Data[j - 1], m_Data[j]); j--) {
                T tmp = m_Data[j - 1];
                m_Data[j - 1] = m_Data[j];
                m_Data[j] = tmp;
            }
        }
    }
#else
    /**
     * @brief Sort the ArrayList based on the predicate.
     *
     * @param predicate is the predicate to call for each element.
     */
    template <typename Callable>
    void sort(Callable predicate) {
        for (size_t i = 1; i < m_Size; i++) {
            for (size_t j = i; j > 0 && predicate(m_Data[j - 1], m_Data[j]); j--) {
                T tmp = m_Data[j - 1];
                m_Data[j - 1] = m_Data[j];
                m_Data[j] = tmp;
            }
        }
    }
#endif

    /**
     * @brief Sort the ArrayLis.
     * By default the ArrayList is sorted in ascending order.
     * The operator > must be defined for the type T.
     *
     */
    void sort() {
        sort([](T a, T b) -> bool { return a > b; });
    }

    /**
     * @brief Reverse the ArrayList.
     *
     */
    void reverse() {
        for (size_t i = 0; i < m_Size / 2; i++) {
            T buffer = m_Data[i];
            m_Data[i] = m_Data[m_Size - 1 - i];
            m_Data[m_Size - 1 - i] = buffer;
        }
    }

    /**
     * @brief Get the begin iterator of the ArrayList.
     *
     * @return Iterator
     */
    Iterator begin() {
        return Iterator(m_Data);
    }

    /**
     * @brief Get the begin iterator of the ArrayList.
     *
     * @return Iterator
     */
    Iterator end() {
        return Iterator(m_Data + m_Size);
    }

    /**
     * @brief Get the size of the ArrayList.
     *
     * @return size_t
     */
    size_t size() const {
        return m_Size;
    }

    /**
     * @brief Check if the ArrayList is empty.
     *
     * @return true if the ArrayList is empty. false otherwise.
     */
    bool isEmpty() const {
        return m_Size == 0;
    }

private:
    T* m_Data;
    size_t m_Size;
    size_t m_Capacity;

    /**
     * @brief Reallocate the ArrayList to a new capacity.
     *
     * @param newCapacity is the new capacity of the ArrayList.
     * @return true if the reallocation was successful. false otherwise.
     */
    bool _reallocate(size_t newCapacity) {
        T* newBlock = new T[newCapacity];
        if (newBlock) {
            if (newCapacity < m_Size) {
                m_Size = newCapacity;
            }
            for (size_t i = 0; i < m_Size; i++) {
                newBlock[i] = m_Data[i];
            }
            delete[] m_Data;
            m_Data = newBlock;
            m_Capacity = newCapacity;
            return true;
        }
        return false;
    }

    /**
     * @brief Deallocate the ArrayList.
     *
     */
    void _deallocate() {
        delete[] m_Data;
        m_Data = NULL;
        m_Size = 0;
        m_Capacity = 0;
    }

    /**
     * @brief Swap the ArrayList with another ArrayList.
     *
     * @param other is the ArrayList to swap with.
     */
    void _swap(ArrayList& other) {
        T* _data = m_Data;
        size_t _size = m_Size;
        size_t _capacity = m_Capacity;

        m_Data = other.m_Data;
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;

        other.m_Data = _data;
        other.m_Size = _size;
        other.m_Capacity = _capacity;
    }
};

#endif