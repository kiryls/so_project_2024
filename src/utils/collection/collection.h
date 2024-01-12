#ifndef COLLECTION_H

#include <sys/_types/_size_t.h>

typedef struct {
    size_t size;
    size_t cap;
    size_t item_size;
    void *items;
} Collection;

Collection collection_create(size_t item_size);
void collection_remove(Collection *collection);

#endif  // !COLLECTION_H
