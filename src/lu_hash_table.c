#include "lu_hash_table-internal.h"
 
#include <stdio.h>  // 为了打印错误信息
#include <stdlib.h> // 为了使用malloc, free
#include <string.h> // 为了使用memset

void                lu_rb_tree_insert(lu_rb_tree_t* tree, int key, void* value);
void                lu_rb_tree_right_rotate(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
void                lu_rb_tree_left_rotate(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
void                lu_rb_tree_insert_fixup(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
void                lu_rb_tree_left_rotate_delete(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
void                lu_rb_tree_delete(lu_rb_tree_t* tree, int key);
void                lu_rb_tree_right_rotate_delete(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
lu_rb_tree_node_t*  lu_rb_tree_find(lu_rb_tree_t* tree, int key);
void                lu_rb_tree_delete_fixup(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
void                lu_rb_tree_transplant(lu_rb_tree_t* tree, lu_rb_tree_node_t* u, lu_rb_tree_node_t* v);
void                lu_rb_tree_destroy_node(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
void                lu_rb_tree_destroy(lu_rb_tree_t* tree);
lu_rb_tree_node_t*  lu_rb_tree_minimum(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
lu_rb_tree_node_t*  lu_rb_tree_maximum(lu_rb_tree_t* tree, lu_rb_tree_node_t* node);
lu_rb_tree_t*       lu_rb_tree_init();


/**
 * @brief Computes a hash value for a given key using the multiplication method.
 *
 * This function implements a hash function based on the multiplication method,
 * using the fractional part of the product between the key and the constant
 * A (the reciprocal of the golden ratio). If the table size is a power of two,
 * the modulo operation is optimized using bitwise operations. Otherwise, a
 * standard modulo operation is applied.
 *
 * @param key The integer key to be hashed.
 * @param table_size The size of the hash table (number of buckets).
 * @return The computed hash value, ranging from 0 to table_size - 1.
 */
int lu_hash_function(int key, int table_size) {
    static const double golden_rate_reciprocal = 0.6180339887;  // 黄金比例的倒数 
    // 乘法哈希法
    double temp = key * golden_rate_reciprocal;
    double fractional_part = temp - (int)temp;  // 提取小数部分
    int hash = (int)(table_size * fractional_part);

    // 如果表大小是2的幂，使用位运算优化
    if ((table_size & (table_size - 1)) == 0) {  // 判断table_size是否是2的幂
        return hash & (table_size - 1);  // 位运算优化
    }
    return hash % table_size;  // 默认情况下使用取模
    
}

 
// 初始化哈希表
lu_hash_table_t* lu_hash_table_init(int table_size) {
    if (table_size <= 0) {
        table_size = LU_HASH_TABLE_DEFAULT_SIZE; // 使用默认大小
    }

    // 分配哈希表内存
    lu_hash_table_t* hash_table = (lu_hash_table_t*)LU_MM_MALLOC(sizeof(lu_hash_table_t));
    if (hash_table == NULL) {
        printf("lu_hash_table_init: malloc failed for hash table\n");
        return NULL;
    }

    // 为哈希桶数组分配内存，使用calloc来确保内存清零
    hash_table->buckets = (lu_hash_bucket_t*)LU_MM_CALLOC(table_size, sizeof(lu_hash_bucket_t));
    if (hash_table->buckets == NULL) {
        printf("lu_hash_table_init: malloc failed for buckets\n");
        free(hash_table);
        return NULL;
    }

    hash_table->table_size = table_size;

    // 初始化每个桶的类型为列表类型
    for (int i = 0; i < table_size; i++) {
        hash_table->buckets[i].type = LU_BUCKET_LIST;
        hash_table->buckets[i].data.list_head = NULL;
    }

    return hash_table;
}


void lu_rb_tree_insert(lu_rb_tree_t* tree, int key, void* value) {
    //printf("Inserting key: %d into RB-tree\n", key);

    if (tree == NULL || tree->nil == NULL) {
        printf("Error: Tree or tree->nil is not initialized\n");
        return;
    }
    // 创建新节点
    lu_rb_tree_node_t* new_node = (lu_rb_tree_node_t*)malloc(sizeof(lu_rb_tree_node_t));
    if (new_node == NULL) {
        printf("Memory allocation failed for new node\n");
        return;
    }
   
    //printf("tree->nil address: %p\n", tree->nil);


    
    //初始化节点字段
    new_node->key = key;
    new_node->value = value;
    new_node->color = RED;  // 新插入的节点是红色
    new_node->left = new_node->right = new_node->parent = tree->nil;

    
    
    // 如果树为空，初始化root为nil
    if (tree->root == tree->nil) {
        tree->root = new_node;                 
        new_node->color = BLACK;
        
    } else {
        lu_rb_tree_node_t* parent = tree->root;
        lu_rb_tree_node_t* current = tree->root;
        while (current != tree->nil) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
           } 
        }

        // 插入新节点
        new_node->parent = parent;
        if (key < parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        if (new_node == NULL || tree == NULL) {
            printf("Error: Invalid node or tree during fixup\n");
            return;
        }


        // 修复红黑树的性质
        lu_rb_tree_insert_fixup(tree, new_node);
    }
}

 


// 初始化红黑树
lu_rb_tree_t* lu_rb_tree_init() {
    lu_rb_tree_t* tree = (lu_rb_tree_t*)malloc(sizeof(lu_rb_tree_t));
    if (tree == NULL) {
        printf("Memory allocation failed for red-black tree\n");
        return NULL;
    }

    // 初始化 nil 节点
    tree->nil = (lu_rb_tree_node_t*)malloc(sizeof(lu_rb_tree_node_t));
    if (tree->nil == NULL) {
        printf("Memory allocation failed for nil node\n");
        free(tree);
        return NULL;
    }
    tree->nil->color = BLACK; // nil 节点的颜色为黑色
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->parent = tree->nil;

    tree->root = tree->nil; // 初始化根节点为 nil

    return tree;
}


void lu_hash_table_insert(lu_hash_table_t* table, int key, void* value) {
    int index = lu_hash_function(key, table->table_size);
    lu_hash_bucket_t* bucket = &table->buckets[index];

    if (bucket->type == LU_BUCKET_LIST) {
        // 在链表中插入
        lu_hash_bucket_node_ptr_t new_node = (lu_hash_bucket_node_ptr_t)malloc(sizeof(lu_hash_bucket_node_t));
        if (new_node == NULL) {
            printf("Memory allocation failed for new node\n");
            return;
        }
        new_node->key = key;
        new_node->value = value;
        new_node->next = bucket->data.list_head;

        bucket->data.list_head = new_node;

        // 检查桶内元素数量是否超过阈值，若超过则转换为红黑树
        int count = 0;
        lu_hash_bucket_node_ptr_t node = bucket->data.list_head;
        
     
        while (node != NULL) {
           
            //printf("Node key: %d, Node address: %p, Next node address: %p\n", node->key, node, node->next);            
            count++;
            node = node->next;
        }
        printf("Bucket size before conversion: %d\n", count);

       if (count > LU_BUCKET_LIST_THRESHOLD) {
           
            printf("Converting bucket to red-black tree\n");      
       
            lu_rb_tree_t* new_tree = lu_rb_tree_init();
            
            if (new_tree == NULL) {
                printf("Memory allocation failed for new red-black tree\n"); 
                return;
            }            

            //printf("RB-tree initialized. Tree address: %p, tree->nil: %p\n", new_tree, new_tree->nil);


            // 插入链表中的所有元素到红黑树
            node = bucket->data.list_head;
          
            while (node != NULL) {                           
               lu_rb_tree_insert(new_tree, node->key, node->value);
               node = node->next;          
                
            }
            

            // 清理链表内存
            node = bucket->data.list_head;
            while (node != NULL) {
                lu_hash_bucket_node_ptr_t temp = node;
                node = node->next;
                free(temp);
            }
            bucket->data.list_head = NULL; // 最后清空链表头指针，防止悬挂指针

            // 将桶的类型修改为红黑树，并关联新创建的红黑树
            bucket->type = LU_BUCKET_RBTREE;
            bucket->data.rb_tree = new_tree;
                    

            printf("Bucket converted successfully to red-black tree\n");
            printf("RB-tree initialized. Tree address: %p, tree->nil: %p\n", new_tree, new_tree->nil);

        }
    } else if (bucket->type == LU_BUCKET_RBTREE) {
        // 在红黑树中插入
        printf("Inserting key %d into red-black tree\n", key);
        if (bucket->data.rb_tree == NULL || bucket->data.rb_tree->nil == NULL) {
            printf("Error: RB-tree or tree->nil is not initialized\n");
            return;
        }

        lu_rb_tree_insert(bucket->data.rb_tree, key, value);
    }
}


 
// 查找元素
void* lu_hash_table_find(lu_hash_table_t* table, int key) {
    int index = lu_hash_function(key, table->table_size);
    lu_hash_bucket_t* bucket = &table->buckets[index];

    if (bucket->type == LU_BUCKET_LIST) {
        // 在链表中查找
        lu_hash_bucket_node_ptr_t node = bucket->data.list_head;
        while (node != NULL) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
    } else if (bucket->type == LU_BUCKET_RBTREE) {
         
        // 在红黑树中查找
        lu_rb_tree_node_t* rb_node = lu_rb_tree_find(bucket->data.rb_tree, key);
        if (rb_node != NULL) {
            return rb_node->value;  
        }
    }

    return NULL;  // 未找到
}

 
// 删除元素
void lu_hash_table_delete(lu_hash_table_t* table, int key) {
    int index = lu_hash_function(key, table->table_size);
    lu_hash_bucket_t* bucket = &table->buckets[index];

    if (bucket->type == LU_BUCKET_LIST) {
        // 在链表中删除
        lu_hash_bucket_node_ptr_t prev = NULL;
        lu_hash_bucket_node_ptr_t node = bucket->data.list_head;
        while (node != NULL) {
            if (node->key == key) {
                if (prev == NULL) {
                    bucket->data.list_head = node->next;
                } else {
                    prev->next = node->next;
                }
                free(node);
                return;
            }
            prev = node;
            node = node->next;
        }
    } else if (bucket->type == LU_BUCKET_RBTREE) {
            
         lu_rb_tree_delete(bucket->data.rb_tree, key);
    }
}

// 提取元素的值
void* lu_hash_table_retrieve(lu_hash_bucket_element_t element) {
    return element ? element->value : NULL;
}

// 销毁哈希表
void lu_hash_table_destroy(lu_hash_table_t* table) {
    if (table == NULL) {
        return; // 安全处理空哈希表
    }
    int i;
    for (i = 0; i < table->table_size; i++) {
        lu_hash_bucket_t* bucket = &table->buckets[i];
        if (bucket->type == LU_BUCKET_LIST) {
            lu_hash_bucket_node_ptr_t node = bucket->data.list_head;
            while (node != NULL) {
                lu_hash_bucket_node_ptr_t temp = node;
                node = node->next;
                free(temp);
            }
            bucket->data.list_head = NULL; // 防止悬挂指针
        } else if (bucket->type == LU_BUCKET_RBTREE) {
            
            // 清理红黑树
            if (bucket->data.rb_tree != NULL) {
                lu_rb_tree_destroy(bucket->data.rb_tree);
                bucket->data.rb_tree = NULL; // 防止悬挂指针
            }
        }
    }
    free(table->buckets);
    table->buckets = NULL;
    free(table);
    table = NULL;

}

 

void lu_rb_tree_right_rotate(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    // 检查左子节点是否为空
    if (node->left == tree->nil) {
        return; // 如果左子节点是nil，说明不需要旋转
    }

    lu_rb_tree_node_t* left = node->left;
    node->left = left->right;

    // 检查 left->right 是否为nil，并更新 parent 指针
    if (left->right != tree->nil) {
        left->right->parent = node;
    }

    left->parent = node->parent;

    if (node->parent == tree->nil) {
        tree->root = left;
    } else if (node == node->parent->left) {
        node->parent->left = left;
    } else {
        node->parent->right = left;
    }

    left->right = node;
    node->parent = left;
}


void lu_rb_tree_left_rotate(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    // 检查右子节点是否为空
    if (node->right == tree->nil) {
        return; // 如果右子节点为空，不进行旋转
    }

    lu_rb_tree_node_t* right = node->right;
    
    // 更新 node 的 right 指针指向 right->left
    node->right = right->left;

    // 检查右子节点的左子树是否为空，并更新其 parent 指针
    if (right->left != tree->nil) {
        right->left->parent = node;
    }

    // 更新 right 节点的 parent 指针
    right->parent = node->parent;

    // 处理根节点的情况
    if (node->parent == tree->nil) {
        tree->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    } printf("Inserting node with key: %d\n", node->key);

    // 执行左旋操作
    right->left = node;
    node->parent = right;
}

void lu_rb_tree_insert_fixup(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    while (node != tree->root && node->parent != tree->nil && node->parent->color == RED) {
        // Ensure node->parent is not nil and has a parent
        lu_rb_tree_node_t* parent = node->parent;
        lu_rb_tree_node_t* grandparent = parent->parent;

        if (parent == grandparent->left) {
            // Uncle is the right child of the grandparent
            lu_rb_tree_node_t* uncle = grandparent->right;

            // Check if uncle is valid and not nil
            if (uncle != tree->nil && uncle != NULL && uncle->color == RED) {
                // Case 1: Uncle is RED, recoloring required
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent; // Move the node up
            } else {
                // Uncle is BLACK or NULL, perform rotations
                if (node == parent->right) {
                    node = parent;
                    lu_rb_tree_left_rotate(tree, node); // Ensure node is valid
                }
                parent->color = BLACK;
                grandparent->color = RED;
                lu_rb_tree_right_rotate(tree, grandparent);
            }
        } else {
              // 在这里打印调试信息
            printf("Parent: %p, Grandparent: %p, Uncle: %p\n", parent, grandparent, grandparent->left);

            // Symmetric case: node->parent is the right child of the grandparent
            lu_rb_tree_node_t* uncle = grandparent->left;

            // Check if uncle is valid and not nil
            if (uncle != tree->nil && uncle != NULL && uncle->color == RED) {
                // Case 1: Uncle is RED, recoloring required
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent; // Move the node up
            } else {
                // Uncle is BLACK or NULL, perform rotations
                if (node == parent->left) {
                    node = parent;
                    lu_rb_tree_right_rotate(tree, node); // Ensure node is valid
                }
                parent->color = BLACK;
                grandparent->color = RED;
                lu_rb_tree_left_rotate(tree, grandparent);
            }
        }
    }

    tree->root->color = BLACK; // Ensure root is always black
}



// 查找红黑树中的节点
lu_rb_tree_node_t* lu_rb_tree_find(lu_rb_tree_t* tree, int key) {
    
    lu_rb_tree_node_t* current = tree->root;
    while (current != tree->nil) {
        if (key == current->key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;  // 找不到
}


// 左旋操作
void lu_rb_tree_left_rotate_delete(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    lu_rb_tree_node_t* right = node->right;
    node->right = right->left;
    if (right->left != tree->nil) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == tree->nil) {
        tree->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

// 右旋操作
void lu_rb_tree_right_rotate_delete(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    lu_rb_tree_node_t* left = node->left;
    node->left = left->right;
    if (left->right != tree->nil) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == tree->nil) {
        tree->root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

// 修复删除后的红黑树性质
void lu_rb_tree_delete_fixup(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    while (node != tree->root && node->color == BLACK) {
        if (node == node->parent->left) {
            lu_rb_tree_node_t* sibling = node->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                lu_rb_tree_left_rotate_delete(tree, node->parent);
                sibling = node->parent->right;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    lu_rb_tree_right_rotate_delete(tree, sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                lu_rb_tree_left_rotate_delete(tree, node->parent);
                node = tree->root;
            }
        } else {
            lu_rb_tree_node_t* sibling = node->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                lu_rb_tree_right_rotate_delete(tree, node->parent);
                sibling = node->parent->left;
            }

            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    lu_rb_tree_left_rotate_delete(tree, sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                lu_rb_tree_right_rotate_delete(tree, node->parent);
                node = tree->root;
            }
        }
    }
    node->color = BLACK;
}

void lu_rb_tree_transplant(lu_rb_tree_t* tree, lu_rb_tree_node_t* u, lu_rb_tree_node_t* v) {
    // 如果 u 是根节点，则更新根节点
    if (u->parent == tree->nil) {
        tree->root = v;
    } else if (u == u->parent->left) {  // 如果 u 是父节点的左子节点
        u->parent->left = v;
    } else {  // 如果 u 是父节点的右子节点
        u->parent->right = v;
    }
    
    // 更新 v 的父节点为 u 的父节点
    if (v != tree->nil) {
        v->parent = u->parent;
    }
}



// 删除红黑树中的节点
void lu_rb_tree_delete(lu_rb_tree_t* tree, int key) {
    lu_rb_tree_node_t* node = lu_rb_tree_find(tree, key);
    if (node == NULL) {
        return;  // 节点不存在
    }

    lu_rb_tree_node_t* y = node;
    lu_rb_tree_node_t* x;
    lu_rb_tree_color_t original_color = y->color;

    if (node->left == tree->nil) {
        x = node->right;
        lu_rb_tree_transplant(tree, node, node->right);
    } else if (node->right == tree->nil) {
        x = node->left;
        lu_rb_tree_transplant(tree, node, node->left);
    } else {
        y = lu_rb_tree_minimum(tree, node->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == node) {
            x->parent = y;
        } else {
            lu_rb_tree_transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        lu_rb_tree_transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    if (original_color == BLACK) {
        lu_rb_tree_delete_fixup(tree, x);
    }
    free(node);
}


// 查找以 node 为根的子树中的最小节点
lu_rb_tree_node_t* lu_rb_tree_minimum(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    while (node->left != tree->nil) {
        node = node->left;   
    }
    return node;  // 返回最左边的节点
}


// 查找以 node 为根的子树中的最大节点
lu_rb_tree_node_t* lu_rb_tree_maximum(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    while (node->right != tree->nil) {
        node = node->right;  // 一直向右走，直到没有右子节点
    }
    return node;  // 返回最右边的节点
}

// 销毁红黑树的节点（递归地释放每个节点）
void lu_rb_tree_destroy_node(lu_rb_tree_t* tree, lu_rb_tree_node_t* node) {
    if (node == tree->nil) {
        return; // 如果是哨兵节点，直接返回
    }

    // 递归销毁左子树和右子树
    lu_rb_tree_destroy_node(tree, node->left);
    lu_rb_tree_destroy_node(tree, node->right);

    // 释放节点的内存
    LU_MM_FREE(node);  // 使用自定义的内存释放宏
}

// 销毁红黑树（销毁树的所有节点，并释放根节点和哨兵节点）
void lu_rb_tree_destroy(lu_rb_tree_t* tree) {
    if (tree == NULL) {
        return;
    }

    // 销毁树的所有节点
    lu_rb_tree_destroy_node(tree, tree->root);

    if (tree->nil != NULL) {
            LU_MM_FREE(tree->nil);
    }
    
    LU_MM_FREE(tree);
}


 

 


 

 