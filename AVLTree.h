#include <cassert>
#include <cmath>
#include "ArraySequence.h"
#include "Pair.h"

using namespace std;

template <class T> class AVLTree {

class Node{

    public:

        T key;
        int height;
        Node *left;
        Node *right;

        Node(T node){
            key = node;
            left = NULL;
            right = NULL;
            height = 1;
       }
};

public:

    Node *root;
    int num; //количество элементов

public:

    AVLTree(){
        root = NULL;
        num = 0;
    }

    void Insert(T value){
        root = insert(root, value); //запуск рекурсивной операции поиска
    }


    void Remove(T value){
        root = remove(root, value);
    }


    Node* Search(T value){
        return search(root, value);
    }


    void Traversal(string travel, ArraySequence<T>* str){
        if(travel == "KLR"){
            traversalKLR(root, str);
        }
        else if(travel == "KRL"){
            traversalKRL(root, str);
        }
        else if(travel == "LRK"){
            traversalLRK(root, str);
        }
        else if(travel == "RLK"){
            traversalRLK(root, str);
        }
        else if(travel == "LKR"){
            traversalLKR(root, str);
        }
        else if(travel == "RKL"){
            traversalRKL(root, str);
        }
    }


    AVLTree<T>* Map(T mappingFunc(T value)){ //
        AVLTree<T>* newTree = new AVLTree<T>;
        traversalMap(newTree, root, mappingFunc);
        return newTree;
    }


    AVLTree<T>* Where(bool comparisonFunc(T value)){
        AVLTree<T>* newTree = new AVLTree<T>;
        traversalWhere(newTree, root, comparisonFunc);
        return newTree;
    }


    static AVLTree<T>* Merge(AVLTree<T>* A, AVLTree<T>* B){
        ArraySequence<T>* arrA = new ArraySequence<T>(A->num);
        traversalArr(A->root, arrA);
        ArraySequence<T>* arrB = new ArraySequence<T>(B->num);
        traversalArr(B->root, arrB);
        auto pair = mergeArray(arrA, arrB, A->num, B->num);
        AVLTree<T>* newTree = new AVLTree<T>;
        newTree->num = pair.GetSecond();
        newTree->root = sortedArrToBST(pair.GetFirst(), 0, newTree->num);
        return newTree;
    }


    AVLTree<T>* ExtractSubtree(T key){
        Node* node = Search(key);
        if(node == NULL){
            return NULL;
        }
        AVLTree<T>* subtree = new AVLTree<T>;
        traversalMap(subtree, node, [](T value){return value;});
        return subtree;
    }


    bool SearchSubtree(AVLTree<T>* tree){
        if(root != NULL && tree->root != NULL){
        Node* node = Search(tree->root->key);
        if(node == NULL){
            return false;
        }
        return traversalKLRSubtree(node, tree->root);
        }
        return false;
    }

private:

    Node* fromStringKLR(ArraySequence<T>* str){//получение из строки для КПЛ
        if(!str->GetLength()){
            return NULL;
        }
        Node* node = new Node(str->Get(0));
        node->height = ceil(log2(str->GetLength()));
        int first = 0;
        for(;first < str->GetLength(); first++) {
            if (str->Get(first) > str->Get(0)){
                break;
            }
        }
        ArraySequence<T>* leftSlice = str->GetSubsequence(1, first);
        ArraySequence<T>* rightSlice = str->GetSubsequence(first, str->GetLength() - 1);
        delete str;
        node->left = fromStringKLR(leftSlice);
        node->right = fromStringKLR(rightSlice);
        return node;
    }


    Node* fromStringKRL(ArraySequence<T>* str){//получение для строки КПЛ
        if(!str->GetLength()){
            return NULL;
        }
        Node* node = new Node(str->Get(0));
        node->height = ceil(log2(str->GetLength()));
        int first = 0;
        for(;first < str->GetLength(); first++) {
            if (str->Get(first) > str->Get(0)){
                break;
            }
        }
        ArraySequence<T>* leftSlice = str->GetSubsequence(first, str->GetLength());
        ArraySequence<T>* rightSlice = str->GetSubsequence(1, first);
        delete str;
        node->right = fromStringKRL(rightSlice);
        node->left = fromStringKRL(leftSlice);
        return node;
    }


    static void traversalArr(Node* node, ArraySequence<T>* arr){//переводим дерево в сортированный массив
        if(node == NULL){
            return;
        }
        //static int i = 0;
        traversalArr(node->left, arr);
        arr->Append(node->key);
        //i++;
        traversalArr(node->right, arr);
    }


    //слияние двух отсортированных массивов в один
    static Pair<ArraySequence<T>*, int> mergeArray(ArraySequence<T>* arrA, ArraySequence<T>* arrB, int countA, int countB){
        ArraySequence<T>* merged = new ArraySequence<T>(countA + countB);
        int i = 0, j = 0, k = 0;
        while (i < countA && j < countB){
            if(arrA->Get(i) < arrB->Get(j)){//вставляем наименьший из двух в позицию K
                merged->Append(arrA->Get(i));
                i++;
            }
            else if(arrB->Get(j) < arrA->Get(i)){//вставляем наименьший из двух в позицию K
                merged->Append(arrB->Get(j));
                j++;
            }
            else{
                merged->Append(arrA->Get(i));
                i++;
                j++;
            }
            k++;
        }
        while(i < countA){
            merged->Append(arrA->Get(i));
            k++;
            i++;
        }
        while(j < countB){
            merged->Append(arrB->Get(j));
            k++;
            j++;
        }
        return Pair<ArraySequence<T>*, int>(merged, k);
    }


    static Node* sortedArrToBST(ArraySequence<T>* arr, int start, int stop){//построение дерева из сортированного массива
        if(start > stop || start == arr->GetLength()){
            return NULL;
        }
        int mid = (start + stop) / 2;
        cout << "Start: " << start << " Stop: " << stop << " Mid: " << mid << endl;
        Node* node = new Node(arr->Get(mid));
        node->height = ceil(log2(stop - start + 1));
        node->left = sortedArrToBST(arr, start, mid - 1);
        node->right = sortedArrToBST(arr, mid + 1, stop);
        return node;
    }


    void traversalMap(AVLTree<T>* newTree, Node* node, T func(T value)){//применение функции map для каждого элемента дерева, обход КЛП
        if(node == NULL){
            return;
        }
        assert(func != NULL);
        newTree->Insert(func(node->key));
        traversalMap(newTree, node->left, func);
        traversalMap(newTree, node->right, func);
    }


    void traversalWhere(AVLTree<T>* newTree, Node* node, bool func(T value)){//применение функции where для каждого элемента дерева, обход КЛП
        if(node == NULL){
            return;
        }
        if(func(node->key)){
            newTree->Insert(node->key);
        }
        traversalWhere(newTree, node->left, func);
        traversalWhere(newTree, node->right, func);
    }


    bool traversalKLRSubtree(Node* nodeA, Node* nodeB){//поиск поддерева, обход КЛП
        if(nodeA == NULL && nodeB == NULL){
            return true;
        }
        if(nodeA == NULL && nodeB != NULL){
            return false;
        }
        if(nodeA != NULL && nodeB == NULL){
            return false;
        }
        if(nodeA->key == nodeB->key){
            bool resultLeft = traversalKLRSubtree(nodeA->left, nodeB->left);
            if(resultLeft){
                return traversalKLRSubtree(nodeA->right, nodeB->right);
            }
            return false;
        }
    }


    void traversalKLR(Node* node, ArraySequence<T>* str){//обход КЛП
        if(node == NULL){
            return;
        }
        str->Append(node->key);
        traversalKLR(node->left, str);
        traversalKLR(node->right, str);
    }


    void traversalKRL(Node* node, ArraySequence<T>* str){//обход КПЛ
        if(node == NULL){
            return;
        }
        str->Append(node->key);
        traversalKRL(node->right, str);
        traversalKRL(node->left, str);
    }


    void traversalLKR(Node* node, ArraySequence<T>* str){//обход ЛКП
        if(node == NULL){
            return;
        }
        traversalLKR(node->left, str);
        str->Append(node->key);
        traversalLKR(node->right, str);

    }


    void traversalLRK(Node* node, ArraySequence<T>* str){//обход ЛПК
        if(node == NULL){
            return;
        }
        traversalLRK(node->left, str);
        traversalLRK(node->right, str);
        str->Append(node->key);
    }


    void traversalRLK(Node* node, ArraySequence<T>* str){//обход ПЛК
        if(node == NULL){
            return;
        }
        traversalRLK(node->right, str);
        traversalRLK(node->left, str);
        str->Append(node->key);
    }


    void traversalRKL(Node* node, ArraySequence<T>* str){//обход ПКЛ
        if(node == NULL){
            return;
        }
        traversalRKL(node->right ,str);
        str->Append(node->key);
        traversalRKL(node->left, str);
    }


    int Height(Node* node){//высота дерева
        if(node == NULL){
            return 0;
        }
        return node->height;
    }


    Node* insert(Node* node, T value){//вставка в дерево
        if(node == NULL){
            num++;
            Node* newNode = new Node(value);
            return newNode;
        }
        if(value < node->key){
            node->left = insert(node->left, value);
        }
        else if(value > node->key){
            node->right = insert(node->right, value);
        }
        int hLeft = Height(node->left);
        int hRight = Height(node->right);
        node->height = ((hLeft > hRight) ? hLeft : hRight) + 1;
        int balance = hLeft - hRight;
        if(balance > 1){
            if(value < node->left->key){
                return rightRotation(node);
            }
            else{
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
        }
        else if(balance < -1){
            if(value > node->right->key){
                return leftRotation(node);
            }
            else{
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
        }
        return node;
    }


    Node* rightRotation(Node* node){//правый поворот
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        node->height = ((Height(node->left) > Height(node->right)) ? Height(node->left) : Height(node->right)) + 1;
        tmp->height = ((Height(tmp->left) > Height(tmp->right)) ? Height(tmp->left) : Height(tmp->right)) + 1;
        return tmp;
    }


    Node* leftRotation(Node* node){//левый поворот
        Node* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        node->height = ((Height(node->left) > Height(node->right)) ? Height(node->left) : Height(node->right)) + 1;
        tmp->height = ((Height(tmp->left) > Height(tmp->right)) ? Height(tmp->left) : Height(tmp->right)) + 1;
        return tmp;
    }


    Node* remove(Node* node, T value){//удаление
        if(node == NULL){
            return NULL;
        }
        if(value < node->key){
            node->left = remove(node->left, value);
        }
        else if(value > node->key){
            node->right = remove(node->right, value);
        }
        else{
            Node* right = node->right;
            if(node->right == NULL){
                Node* left = node->left;
                delete node;
                node = left;
            }
            else if(node->left == NULL){
                delete node;
                node = right;
            }
            else{
                while(right->left != NULL){
                    right = right->left;
                }
                node->key = right->key;
                node->right = remove(node->right, right->key);
            }
        }
        if(node == NULL){
            return node;
        }
        int hLeft = Height(node->left);
        int hRight = Height(node->right);
        node->height = ((hLeft > hRight) ? hLeft : hRight) + 1;
        int balance = hLeft - hRight;
        if(balance > 1){
            if(hLeft >= hRight){
                return rightRotation(node);
            }
            else{
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
        }
        else if(balance < -1){
            if(hRight >= hLeft){
                return leftRotation(node);
            }
            else{
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
        }
        return node;
    }


    Node* search(Node* node, T value){//поиск элемента
        if(node == NULL){
            return NULL;
        }
        T key = node->key;
        if(key == value){
            return node;
        }
        if(key > value){
            return search(node->left, value);
        }
        if(key < value){
            return search(node->right, value);
        }
    }
};
