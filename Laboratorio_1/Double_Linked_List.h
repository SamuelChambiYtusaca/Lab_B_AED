#ifndef _D_LINKED_LIST_
#define _D_LINKED_LIST_
#include "NodoD.h"
#include "iostream"
using namespace std;
template<typename T>
class Double_Linked_List{
    private:
        NodoD<T> *head;
        int size;
    public:
        Double_Linked_List();/*Constructor por defecto*/
        Double_Linked_List(const Double_Linked_List<T> &);/*Copia*/
        Double_Linked_List(Double_Linked_List<T> &&);/*Movimiento*/
        void push_back(T);/*Inserta el elemento al final de la lista*/
        void pop_back();/*Elimina el ultimo elemento de la lista*/
        void print();/*Imprime la lista*/
        void insert(T);/*Inserta elementos a la lista en orden ascendente*/
        void remove(T);/*Elimina el elemento pasado como argumento*/
        bool find(T);/*Valor booleano para comprobar la existencia de un elemento*/
        ~Double_Linked_List();
};

template<typename T>
Double_Linked_List<T>::Double_Linked_List(){
    this->head = nullptr;
    this->size = 0;
}

template<typename T>
Double_Linked_List<T>::Double_Linked_List(const Double_Linked_List<T> &p){
    this->head = nullptr;
    this->size = 0;
    NodoD<T> *aux = p.head; 
    while(aux){
        this->push_back(aux->get_dato());
        aux = aux->get_sig();
    }
}

template<typename T>
Double_Linked_List<T>::Double_Linked_List(Double_Linked_List<T> &&p){
    this->head = p.head;
    this->size = p.size;
    p.head = nullptr;
    p.size = 0;
}

template<typename T>
void Double_Linked_List<T>::push_back(T dato){
    NodoD<T> *nuevo = new NodoD<T>(dato);
    if(!this->head){
        this->head = nuevo;
    }else{
        NodoD<T> *aux = this->head;
        while(aux->get_sig()){
            aux = aux->get_sig();
        }
        aux->set_sig(nuevo);
        nuevo->set_ant(aux);
    }
    size++;
    return;
}

template<typename T>
void Double_Linked_List<T>::pop_back(){
    if(!this->head){
        cout << "La lista se encuentra vacia.\n";
        return;
    }else if(this->size == 1){
        delete head;
        this->head = nullptr;
    }
    else{
        NodoD<T> *aux = this->head;
        while(aux->get_sig()){
            aux = aux->get_sig();
        }
        aux->get_ant()->set_sig(nullptr);
        delete aux;
    }
    size--;
    return;
}

template<typename T>
void Double_Linked_List<T>::insert(T dato){
    NodoD<T> *nuevo = new NodoD<T>(dato);
    if(!this->head){
        head = nuevo;
    }else{
        NodoD<T>*aux = this->head;
        if (this->head->get_dato() > dato) {
            nuevo->set_sig(this->head);
            this->head = nuevo;
            nuevo->get_sig()->set_ant(nuevo);
        }
        else{
            while(aux->get_sig() && aux->get_sig()->get_dato() < dato ){
                aux = aux->get_sig();
            }
            nuevo->set_sig(aux->get_sig());
            if(aux->get_sig())
                aux->get_sig()->set_ant(nuevo);
            aux->set_sig(nuevo);
            nuevo->set_ant(aux);  
        }
    }
    size++;
    return;
}

template<typename T>
void Double_Linked_List<T>::remove(T dato){
    if(!this->head){
        cout << "La lista se encuentra vacia\n";
        return;
    }else{
        NodoD<T> *aux = this->head;
        while(aux->get_sig() && aux->get_dato()!=dato){
            aux = aux->get_sig();
        }
        if(aux->get_dato() == dato){
            if(aux->get_sig()){
                aux->get_sig()->set_ant(aux->get_ant());
            }
            aux->get_ant()->set_sig(aux->get_sig());
            delete aux;            
        }else{
            cout << "Elemento no encontrado\n";
            return;
        }
    }
    size--;
    return;
}

template<typename T>
void Double_Linked_List<T>::print(){
    NodoD<T> *ptr = head;
    if(!head){
        cout << "La lista esta vacia.\n";
    }else{
        int i = 1;
        while(i<this->size){
            cout<<"[" << i << ":" << ptr->get_dato() << "]->";
            ptr = ptr->get_sig();
            i++; 
        }
        cout << "[" << i << ":" << ptr->get_dato() << "]\n";
        return;
    }
}

template<typename T>
bool Double_Linked_List<T>::find(T dato){
    if(!this->head){
        return false;
    }else{
        NodoD<T>*aux = this->head;
        while(aux->get_sig()){
            if(aux->get_dato()==dato)
                return true;
            aux = aux->get_sig();
        }
        return false;
    }
}

template<typename T>
Double_Linked_List<T>::~Double_Linked_List(){
    while(this->size){
        this->pop_back();
    }
    delete head;
}
#endif
