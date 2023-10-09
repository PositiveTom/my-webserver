#ifndef MEMORYPOOL_TCC
#define MEMORYPOOL_TCC

template<class T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool() noexcept {
    current_block_ = nullptr;
    current_slot_ = nullptr;
    free_slot_ = nullptr;
    last_slot_ = nullptr;
}

template<class T, size_t BlockSize>
T* MemoryPool<T, BlockSize>::allocate(size_t n, const_pointer hint) {
    if(free_slot_ != nullptr) {
        //  从空闲链表中取出一个节点当作头节点
        T* p = reinterpret_cast<T*>(free_slot_);
        free_slot_ = free_slot_->next_;
        return p;
    } else {
        if(current_slot_ >= last_slot_) {
            //  分配内存块
            allocateBlock();
        }
        return reinterpret_cast<T*>(current_slot_++);
    }
}

template<class T, size_t BlockSize>
void MemoryPool<T, BlockSize>::allocateBlock() {
    //  分配新的内存块
    char* new_block = reinterpret_cast<char*>(operator new(BlockSize));

    //  创建新链表节点, 当作旧链表节点的前驱节点
    reinterpret_cast<Slot_*>(new_block)->next_ = current_block_;
    current_block_ = reinterpret_cast<Slot_*>(new_block);

    //  计算新内存块中当前空闲链表节点
    char* body = new_block + sizeof(Slot_*);
    size_t body_padding = padPointer(body, alignof(Slot_));
    current_slot_ = reinterpret_cast<Slot_*>(body + body_padding);

    //  计算新内存块中的末尾节点
    last_slot_ = reinterpret_cast<Slot_*>(new_block + BlockSize - sizeof(Slot_) + 1);
}

template<class T, size_t BlockSize>
inline void MemoryPool<T, BlockSize>::deallocate(T* p, size_t n) {
    if(p != nullptr) {
        //  空闲链表节点新增节点
        reinterpret_cast<Slot_*>(p)->next_ = free_slot_;
        free_slot_ = reinterpret_cast<Slot_*>(p);
    }
}

template<class T, size_t BlockSize>
template<typename U, class... Args>
void MemoryPool<T, BlockSize>::construct(U* p, Args&&... args) {
    new (p) U (std::forward<Args>(args)...);
}

template<class T, size_t BlockSize>
template<typename U>
void MemoryPool<T, BlockSize>::destroy(U* p) {
    p->~U();
}

template <class T, size_t BlockSize>
MemoryPool<T, BlockSize>::~MemoryPool() noexcept {
    Slot_* curr = current_block_;
    while(curr) {
        Slot_* next = curr->next_;
        operator delete( reinterpret_cast<void*>(curr) );
        curr = next;
    }
}

// template <class T, size_t BlockSize>
// size_t MemoryPool<T, BlockSize>::max_size() const noexcept {
//     size_t maxBlocks = -1 / BlockSize;
//     return (BlockSize - sizeof(char*)) / sizeof(Slot_) * maxBlocks;
// }


#endif