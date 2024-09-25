template<class T>
ArbolAVL<T>::ArbolAVL() : raiz(nullptr) {}

template<class T>
ArbolAVL<T>::~ArbolAVL() {
    delete raiz;
}

template<class T>
bool ArbolAVL<T>::esVacio() {
    return this->raiz == nullptr;
}

template<class T>
int ArbolAVL<T>::altura() {
    return esVacio() ? -1 : altura(this->raiz);
}

template<class T>
int ArbolAVL<T>::altura(Nodo<T>* nodoActual) {
    if (nodoActual == nullptr) {
        return -1;
    }
    int alturaIzq = altura(nodoActual->obtenerHijoIzq());
    int alturaDer = altura(nodoActual->obtenerHijoDer());
    return std::max(alturaIzq, alturaDer) + 1;
}

template<class T>
int ArbolAVL<T>::tamano() {
    return tamano(this->raiz);
}

template<class T>
int ArbolAVL<T>::tamano(Nodo<T>* nodoActual) {
    if (nodoActual == nullptr) {
        return 0;
    }
    return 1 + tamano(nodoActual->obtenerHijoIzq()) + tamano(nodoActual->obtenerHijoDer());
}

template<class T>
bool ArbolAVL<T>::insertar(T& val) {
    raiz = insertar(raiz, val);
    return true;
}

template<class T>
Nodo<T>* ArbolAVL<T>::insertar(Nodo<T>* nodo, T& val) {
    if (nodo == nullptr) return new Nodo<T>(val);

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(insertar(nodo->obtenerHijoIzq(), val));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(insertar(nodo->obtenerHijoDer(), val));
    } else {
        return nodo;
    }

    nodo->fijarAltura(1 + std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && val < nodo->obtenerHijoIzq()->obtenerDato()) {
        return rotarDerecha(nodo);
    }
    if (balance < -1 && val > nodo->obtenerHijoDer()->obtenerDato()) {
        return rotarIzquierda(nodo);
    }
    if (balance > 1 && val > nodo->obtenerHijoIzq()->obtenerDato()) {
        return rotarIzquierdaDerecha(nodo);
    }
    if (balance < -1 && val < nodo->obtenerHijoDer()->obtenerDato()) {
        return rotarDerechaIzquierda(nodo);
    }

    return nodo;
}

template<class T>
int ArbolAVL<T>::obtenerBalance(Nodo<T>* nodo) {
    if (nodo == nullptr) return 0;
    return altura(nodo->obtenerHijoIzq()) - altura(nodo->obtenerHijoDer());
}

template<class T>
Nodo<T>* ArbolAVL<T>::rotarDerecha(Nodo<T>* y) {
    Nodo<T>* x = y->obtenerHijoIzq();
    Nodo<T>* T2 = x->obtenerHijoDer();

    x->fijarHijoDer(y);
    y->fijarHijoIzq(T2);

    y->fijarAltura(std::max(altura(y->obtenerHijoIzq()), altura(y->obtenerHijoDer())) + 1);
    x->fijarAltura(std::max(altura(x->obtenerHijoIzq()), altura(x->obtenerHijoDer())) + 1);

    return x;
}

template<class T>
Nodo<T>* ArbolAVL<T>::rotarIzquierda(Nodo<T>* x) {
    Nodo<T>* y = x->obtenerHijoDer();
    Nodo<T>* T2 = y->obtenerHijoIzq();

    y->fijarHijoIzq(x);
    x->fijarHijoDer(T2);

    x->fijarAltura(std::max(altura(x->obtenerHijoIzq()), altura(x->obtenerHijoDer())) + 1);
    y->fijarAltura(std::max(altura(y->obtenerHijoIzq()), altura(y->obtenerHijoDer())) + 1);

    return y;
}

template<class T>
bool ArbolAVL<T>::eliminar(T& val) {
    if (raiz != nullptr) {
        raiz = eliminar(raiz, val);
        return true;
    }
    return false;
}

template<class T>
Nodo<T>* ArbolAVL<T>::eliminar(Nodo<T>* nodo, T& val) {
    if (nodo == nullptr) return nodo;

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(eliminar(nodo->obtenerHijoIzq(), val));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(eliminar(nodo->obtenerHijoDer(), val));
    } else {
        if (nodo->obtenerHijoIzq() == nullptr || nodo->obtenerHijoDer() == nullptr) {
            Nodo<T>* temp = nodo->obtenerHijoIzq() ? nodo->obtenerHijoIzq() : nodo->obtenerHijoDer();

            if (temp == nullptr) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }

            delete temp;
        } else {
            Nodo<T>* temp = encontrarMinimo(nodo->obtenerHijoDer());
            nodo->fijarDato(temp->obtenerDato());
            nodo->fijarHijoDer(eliminar(nodo->obtenerHijoDer(), temp->obtenerDato()));
        }
    }

    if (nodo == nullptr) return nodo;

    nodo->fijarAltura(1 + std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->obtenerHijoIzq()) >= 0) {
        return rotarDerecha(nodo);
    }
    if (balance > 1 && obtenerBalance(nodo->obtenerHijoIzq()) < 0) {
        nodo->fijarHijoIzq(rotarIzquierda(nodo->obtenerHijoIzq()));
        return rotarDerecha(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->obtenerHijoDer()) <= 0) {
        return rotarIzquierda(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->obtenerHijoDer()) > 0) {
        nodo->fijarHijoDer(rotarDerecha(nodo->obtenerHijoDer()));
        return rotarIzquierda(nodo);
    }

    return nodo;
}

template<class T>
Nodo<T>* ArbolAVL<T>::encontrarMinimo(Nodo<T>* nodo) {
    Nodo<T>* actual = nodo;
    while (actual->obtenerHijoIzq() != nullptr) {
        actual = actual->obtenerHijoIzq();
    }
    return actual;
}

template<class T>
std::vector<T> ArbolAVL<T>::inOrden() {
    std::vector<T> elementos;
    inOrden(raiz, elementos);
    return elementos;
}

template<class T>
void ArbolAVL<T>::inOrden(Nodo<T>* nodo, std::vector<T>& elementos) {
    if (nodo != nullptr) {
        inOrden(nodo->obtenerHijoIzq(), elementos);
        elementos.push_back(nodo->obtenerDato());
        inOrden(nodo->obtenerHijoDer(), elementos);
    }
}

template<class T>
void ArbolAVL<T>::preOrden() {
    preOrden(raiz);
}

template<class T>
void ArbolAVL<T>::preOrden(Nodo<T>* nodoActual) {
    if (nodoActual != nullptr) {
        std::cout << nodoActual->obtenerDato() << " ";
        preOrden(nodoActual->obtenerHijoIzq());
        preOrden(nodoActual->obtenerHijoDer());
    }
}

template<class T>
void ArbolAVL<T>::posOrden() {
    posOrden(raiz);
}

template<class T>
void ArbolAVL<T>::posOrden(Nodo<T>* nodoActual) {
    if (nodoActual != nullptr) {
        posOrden(nodoActual->obtenerHijoIzq());
        posOrden(nodoActual->obtenerHijoDer());
        std::cout << nodoActual->obtenerDato() << " ";
    }
}

template<class T>
void ArbolAVL<T>::nivelOrden() {
    if (raiz == nullptr) return;

    std::queue<Nodo<T>*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        Nodo<T>* nodoActual = cola.front();
        cola.pop();
        std::cout << nodoActual->obtenerDato() << " ";

        if (nodoActual->obtenerHijoIzq() != nullptr) {
            cola.push(nodoActual->obtenerHijoIzq());
        }
        if (nodoActual->obtenerHijoDer() != nullptr) {
            cola.push(nodoActual->obtenerHijoDer());
        }
    }
}

#endif 
