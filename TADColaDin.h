//
//  TADColaDin.h
//  AAEDXP5
//
//  Created by AliciaOliva on 3/12/25.
//
// ===== IMPLEMENTACIÓN DE COLA COMO ESTRUCTURA ENLAZADA CIRCULAR =====

#include <cstddef>
#include <utility>

template <typename T>
class Queue{
public:
    Queue();
    ~Queue();
    Queue(const Queue& Q);
    bool empty();
    Queue& operator =(const Queue& Q);
    const T& start() const;
    const size_t length();
    void pop();
    void push(const T& x);
    
private:
    struct node {
        T elem;
        node* sig;
        node(const T& e, node* p = nullptr) : elem(e), sig(p) {}
    };
    node* end;
    size_t node_counter;
};

template <typename T>
Queue<T>::Queue(){
    end = nullptr;
    node_counter = 0;
}

template <typename T>
Queue<T>::~Queue(){
    if (end != nullptr) // si la cola no está vacía || Alternativa: node_counter != 0
    {
        node* primero = end->sig; // guardamos el primer elemento para poder acceder después
        end->sig = nullptr; // con esto rompemos el círculo, y ahora podemos borrar
    
        // Como si fuera una lista enlazada normal
        node* actual = primero;
        while(actual != nullptr){
            node* aux = actual->sig;
            delete actual;
            actual = aux;
        }
    }
}

template <typename T>
Queue<T>::Queue(const Queue& Q) : end(nullptr), node_counter(0) {
    if (Q.end != nullptr) {  // si la cola Q no está vacía
        // copiar el primer nodo
        node* primero_Q = Q.end->sig;  // primer nodo de Q
        end = new node(primero_Q->elem, nullptr);  // crear primer nodo de la copia
        node* ultimo = end;  // para ir enlazando
        
        // copiar el resto de nodos
        node* actual_Q = primero_Q->sig;  // Ssgundo nodo de Q
        while (actual_Q != primero_Q) {  // hasta volver al primero
            ultimo->sig = new node(actual_Q->elem, nullptr);
            ultimo = ultimo->sig;
            actual_Q = actual_Q->sig;
        }
        
        // cerrar el círculo
        ultimo->sig = end;
        
        node_counter = Q.node_counter;
    }
}

template <typename T>
inline bool Queue<T>::empty(){
    return node_counter == 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& Q) {
    if (this != &Q) {  // autoasignación
        // destruir la cola donde copiamos
        if (end != nullptr) {
            node* primero = end->sig;
            end->sig = nullptr;  // romper el círculo
            node* actual = primero;
            while (actual != nullptr) {
                node* aux = actual->sig;
                delete actual;
                actual = aux;
            }
        }
        
        // copiar desde Q
        end = nullptr;
        node_counter = 0;
        
        if (Q.end != nullptr) {
            // copiar el primer elemento
            node* primero_Q = Q.end->sig;
            end = new node(primero_Q->elem);
            node* ultimo = end;
            
            // copiar el resto
            for (node* p = primero_Q->sig; p != primero_Q; p = p->sig) {
                ultimo = ultimo->sig = new node(p->elem);
            }
            
            // cerrar
            ultimo->sig = end;
            
            node_counter = Q.node_counter;
        }
    }
    return *this;
}

template <typename T>
inline const T& Queue<T>::start() const{
    if (end != nullptr) return end->sig->elem;
}

template <typename T>
inline const size_t Queue<T>::length(){
    return node_counter;
}

template <typename T>
void Queue<T>::pop(){
    if (end != nullptr){ // no esta vacia
        if (end->sig == end){ // queda solo un nodo
            delete end;
            end = nullptr;
        }
        else {
            node* aux = end->sig;
            end->sig = end->sig->sig;
            delete aux;
        }
        --node_counter;
    }
}

template <typename T>
void Queue<T>::push(const T& x){
    if (end == nullptr){ // si la cola esta vacia
        end = new node(x);
        end->sig = end; // apunta a si mismo
    }else{
        node* nuevo = new node(x, end->sig);
        end->sig = nuevo; // unimos
        end = nuevo; // ahora este es el ultimo
    }
    ++node_counter;
}



