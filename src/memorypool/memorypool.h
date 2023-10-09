#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <iostream>
#include <algorithm>
#include <utility>
//  定长内存池
//      组成: 内存块链表指针, 空闲链表指针, 空闲节点指针, 内存块边界节点指针

template<class T, size_t BlockSize = 4096>
class MemoryPool {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;

    template <class U>
    struct rebind {
        typedef MemoryPool<U> other;
    };

    MemoryPool() noexcept;
    ~MemoryPool() noexcept;
    //  分配元素节点的函数
    T* allocate(size_t n = 1, const_pointer hint = 0);
    //  释放分配元素的内存
    void deallocate(T* p, size_t n = 1);
    //  调用对象的构造函数
    template<typename U, class... Args>
    void construct(U* p, Args&&... agrs);
    //  调用析构函数
    template<typename U>
    void destroy(U* p);

    //  额外添加
    //  拷贝构造函数
    MemoryPool(const MemoryPool& memoryPool) noexcept : MemoryPool() {}
    //  移动构造函数
    MemoryPool(MemoryPool&& memoryPool) noexcept {
        current_block_ = memoryPool.current_block_;
        memoryPool.current_block_ = nullptr;
        current_slot_ = memoryPool.current_slot_;
        free_slot_ = memoryPool.free_slot_;
        last_slot_ = memoryPool.last_slot_;
    }
    // size_t max_size() const noexcept;

    //  不会使用的一个构造函数
    template <class U>
    MemoryPool(const MemoryPool<U>& memoryPool) noexcept : MemoryPool() {}

    // //  12  
    // pointer address(T& x) const noexcept {
    //     return &x;
    // }
    // //  13
    // const_pointer address(const T& x) const noexcept {
    //     return &x;
    // }

    // MemoryPool& operator=(const MemoryPool& memoryPool) = delete;

    // //  8 重构等号运算符号
    // MemoryPool& operator=(MemoryPool&& memoryPool) noexcept {
    //     if(this != &memoryPool) {
    //         std::swap(current_block_, memoryPool.current_block_);
    //         current_slot_ = memoryPool.current_slot_;
    //         free_slot_ = memoryPool.free_slot_;
    //         last_slot_ = memoryPool.last_slot_;
    //     }
    //     return *this;
    // }

    // //  9
    // template<class... Args>
    // pointer newElement(Args&&... args) {
    //     pointer ret = allocate();
    //     construct<value_type>(ret, std::forward<Args>(args)...);
    //     return ret;
    // }

    // //  10
    // void deleteElement(pointer p) {
    //     if(p != nullptr) {
    //         p->~value_type();
    //         deallocate(p);
    //     }
    // }


private:
    //  分配额外的内存块
    void allocateBlock();

    size_t padPointer(char* p, size_t align) const noexcept {
        unsigned long ret = reinterpret_cast<unsigned long>(p);
        return ((align - ret) % align);
    }

    union Slot_ {
        T val_;
        Slot_* next_;
    };

    Slot_* current_block_; // 内存块链表指针
    Slot_* current_slot_; // 空闲节点指针
    Slot_* free_slot_; // 空闲链表指针
    Slot_* last_slot_; // 内存块边界节点指针

};

#include "memorypool/memorypool.tcc"

#endif