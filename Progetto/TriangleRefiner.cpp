#include "TriangleRefiner.hpp"

namespace GeDiM
{
Output::ExitCodes TriangleRefiner::RefineMesh()
{
	unsigned edgeId = 0;
	while (anyTriangleToCut()) // Il ciclo procede fino a quando ci sono lati da tagliare
	{
		edgeId = (edgeId + 1) % meshPointer->NumberOfEdges(); // Il modulo � necessario per poter scorrere il vettore in modo circolare
		if (not idEdgesToCut.at(edgeId))					  // Se il lato non � da tagliare lo ignoro e passo oltre
			continue;

		GenericEdge *L = meshPointer->Edge(edgeId); // Creo un puntatore al lato da tagliare L

		if (IsOnBorder(L)) // Se � un lato di bordo della mesh
		{
			GenericCell *C0;
			// Creo un puntatore all'unica cella adiacente C0
			if (L->Cell(0) == NULL)
				C0 = meshPointer->Cell(L->Cell(1)->Id());
			if (L->Cell(1) == NULL)
				C0 = meshPointer->Cell(L->Cell(0)->Id());
			RefineBorderTriangle(C0);		 // Raffino il triangolo nella condizione di bordo
			idEdgesToCut.at(edgeId) = false; // Indico a idEdgesToCut che il lato non � pi� da tagliare
		}
		else if (LongestEdge(L->Cell(0)) == LongestEdge(L->Cell(1))) // Se il lato � il pi� lungo di entrambi i triangoli a cui appartiene
		{
			GenericCell *C0 = meshPointer->Cell(L->Cell(0)->Id()); // Creo il puntatore al primo triangolo C0
			GenericCell *C1 = meshPointer->Cell(L->Cell(1)->Id()); // Creo il puntatore al secondo triangolo C1
			RefinePairedTriangles(C0, C1);						   // Raffino entrambi i triangoli contemporaneamente
			idEdgesToCut.at(edgeId) = false;					   // Indico a idEdgesToCut che il lato non � pi� da tagliare
		}
		else
		{
			// Se il lato non rientra nei due casi precedenti preparo per il raffinamento i triangoli a cui appartiene
			if (L->HasRightCell())
				PrepareTriangle(L->RightCell()->Id());
			if (L->HasLeftCell())
				PrepareTriangle(L->LeftCell()->Id());
		}
	}
	return Output::Success;
}

void TriangleRefiner::RotateCell(GenericCell *C)
{
	GenericEdge *L = meshPointer->Edge(LongestEdge(C)->Id()); // Creo un puntatore al lato pi� lungo del triangolo
	// Ruoto i lati al fine di avere L in posizione 0 e mantenendo il verso antiorario della rappresentazione
	if (L == C->Edge(1))
	{
		C->InsertEdge(C->Edge(2), 1);
		C->InsertEdge(C->Edge(0), 2);
		C->InsertEdge(L, 0);
	}
	else if (L == C->Edge(2))
	{
		C->InsertEdge(C->Edge(1), 2);
		C->InsertEdge(C->Edge(0), 1);
		C->InsertEdge(L, 0);
	}
	// Ruoto i punti fino a quando quello in posizione 2 non appartiene pi� al lato pi� lungo L
	while ((C->Point(2) == L->Point(0)) or (C->Point(2) == L->Point(1)))
	{
		const GenericPoint *tmp = C->Point(0); // Creo una variabile temporanea per effettuare gli scambi di posizione
		C->InsertPoint(C->Point(2), 0);
		C->InsertPoint(C->Point(1), 2);
		C->InsertPoint(tmp, 1);
	}
}

void TriangleRefiner::PrepareTriangle(const unsigned int &value)
{
	GenericCell *C = meshPointer->Cell(value); // Creo un puntatore al triangolo da preparare C
	const GenericEdge *L = LongestEdge(C);	 // Creo un puntatore al lato pi� lungo L
	idEdgesToCut.at(L->Id()) = true;		   // Indico a IdEdgesToCut che L deve essere tagliato
	RotateCell(C);							   // Ruoto i lati e i punti per avere una rappresentazione univoca
}
void TriangleRefiner::PensaciTuAlLatoIgnoto(GenericCell *C, GenericEdge *E)
{
	// Aggiorno correttamente le informazioni di vicinanza di un lato e dei triangoli vicni dopo aver raffinato
	if (E->Cell(0) == C->Father())
	{
		E->InsertCell(C, 0);
		C->AddCell(E->Cell(1));
	}
	else
	{
		E->InsertCell(C, 1);
		C->AddCell(E->Cell(0));
	}
}
void TriangleRefiner::RefinePairedTriangles(GenericCell *C0, GenericCell *C1)
{
	// Ruoto entrambi i triangoli di input
	RotateCell(C0);
	RotateCell(C1);
	// Creo il puntatore al lato pi� lungo di entrambe
	GenericEdge *longest = meshPointer->Edge(LongestEdge(C0)->Id());

	// Creo gli oggetti necessari vuoti
	GenericPoint *midpoint = NewPoint(); // Punto medio

	GenericEdge *subEdge0 = NewEdge(); // Figli del lato pi� lungo
	GenericEdge *subEdge1 = NewEdge();

	GenericEdge *median0 = NewEdge(); // Mediane
	GenericEdge *median1 = NewEdge();

	GenericCell *C0_0 = NewCell(); // Figli dei due triangoli
	GenericCell *C0_1 = NewCell();
	GenericCell *C1_0 = NewCell();
	GenericCell *C1_1 = NewCell();

	SetFamily(longest, subEdge0, subEdge1); // Imposto le informazioni di parentela fra lati
	SetFamily(C0, C0_0, C0_1);				// Imposto le informazioni di parentela fra triangoli
	SetFamily(C1, C1_0, C1_1);

	// Imposto le coordinate del punto medio
	midpoint->SetCoordinates(0.5 * (longest->Point(0)->Coordinates() + longest->Point(1)->Coordinates()));

	// Costruisco i lati indicando le celle con cui confinano e i punti che vi appartengono
	SetEdgeGeometry(subEdge0, C0->Point(0), midpoint, C1_0, C0_0);

	SetEdgeGeometry(subEdge1, midpoint, C0->Point(1), C1_1, C0_1);

	SetEdgeGeometry(median0, C0->Point(2), midpoint, C0_0, C0_1);

	SetEdgeGeometry(median1, midpoint, C1->Point(2), C1_0, C1_1);

	// Costruisco il primo sottotriangolo
	SetCellPoints(C0_0, C0->Point(0), midpoint, C0->Point(2));
	SetCellEdges(C0_0, subEdge0, median0, C0->Edge(2));
	C0_0->AddCell(C1_0);
	C0_0->AddCell(C0_1);
	PensaciTuAlLatoIgnoto(C0_0, meshPointer->Edge(C0->Edge(2)->Id()));

	// Costruisco il secondo sottotriangolo
	SetCellPoints(C0_1, midpoint, C0->Point(1), C0->Point(2));
	SetCellEdges(C0_1, median0, subEdge1, C0->Edge(1));
	C0_1->AddCell(C0_0);
	C0_1->AddCell(C1_1);
	PensaciTuAlLatoIgnoto(C0_1, meshPointer->Edge(C0->Edge(1)->Id()));

	// Costruisco il terzo sottotriangolo
	SetCellPoints(C1_0, C0->Point(0), C1->Point(2), midpoint);
	SetCellEdges(C1_0, median1, subEdge0, C1->Edge(1));
	C1_0->AddCell(C1_1);
	C1_0->AddCell(C0_0);
	PensaciTuAlLatoIgnoto(C1_0, meshPointer->Edge(C1->Edge(1)->Id()));

	// Costruisco il quarto sottotriangolo
	SetCellPoints(C1_1, midpoint, C1->Point(2), C0->Point(1));
	SetCellEdges(C1_1, subEdge1, median1, C1->Edge(2));
	C1_1->AddCell(C0_1);
	C1_1->AddCell(C1_0);
	PensaciTuAlLatoIgnoto(C1_1, meshPointer->Edge(C1->Edge(2)->Id()));

	// Disattivo i triangoli e il lato padri
	C0->SetState(false);
	C1->SetState(false);
	longest->SetState(false);

	//Eredita marker
	midpoint->SetMarker(longest->Marker());

	// Se i sottotriangoli creati hanno lati marcati li preparo per il raffinamento
	if (HasMarkedEdges(C0_0))
		PrepareTriangle(C0_0->Id());
	if (HasMarkedEdges(C0_1))
		PrepareTriangle(C0_1->Id());
	if (HasMarkedEdges(C1_0))
		PrepareTriangle(C1_0->Id());
	if (HasMarkedEdges(C1_1))
		PrepareTriangle(C1_1->Id());
}
void TriangleRefiner::RefineBorderTriangle(GenericCell *C0)
{
	RotateCell(C0); // Ruoto la cella

	GenericEdge *longest = meshPointer->Edge(LongestEdge(C0)->Id()); // Creo il puntatore al lato pi� lungo

	// Creo gli oggetti necessari vuoti
	GenericPoint *midpoint = NewPoint(); // Punto medio

	GenericEdge *subEdge0 = NewEdge(); // Figli del lato pi� lungo
	GenericEdge *subEdge1 = NewEdge();

	GenericEdge *median0 = NewEdge(); // Mediana

	GenericCell *C0_0 = NewCell(); // Figli del triangolo
	GenericCell *C0_1 = NewCell();

	SetFamily(longest, subEdge0, subEdge1); // Imposto le informazioni di parentela fra lati
	SetFamily(C0, C0_0, C0_1);				// Imposto le informazioni di parentela fra triangoli

	// Imposto le coordinate del punto medio
	midpoint->SetCoordinates(0.5 * (longest->Point(0)->Coordinates() + longest->Point(1)->Coordinates()));

	// Costruisco i lati indicando i triangoli con cui confinano e i punti che vi appartengono
	SetEdgeGeometry(subEdge0, C0->Point(0), midpoint, NULL, C0_0);
	SetEdgeGeometry(subEdge1, midpoint, C0->Point(1), NULL, C0_1);
	SetEdgeGeometry(median0, C0->Point(2), midpoint, C0_0, C0_1);

	// Costruisco il primo sottotriangolo
	SetCellPoints(C0_0, C0->Point(0), midpoint, C0->Point(2));
	SetCellEdges(C0_0, subEdge0, median0, C0->Edge(2));
	C0_0->AddCell(C0_1);
	PensaciTuAlLatoIgnoto(C0_0, meshPointer->Edge(C0->Edge(2)->Id()));
	C0_0->AddCell(NULL); // Il triangolo � di bordo

	// Costruisco il secondo sottotriangolo
	SetCellPoints(C0_1, midpoint, C0->Point(1), C0->Point(2));
	SetCellEdges(C0_1, median0, subEdge1, C0->Edge(1));
	PensaciTuAlLatoIgnoto(C0_1, meshPointer->Edge(C0->Edge(1)->Id()));
	C0_1->AddCell(C0_0);
	C0_1->AddCell(NULL); // Il triangolo � di bordo

	// Disattivo il triangolo padre e il lato padre
	C0->SetState(false);
	longest->SetState(false);

    //Eredita marker
	midpoint->SetMarker(longest->Marker());

	// Se i sottotriangoli creati hanno lati marcati li preparo per il raffinamento
	if (HasMarkedEdges(C0_0))
		PrepareTriangle(C0_0->Id());
	if (HasMarkedEdges(C0_1))
		PrepareTriangle(C0_1->Id());
}

void TriangleRefiner::AggiornaInformazioniPunti()
{
	for (unsigned int i = 0; i < meshPointer->NumberOfPoints(); i++)
	{
		GenericPoint *punto = meshPointer->Point(i);

		//cancella le celle
		punto->AllocateCells(0);

		//cancella i lati
		punto->AllocateEdges(0);

		//Ciclo su tutte le celle. Se contengono il punto aggiorno le informazioni dei punti
		for (unsigned int j = 0; j < meshPointer->NumberOfCells(); j++)
		{
			const GenericCell* cella = meshPointer->Cell(j);
			if (punto->Id() == cella->Point(0)->Id())
				punto->AddCell(cella);
			if (punto->Id() == cella->Point(1)->Id())
				punto->AddCell(cella);
			if (punto->Id() == cella->Point(2)->Id())
				punto->AddCell(cella);
		}
		//Ciclo su tutti i lati. Se contengono il punto aggiorno le informazioni del punto
		for (unsigned int j = 0; j < meshPointer->NumberOfEdges(); j++)
		{
			const GenericEdge* lato = meshPointer->Edge(j);
			if (punto->Id() == lato->Point(0)->Id())
				punto->AddEdge(lato);
			if (punto->Id() == lato->Point(1)->Id())
				punto->AddEdge(lato);
		}
	}
}

} // namespace GeDiM
