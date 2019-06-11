#include "TriangleRefiner.hpp"
#include "Output.hpp"

using namespace std;

namespace GeDiM
{
Output::ExitCodes TriangleRefiner::RefineTriangle(const unsigned int &value)
{
	GenericCell *C0 = meshPointer->Cell(value);
	// Controllo che la cella non sia stata gia' tagliata
	assert(C0->IsActive());

	RotateCell(C0);
	GenericEdge *E0 = meshPointer->Edge(C0->Edge(0)->Id());

	// Per ogni triangolo che visito devo sicuramente creare la mediana e le due sottocelle
	GenericEdge *median = NewEdge();
	GenericCell *C0_0 = NewCell();
	GenericCell *C0_1 = NewCell();
	// Appena li creo imposto le parentele
	SetFamily(C0, C0_0, C0_1);

	// Poi potrei aver bisogno di creare il punto medio e i due sottolati. Oppure li devo "pescare"
	GenericEdge *subedge0;
	GenericEdge *subedge1;
	GenericPoint *midpoint;

	if (E0->IsActive())
	{
		subedge0 = NewEdge();
		subedge1 = NewEdge();
		midpoint = NewPoint();
		// Appena li creo imposto le parentele
		SetFamily(E0, subedge0, subedge1);
		// Imposto le coordinate del punto medio appena creato
		midpoint->SetCoordinates(0.5 * (E0->Point(0)->Coordinates() + E0->Point(1)->Coordinates()));
		// Imposto le info dei lati appena creati
		SetEdgeGeometry(subedge0, E0->Point(0), midpoint, NULL, C0_0);
		SetEdgeGeometry(subedge1, midpoint, E0->Point(1), NULL, C0_1);

		// La cella affianco al lato lungo deve essere marcata
		if ((E0->Cell(0) != NULL) and (E0->Cell(0) != C0))
			idCellsToRefine.emplace(E0->Cell(0)->Id());
		if ((E0->Cell(1) != NULL) and (E0->Cell(1) != C0))
			idCellsToRefine.emplace(E0->Cell(1)->Id());
	}
	else
	{
		//Devo avere esattamente due figli
		assert(E0->NumberOfChilds() == 2);
		subedge0 = meshPointer->Edge(E0->Child(0)->Id()); // Non sono sicuro dell'ordine
		subedge1 = meshPointer->Edge(E0->Child(1)->Id()); // Non sono sicuro dell'ordine
		midpoint = meshPointer->Point(puntocomune(subedge0, subedge1));
		// Le coordinate del punto medio sono già giuste
		assert(midpoint->Coordinates() == (0.5 * (E0->Point(0)->Coordinates() + E0->Point(1)->Coordinates())));
		// Controllo che i due subedge abbiamo un NULL in posizione zero nelle celle
		if(subedge0->NumberOfCells() != 2)
			subedge0->AddCell(C0_0);
		else
			subedge0->InsertCell(C0_0, 0);

		if(subedge1->NumberOfCells() != 2)
			subedge1->AddCell(C0_1);
		else
			subedge1->InsertCell(C0_1, 0);
	}

	// Ora collego gli oggetti sicuramente appena creati tra loro
	SetEdgeGeometry(median, C0->Point(2), midpoint, C0_0, C0_1);

	// Costruisco il primo sottotriangolo
	SetCellPoints(C0_0, C0->Point(0), midpoint, C0->Point(2));
	SetCellEdges(C0_0, subedge0, median, C0->Edge(2));

	// Costruisco il secondo sottotriangolo
	SetCellPoints(C0_1, midpoint, C0->Point(1), C0->Point(2));
	SetCellEdges(C0_1, median, subedge1, C0->Edge(1));

	// Sostituisco i lati
	

	C0->SetState(false);
	E0->SetState(false);

	const GenericCell* altra;
	if ((altra = scegliAltra(C0->Edge(1),C0)) != NULL)
	{
		if ((idCellsToRefine.find(altra->Id()) != idCellsToRefine.end()) and (LongestEdge(altra) == C0->Edge(1)))
			idCellsToRefine.emplace(C0_1->Id());
	}
	if ((altra = scegliAltra(C0->Edge(2),C0)) != NULL)
	{
		if ((idCellsToRefine.find(altra->Id()) != idCellsToRefine.end()) and (LongestEdge(altra) == C0->Edge(2)))
			idCellsToRefine.emplace(C0_0->Id());
	}
	
	

	return Output::Success;
}

} // namespace GeDiM
