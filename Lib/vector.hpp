#include <new>

template <typename T>
class Vector {

private:
	T* data_ = nullptr;

	size_t size_     = 0;
	size_t capacity_ = 1;

public:
	explicit Vector(const size_t init_size = 0);
	explicit Vector(const size_t init_size, const T& init_val);
	
	Vector(const Vector& copyable);
	Vector(Vector&& expired);

	Vector& operator=(const Vector& copyable);
	Vector& operator=(Vector&& expired);

	~Vector();

	size_t size()     const;
	bool   empty()    const;
	size_t capacity() const;

	void resize(const size_t new_size, const T& new_val = {});
	void reserve(const size_t new_capacity);

	void push_back(const T& new_val);
	void pop_back();

	template <typename... Args>
	void emplace_back(Args&&... args);

	T& operator[](size_t i);
	const T& operator[](size_t i) const;

	class Iter;

	Iter begin();
	Iter end();
};

template <typename T>
Vector<T>::Vector(const size_t init_size): size_(init_size), capacity_(init_size + 1){
	
	data_ = reinterpret_cast<T*>(::operator new(capacity_ * sizeof(T)));
};

template <typename T>
Vector<T>::Vector(const size_t init_size, const T& init_val): Vector<T>::Vector(init_size){ 

	for (size_t i = 0; i < size_; ++i){
		new (&data_[i]) T(init_val);
	};
};

template <typename T>
Vector<T>::Vector(const Vector& copyable){
	
	size_     = copyable.size();
	capacity_ = copyable.capacity();

	data_ = reinterpret_cast<T*>(::operator new(capacity_ * sizeof(T)));

	for (size_t i = 0; i < size_; ++i){
		new (&data_[i]) T(copyable[i]);
	};
};

template <typename T>
Vector<T>::Vector(Vector&& expired){

	size_     = expired.size();
	capacity_ = expired.capacity();

	data_ = expired.data_;

	expired.data_     = nullptr;
	expired.size_     = 0;
	expired.capacity_ = 0;
};

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& copyable){

	if (this == &copyable) return *this;
	
	size_     = copyable.size();
	capacity_ = copyable.capacity();

	::operator delete(data_);
	data_ = reinterpret_cast<T*>(::operator new(capacity_ * sizeof(T)));

	for (size_t i = 0; i < size_; ++i){
		new (&data_[i]) T(copyable[i]);
	};

	return *this;
};

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& expired){
	
	size_     = expired.size();
	capacity_ = expired.capacity();

	::operator delete(data_);
	data_ = expired.data_;

	expired.data_     = nullptr;
	expired.size_     = 0;
	expired.capacity_ = 0;

	return *this;
};

template <typename T>
Vector<T>::~Vector<T>(){
	for (size_t i = 0; i < size_; ++i){
		data_[i].~T();
	};

	::operator delete(data_);
};

template <typename T>
size_t Vector<T>::size() const {
	return size_;
};

template <typename T>
size_t Vector<T>::capacity() const {
	return capacity_;
};

template <typename T>
void Vector<T>::resize(const size_t new_size, const T& new_val){
	//assert(new_size >= 0);
	
	if (new_size > capacity_){
		T* new_data = reinterpret_cast<T*>(::operator new(new_size * sizeof(T)));

		for (size_t i = 0; i < size_; ++i)
			new(&new_data[i]) T(std::move(data_[i])); 

		for (size_t i = size_; i < new_size; ++i) 
			new(&new_data[i]) T(new_val);

		size_ = capacity_ = new_size;
		::operator delete(data_);
		data_ = new_data;

		return;
	};

	if (new_size > size_){
		for (size_t i = size_; i < new_size; ++i) new(&data_[i]) T(new_val);
		
		size_ = new_size;

		return;
	};

	if (new_size < size_){
		for (size_t i = new_size; i < size_; ++i) data_[i].~T();

		size_ = new_size;

		return;
	};
};

template <typename T>
void Vector<T>::reserve(const size_t new_capacity){
	//assert(new_capacity > 0);
	
	if (new_capacity > capacity_){
		T* new_data = ::operator new(new_capacity * sizeof(T));

		for (size_t i = 0; i < size_; ++i)
			new(&new_data[i]) T(std::move(data_[i])); 

		capacity_ = new_capacity;

		::operator delete(data_);
		data_ = new_data;
	};
};

template <typename T>
void Vector<T>::push_back(const T& new_val){
	
	if (size_ < capacity_){
		new (&data_[size_++]) T(new_val);
	}

	else {
		capacity_ *= 2;
		T* new_data = reinterpret_cast<T*>(::operator new (capacity_ * sizeof(T)));
		
		for (size_t i = 0; i < size_; ++i)
			new (&new_data[i]) T(std::move(data_[i]));

		new (&new_data[size_++]) T(new_val);

		::operator delete(data_);
		data_ = new_data;

	};
};

template <typename T>
void Vector<T>::pop_back(){
	data_[--size_].~T();
};

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args&&... args){
	if (size_ < capacity_){
		new (&data_[size_++]) T(std::forward<Args>(args)...);
	}

	else {
		capacity_ *= 2;
		T* new_data = reinterpret_cast<T*>(::operator new(capacity_ * sizeof(T)));
		
		for (size_t i = 0; i < size_; ++i)
			new(&new_data[i]) T(std::move(data_[i]));

		new (&new_data[size_++]) T(std::forward<Args>(args)...);

		::operator delete(data_);
		data_ = new_data;
	};
};

template <typename T>
T& Vector<T>::operator[](size_t i){
	return data_[i];
};

template <typename T>
const T& Vector<T>::operator[](size_t i) const{
	return data_[i];
};

template <typename T>
class Vector<T>::Iter {
private:
	T* ptr = nullptr;

public:


	Iter() = default;
	explicit Iter(T* ptr): ptr(ptr){};


	T operator*(){
		return *ptr;
	};

	Iter operator+(int offset){
		return Iter(ptr + offset);
	};

	Iter operator-(int offset){
		return Iter(ptr - offset);
	};

	Iter operator++(int){
		*this = *this + 1;
		return *this;
	};

	Iter operator++(){
		*this = *this + 1;
		return *this;
	};

	Iter operator--(int){
		*this = *this - 1;
		return *this;
	};

	Iter operator--(){
		*this = *this - 1;
		return *this;
	};

	bool operator==(const Iter& another){
		return ptr == another.ptr;
	};

	bool operator!=(const Iter& another){
		return ptr != another.ptr;
	};

	bool operator>=(const Iter& another){
		return ptr >= another.ptr;
	};
	
	 bool operator<=(const Iter& another){
		return ptr <= another.ptr;
	};

};


template <typename T>
typename Vector<T>::Iter Vector<T>::begin(){
	return typename Vector<T>::Iter(data_);
};

template <typename T>
typename Vector<T>::Iter Vector<T>::end(){
	return typename Vector<T>::Iter(data_ + size_);
};

template <>
class Vector<bool> {

	char* data_ = nullptr;

private:
	class BoolReference {

	private:
		char* cur_byte = nullptr;
		int bit_offset = 0;

	public:
		BoolReference() = delete;
		BoolReference(char* cur_byte, int bit_offset): cur_byte(cur_byte), bit_offset(bit_offset){};

		BoolReference& operator=(bool new_val){

			if (new_val == true) (*cur_byte) |=   1 << bit_offset;
			else                 (*cur_byte) &= ~(1 << bit_offset);

			return *this;
		}

		operator bool(){
			return ((*cur_byte) >> bit_offset) & 1;
		}
	};

	BoolReference operator [](int i){
		return BoolReference(data_ + (i / 8), i % 8);
	};
};
