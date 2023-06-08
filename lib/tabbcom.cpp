#include "tabbcom.h"

TVectorCom sumarVectores(TVectorCom v1,TVectorCom v2){
    for(int i=1;i<=v2.Tamano();i++){
        v1.Redimensionar(v1.Tamano()+1);
        v1[v1.Tamano()]=v2[i];
    }
    return v1;
}

TNodoABB::TNodoABB()
{
    this->item = TComplejo();
    this->iz = TABBCom();
    this->de = TABBCom();
}

TNodoABB::TNodoABB(const TNodoABB &copia)
{
    this->item = copia.item;
    this->iz = copia.iz;
    this->de = copia.de;
}

TNodoABB::~TNodoABB()
{
    this->item = TComplejo();
    this->iz = TABBCom();
    this->de = TABBCom();
}

TNodoABB &TNodoABB::operator=(const TNodoABB &objeto)
{
    if (this != &objeto)
    {
        this->item = objeto.item;

        if (objeto.iz.nodo != NULL)
        {
            this->iz.nodo = new TNodoABB(*objeto.iz.nodo);
        }
        else
        {
            this->iz.nodo = NULL;
        }
        if (objeto.de.nodo != NULL)
        {
            this->de.nodo = new TNodoABB(*objeto.de.nodo);
        }
        else
        {
            this->de.nodo = NULL;
        }
    }
    return *this;
}

TABBCom::TABBCom()
{
    this->nodo = NULL;
}

TABBCom::TABBCom(const TABBCom &copia)
{
    
    if(!copia.EsVacio()){
        this->nodo = new TNodoABB();
        this->nodo->item = copia.nodo->item;
        this->nodo->iz = copia.nodo->iz;
        this->nodo->de = copia.nodo->de;
    }
    else{
        this->nodo=NULL;
    }
}

TABBCom::~TABBCom()
{
    delete nodo;
    this->nodo = NULL;
}

TABBCom &TABBCom::operator=(const TABBCom &copia)
{
    if (this != &copia)
    {
        if (copia.nodo != NULL)
        {
            (*this).~TABBCom();
            this->nodo = new TNodoABB();
            this->nodo->item = copia.nodo->item;
            this->nodo->iz = copia.nodo->iz;
            this->nodo->de = copia.nodo->de;
        }
        else
        {
            nodo = NULL;
        }
    }

    return *this;
}

bool TABBCom::operator==(const TABBCom &objeto)
{
    if (this->EsVacio() && objeto.EsVacio())
        return true;
    else if(this->EsVacio() || objeto.EsVacio())
        return false;
    TABBCom copiaObjeto = objeto;
    TVectorCom inorden1 = this->Inorden();
    TVectorCom inorden2 = copiaObjeto.Inorden();

    return inorden1 == inorden2;
}

bool TABBCom::EsVacio() const
{
    return this->nodo == NULL;
}

bool TABBCom::Insertar(const TComplejo &objeto)
{
    if (this->EsVacio())
    {
        this->nodo = new TNodoABB();
        this->nodo->item = objeto;
        return true;
    }
    else
    {
        if (this->nodo->item == TComplejo(objeto))
        {
            return false;
        }
        else if (this->nodo->item.Mod() > TComplejo(objeto).Mod())
        {
            return nodo->iz.Insertar(objeto);
        }
        else
        {
            return nodo->de.Insertar(objeto);
        }
    }
}

bool TABBCom::Borrar(const TComplejo &objeto)
{
    if (!Buscar(objeto))
    {
        return false;
    }
    else
    {
        this->nodo = BorrarAux(this->nodo, objeto);
        return true;
    }
}

TNodoABB *TABBCom::BorrarAux(TNodoABB *nodo, const TComplejo &objeto)
{
    TComplejo objetoCopia(objeto);
    if (nodo == NULL)
    {
        return nodo;
    }

    if (objetoCopia < nodo->item)
    {
        nodo->iz.nodo = BorrarAux(nodo->iz.nodo, objeto);
    }
    else if (objetoCopia > nodo->item)
    {
        nodo->de.nodo = BorrarAux(nodo->de.nodo, objeto);
    }
    else
    {
        if (nodo->iz.EsVacio())
        {
            TNodoABB *aux = nodo->de.nodo;
            delete nodo;
            return aux;
        }
        else if (nodo->de.EsVacio())
        {
            TNodoABB *aux = nodo->iz.nodo;
            delete nodo;
            return aux;
        }
        else
        {
            nodo->item = MayorMenores(nodo->iz.nodo);
            nodo->iz.nodo = BorrarAux(nodo->iz.nodo, nodo->item);
        }
    }

    return nodo;
}

TComplejo TABBCom::MayorMenores(TNodoABB *n)
{
    TComplejo mayor = n->item;

    while (n->de.nodo != nullptr)
    {
        n = n->de.nodo;
        mayor = n->item;
    }

    return mayor;
}

bool TABBCom::Buscar(const TComplejo &objeto)
{
    bool encontrado = false;

    if (this->EsVacio())
    {
        return false;
    }
    else if (this->nodo->item == objeto)
    {
        encontrado = true;
    }
    else if (this->nodo->iz.Buscar(objeto))
    {
        encontrado = true;
    }
    else if (this->nodo->de.Buscar(objeto))
    {
        encontrado = true;
    }

    return encontrado;
}

TComplejo TABBCom::Raiz()
{
    if (this->EsVacio())
    {
        return TComplejo();
    }
    else
    {
        return TComplejo(this->nodo->item);
    }
}

int TABBCom::Altura()
{
    if (this->EsVacio())
    {
        return 0;
    }
    else if (this->nodo->iz.EsVacio() && this->nodo->de.EsVacio())
    {
        return 1;
    }
    else
    {
        if (this->nodo->iz.Altura() > this->nodo->de.Altura())
        {
            return this->nodo->iz.Altura() + 1;
        }
        else
        {
            return this->nodo->de.Altura() + 1;
        }
    }
}

int TABBCom::Nodos() const
{
    if (this->EsVacio())
    {
        return 0;
    }
    else if (this->nodo->iz.EsVacio() && this->nodo->de.EsVacio())
    {
        return 1;
    }
    else
    {
        return this->nodo->iz.Nodos() + 1 + this->nodo->de.Nodos();
    }
}

int TABBCom::NodosHoja()
{
    if (this->EsVacio())
    {
        return 0;
    }
    else if (this->nodo->iz.EsVacio() && this->nodo->de.EsVacio())
    {
        return 1;
    }
    else
    {
        return this->nodo->iz.NodosHoja() + this->nodo->de.NodosHoja();
    }
}

TVectorCom TABBCom::Inorden()
{
    int posicion = 1;
    TVectorCom vector(Nodos());
    InordenAux(vector, posicion);
    return vector;
}

void TABBCom::InordenAux(TVectorCom &v, int &posicion)
{
    if (nodo)
    {
        nodo->iz.InordenAux(v, posicion);
        v[posicion++] = nodo->item;
        nodo->de.InordenAux(v, posicion);
    }
}

TVectorCom TABBCom::Preorden()
{
    int posicion = 1;
    TVectorCom vector(Nodos());
    PreordenAux(vector, posicion);
    return vector;
}

void TABBCom::PreordenAux(TVectorCom &vector, int &posicion)
{
    if (!this->EsVacio())
    {
        vector[posicion++] = this->nodo->item;
        this->nodo->iz.PreordenAux(vector, posicion);
        this->nodo->de.PreordenAux(vector, posicion);
    }
}

TVectorCom TABBCom::Postorden()
{
    int posicion = 1;
    TVectorCom vector(Nodos());
    PostordenAux(vector, posicion);
    return vector;
}

void TABBCom::PostordenAux(TVectorCom &vector, int &posicion)
{
    if (!this->EsVacio())
    {
        this->nodo->iz.PostordenAux(vector, posicion);
        this->nodo->de.PostordenAux(vector, posicion);
        vector[posicion++] = this->nodo->item;
    }
}

TVectorCom TABBCom::Niveles() const
{
    if (this->EsVacio())
    {
        return TVectorCom();
    }

    TVectorCom resultado(this->Nodos());
    int pos = 1;

    queue<const TNodoABB *> cola;
    cola.push(nodo);

    while (!cola.empty())
    {
        const TNodoABB *actual = cola.front();
        cola.pop();

        resultado[pos++] = actual->item;

        if (!actual->iz.EsVacio())
        {
            cola.push(actual->iz.nodo);
        }

        if (!actual->de.EsVacio())
        {
            cola.push(actual->de.nodo);
        }
    }

    return resultado;
}

TVectorCom TABBCom::ABBCamino(const TListaCom &lista)
{
    TListaPos pos = lista.Primera();
    TVectorCom vector_salida;
    while(!pos.EsVacia()){
        TComplejo com_i= lista.Obtener(pos);
        if(!this->Buscar(com_i)){
            this->Insertar(com_i);
            TVectorCom recorrido=ABBCamino_aux(this->Raiz(),com_i);
            
            TVectorCom aux=sumarVectores(vector_salida,recorrido);
            vector_salida.Redimensionar(aux.Tamano());
            vector_salida=aux;
            
        }

        pos=pos.Siguiente();
    }
    return vector_salida;
}

TVectorCom TABBCom::ABBCamino_aux(const TComplejo &inicio, const TComplejo &final){
    TComplejo inicio_copia=inicio, final_copia=final;
    TABBCom copia_arbol = (*this);
    TVectorCom vector;
    if(copia_arbol.Buscar(inicio) && copia_arbol.Buscar(final_copia)){
        while(true){
            vector.Redimensionar(vector.Tamano()+1);
            vector[vector.Tamano()]=copia_arbol.Raiz();
            
            if(copia_arbol.Raiz()==final)
                break;

            if(final_copia<copia_arbol.Raiz() && !copia_arbol.nodo->iz.EsVacio())
                copia_arbol=TABBCom(copia_arbol.nodo->iz);
            else if (final_copia>copia_arbol.Raiz() && !copia_arbol.nodo->iz.EsVacio())
                copia_arbol=TABBCom(copia_arbol.nodo->de);
        };
    }
    return vector;

};

TComplejo*  TABBCom::MostrarNiveles (TListaCom  & lista){
    TListaPos pos=lista.Primera().Siguiente();
    TListaCom lista_impares;
    lista_impares.InsCabeza(lista.primero->e);
    for(int i = 2; i<=lista.Longitud();i++){
        if(pos.EsVacia()){
            break;
        }
        if(i%2!=0)
            lista_impares.InsertarD(pos.pos->e,lista_impares.Ultima());

        pos=pos.Siguiente();
    }

    TComplejo *v=new TComplejo[lista_impares.Longitud()];
    TListaPos pos_impares=lista_impares.Primera();
    for(int i=0;i<lista_impares.Longitud();i++){
        v[i]=lista_impares.Obtener(pos_impares);
        pos_impares=pos_impares.Siguiente();
    }

    //Vaciar arbol
    this->~TABBCom();
    //LLenar arbol
    for(int i=0;i<lista_impares.Longitud();i++){
        this->Insertar(v[i]);
    }

    for(int i=0;i<lista_impares.Longitud();i++){
        for(int j=1;j<=this->Altura();j++){
            if(Nivel_aux(j,*this).ExisteCom(v[i])){
                cout<<"{Elemento: "<<v[i].Re()<<". Elementos de su nivel: ";
                
                for(int k=1;k<=Nivel_aux(j,*this).Tamano();k++)
                    cout<<Nivel_aux(j,*this)[k].Re()<<" ";
                
                cout<<"}"<<endl;
            }
        }
    }

    return v;
}

TVectorCom TABBCom::Nivel_aux(const int &nivel,const TABBCom &arbol){
    TVectorCom salida;
    TABBCom copia(arbol);
    TVectorCom vec1, vec2;

    if(copia.nodo == NULL) { // Asegúrate de que el nodo actual no es NULL
        return salida;
    }

    // Aquí cambiamos la comprobación de la altura por una comprobación del nivel
    if(nivel == 1){ // Si estamos en el nivel deseado (es decir, la raíz)
        salida.Redimensionar(1);
        salida[1] = copia.Raiz();
    }
    else{
        if(copia.nodo->iz.nodo != NULL) { // Comprueba si el hijo izquierdo existe antes de la llamada recursiva
            vec1 = Nivel_aux(nivel - 1, TABBCom(copia.nodo->iz));
        }

        if(copia.nodo->de.nodo != NULL) { // Comprueba si el hijo derecho existe antes de la llamada recursiva
            vec2 = Nivel_aux(nivel - 1, TABBCom(copia.nodo->de));
        }

        salida = sumarVectores(vec1, vec2);
    }

    return salida;
}


bool TABBCom::examen(TListaCom & lista){
    bool salida=false;
    TListaPos pos=lista.Primera();
    TComplejo min=lista.primero->e,max=lista.Obtener(lista.Primera());
    while (!pos.EsVacia())
    {
        TComplejo elemento=lista.Obtener(pos);
        if(elemento<min)
            min=elemento;
        
        if(elemento>max)
            max=elemento;

        pos=pos.Siguiente();
    }

    TABBCom arbol_1=Encontrar_arbol_nodo(min);
    TABBCom arbol_2=Encontrar_arbol_nodo(max);
    if(arbol_1.Buscar(max) || arbol_2.Buscar(min))
        salida=true;

    return salida;
    
}

TABBCom TABBCom::Encontrar_arbol_nodo(TComplejo & object){
    if(this->EsVacio()) {
        return TABBCom();
    } else if (this->Raiz() == object) {
        return *this;
    } else if (object.Re() < this->Raiz().Re()) {
        return this->nodo->iz.Encontrar_arbol_nodo(object);
    } else {
        return this->nodo->de.Encontrar_arbol_nodo(object);
    }
}

int * TABBCom::Multicamino(TListaCom & lista1,TListaCom & lista2){
    int longitud1=lista1.Longitud(),longitud2=lista2.Longitud();
    int *salida= new int[max(longitud1,longitud2)];
    TListaPos pos1=lista1.Primera();
    TListaPos pos2=lista2.Primera();
    int cont=0;

    while (!pos1.EsVacia() || !pos2.EsVacia())
    {
        TComplejo elemento1=lista1.Obtener(pos1);
        TComplejo elemento2=lista1.Obtener(pos2);
        if(pos1.EsVacia() || pos2.EsVacia())
            salida[cont]=0;
        else{
            if(this->Encontrar_arbol_nodo(elemento1).Buscar(elemento2))
                salida[cont]=1;
            else
                salida[cont]=0;
        }

        cont++;
        pos1=pos1.Siguiente();
        pos2=pos2.Siguiente();
    }
    

    return salida;
}


ostream &operator<<(ostream &os, const TABBCom &arbin)
{
    os << arbin.Niveles();
    return os;
}
