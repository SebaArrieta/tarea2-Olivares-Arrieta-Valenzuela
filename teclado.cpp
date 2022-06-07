#include <iostream>
#include <fstream>
using namespace std;
typedef char tElem;

//Nodo que tiene una información y un nodo que le sigue
struct tNodo{
    tElem info;
    tNodo* sig;
};

/*****
* class Lista
******
* clase Lista que crea una lista enlazada, en esta lista enlazada se puede añadir un nuevo elemento, mover el puntero al inicio,
mover el puntero al final, atras o al nodo siguiente, la lista cuenta con un tamaño, una posicion, una cabeza, una cola y un nodo actual.
El nodo siguiente del nodo curr correspondera al nodo actual, es decir curr->sig, será el nodo actual, debido a que el nodo head
solo sirve como head, no contiene información y siempre sera el primer nodo de la lista enlazada, aunque no se puede acceder a el desde fuera
*****/
class Lista{
    private:
        tNodo* head;
        tNodo* tail;
        tNodo* curr;
        unsigned int size;
        unsigned int pos;
    public:
        Lista();
        ~Lista();
        tNodo* crearNodo(tElem x);
        int insertar(tElem x);
        void moveToStart();
        void moveToEnd();
        void prev();
        void next();
        unsigned int getSize();
        tElem getInfo();
        void clear();
};

/*****
* Lista::Lista
******
* Constructor de la clase Lista, que crea un nodo head el cual es igual a la cola y al actual,
establece el nodo siguiente en NULL
finalmente establece tamaño y posicion en 0;
******
* Input:
* No posee input
******
* Returns:
* No retorna
*****/
Lista::Lista(){
    head = tail = curr = new tNodo;
    head->sig = tail ->sig = curr->sig = NULL;
    size = 0; pos = 0;
}

/*****
* Lista::~Lista
******
* Destructor de la clase Lista,
El destructor mediante un ciclo y partiendo desde el head, establece un nodo auxiliar que va a corresponder a la cabeza actual,
luego elimina la cabeza, y la nueva cabeza será el nodo auxiliar, hace esto hasta que el head sea NULL
finalmente elimina el head
******
* Input:
* No posee input
******
* Returns:
* No retorna
*****/
Lista::~Lista(){ // destructor que elimina todos los nodos para que no queden en la memoria
    tNodo* nodo;

    while(head!= NULL){ //se detiene cuando elimine todos los nodos y solo quede el ultimo que apunta a NULL;
        nodo = head->sig; //apunta al siguiente y al siguiente asi sucesivamente
        delete head; //eliminamos el head de la lista
        head = nodo; //el nuevo head va a ser el que continuaba al head actual
    }
    delete head; // elimina el ultimo head
}

/*****
* int Lista::insertar
******
*Metodo que crea un nuevo nodo en cualquier posicion, mediante la ayuda de un nodo auxiliar.
El nuevo nodo va a estar entre el nodo actual y el nodo siguiente del actual.
******
* Input:
* tElem x : información del nuevo nodo que se desea añadir
******
* Returns:
* int, retorna la posición del nuevo nodo que se añadió
*****/
int Lista::insertar(tElem x){
    tNodo* aux = curr->sig;
    curr->sig = new tNodo;
    curr->sig->info = x;
    curr->sig->sig = aux;
    if(tail == curr) {tail = curr->sig; } //si el actual es cola, la cola será el nuevo que se creó
    size++;
    return pos;
}

/*****
* void Lista::moveToStart
******
* Metodo que establece como nodo actual el head de la lista, y establece que la posicion es 0
******
* Input:
* .......
******
* Returns:
* void
*****/
void Lista::moveToStart(){ curr = head; pos = 0; }

/*****
* void Lista::moveToEnd
******
* Metodo que establece como nodo actual la cola de la lista (tail), y establece que la posicion es igual al tamaño de la lista
******
* Input:
* .......
******
* Returns:
* void
*****/
void Lista::moveToEnd(){ curr = tail; pos = size; }

/*****
* void Lista::prev
******
* metodo que establece el nodo actual como el nodo que se encuentra atras de este, la posicion disminuye en 1
******
* Input:
* .......
******
* Returns:
* void
*****/
void Lista::prev(){
    tNodo* nodo;
    if (curr == head){ return; } //si se encuentra en head no se puede ir más atras
    nodo = head;    
    while(nodo->sig != curr){ nodo = nodo->sig; } // va avanzando hasta llegar al anterior del actual
    curr = nodo; // el nodo actual ahora es el anterior 
    pos--;
}

/*****
* void Lista::next
******
* metodo que establece el nodo actual como el nodo que se encuentra despues de este, la posicion aumenta en 1
******
* Input:
* .......
******
* Returns:
* void
*****/
void Lista::next(){
    if(curr!=tail){curr = curr->sig; pos++; }
}

/*****
* void Lista::getSize
******
* metodo que retorna el tamaño de la lista
******
* Input:
* .......
******
* Returns:
* unsigned int, retorna el tamaño de la lista
*****/
unsigned int Lista::getSize(){ return size;}

/*****
* tElem Lista::getInfo
******
* Metodo que retorna la información del nodo actual
******
* Input:
* .......
******
* Returns:
* tElem,retorna la información del nodo actual, si el nodo es NULL retorna \0
*****/
tElem Lista::getInfo(){
    if(curr->sig != NULL){
        return curr->sig->info;
    }
    return '\0';
}

/*****
* void modificarTexto
******
* Función que mediante un archivo de texto entregado va leyendo el texto y cada caracter lo va añadiendo a una lista de la clase Lista
si el caracter corresponde a: '<','>',']','[' el nodo actual y la posicion correspondera a,
el nodo anterior, nodo siguiente, nodo final, nodo inicial respectivamente, este caracter no se añade a la lista,
luego continua añadiendo desde la posicion en que quedó hasta encontrar nuevamente uno de los caracter mencionados anteriormente,
el metodo deja de añadir cuando encuentra un caracter del tipo '\r', del tipo '\n' o cuando se llegue al final del archivo,
Cuando suceda algo de esto se añade cada información del nodo en un archivo de texto, luego se elimina el objeto lista.
Luego repite el proceso. El proceso para completamente al llegar al final del archivo
******
* Input:
* .......
******
* Returns:
* void
*****/
void modificarTexto(){
    ifstream entrada; // archivo modo lectura
    ofstream salida; // archivo modo escritura
    entrada.open("teclado-entrada.txt"); //abre el archivo "teclado-entrada.txt"
    if(!entrada.is_open()){
        cout<<"error al abrir el archivo de entrada"<<endl; 
        return;
    }

    salida.open("teclado-salida.txt"); // abre el archivo "teclado-salida.txt"
    if(!salida.is_open()){
        cout<<"error al abrir el archivo de salida"<<endl; 
        return;
    }

    Lista* list = new Lista;  // crea un objeto tipo Lista* de nombre list
    char c;// caracter
    unsigned int size;
    entrada.get(c); //obtiene un caracter del archivo y se lo establece a c
    while(!entrada.eof()){ //para cuando llegue al final del archivo
        while(c != '\r' && c != '\n' && !entrada.eof()){ //se detiene cuando encuentra un salto de linea
            switch(c){
                case '<':
                    list->prev(); // va a la posicion anterior de la lista
                    break;
                case '>':
                    list->next();// va a la posicion siguiente de la lista
                    break;
                case '[':
                    list->moveToStart(); // va a la posicion inicial de la lista
                    break;
                case ']':
                    list->moveToEnd(); // va a la posicion final de la lista
                    break;
                default:
                    list->insertar(c); // inserta un nuevo nodo en la posicion actual con la informacion del char c
                    list->next(); // se mueve a la posicion siguiente de la lista
                    break;
            }
            entrada.get(c); //obtiene el caracter del archivo
        }
        size = list->getSize(); // establece size como el tamaño de la lista
        list->moveToStart(); // la posicion actual de la lista es la inicial

        for(unsigned int i = 0; i<size;i++){ // va añadiendo cada elemento de la lista en un archivo
            salida<<list->getInfo();
            list->next();
        }
        delete list; // elimina el objeto list
        list = new Lista;
        entrada.get(c);//se salta el \r
        entrada.get(c);// se salta el \n
        if(!entrada.eof()){ salida<<'\n'; } // solo hace el salto de linea cuando no sea el final del texto
    }
    delete list; //elimina la ultima lista creada
    entrada.close(); //cierra el archivo entrada
    salida.close(); //cierra el archivo salida

} 

/*****
* int main
******
* Funcion main que llama a la funcion modificar texto
******
* Input:
* .......
******
* Returns:
* int, int que indica que el prograba acaba, no es necesario 
*****/
int main(){
    modificarTexto();
    return 0;
}