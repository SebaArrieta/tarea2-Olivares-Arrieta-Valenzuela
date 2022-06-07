#include <iostream>

using namespace std;
typedef int tElem;

//Nodo que contiene informacion, hijo derecho e izquierdo, un contador y contadorMenor que corresponde a los que son menores que el 
struct tNodo{
    tElem info;
    int contador;
    int contadorMenor;
    tNodo* izq;
    tNodo* der;
};

/*****
* class RankedABB
******
* Clase que sirve para crear un arbol de busqueda binario, hacer insersion de nodos, buscar un nodo en especifico dentro del arbol,
y tambien ver los nodos menores que un nodo
*****/
class RankedABB{
    public:
        RankedABB();
        ~RankedABB();
        void insert(tElem x);
        void insert(tElem x, tNodo *&nodo);
        bool find(tElem x,tNodo *&tNodo);
        bool find(tElem x);
        int rank(tElem x);
        int rank(tElem x,tNodo *tNodo);
        tNodo* nuevoNodo(tElem x);
        void clear(tNodo *&nodo);
    private:
        int setContador(tNodo *nodo);
        void setContadorMenor(tNodo *nodo);
        tNodo *raiz; // se crea la raiz como un puntero a nodos
        int numEle;
};

/*****
*Funcion tipo: RankedABB::
 Nombre Funcion:RankedABB
******
* constructor de la clase RankedABB,
el constructor establece la raiz en null y el num ele en 0
******
* Input:
* No posee input
******
* Returns:
* No retorna
*****/
RankedABB::RankedABB(){
    raiz = NULL;
    numEle = 0;
}

/*****
*Funcion tipo: ~RankedABB::
 Nombre Funcion: ~RankedABB
******
* Destructor de la clase RankedABB.
El destructor hace una llamada al metodo clear para eliminar cada nodo que existe en el arbol,
finalmente elimina el nodo faltalte el cual es el nodo raiz
******
* Input:
* No posee imput
******
* Returns:
* No retorna
*****/
RankedABB::~RankedABB(){ //elimina mediante el clear y luego elimina la raiz
    clear(raiz);
    delete raiz;
}

/*****
*Funcion tipo: void 
 Nombre Funcion: RankedABB::clear
******
* El metodo va eliminando cada nodo perteneciente al arbol mediante una busqueda recursiva in order.
El metodo va hacia el nodo de más a la izquierda y ve si es NULL,
si el nodo es NULL vuelve al padre y elimina el nodo izquierdo, luego hace lo mismo con el derecho.
******
* Input:
* tNodo *&nodo: Parametro que se usa para pasar un puntero por referencia, en este caso un nodo de un arbol
******
* Returns:
*void
*****/
void RankedABB::clear(tNodo *&nodo){ //va eliminando mediante busqueda in order
    if(nodo != NULL){
        clear(nodo->izq); 
        delete nodo->izq;
        clear(nodo->der);
        delete nodo->der;
    }
}

/*****
* Funcion tipo: tNodo* 
  Nombre Funcion: RankedABB::nuevoNodo
******
* Metodo que crea un nuevo nodo mediante memoria dinamica.
Este nodo contendra la informacion pasada por parametros y establecerá sus hijos en NULL.
Luego el metodo aumenta 1 al num de elementos y retorna este nuevo nodo

******
* Input:
* tElem x : Parametro que contiene la información del nuevo nodo que se quiere añadir
******
* Returns:
* tNodo*, retorna el nuevo nodo creado por memoria dinamica
*****/
tNodo* RankedABB::nuevoNodo(tElem x){
    tNodo* nodo = new tNodo;
    nodo->der = NULL;
    nodo->izq = NULL;
    nodo->info = x;
    nodo->contador = 0;
    nodo->contadorMenor = 0;
    numEle++;
    return nodo;
}

/*****
* Funcion tipo: void
  Nombre Funcion: insert
******
* Metodo que hace una llamada a una sobrecarga suya, luego llama al metodo seContador para contar....
y finalmente llama al metodo setContadorMenor
******
* Input:
* tElem x : Parametro que contiene la información del nuevo nodo que se quiere insertar
******
* Returns:
* void
*****/
void RankedABB::insert(tElem x){ //se crea una sobrecarga del metodo, para que al acceder a este metodo desde el main no sea necesario dar un nodo
    insert(x,raiz);
    setContador(raiz);
    setContadorMenor(raiz);

}

/*****
* Funcion tipo: void
  Nombre Funcion: insert
******
*Metodo que mediante recursividad va recorriendo el arbol viendo si el valor entregado es menor que el del nodo actual o mayor,
dependiendo de si es mayor o menor toma un camino u otro,
estos caminos hacen una llamada a la función de manera recursiva,
pasandoles por parametro el nodo izquierdo o derecho y la informacion del nuevo nodo,
finalmente cuando llega a un nodo NULL se crea un nuevo nodo 
haciendo una llamada al metodo nuevoNodo, y se le pasa por parametro el valor.
******
* Input:
* tElem x : Parametro que contiene la información del nuevo nodo a insertar
* tNodo *&nodo: Parametro que se usa para pasar un puntero por referencia, en este caso un nodo de un arbol
******
* Returns:
* void
*****/
void RankedABB::insert(tElem x, tNodo *&nodo){
    if(nodo == NULL){
        nodo = nuevoNodo(x); //le asignamos este nuevo nodo para quitarle el valor de NULL
    }
    else{
        if(nodo->info > x) insert(x,nodo->izq);
        else if(nodo->info < x) insert(x,nodo->der);
        else return;
    }
}

/*****
* Funcion tipo: int
  Nombre Funcion: setContador
******
* Función que contabiliza todos los hijos de cada nodo y los alacena en la el parámetro contador además de esto también obtiene la cantidad de hijos de los sub arboles izquierdos
y los guarda en la variable contadorMenor, la finalidad de esta función es tener los valores necesarios para calcular la cantidad de nodos que tengan un valor menor, hasta ahora
solo se calcula una parte de los nodos menores y el resto se complementará en la función setContadorMenor.
******
* Input:
* tNodo *nodo: parametro que indica el nodo por el cual se iniciara el recorrido para iniciar el conteo de nodos.
* .......
******
* Returns:
* esta funcion es recursiva y retorna el parametro contador el cual indica la cantidad de hijos del nodo indicado en el parametro
*****/
int RankedABB::setContador(tNodo *nodo){ 
    if(nodo == NULL){
        return -1;
    }

    int izq = setContador(nodo->izq);
    nodo->contadorMenor =0;
    nodo->contador = 0;
    int der = setContador(nodo->der);
    nodo->contadorMenor=0;
    nodo->contador = 0;
    
    if(izq != -1){
        nodo->contadorMenor += izq + 1;
    }

    nodo->contador += izq+der+2;

    return nodo->contador;
}

/*****
* Funcion tipo: void 
  Nombre Funcion: setContadorMenor
******
* Esta función ayuda a complementar la variable ContadorMenor de cada nodo al sumar la cantidad de nodos con valores menores al pasado por parámetro que se encuentran en otras 
zonas del árbol que no sean solo del lado izquierdo del nodo en el parámetro.

******
* Input:
* tNodo *&nodo: Parametro que se usa para pasar un puntero por referencia, en este caso un nodo de un arbol
* .......
******
* Returns:
* void, esta funcion no retorna nada y es recursiva 
*****/
void RankedABB::setContadorMenor(tNodo *nodo){
    if(nodo == NULL){
        return;
    }
    if(nodo->der != NULL){
        nodo->der->contadorMenor += nodo->contadorMenor+1;

        if(nodo->der->izq != NULL){
            tNodo *aux = nodo->der->izq;
            while (aux != NULL){
                aux->contadorMenor += nodo->contadorMenor+1;
                aux = aux->izq;
            }
        }
    }
    
    setContadorMenor(nodo->izq);
    setContadorMenor(nodo->der);
}

/*****
* Funcion tipo: bool 
  Nombre Funcion:find
******
* Metodo que llama a una sobrecarga suya, retornando el valor que retorne el metodo
******
* Input:
* tElem x : Información del nodo a buscar
******
* Returns:
* bool, retorna true en caso de que el metodo a llamar encuentre el nodo y false cuando no lo encuentre.
*****/
bool RankedABB::find(tElem x){ //se crea una sobrecarga del metodo, para que al acceder a este metodo desde el main no sea necesario dar un nodo
    return find(x,raiz);
}

/*****
* Funcion tipo: bool 
  Nombre Funcion:find
******
*Metodo que mediante recursividad va recorriendo el arbol viendo si el valor entregado es menor que el del nodo actual, mayor o igual
dependiendo de si es mayor o menor toma un camino u otro,
estos caminos hacen una llamada a la función de manera recursiva,
pasandoles por parametro el nodo izquierdo o derecho y la informacion del nuevo nodo,
cuando llega a un nodo que contiene la misma información que la pasada por parametros el metodo retorna true.
Si el metodo no encuentra ninguno que sea igual, al llegar a un nodo NULL retornará false
******
* Input:
* tElem x : información del parametro a buscar
* tNodo *&nodo : Parametro que se usa para pasar un puntero por referencia, en este caso un nodo de un arbol
******
* Returns:
* bool, retorna true en caso de que se encuentre el nodo, y false en caso de que no se encuentre
*****/
bool RankedABB::find(tElem x,tNodo *&nodo){ 
    if(nodo != NULL){   
        if(nodo->info > x) return find(x, nodo->izq); 
        else if(nodo->info < x) return find(x, nodo->der); 
        else if(nodo->info == x) return true; 
    }
    return false;
}

/*****
* Funcion tipo: int 
  Nombre Funcion:rank
******
* Metodo que llama a una sobrecarga suya pasandole por parametros la informacion del nodo
******
* Input:
* tElem x : Parametro que contiene la informacion del metodo que se le quiere buscar los menores
* .......
******
* Returns:
* int, retorna el numero que entregue el metodo a llamar, el numero corresponderá a los nodos que son menores que el nodo que se busca
*****/
int RankedABB::rank(tElem x){ //se crea una sobrecarga del metodo, para que al acceder a este metodo desde el main no sea necesario dar un nodo
    return rank(x,raiz);
}

/*****
* Funcion tipo:int 
  Nombre Funcion:rank
******
* metodo que se encarga de realizar las comparaciones necesarias mientras realiza un recorrido por el arbol y asi determinar todos los nodos cuyos valores sean menores a los valores
pasados por el paramentro, para esto hace uso de la variable contadorMenor y de una busqueda de algun nodo cuyo valor se aproxime o sea igual al seleccionado.
******
* Input:
* tElem x: entero seleccionado para iniciar la busqueda de los valores menores o iguales al mismo en el arbol.
tNodo *nodo: nodo cuyo valor servira como referencia para encontrar un valor que se aproxime o iguale a x.
* .......
******
* Returns:
* int retorna la cantodad de nodos cuyos valores sean menores o iguales a x.
*****/
int RankedABB::rank(tElem x,tNodo *nodo){
    if(nodo != NULL){   
        if(x > nodo->info){
            if(nodo->der != NULL){
                return rank(x, nodo->der);
            }else{
                return nodo->contadorMenor+1;
            }
        }else if(x < nodo->info){
            if(nodo->izq != NULL){
                return rank(x, nodo->izq);
            }else{
                return nodo->contadorMenor;
            }
        }else{
            return nodo->contadorMenor + 1;
        }
    }else{
        return -1;
    }
    
}
