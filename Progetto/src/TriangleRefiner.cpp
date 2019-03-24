#include "TriangleRefiner.hpp"

namespace GeDiM
{
    double distance(const GenericPoint* A, const GenericPoint* B)
    {
        return((A->Coordinates()-B->Coordinates()).norm());
    }
	const GenericEdge* LongestEdgePtr(const GenericCell* cell)
    {
        // Sono veramente un triangolo?
        assert(cell->NumberOfPoints() == 3);
        assert(cell->NumberOfEdges() == 3);

        double a = distance(cell->Edge(0)->Point(0),cell->Edge(0)->Point(1));
        double b = distance(cell->Edge(1)->Point(0),cell->Edge(1)->Point(1));
        double c = distance(cell->Edge(2)->Point(0),cell->Edge(2)->Point(1));
        if ((a > b) and (a > c))
            return cell->Edge(0);
        else if (b > c)
            return cell->Edge(1);
        else
            return cell->Edge(2);
    }
	Output::ExitCodes correggiOrientamento(GenericCell* cell)
    {
        // Sono veramente un triangolo?
        assert(cell->NumberOfPoints() == 3);
        assert(cell->NumberOfEdges() == 3);

        // Ruoto i vertici in modo che points[0] == LongestEdgePtr->Point(0)
        // Il punto 0 del lato più lungo è costante
        const GenericEdge* longestEdge = LongestEdgePtr(cell);
        const GenericPoint* P = longestEdge->Point(0);
        if (cell->Point(0) == P)
            return Output::Success;
        else if (cell->Point(1) == P)
        {
            // ruoto da una parte
            cell->InsertPoint(cell->Point(2),1);
            cell->InsertPoint(cell->Point(0),2);
            cell->InsertPoint(P,0);

            cell->InsertEdge(cell->Edge(2),1);
            cell->InsertEdge(cell->Edge(0),2);
            cell->InsertEdge(longestEdge,0);
        }
        else if (cell->Point(2) == P)
        {
            // ruoto dall'altra parte
            cell->InsertPoint(cell->Point(1),2);
            cell->InsertPoint(cell->Point(0),1);
            cell->InsertPoint(P,0);

            cell->InsertEdge(cell->Edge(1),2);
            cell->InsertEdge(cell->Edge(0),1);
            cell->InsertEdge(longestEdge,0);
        }
        else
        {
            cerr << "Lato non trovato\n";
            return Output::GenericError;
        }
        return Output::Success;
    }

    TriangleRefiner::TriangleRefiner() { meshPointer = NULL;}
	TriangleRefiner::~TriangleRefiner() { }
	void TriangleRefiner::SetMesh( GenericMesh& mesh )
    {
        meshPointer = &mesh;
        cellsToCut.assign(meshPointer->NumberOfCells(),false);
        edgesToCut.assign(meshPointer->NumberOfEdges(),false);
    }
    void TriangleRefiner::AddCellToRefine( const unsigned int& value )
    {
        // Se la cella è già stata segnata come da raffinare allora esco subito
        if (cellsToCut.at(value) == true) return;
        // Altrimenti la setto da raffinare
        cellsToCut.at(value) = true;
        // La oriento nel modo corretto
        GenericCell* cellaAttuale = meshPointer->Cell(value);
        correggiOrientamento(cellaAttuale);
        // Setto da tagliare il lato più lungo
        const GenericEdge* longestEdge = LongestEdgePtr(cellaAttuale);
        edgesToCut.at(longestEdge->Id()) = true;
        // Poi ricorro sui vicini
        if ((longestEdge->RightCell() != NULL) and (longestEdge->RightCell() != cellaAttuale))
            AddCellToRefine(longestEdge->RightCell()->Id());
        else if ((longestEdge->LeftCell() != NULL) and (longestEdge->LeftCell() != cellaAttuale))
            AddCellToRefine(longestEdge->LeftCell()->Id());

        return;
    }
    Output::ExitCodes TriangleRefiner::RefineMesh()
    {
    	for(unsigned int cellId = 0; cellId < meshPointer->NumberOfCells(); cellId++)
        {
            if (cellsToCut.at(cellId) == true)
            {
                // La preparo per essere tagliata
                AddCellToRefine(cellId);

                // Ingredienti che mi servono
                GenericCell* cell = meshPointer->Cell(cellId);
                GenericEdge* longestEdge = meshPointer->Edge(LongestEdgePtr(cell)->Id());
                const GenericPoint* P0 = longestEdge->Point(0);
                const GenericPoint* P1 = longestEdge->Point(1);
                const GenericPoint* Pp = cell->Point(2); // Punto opposto al lato lungo
                const GenericEdge* L0 = cell->Edge(1);
                const GenericEdge* L1 = cell->Edge(2);
                bool hafigli = false;


                GenericPoint* Pm;
                GenericEdge *E0, *E1, *Ee;
                GenericCell *C0, *C1;
                if (not(longestEdge->HasChilds()))
                {
                    // Creo vuoti tutti gli oggetti nuovi e li aggiungo alla struttura
                    Pm = meshPointer->CreatePoint();  // Punto medio del lato lungo
                    meshPointer->AddPoint(Pm);
                    E0 = meshPointer->CreateEdge();    // Primo sotto-segmento del lato lungo
                    meshPointer->AddEdge(E0);
                    E1 = meshPointer->CreateEdge();    // Secondo sotto-segmento del lato lungo
                    meshPointer->AddEdge(E1);
                    Ee = meshPointer->CreateEdge();    // Mediana del lato lungo
                    meshPointer->AddEdge(Ee);
                    C0 = meshPointer->CreateCell();    // Prima sotto-cella
                    meshPointer->AddCell(C0);
                    C1 = meshPointer->CreateCell();    // Seconda sotto-cella
                    meshPointer->AddCell(C1);
                    // Devo allungare i vettori di bool
                    // Ho creato 3 edge e 2 cell
                    edgesToCut.push_back(false);
                    edgesToCut.push_back(false);
                    edgesToCut.push_back(false);
                    cellsToCut.push_back(false);
                    cellsToCut.push_back(false);

                    // Aggiorno le informazioni di parentela
                    longestEdge->AddChild(E0);
                    longestEdge->AddChild(E1);
                    E0->SetFather(longestEdge);
                    E1->SetFather(longestEdge);
                    cell->AddChild(C0);
                    cell->AddChild(C1);
                    C0->SetFather(cell);
                    C1->SetFather(cell);

                    // Creazione del punto medio
                    Pm->SetCoordinates(0.5*(P0->Coordinates()+P1->Coordinates()));

                    // Inserisco i punti su cui insiste il primo segmento
                    E0->AddPoint(P0);
                    E0->AddPoint(Pm);

                    // Inserisco i punti su cui insiste il secondo segmento
                    E1->AddPoint(Pm);
                    E1->AddPoint(P1);

                }
                else
                {
                    hafigli = true;
                    E0 = (GenericEdge*)longestEdge->Child(1);  //bisogna invertire gli indici per rispettare l'orientamento
                    E1 = (GenericEdge*)longestEdge->Child(0);
                    Pm = meshPointer->Point(E0->Point(1)->Id());

                    Ee = meshPointer->CreateEdge();    // Mediana del lato lungo
                    meshPointer->AddEdge(Ee);
                    C0 = meshPointer->CreateCell();    // Prima sotto-cella
                    meshPointer->AddCell(C0);
                    C1 = meshPointer->CreateCell();    // Seconda sotto-cella
                    meshPointer->AddCell(C1);
                    edgesToCut.push_back(false);
                    cellsToCut.push_back(false);
                    cellsToCut.push_back(false);

                    cell->AddChild(C0);
                    cell->AddChild(C1);
                    C0->SetFather(cell);
                    C1->SetFather(cell);


                }


                // Inserisco i punti su cui insiste la mediana
                Ee->AddPoint(Pp);
                Ee->AddPoint(Pm);

                // Inserisco i punti su cui insite la prima sotto-cella
                C0->AddPoint(Pm);
                C0->AddPoint(Pp);
                C0->AddPoint(P0);
                // Inserisco i lati su cui insite la prima sotto-cella
                C0->AddEdge(Ee);
                C0->AddEdge(L1);
                C0->AddEdge(E0);

                // Inserisco i punti su cui insite la seconda sotto-cella
                C1->AddPoint(Pm);
                C1->AddPoint(P1);
                C1->AddPoint(Pp);
                // Inserisco i lati su cui insite la seconda sotto-cella
                C1->AddEdge(E1);
                C1->AddEdge(L0);
                C1->AddEdge(Ee);

                // Aggiorno le informazioni di vicinanza
                // Punto medio balza perchè è un punto e i punti non hanno diritti

                // Per i lati RightCell = cells[0]
                // Primo/secondo sottosegmento si appoggia all'ignoto da una parte e da C0/C1 sull'altra

                // Aggiornare la vicinanza di L0      TO DO
                // Aggiornare la vicinanza di L1      TO DO
                // Aggiornare  la vicinanza delle celle adiacenti a C1 e C0

                E0->AllocateCells(2);
                //E0->InsertCell(bho0,0);           Solo se ha figli
                E0->InsertCell(C0,1);
                E1->AllocateCells(2);
                //E1->InsertCell(bho0,0);           Solo se ha figli
                E1->InsertCell(C1,1);

                // Mediana del lato lungo
                Ee->AddCell(C0);
                Ee->AddCell(C1);

                // Prima sottocella
                C0->AllocateCells(3);
                C0->InsertCell(C1,0);
                C0->InsertCell((L1->RightCell()),1);
                //C0->InsertCell(bho0,2);           Solo se ha figli

                // Seconda sottocella
                C1->AllocateCells(3);
                //C1->InsertCell(bho0,0);           Solo se ha figli
                C1->InsertCell((L0->RightCell()),1);
                C1->InsertCell(C0,2);

                if (hafigli){
                   E0->InsertCell((GenericCell*)longestEdge->RightCell()->Child(1),0);
                   E1->InsertCell((GenericCell*)longestEdge->RightCell()->Child(0),0);

                   C0->InsertCell(E0->RightCell(),2);
                   C1->InsertCell(E1->RightCell(),0);

                }



                // Ora ho tagliato il lato più lungo e ho raffinato la cella
                cellsToCut.at(cellId) = false;
                edgesToCut.at(longestEdge->Id()) = false; // Forse questa riga non va qua ma nell'if        TODO

                // Se una delle celle ha almeno un lato da tagliare è da raffinare
                if (edgesToCut.at(C0->Edge(0)->Id()) or
                    edgesToCut.at(C0->Edge(1)->Id()) or
                    edgesToCut.at(C0->Edge(2)->Id()))
                    AddCellToRefine(C0->Id());

                if (edgesToCut.at(C1->Edge(0)->Id()) or
                    edgesToCut.at(C1->Edge(1)->Id()) or
                    edgesToCut.at(C1->Edge(2)->Id()))
                    AddCellToRefine(C1->Id());



                // Ricontrollo tutto il vettore
                cellsToCut.at(cellId) = false;
                cellId = 0;
            }
        }
    	return Output::Success;
    }



}
