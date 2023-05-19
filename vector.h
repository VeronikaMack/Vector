#ifndef VECTOR_H
#define VECTOR_H
#include <memory>
#include <algorithm>
#include <chrono>

template <class T>
class Vector{
public:
    //MEMBER TYPES:
typedef T* iterator; 
typedef const T* const_iterator; 
typedef size_t size_type;
typedef T value_type; 
typedef std::ptrdiff_t difference_type;
typedef value_type &reference;
typedef const value_type &const_reference;
//typedef std::allocator_traits<std::allocator<value_type>>::pointer pointer;
//typedef std::allocator_traits<std::allocator<value_type>>::const_pointer const_pointer;
typedef std::reverse_iterator<iterator> reverse_iterator;
typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
private:
iterator data; 
iterator avail;
iterator limit;

std::allocator<T> alloc; //objektas atminties valdymui

// išskirti atmintį (array) ir ją inicializuoti
void create() 
{
   data = avail = limit = nullptr;
}
void create(size_type n, const T& value)
{
    if (n > max_size())
    throw std::out_of_range("Exceeded maximum size limit");

    data = alloc.allocate(n); // grąžina ptr į array pirmą elementą
    limit = avail = data + n; // sustato rodykles į vietas
    uninitialized_fill(data, limit, value); // inicializuoja elementus val reikšme
}
void create(const_iterator begin, const_iterator end)
{
    data = alloc.allocate(end - begin); // išskirti vietos j-i elementams
    limit = avail = std::uninitialized_copy(begin, end, data);// nukopijuoja elementus iš intervalo 
}

// sunaikinti elementus array ir atlaisvinti atmintį
void uncreate()
{  
 if (data) {
 // sunaikinti (atbuline tvarka) sukonstruotus elementus
 iterator it = avail;
 while (it != data)
 alloc.destroy(--it);
 // atlaisvinti išskirtą atmintį. Turi būti data != nullptr
 alloc.deallocate(data, limit - data);
 }
 // reset'inam pointer'iuss - Vector'ius tuščias
 data = limit = avail = nullptr;
}

// pagalbinės funkcijos push_back realizacijai
void grow()
{
 // dvigubai daugiau vietos, nei buvo
 size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
 // išskirti naują vietą ir perkopijuoti egzistuojančius elementus
 iterator new_data = alloc.allocate(new_size);
 iterator new_avail = std::uninitialized_copy(data, avail, new_data);
 // atlaisvinti seną vietą
 uncreate();

 // reset'int rodykles į naujai išskirtą vietą
 data = new_data;
 avail = new_avail;
 limit = data + new_size;
};
void grow(int n)
{
    size_type new_size = n;
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}
void unchecked_append(const T& value)
{
    alloc.construct(avail++, value);
}

public:


//MEMBER FUNCTIONS:
//konstruktoriai
Vector() { create(); }
explicit Vector(size_type n, const T& val = T{}) { create(n, val); }
Vector(const Vector& v) { create(v.begin(), v.end()); } //copy konstruktorius
//destructor
~Vector() { uncreate(); } 
//priskyrimo operatorius
Vector& operator=(const Vector& cop){
 if (&cop != this) {
 uncreate();
 create(cop.begin(), cop.end());
 }
 return *this;
}
//assign
void assign( size_type count, const T& value ){ create(count, value); }



//ELEMENT ACCESS:
//at
reference at( size_type a ){ return (a < size()) ? data[a] : throw std::out_of_range("out_of_range(Vector::at())"); }
//reference operator
reference operator[]( size_type a ){return data[a];}
const_reference operator[]( size_type b ) const{return data[b];}
//front
reference front(){return data[0];}
const_reference front() const{return data[0];}
//back
reference back(){return *(avail-1);}
const_reference back() const{return *(avail-1);}
//data
T* data_() noexcept{return data;}
const T* data_() const noexcept{return data;}

//ITERATORS:
//begin
iterator begin() { return data; } 
 const_iterator begin() const { return data; } 
//end
 iterator end() { return avail; } 
 const_iterator end() const { return avail; } 
//reverse begin
reverse_iterator rbegin() noexcept { return reverse_iterator(avail); }
const_reverse_iterator rbegin() const noexcept { return reverse_iterator(avail); }
//reverse end
reverse_iterator rend() noexcept { return reverse_iterator(data); }
const_reverse_iterator rend() const noexcept { return reverse_iterator(data); }

//CAPACITY
//empty
bool empty() const noexcept{return data==avail;}
//size
size_type size() const { return limit - data;}//kiek elementu tarp rodykliu
//max_size
size_type max_size() const noexcept{return std::numeric_limits<size_type>::max();}
//reserve
void reserve( size_type new_cap ){if (new_cap > capacity()) grow(new_cap);}
//capacity
size_type capacity() const noexcept{return limit - data;}
//shrink_to_fit
void shrink_to_fit(){limit = avail;}

//MODIFIERS
//clear
void clear() noexcept{uncreate();}
//insert
iterator insert( const_iterator pos, T&& value )
{
    if (avail==limit)//jei nera vietos reik didint
    {
        grow();
    }
    iterator p = const_cast<iterator>(pos);
    std::copy_backward(pos, avail, avail + 1);
    *p = value;
    avail++;
    return p;

}
//emplace
template< class... Args >
iterator emplace( const_iterator pos, Args&&... args )
{
    if (avail == limit)
    {
        grow();
    }
    iterator p = const_cast<iterator>(pos);
    std::copy_backward(pos, avail, avail + 1);
    *p = T(std::forward<Args>(args)...);
    avail++;
    return p;
}
//erase
iterator erase( const_iterator pos )
{
    iterator p = const_cast<iterator>(pos);
    std::copy(p+1, avail, p);
    alloc.destroy(--avail);
    return p;
}
iterator erase( const_iterator first, const_iterator last ){
    iterator p = const_cast<iterator>(first);
    iterator q = const_cast<iterator>(last);
    std::copy(q, avail, p);
    while (q != avail) {
        alloc.destroy(--avail);
    }
    return p;
}

//push_back
 void push_back(const T& val) {
 if (avail == limit)
 {
     grow();// išskirti vietos, jei reikia
 } 
 unchecked_append(val);
 }
//emplace_back
reference emplace_back(const T& value )
{
    if(avail == limit)
    {
        grow();
    }
       unchecked_append(value);
}
//pop_back
void pop_back()
{
    if (data == avail)
    {
            throw std::out_of_range("Container is empty(Pop_back())");
    }
    alloc.destroy(--avail);
}
//resize
void resize( size_type count, const value_type& value )
{
if(count > max_size())
{
    throw std::out_of_range("Maximum size of the container has been exceeded(resize())");
}
if(count>size())
{
    if(count>capacity())
    {
        grow(count);
    }
    for(size_type i = size(); i!=count; i++)
    {
        unchecked_append(value);
    }

}
else if(count<size())
{
      while (avail != data + count)
      {
         alloc.destroy(--avail);
      }
   
}
}
//swap
void swap( Vector& other )
{
    std::swap(data, other.data);
    std::swap(avail, other.avail);
    std::swap(limit, other.limit);
}
//OPERATORS:
 //==
bool operator==(const Vector<T>& rhs )
{
 if(size()==rhs.size())
 {
    for (size_type i = 0; i<size(); i++)
    {
        if(data_()[i]!=rhs.data_()[i])
        {
            return false;
        }
    }
 }
 else if(size()!=rhs.size())
 {
    return false;
 }
 else return true;
}
//!=
bool operator!=(const Vector<T>& rhs)
{
    return *this != rhs;
}
//<
bool operator<(const Vector<T>& rhs)
{
   for(size_type i = 0; i<min(size(), rhs.size()); i++)
   {
     if(data[i]<rhs.data[i])
     {
        return true;
     }
     
   }
   return false;
}
//<=
bool operator<=(const Vector<T>& rhs)
{
    for(size_type i = 0; i<min(size(), rhs.size()); i++)
   {
     if(data[i]<=rhs.data[i])
     {
        return true;
     }
     
   }
   return false;
}
//>
bool operator>(const Vector<T>& rhs)
{
    for(size_type i = 0; i<min(size(), rhs.size()); i++)
   {
     if(data[i]>rhs.data[i])
     {
        return true;
     }
     
   }
   return false;
}
//>=
bool operator>=(const Vector<T>& rhs)
{
   for(size_type i = 0; i<min(size(), rhs.size()); i++)
   {
     if(data[i]>=rhs.data[i])
     {
        return true;
     }
     
   }
   return false;
}
void swap(Vector<T>& lhs, Vector<T>& rhs) {
        std::swap(lhs.data, rhs.data);
        std::swap(lhs.avail, rhs.avail);
        std::swap(lhs.limit, rhs.limit);
      }
};

template<class T> 
class allocator {
public:
 T* allocate(size_t n)
 {
     return static_cast<T *>(::operator new(n * sizeof(T)));// išskirti `raw` atmintį
 }
 void deallocate(T* p, size_t n)
 {
    ::operator delete(p, n * sizeof(T));
 }
 void construct(T* p, const T& val)// atlaisvinti atmintį
 {
    new (p) T(val);// sukonstruoti 1 objektą
 } 
 void destroy(T* p)
 {
    p->~T();// sunaikinti 1 objektą
 }
 
};


using namespace std::chrono;



#endif




















