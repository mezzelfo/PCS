#ifndef TRIANGLEREFINER_HPP
#define TRIANGLEREFINER_HPP

#include "GenericDomain.hpp"
#include "GenericMesh.hpp"
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

namespace GeDiM
{
	class TriangleRefiner
	{
	private:
		/*
			Seguono dichiarazione e definizione di funzioni semplici o di supporto
		*/
		// Ritorna la distanza tra due punti
		static double Distance(const GenericPoint* P1, const GenericPoint* P2)
		{
			return (P1->Coordinates()-P2->Coordinates()).norm();
		}

		// Ritorna il lato più lungo di una cella
		const GenericEdge* LongestEdge(const GenericCell* C)
		{
			double a = Distance(C->Edge(0)->Point(0),C->Edge(0)->Point(1));
			double b = Distance(C->Edge(1)->Point(0),C->Edge(1)->Point(1));
			double c = Distance(C->Edge(2)->Point(0),C->Edge(2)->Point(1));
			if ((a >= b) and (a >= c))
				return C->Edge(0);
			else if ((b >= a) and (b >= c))
				return C->Edge(1);
			else
				return C->Edge(2);
		}

		// Ritorna true se la cella ha almeno un lato marcato
		bool HasMarkedEdges(const GenericCell* C)
		{
			return (idEdgesToCut.at(C->Edge(0)->Id())) or (idEdgesToCut.at(C->Edge(1)->Id())) or (idEdgesToCut.at(C->Edge(2)->Id()));
		}

		// Ritorna true se il lato è sul bordo. Confinare con la cella NULL significa essere sul bordo
		bool IsOnBorder(const GenericEdge* E)
		{
			return (E->Cell(0) == NULL) or (E->Cell(1) == NULL);
		}

		// Creano in modo corretto e coerente vari tipi di oggetti geometrici
		GenericPoint* NewPoint()
		{
			GenericPoint* P = meshPointer->CreatePoint();
			meshPointer->AddPoint(P);
			return P;
		}
		GenericEdge* NewEdge()
		{
			GenericEdge* E = meshPointer->CreateEdge();
			meshPointer->AddEdge(E);
			idEdgesToCut.push_back(false);
			return E;
		}
		GenericCell* NewCell()
		{
			GenericCell* C = meshPointer->CreateCell();
			meshPointer->AddCell(C);
			return C;
		}

		// Inizializza un lato vuoto con informazioni geometriche di punti e celle
		void SetEdgeGeometry(GenericEdge* E, const GenericPoint* P0, const GenericPoint* P1, const GenericCell* right, const GenericCell* left)
		{
			//Chiedere a berrone perchè manca E->InitializePoint(2);
			E->AddPoint(P0);
			E->AddPoint(P1);
			E->InitializeCells(2);
			E->AddCell(right);	//RightCell = cell[0]
			E->AddCell(left);	//LeftCell = cell[1]
		}

		// Inizializza le informazioni di parentela di un padre e due figli (situazione più  usuale)
		void SetFamily(GenericTreeNode* father, GenericTreeNode* C1, GenericTreeNode* C2)
		{
			father->InitializeChilds(2);
			father->AddChild(C1);
			father->AddChild(C2);
			C1->SetFather(father);
			C2->SetFather(father);
		}
		
		// Inizializzano le informazioni geometriche (solo punti e lati) di una cella vuota
		void SetCellPoints(GenericCell* C, const GenericPoint* P0, const GenericPoint* P1, const GenericPoint* P2)
		{
			C->InitializePoints(3);
			C->AddPoint(P0);
			C->AddPoint(P1);
			C->AddPoint(P2);
		}
		void SetCellEdges(GenericCell* C, const GenericEdge* E0, const GenericEdge* E1, const GenericEdge* E2)
		{
			C->InitializeEdges(3);
			C->AddEdge(E0);
			C->AddEdge(E1);
			C->AddEdge(E2);
		}

		// Dato un lato e una cella ad esso adiacente, ritorna l'altra cella adiacente al lato
		const GenericCell* OtherAdjacentCell(const GenericEdge* E, const GenericCell* me)
		{
			if (E->RightCell() == me)
				return E->LeftCell();
			return E->RightCell();
		}

		/*
			Seguono dichiarazioni di funzioni algoritmiche importanti o complesse
		*/
		void RotateCell(GenericCell* C);								// Riordina i puntatori a lati e punti della cella in modo coerente
		void PensaciTuAlLatoIgnoto(GenericCell* C, GenericEdge* E);		// Sistema le condizioni di vicinanza tra una cella ed un lato "esterno"
		void RefinePairedTriangles(GenericCell* C0, GenericCell* C1);	// Taglia contemporanemante due triangoli che condividono il lato lungo
		void RefineBorderTriangle(GenericCell* C0);						// Taglia un triangolo che ha il lato lungo sul bordo della mesh

		/*
			Membri della classe TriangleRefiner
		*/
		GenericMesh* meshPointer;	// Puntatore alla mesh
		vector<bool> idEdgesToCut;	// Vettore di bool. Se l'elemento n-esimo del vettore è true allora l'edge con id=n è da tagliare

	public:
		// Nel costruttore richiedo una mesh e preparo il vettore di bool grande abbastanza
		TriangleRefiner(GenericMesh& mesh)
		{
			meshPointer = &mesh;
			idEdgesToCut.assign(meshPointer->NumberOfEdges(), false);
		}
		~TriangleRefiner()
		{
			meshPointer = NULL;
			idEdgesToCut.clear();
		}

		// Ritorna true se nel vettore c'è ancora almento un true
		bool anyTriangleToCut()
		{
		for(unsigned edgeId = 0; edgeId < meshPointer->NumberOfEdges(); edgeId++)
			if (idEdgesToCut.at(edgeId))
				return true;
			
		return false;
		}

		// Funzione che gira la cella e marca da tagliare il lato più lungo
		void PrepareTriangle(const unsigned int& value);

		// Rifinisci la mesh in maniera conforme
		Output::ExitCodes RefineMesh();
	};
}

#endif
