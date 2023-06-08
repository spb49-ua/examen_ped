#include "tavlcom.h"

TComplejo TAVLCom::Encontrar_mayor_elemento()
{
	if (!this->raiz->de.EsVacio())
	{
		return this->raiz->de.Encontrar_mayor_elemento();
	}
	else
	{
		return this->raiz->item;
	}
}

TNodoAVL::TNodoAVL()
{
	this->item = TComplejo();
	this->iz = TAVLCom();
	this->de = TAVLCom();
	this->fe = 0;
}

TNodoAVL::TNodoAVL(const TNodoAVL &copia)
{
	this->item = copia.item;
	this->iz = copia.iz;
	this->de = copia.de;
	this->fe = copia.fe;
}

TNodoAVL::~TNodoAVL()
{
	this->item = TComplejo();
	this->iz = TAVLCom();
	this->de = TAVLCom();
	this->fe = 0;
}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &objeto)
{
	if (this != &objeto)
	{
		this->item = objeto.item;

		if (objeto.iz.raiz != NULL)
		{
			this->iz.raiz = new TNodoAVL(*objeto.iz.raiz);
		}
		else
		{
			this->iz.raiz = NULL;
		}
		if (objeto.de.raiz != NULL)
		{
			this->de.raiz = new TNodoAVL(*objeto.de.raiz);
		}
		else
		{
			this->de.raiz = NULL;
		}
	}
	return *this;
}

TAVLCom::TAVLCom()
{
	this->raiz = NULL;
}

TAVLCom::TAVLCom(const TAVLCom &copia)
{

	if (!copia.EsVacio())
	{
		this->raiz = new TNodoAVL();
		this->raiz->item = copia.raiz->item;
		this->raiz->iz = copia.raiz->iz;
		this->raiz->de = copia.raiz->de;
	}
	else
	{
		this->raiz = NULL;
	}
}

TAVLCom::~TAVLCom()
{
	delete raiz;
	this->raiz = NULL;
}

TAVLCom &TAVLCom::operator=(const TAVLCom &copia)
{
	if (this != &copia)
	{
		if (copia.raiz != NULL)
		{
			(*this).~TAVLCom();
			this->raiz = new TNodoAVL();
			this->raiz->item = copia.raiz->item;
			this->raiz->iz = copia.raiz->iz;
			this->raiz->de = copia.raiz->de;
		}
		else
		{
			raiz = NULL;
		}
	}

	return *this;
}

bool TAVLCom::operator==(const TAVLCom &objeto)
{
	if (this->EsVacio() && objeto.EsVacio())
		return true;
	else if (this->EsVacio() || objeto.EsVacio())
		return false;
	TAVLCom copiaObjeto = objeto;
	TVectorCom inorden1 = this->Inorden();
	TVectorCom inorden2 = copiaObjeto.Inorden();

	return inorden1 == inorden2;
}

bool TAVLCom::operator!=(const TAVLCom &objeto)
{
	return !(*this == objeto);
}

bool TAVLCom::EsVacio() const
{
	return this->raiz == NULL;
}

void TAVLCom::RotacionDD()
{
	TNodoAVL *root, *rightChild, *rightLeftChild;

	root = this->raiz;
	rightChild = root->de.raiz;
	rightLeftChild = rightChild->iz.raiz;

	raiz = rightChild;
	rightChild->iz.raiz = root;
	root->de.raiz = rightLeftChild;

	switch (rightChild->fe)
	{
	case 1:
		rightChild->fe = 0;
		root->fe = 0;
		break;

	case 0:
		rightChild->fe = -1;
		root->fe = 1;
		break;
	}
}

void TAVLCom::RotacionII()
{
	TNodoAVL *root, *leftChild, *leftRightChild;

	root = raiz;
	leftChild = root->iz.raiz;
	leftRightChild = leftChild->de.raiz;

	raiz = leftChild;
	leftChild->de.raiz = root;
	root->iz.raiz = leftRightChild;

	switch (leftChild->fe)
	{
	case -1:
		leftChild->fe = 0;
		root->fe = 0;
		break;

	case 0:
		leftChild->fe = 1;
		root->fe = -1;
		break;
	}
}

void TAVLCom::RotacionDI()
{
	TNodoAVL *root, *rightChild, *rightLeftChild, *rightLeftLeftChild, *rightLeftRightChild;

	root = raiz;
	rightChild = root->de.raiz;
	rightLeftChild = rightChild->iz.raiz;
	rightLeftLeftChild = rightLeftChild->iz.raiz;
	rightLeftRightChild = rightLeftChild->de.raiz;

	raiz = rightLeftChild;
	rightLeftChild->iz.raiz = root;
	rightLeftChild->de.raiz = rightChild;
	root->de.raiz = rightLeftLeftChild;
	rightChild->iz.raiz = rightLeftRightChild;

	switch (rightLeftChild->fe)
	{
	case 0:
		rightLeftChild->fe = 0;
		rightChild->fe = 0;
		root->fe = 0;
		break;

	case 1:
		rightLeftChild->fe = 0;
		rightChild->fe = 0;
		root->fe = -1;
		break;

	case -1:
		rightLeftChild->fe = 0;
		rightChild->fe = 1;
		root->fe = 0;
		break;
	}
}

void TAVLCom::RotacionID()
{
	TNodoAVL *root, *leftChild, *leftRightChild, *leftRightLeftChild, *leftRightRightChild;

	root = raiz;
	leftChild = root->iz.raiz;
	leftRightChild = leftChild->de.raiz;
	leftRightLeftChild = leftRightChild->iz.raiz;
	leftRightRightChild = leftRightChild->de.raiz;

	raiz = leftRightChild;
	leftRightChild->iz.raiz = leftChild;
	leftRightChild->de.raiz = root;
	leftChild->de.raiz = leftRightLeftChild;
	root->iz.raiz = leftRightRightChild;

	switch (leftRightChild->fe)
	{
	case 0:
		leftRightChild->fe = 0;
		leftChild->fe = 0;
		root->fe = 0;
		break;

	case 1:
		leftRightChild->fe = 0;
		leftChild->fe = -1;
		root->fe = 0;
		break;

	case -1:
		leftRightChild->fe = 0;
		leftChild->fe = 0;
		root->fe = 1;
		break;
	}
}

bool TAVLCom::InsertarAux(const TComplejo &complex, bool &hasGrown)
{
	bool isInserted, growOnRight = false, growOnLeft = false;

	if (this->EsVacio())
	{
		this->raiz = new TNodoAVL();
		this->raiz->item = complex;
		hasGrown = isInserted = true;
	}
	else
	{
		if (this->raiz->item == complex)
		{
			isInserted = hasGrown = false;
		}
		else
		{
			if (this->raiz->item > complex)
			{
				isInserted = this->raiz->iz.InsertarAux(complex, growOnLeft);
			}
			else
			{
				isInserted = this->raiz->de.InsertarAux(complex, growOnRight);
			}

			if (growOnLeft || growOnRight)
			{
				if (growOnLeft)
				{
					this->raiz->fe--;

					switch (this->raiz->fe)
					{
					case 0:
					case -1:
						hasGrown = this->raiz->fe;
						break;

					case -2:
						hasGrown = false;

						if (this->raiz->iz.raiz->fe == -1)
						{
							this->RotacionII();
						}
						else
						{
							this->RotacionID();
						}
						break;
					}
				}
				else
				{
					this->raiz->fe++;

					switch (this->raiz->fe)
					{
					case 0:
					case 1:
						hasGrown = this->raiz->fe;
						break;

					case 2:
						hasGrown = false;

						if (this->raiz->de.raiz->fe == 1)
						{
							this->RotacionDD();
						}
						else
						{
							this->RotacionDI();
						}
						break;
					}
				}
			}
			else
			{
				hasGrown = false;
			}
		}
	}

	return isInserted;
}

bool TAVLCom::Insertar(const TComplejo &complex)
{
	bool aux = false;
	return this->InsertarAux(complex, aux);
}

bool TAVLCom::Borrar(const TComplejo &cal, bool &decrece)
{
	bool decrecePorDerecha = false, decrecePorIzquierda = false;
	bool borrado;
	TComplejo calendarioMayor;
	TNodoAVL *punteroNodo, *punteroAux;

	if (this->EsVacio())
	{
		borrado = decrece = false;
	}
	else
	{
		if (this->raiz->item == cal)
		{
			if (this->raiz->iz.EsVacio() && raiz->de.EsVacio())
			{
				delete raiz;
				raiz = NULL;
				decrece = borrado = true;
			}
			else
			{
				if (raiz->iz.raiz == NULL && raiz->de.raiz != NULL)
				{
					punteroNodo = raiz;
					raiz = raiz->de.raiz;
					punteroNodo->de.raiz = NULL;
					delete punteroNodo;
					decrece = borrado = true;
				}
				else
				{
					if (raiz->iz.raiz != NULL && raiz->de.raiz == NULL)
					{
						punteroNodo = raiz;
						raiz = raiz->iz.raiz;
						punteroNodo->iz.raiz = NULL;
						delete punteroNodo;
						decrece = borrado = true;
					}
					else
					{
						calendarioMayor = raiz->iz.Encontrar_mayor_elemento();
						punteroAux = raiz;
						borrado = Borrar(calendarioMayor, decrece);
						punteroAux->item = calendarioMayor;
					}
				}
			}
		}
		else
		{
			if (raiz->item > cal)
			{
				borrado = raiz->iz.Borrar(cal, decrecePorIzquierda);
			}
			else
			{
				borrado = raiz->de.Borrar(cal, decrecePorDerecha);
			}

			if (borrado)
			{
				if (!decrecePorIzquierda && !decrecePorDerecha)
				{
					decrece = false;
				}
				else
				{
					if (decrecePorIzquierda)
					{
						raiz->fe++;

						switch (raiz->fe)
						{
						case 0:
							decrece = true;
							break;

						case 1:
							decrece = false;
							break;

						case 2:
							switch (raiz->de.raiz->fe)
							{
							case -1:
								RotacionDI();
								decrece = true;
								break;

							case 1:
								RotacionDD();
								decrece = true;
								break;

							case 0:
								RotacionDD();
								decrece = false;
								break;
							}
							break;
						}
					}
					else
					{
						if (decrecePorDerecha)
						{
							raiz->fe--;

							switch (raiz->fe)
							{
							case -1:
								decrece = false;
								break;

							case 0:
								decrece = true;
								break;

							case -2:
								switch (raiz->iz.raiz->fe)
								{
								case -1:
									RotacionII();
									decrece = true;
									break;

								case 0:
									RotacionII();
									decrece = false;
									break;

								case 1:
									RotacionID();
									decrece = true;
									break;
								}
								break;
							}
						}
					}
				}
			}
		}
	}

	return borrado;
}

bool TAVLCom::Borrar(const TComplejo &c)
{
	bool aux = false;
	return Borrar(c, aux);
}

TComplejo TAVLCom::MayorMenores(TNodoAVL *n)
{
	TComplejo mayor = n->item;

	while (n->de.raiz != nullptr)
	{
		n = n->de.raiz;
		mayor = n->item;
	}

	return mayor;
}

bool TAVLCom::Buscar(const TComplejo &objeto) const
{
	bool encontrado = false;

	if (this->EsVacio())
	{
		return false;
	}
	else if (this->raiz->item == objeto)
	{
		encontrado = true;
	}
	else if (this->raiz->iz.Buscar(objeto))
	{
		encontrado = true;
	}
	else if (this->raiz->de.Buscar(objeto))
	{
		encontrado = true;
	}

	return encontrado;
}

TComplejo TAVLCom::Raiz()
{
	if (this->EsVacio())
	{
		return TComplejo();
	}
	else
	{
		return TComplejo(this->raiz->item);
	}
}

int TAVLCom::Altura()
{
	if (this->EsVacio())
	{
		return 0;
	}
	else if (this->raiz->iz.EsVacio() && this->raiz->de.EsVacio())
	{
		return 1;
	}
	else
	{
		if (this->raiz->iz.Altura() > this->raiz->de.Altura())
		{
			return this->raiz->iz.Altura() + 1;
		}
		else
		{
			return this->raiz->de.Altura() + 1;
		}
	}
}

int TAVLCom::Nodos() const
{
	if (this->EsVacio())
	{
		return 0;
	}
	else if (this->raiz->iz.EsVacio() && this->raiz->de.EsVacio())
	{
		return 1;
	}
	else
	{
		return this->raiz->iz.Nodos() + 1 + this->raiz->de.Nodos();
	}
}

int TAVLCom::NodosHoja()
{
	if (this->EsVacio())
	{
		return 0;
	}
	else if (this->raiz->iz.EsVacio() && this->raiz->de.EsVacio())
	{
		return 1;
	}
	else
	{
		return this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
	}
}

TVectorCom TAVLCom::Inorden()
{
	int posicion = 1;
	TVectorCom vector(Nodos());
	InordenAux(vector, posicion);
	return vector;
}

void TAVLCom::InordenAux(TVectorCom &v, int &posicion)
{
	if (raiz)
	{
		raiz->iz.InordenAux(v, posicion);
		v[posicion++] = raiz->item;
		raiz->de.InordenAux(v, posicion);
	}
}

TVectorCom TAVLCom::Preorden()
{
	int posicion = 1;
	TVectorCom vector(Nodos());
	PreordenAux(vector, posicion);
	return vector;
}

void TAVLCom::PreordenAux(TVectorCom &vector, int &posicion)
{
	if (!this->EsVacio())
	{
		vector[posicion++] = this->raiz->item;
		this->raiz->iz.PreordenAux(vector, posicion);
		this->raiz->de.PreordenAux(vector, posicion);
	}
}

TVectorCom TAVLCom::Postorden()
{
	int posicion = 1;
	TVectorCom vector(Nodos());
	PostordenAux(vector, posicion);
	return vector;
}

void TAVLCom::PostordenAux(TVectorCom &vector, int &posicion)
{
	if (!this->EsVacio())
	{
		this->raiz->iz.PostordenAux(vector, posicion);
		this->raiz->de.PostordenAux(vector, posicion);
		vector[posicion++] = this->raiz->item;
	}
}

TVectorCom TAVLCom::Niveles() const
{
	if (this->EsVacio())
	{
		return TVectorCom();
	}

	TVectorCom resultado(this->Nodos());
	int pos = 1;

	queue<const TNodoAVL *> cola;
	cola.push(raiz);

	while (!cola.empty())
	{
		const TNodoAVL *actual = cola.front();
		cola.pop();

		resultado[pos++] = actual->item;

		if (!actual->iz.EsVacio())
		{
			cola.push(actual->iz.raiz);
		}

		if (!actual->de.EsVacio())
		{
			cola.push(actual->de.raiz);
		}
	}

	return resultado;
}

int *TAVLCom::HijosAVL(const TListaCom &objeto)
{
	TListaPos pos;
	pos = objeto.Primera();
	// ENCONTRAR PADRE
	int *sexo_vector = new int[objeto.Longitud()];
	for (int i = 0; i < objeto.Longitud(); i++)
	{
		TComplejo elemento = objeto.Obtener(pos);
		TAVLCom padreNode = this->Buscar_padre(elemento); // Obtener el subárbol del padre
		int salida_int;

		if (!this->Buscar(elemento)) // El nodo no está en el árbol
		{
			salida_int = 0;
		}
		else if (this->Raiz() == elemento) // El nodo es la raíz del árbol
		{
			salida_int = 5;
		}
		else if (!padreNode.EsVacio())
		{
			if (this->es_hijo_izquierdo(elemento)) // Si es hijo izquierdo
			{
				if (!this->tiene_hermano_derecho(elemento)) // y no tiene hermano derecho
					salida_int = 1;
				else
					salida_int = 2;
			}
			else if (this->es_hijo_derecho(elemento)) // Si es hijo derecho
			{
				if (!this->tiene_hermano_izquierdo(elemento)) // y no tiene hermano izquierdo
					salida_int = 3;
				else
					salida_int = 4;
			}
			else if (padreNode.EsVacio())
			{
				salida_int = 0;
			}
			else
			{
				salida_int = 69;
			}
		}

		sexo_vector[i] = salida_int;
		pos = pos.Siguiente();
	};

	return sexo_vector;
}

TAVLCom TAVLCom::Buscar_padre(const TComplejo &objeto) const
{
	if(this->EsVacio()) {
		return TAVLCom();
	}
	else if(!this->raiz->iz.EsVacio() && this->raiz->iz.Raiz() == objeto) {
		return *this;
	}
	else if(!this->raiz->de.EsVacio() && this->raiz->de.Raiz() == objeto) {
		return *this;
	}
	else if(objeto.Re() < TAVLCom(*this).Raiz().Re()) {
		return this->raiz->iz.Buscar_padre(objeto);
	}
	else {
		return this->raiz->de.Buscar_padre(objeto);
	}
}


bool TAVLCom::es_hijo_izquierdo(const TComplejo objeto) const{
	if (this->Buscar(objeto))
	{
		TAVLCom padreAVL = this->Buscar_padre(objeto);
		if (!padreAVL.EsVacio())
		{
			if (padreAVL.raiz->iz.Raiz() == objeto)
			{
				return true;
			}
		}
	}
	return false;
}

bool TAVLCom::es_hijo_derecho(const TComplejo objeto) const{
	if (this->Buscar(objeto))
	{
		TAVLCom padreAVL = this->Buscar_padre(objeto);
		if (!padreAVL.EsVacio())
		{
			if (padreAVL.raiz->de.Raiz() == objeto)
			{
				return true;
			}
		}
	}
	return false;
}

bool TAVLCom::tiene_hermano_derecho(const TComplejo objeto) const{
	if (this->Buscar(objeto))
	{
		TAVLCom padreAVL = this->Buscar_padre(objeto);
		if (!padreAVL.EsVacio())
		{
			if (!padreAVL.raiz->de.EsVacio())
			{
				if (padreAVL.raiz->de.Raiz() != objeto)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool TAVLCom::tiene_hermano_izquierdo(const TComplejo objeto) const{
	if (this->Buscar(objeto))
	{
		TAVLCom padreAVL = this->Buscar_padre(objeto);
		if (!padreAVL.EsVacio())
		{
			if (!padreAVL.raiz->iz.EsVacio())
			{
				if (padreAVL.raiz->iz.Raiz() != objeto)
				{
					return true;
				}
			}
		}
	}
	return false;
}

TListaCom TAVLCom::Caminos_AVL (TVectorCom & object ){
	TListaCom salida;
	for(int i=1;i<=object.Tamano();i++){
		TComplejo elemento = object[i];
		if(this->Buscar(elemento)){
			int parte_real=elemento.Re();
			if(parte_real % 2 == 0){
				salida=salida+this->Caminos_AVL_recorrido_derecha(elemento);
			}
			else{
				salida=salida+this->Caminos_AVL_recorrido_izquierda(elemento);
			}
		}
		else{
			if (!salida.EsVacia())
				salida.InsertarD(TComplejo(),salida.Ultima());
			else
				salida.InsCabeza(TComplejo());
		}
	}
	return salida;
}

TListaCom TAVLCom::Caminos_AVL_recorrido_derecha(TComplejo & object ){
	TAVLCom copia=(*this);
	TListaCom recorrido;
	//Encontrar nodo
	copia=TAVLCom(copia.Encontrar_arbol_nodo(object));
	
	while(true){
		TComplejo insercion;
		if(copia.raiz->iz.EsVacio() && copia.raiz->de.EsVacio()){
			if (recorrido.Longitud()==0)
				recorrido.InsCabeza(copia.Raiz());
			else
				recorrido.InsertarD(copia.Raiz(),recorrido.Ultima());
			break;
		}
		else if(!copia.raiz->de.EsVacio()){
			insercion=copia.Raiz();
			copia=TAVLCom(copia.raiz->de);
		}
		else{
			insercion=copia.Raiz();
			copia=TAVLCom(copia.raiz->iz);
		}
		if (recorrido.Longitud()==0)
			recorrido.InsCabeza(insercion);
		else
			recorrido.InsertarD(insercion,recorrido.Ultima());
		
	};
	return recorrido;
}

TListaCom TAVLCom::Caminos_AVL_recorrido_izquierda(TComplejo & object ){
	TAVLCom copia=(*this);
	TListaCom recorrido;
	//Encontrar nodo
	copia=TAVLCom(copia.Encontrar_arbol_nodo(object));
	
	while(true){
		TComplejo insercion;
		if(copia.raiz->iz.EsVacio() && copia.raiz->de.EsVacio()){
			if (recorrido.Longitud()==0)
				recorrido.InsCabeza(copia.Raiz());
			else
				recorrido.InsertarD(copia.Raiz(),recorrido.Ultima());
			break;
		}
		else if(!copia.raiz->iz.EsVacio()){
			insercion=copia.Raiz();
			copia=TAVLCom(copia.raiz->iz);
		}
		else{
			insercion=copia.Raiz();
			copia=TAVLCom(copia.raiz->de);
		}
		if (recorrido.Longitud()==0)
			recorrido.InsCabeza(insercion);
		else
			recorrido.InsertarD(insercion,recorrido.Ultima());
		
	};
	return recorrido;
}

TAVLCom TAVLCom::Encontrar_arbol_nodo(TComplejo & object){
    if(this->EsVacio()) {
        return TAVLCom();
    } else if (this->Raiz() == object) {
        return *this;
    } else if (object.Re() < this->Raiz().Re()) {
        return this->raiz->iz.Encontrar_arbol_nodo(object);
    } else {
        return this->raiz->de.Encontrar_arbol_nodo(object);
    }
}


int *TAVLCom::BuscaAVL (TListaCom & lista){
	int aux=lista.Longitud();
	int *vector = new int[aux];

	TListaPos pos=lista.Primera();
	int i=0;
	while (!pos.EsVacia())
	{
		TComplejo elemento=lista.Obtener(pos);

		if(!this->Buscar(elemento))
			vector[i]=0;
		else if(this->es_hijo_izquierdo(elemento))
			vector[i]=1;
		else if(this->es_hijo_derecho(elemento))
			vector[i]=2;
		else if(this->Raiz()==elemento)
			vector[i]=3;

		pos=pos.Siguiente();
		i++;
	}

	return vector;
	
}

ostream &operator<<(ostream &os, const TAVLCom &arbin)
{
	TAVLCom copia = arbin;
	os << copia.Inorden();
	return os;
}
