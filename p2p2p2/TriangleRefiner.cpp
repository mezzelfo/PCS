#include "TriangleRefiner.hpp"
#include "Output.hpp"

using namespace std;

namespace GeDiM
{
Output::ExitCodes TriangleRefiner::RefineTriangle(const unsigned int &value)
{
	GenericCell *C0 = meshPointer->Cell(value);
	RotateCell(C0);

	GenericEdge *E0 = meshPointer->Edge(C0->Edge(0)->Id());
	GenericEdge *Em = NewEdge();
	if (E0->IsActive())
	{

		cout << "qui1" << endl;

		// Creo il puntatore al lato piu' lungo di entrambe
		GenericEdge *longest = meshPointer->Edge(LongestEdge(C0)->Id());

		// Creo gli oggetti necessari vuoti
		GenericPoint *midpoint = NewPoint(); // Punto medio

		GenericEdge *subEdge0 = NewEdge(); // Figli del lato piu' lungo
		GenericEdge *subEdge1 = NewEdge();

		GenericEdge *median0 = NewEdge(); // Mediana

		GenericCell *C0_0 = NewCell(); // Figli del triangolo
		GenericCell *C0_1 = NewCell();

		SetFamily(longest, subEdge0, subEdge1); // Imposto le informazioni di parentela fra lati
		SetFamily(C0, C0_0, C0_1);				// Imposto le informazioni di parentela fra triangoli

		// Imposto le coordinate del punto medio
		midpoint->SetCoordinates(0.5 * (longest->Point(0)->Coordinates() + longest->Point(1)->Coordinates()));

		cout << "qui2" << endl;

		// Costruisco i lati indicando le celle con cui confinano e i punti che vi appartengono
		SetEdgeGeometry(subEdge0, C0->Point(0), midpoint, NULL, C0_0);

		SetEdgeGeometry(subEdge1, midpoint, C0->Point(1), NULL, C0_1);

		SetEdgeGeometry(median0, C0->Point(2), midpoint, C0_0, C0_1);

		cout << "qui3" << endl;

		// Costruisco il primo sottotriangolo
		SetCellPoints(C0_0, C0->Point(0), midpoint, C0->Point(2));
		SetCellEdges(C0_0, subEdge0, median0, C0->Edge(2));
		//C0_0->AddCell(NULL);
		//C0_0->AddCell(C0_1);
		//C0_0->AddCell(NULL);

		// Costruisco il secondo sottotriangolo
		SetCellPoints(C0_1, midpoint, C0->Point(1), C0->Point(2));
		SetCellEdges(C0_1, median0, subEdge1, C0->Edge(1));
		//C0_1->AddCell(C0_0);
		//C0_1->AddCell(NULL);
		//C0_1->AddCell(NULL);

		cout << "qui4" << endl;

		// Disattivo i triangoli e il lato padri
		C0->SetState(false);
		longest->SetState(false);

		//Eredita marker
		midpoint->SetMarker(longest->Marker());

		cout << "qui5" << E0->Cell(0) << endl;

		if (E0->Cell(0) != NULL)
			if (E0->Cell(0)->Id() == C0->Id())
				idCellsToRefine.emplace(E0->Cell(1)->Id());
			else if (E0->Cell(1) != NULL)
				if (E0->Cell(1)->Id() == C0->Id())
					idCellsToRefine.emplace(E0->Cell(0)->Id());
				else
				{
					std::cerr << "nope2" << std::endl;
					exit(EXIT_FAILURE);
				}

		cout << "qui6 - fine" << endl;
	}
	else
	{
		cout << "qua1" << endl;

		// Creo il puntatore al lato piu' lungo di entrambe
		GenericEdge *longest = meshPointer->Edge(LongestEdge(C0)->Id());

		// Creo gli oggetti necessari vuoti
		GenericEdge *subEdge0 = meshPointer->Edge(longest->Child(1)->Id()); // Figli del lato piu' lungo
		GenericEdge *subEdge1 = meshPointer->Edge(longest->Child(0)->Id());

		cout << "qua2" << endl;

		GenericPoint *midpoint = meshPointer->Point(puntocomune(subEdge0, subEdge1)); // Punto medio

		GenericEdge *median0 = NewEdge(); // Mediana

		GenericCell *C0_0 = NewCell(); // Figli del triangolo
		GenericCell *C0_1 = NewCell();

		SetFamily(longest, subEdge0, subEdge1); // Imposto le informazioni di parentela fra lati
		SetFamily(C0, C0_0, C0_1);				// Imposto le informazioni di parentela fra triangoli

		cout << "qua3" << endl;

		// Imposto le coordinate del punto medio
		midpoint->SetCoordinates(0.5 * (longest->Point(0)->Coordinates() + longest->Point(1)->Coordinates()));

		// Costruisco i lati indicando le celle con cui confinano e i punti che vi appartengono
		subEdge0->InsertCell(C0_0, 0);
		subEdge1->InsertCell(C0_1, 0);

		SetEdgeGeometry(median0, C0->Point(2), midpoint, C0_0, C0_1);

		cout << "qua4" << endl;

		// Costruisco il primo sottotriangolo
		SetCellPoints(C0_0, C0->Point(0), midpoint, C0->Point(2));
		SetCellEdges(C0_0, subEdge0, median0, C0->Edge(2));
		//C0_0->AddCell(NULL);
		//C0_0->AddCell(C0_1);
		//C0_0->AddCell(NULL);

		// Costruisco il secondo sottotriangolo
		SetCellPoints(C0_1, midpoint, C0->Point(1), C0->Point(2));
		SetCellEdges(C0_1, median0, subEdge1, C0->Edge(1));
		//C0_1->AddCell(C0_0);
		//C0_1->AddCell(NULL);
		//C0_1->AddCell(NULL);

		cout << "qua5" << endl;

		// Disattivo il triangolo e il lato padre
		C0->SetState(false);
		longest->SetState(false);

		//Eredita marker
		midpoint->SetMarker(longest->Marker());

		cout << "qua6 - fine" << endl;
	}

	return Output::Success;
}

} // namespace GeDiM
