#include "GenericDomain.hpp"
#include "Output.hpp"

namespace GeDiM
{
	// ***************************************************************************
	// IGenericDomainRotation Implementation
	// ***************************************************************************
	IRotation::IRotation()
	{
		rotation = NULL;
		originTranslation = NULL;
	}

	IRotation::IRotation(const IRotation& irotation)
	{
		if(irotation.rotation != NULL)
			rotation = new Matrix3d(*irotation.rotation);
		else
			rotation = NULL;
		if(irotation.originTranslation != NULL)
			originTranslation = new Vector3d(*irotation.originTranslation);
		else
			originTranslation = NULL;
	}
	IRotation::~IRotation()
	{
		rotation = NULL;
		originTranslation = NULL;
	}
	// ***************************************************************************
	Output::ExitCodes IRotation::RotateVertices(const vector<Vector3d>& verticesToRotate, vector<Vector3d>& rotatedVertices) const
	{
		const unsigned int& numVertices = verticesToRotate.size();

		rotatedVertices.clear();
		rotatedVertices.reserve(numVertices);

		for(unsigned int i = 0; i < numVertices; i++)
			rotatedVertices.push_back(RotatePoint(verticesToRotate[i]));

		return Output::Success;
	}
	// ***************************************************************************
	Vector3d IRotation::RotatePoint(const Vector3d& point, const bool& translation, const bool& inverse) const
	{
		if (originTranslation == NULL && rotation == NULL)
			return point;

		if (rotation == NULL)
		{
			if (inverse)
				return point + Translation();
			else
				return point - Translation();
		}

		if (originTranslation == NULL || translation == false)
		{
			if (inverse)
				return RotationMatrix() * point;
			else
				return RotationMatrix().transpose() * point;
		}

		if (inverse)
			return RotationMatrix() * point + Translation();
		else
			return RotationMatrix().transpose() * (point - Translation());
	}
	// ***************************************************************************
	// GenericDomain Implementation
	// ***************************************************************************
	GenericDomain::GenericDomain(const unsigned int& _globalId)
	{
		ConstructorBase(_globalId);
	}
	GenericDomain::GenericDomain(const unsigned int& _globalId, const unsigned int& _totalNumberVertices)
	{
		ConstructorBase(_globalId);

		if (_totalNumberVertices == 0)
		{
			Output::PrintWarningMessage("Impossible to create domain %d with zero vertices", false, _globalId);
			return;
		}

		InitializeVertices(_totalNumberVertices);
	}
	GenericDomain::GenericDomain(const unsigned int& _globalId, const unsigned int& _totalNumberVertices, const unsigned int& _totalNumberEdges)
	{
		ConstructorBase(_globalId);

		if (_totalNumberVertices == 0)
		{
			Output::PrintWarningMessage("Impossible to create domain %d with zero vertices", false, _globalId);
			return;
		}

		if (_totalNumberEdges == 0)
		{
			Output::PrintWarningMessage("Impossible to create domain %d with zero edges", false, _globalId);
			return;
		}

		InitializeVertices(_totalNumberVertices);
		InitializeEdges(_totalNumberEdges);
	}
	GenericDomain::GenericDomain(const unsigned int& _globalId, const unsigned int& _totalNumberVertices, const unsigned int& _totalNumberEdges, const unsigned int& _totalNumberFaces)
	{
		ConstructorBase(_globalId);

		if (_totalNumberVertices == 0)
		{
			Output::PrintWarningMessage("Impossible to create domain %d with zero vertices", false, _globalId);
			return;
		}

		if (_totalNumberEdges == 0)
		{
			Output::PrintWarningMessage("Impossible to create domain %d with zero edges", false, _globalId);
			return;
		}

		if (_totalNumberFaces == 0)
		{
			Output::PrintWarningMessage("Impossible to create domain %d with zero faces", false, _globalId);
			return;
		}

		InitializeVertices(_totalNumberVertices);
		InitializeEdges(_totalNumberEdges);
		InitializeFaces(_totalNumberFaces);
	}

	GenericDomain::GenericDomain(const GenericDomain& domain)
	{
		//Constructor GenericDomain
		globalId = domain.globalId;
		description = domain.description; ///< Description of the domain
		initialized = domain.initialized;

		totalNumberVertices = domain.totalNumberVertices; ///< Number of vertices of the domain
		totalNumberEdges = domain.totalNumberEdges; ///< Number of edges of the domain
		totalNumberFaces = domain.totalNumberFaces; ///< Number of faces of the domain

		unsigned int sizeVertices = domain.vertices.size();
		if(sizeVertices > 0)
			vertices.resize(sizeVertices);
		for(unsigned int v = 0; v < sizeVertices; v++)
			vertices[v] = domain.vertices[v]; ///< Array of domain vertices

		unsigned int sizeEdges = domain.edgeVertices.size();
		if(sizeEdges > 0)
			edgeVertices.resize(sizeEdges);
		for(unsigned int ev = 0; ev < sizeEdges; ev++)
			edgeVertices[ev] = domain.edgeVertices[ev]; ///< Array of domain vertices

		unsigned int sizeFace = domain.faceVertices.size();
		if(sizeFace > 0)
			faceVertices.resize(sizeFace);
		for(unsigned int f = 0; f < sizeFace; f++)
		{
			unsigned int sizeFaceVertices = domain.faceVertices[f].size();
			if(sizeFaceVertices > 0)
				faceVertices[f].resize(sizeFaceVertices);
			for(unsigned int fv = 0; fv < sizeFaceVertices; fv++)
				(faceVertices[f])[fv] = (domain.faceVertices[f])[fv];
		}

		sizeFace = domain.faceEdges.size();
		if(sizeFace > 0)
			faceEdges.resize(sizeFace);
		for(unsigned int f = 0; f < sizeFace; f++)
		{
			unsigned int sizeFaceEdge = domain.faceEdges[f].size();
			if(sizeFaceEdge > 0)
				faceEdges[f].resize(sizeFaceEdge);
			for(unsigned int fe = 0; fe < sizeFaceEdge; fe++)
				(faceVertices[f])[fe] = (domain.faceVertices[f])[fe];
		}

		rotationMatrix = domain.rotationMatrix;

		unsigned int sizeRotatedVertices = domain.rotatedVertices.size();
		if(sizeVertices > 0)
			rotatedVertices.resize(sizeVertices);
		for(unsigned int rv = 0; rv < sizeRotatedVertices; rv++)
			rotatedVertices[rv] = domain.rotatedVertices[rv]; ///< Array of domain vertices

		measure = domain.measure; ///< Measure of the domain

		centroid = domain.centroid; ///< Centroid of the domain
		squaredRadius = domain.squaredRadius; ///< Squared radius of the domain (squared max distance between centroid and vertices)
		radius = domain.radius; ///< Radius of the domain (max distance between centroid and vertices)

		for(map<string,void*>::const_iterator it = domain.properties.begin(); it != domain.properties.end(); it++)
			properties[it->first] = domain.properties.at(it->first);
	}

	GenericDomain::~GenericDomain()
	{
		vertices.clear();
		edgeVertices.clear();

		for (unsigned int f = 0; f < faceEdges.size(); f++)
			faceEdges[f].clear();
		faceEdges.clear();

		for (unsigned int f = 0; f < faceVertices.size(); f++)
			faceVertices[f].clear();
		faceVertices.clear();

		rotatedVertices.clear();

		initialized = false;
	}
	// ***************************************************************************
	void GenericDomain::ConstructorBase(const unsigned int& _globalId)
	{
		globalId = _globalId;

		totalNumberVertices = 0;
		totalNumberEdges = 0;
		totalNumberFaces = 0;

		measure = 0.0;

		centroid.setZero();
		squaredRadius = 0.0;
		radius = 0.0;
		description = "Domain";

		rotationMatrix.setIdentity();

		initialized = false;
		toBeExport = true;
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain::ComputeRadius(const double& squaredTolerance)
	{
		if (NumberVertices() != TotalNumberVertices())
		{
			Output::PrintWarningMessage("Domain %d. Impossible to compute the radius. It has %d vertices, expected %d.", false, globalId, NumberVertices(), TotalNumberVertices());
			return Output::GenericError;
		}

		squaredRadius = 0.0;
		radius = 0.0;
		const size_t numberVertices = NumberVertices();
		for (unsigned int v = 0; v < numberVertices; v++)
		{
			double squaredDistance = (centroid - vertices[v]).squaredNorm();
			if (squaredRadius < squaredDistance)
				squaredRadius = squaredDistance;
		}
		radius = sqrt(squaredRadius);

		if (fabs(squaredRadius) < squaredTolerance)
		{
			squaredRadius = 0.0;
			Output::PrintErrorMessage("Domain %d. Squared Radius too small: %.2e - tolerance %.2e", false, globalId, squaredRadius, squaredTolerance);
			return Output::GenericError;
		}

		return Output::Success;
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain::AddVertex(const Vector3d& vertex)
	{
		if (vertices.size() == totalNumberVertices)
		{
			Output::PrintErrorMessage("Domain %d. Vertices size %d already reached", false, globalId, totalNumberVertices);
			return Output::GenericError;
		}

		vertices.push_back(vertex);
		return Output::Success;
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain::AddEdge(const unsigned int& originNumber, const unsigned int& endNumber)
	{
		if (edgeVertices.size() == 2 * totalNumberEdges)
		{
			Output::PrintErrorMessage("Domain %d. Edges size %d already reached", false, globalId, totalNumberEdges);
			return Output::GenericError;
		}

		if (originNumber > totalNumberVertices - 1)
		{
			Output::PrintErrorMessage("Domain %d. Vertex origin position %d not existed, expected less than %d", false, globalId, originNumber, totalNumberVertices);
			return Output::GenericError;
		}

		if (endNumber > totalNumberVertices - 1)
		{
			Output::PrintErrorMessage("Domain %d. Vertex destination position %d not existed, expected less than %d", false, globalId, endNumber, totalNumberVertices);
			return Output::GenericError;
		}

		edgeVertices.push_back(originNumber);
		edgeVertices.push_back(endNumber);

		return Output::Success;
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain::AddFace(vector<unsigned int> _faceVertices, vector<unsigned int> _faceEdges)
	{
		if (faceVertices.size() == totalNumberFaces)
		{
			Output::PrintErrorMessage("Domain %d. Faces size %d already reached", false, globalId, totalNumberFaces);
			return Output::GenericError;
		}

		if (_faceVertices.size() == 0 || _faceEdges.size() == 0)
		{
			Output::PrintErrorMessage("Domain %d. No face vertices or edges", false, globalId);
			return Output::GenericError;
		}

		faceVertices.push_back(vector<unsigned int>(_faceVertices.size()));
		faceEdges.push_back(vector<unsigned int>(_faceEdges.size()));

		memcpy(faceVertices.back().data(), _faceVertices.data(), _faceVertices.size() * sizeof(unsigned int));
		memcpy(faceEdges.back().data(), _faceEdges.data(), _faceEdges.size() * sizeof(unsigned int));

		return Output::Success;
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain::InitializeProperty(const string& key)
	{
		map<string,void*>::iterator finder;
		finder = properties.find(key);

		if(finder == properties.end())
		{
			pair <string, void*> property(key, NULL);
			properties.insert(property);
			return Output::Success;
		}
		else
			return Output::GenericError;
	}
	// ***************************************************************************
	// GenericDomain1D Implementation
	// ***************************************************************************
	GenericDomain1D::GenericDomain1D(const unsigned int& _globalId, const bool& initializeVertices) : GenericDomain(_globalId)
	{
		tangent.setZero();

		if (!initializeVertices)
			return;

		InitializeVertices(2);
	}

	GenericDomain1D::GenericDomain1D(const GenericDomain1D& domain) : GenericDomain(domain), IRotation(domain)
	{
		tangent = domain.tangent;
		SetRotationMatrix(Matrix3d(domain.rotationMatrix));
		SetOriginTranslation(Vector3d(domain.vertices[0]));
	}

	GenericDomain1D::~GenericDomain1D()
	{
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain1D::Initialize()
	{
		/// <ul>
		Output::ExitCodes result;

		if (IsInitialized())
		{
			Output::PrintErrorMessage("Domain %d initialization. Domain already initialized.", false, globalId);
			return Output::GenericError;
		}

		/// <li> Add edge
		InitializeEdges(1);
		result = AddEdge(0, 1);
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. AddEdge failed.", false, globalId);
			return result;
		}

		/// <li> Compute Tangent
		result = ComputeTangent();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputeTangent failed.", false, globalId);
			return result;
		}

		SetOriginTranslation(vertices[0]);
		result = ComputeRotationMatrix();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputeRotationMatrix failed.", false, globalId);
			return result;
		}

		/// <li> Compute Rotation
		result = RotateVertices(vertices, rotatedVertices);
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. RotateVertices failed.", false, globalId);
			return result;
		}

		/// <li> Compute Length and Centroid
		result = ComputeLengthAndCentroid();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputeLengthAndCentroid failed.", false, globalId);
			return result;
		}

		/// <li> Compute Radius
		result = ComputeRadius();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputeRadius failed.", false, globalId);
			return result;
		}

		initialized = true;

		return Output::Success;

		/// </ul>
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain1D::ComputeTangent()
	{
		/// <ul>
		if (NumberVertices() != TotalNumberVertices())
		{
			Output::PrintWarningMessage("Domain %d. Impossible to compute the geometric properties. It has %d vertices, expected %d", false, globalId, NumberVertices(), TotalNumberVertices());
			return Output::GenericError;
		}

		/// <li> Compute tangent
		tangent = vertices[1] - vertices[0];
		tangent.normalize();

		return Output::Success;

		/// </ul>
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain1D::ComputeRotationMatrix(const double& rotationTolerance)
	{
		if (NumberVertices() != TotalNumberVertices())
		{
			Output::PrintWarningMessage("Domain %d. Impossible to compute the geometric properties. It has %d vertices, expected %d", false, globalId, NumberVertices(), TotalNumberVertices());
			return Output::GenericError;
		}

		Quaterniond quaternion;
		quaternion.setFromTwoVectors(Eigen::Vector3d(1.0,0,0), tangent);
		rotationMatrix = quaternion.toRotationMatrix();

		SetRotationMatrix(rotationMatrix);

		return Output::Success;
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain1D::ComputeLengthAndCentroid(const double& lengthTolerance)
	{
		if (NumberVertices() != TotalNumberVertices())
		{
			Output::PrintWarningMessage("Domain %d. Impossible to compute the geometric properties. It has %d vertices, expected %d.", false, globalId, NumberVertices(), TotalNumberVertices());
			return Output::GenericError;
		}

		measure = (vertices[0] - vertices[1]).norm();
		centroid = (vertices[0] + vertices[1]) / 2.0;

		if (fabs(measure) < lengthTolerance)
		{
			measure = 0.0;
			Output::PrintErrorMessage("Domain %d. Length too small: %.2e - tolerance %.2e", false, globalId, measure, lengthTolerance);
			return Output::GenericError;
		}

		return Output::Success;
	}
	// ***************************************************************************
	// GenericDomain2D Implementation
	// ***************************************************************************
	GenericDomain2D::GenericDomain2D(const unsigned int& _globalId) : GenericDomain(_globalId)
	{
		planeTranslation = 0;
		planeNormal.setZero();
	}
	GenericDomain2D::GenericDomain2D(const unsigned int& _globalId, const unsigned int& _totalNumberVertices) : GenericDomain(_globalId, _totalNumberVertices, _totalNumberVertices), IRotation()
	{
		planeTranslation = 0;
		planeNormal.setZero();
	}

	GenericDomain2D::GenericDomain2D(const GenericDomain2D& domain) : GenericDomain(domain), IRotation(domain)
	{
		planeNormal = domain.planeNormal;
		planeTranslation = domain.planeTranslation;
	}

	GenericDomain2D::~GenericDomain2D()
	{
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain2D::Initialize()
	{
		/// <ul>
		Output::ExitCodes result;

		if (IsInitialized())
		{
			Output::PrintErrorMessage("Domain %d initialization. Domain already initialized.", false, globalId);
			return Output::GenericError;
		}

		/// <li> Add Face
		vector<unsigned int> vertexIndices(totalNumberVertices);

		for (unsigned int p = 0; p < totalNumberVertices; p++)
			vertexIndices[p] = p;

		InitializeFaces(1);
		result = AddFace(vertexIndices, vertexIndices);
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. AddFace failed.", false, globalId);
			return result;
		}

		/// <li> Compute Plane
		result = ComputePlane();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputePlane failed.", false, globalId);
			return result;
		}

		/// <li> Compute Rotation
		SetOriginTranslation(vertices[0]);
		result = ComputeRotationMatrix();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputeRotationMatrix failed.", false, globalId);
			return result;
		}

		result = RotateVertices(vertices, rotatedVertices);
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. RotateVertices failed.", false, globalId);
			return result;
		}

		/// <li> Compute Area and Centroid
		result = ComputeAreaAndCentroid();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputeAreaAndCentroid failed.", false, globalId);
			return result;
		}

		/// <li> Compute Radius
		result = ComputeRadius();
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Domain %d initialization. ComputeRadius failed.", false, globalId);
			return result;
		}

		initialized = true;

		return Output::Success;

		/// </ul>
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain2D::ComputePlane()
	{
		/// <ul>
		if (NumberEdges() != TotalNumberEdges())
		{
			Output::PrintWarningMessage("Domain %d. Impossible to compute the geometric properties. It has %d edges, expected %d", false, globalId, NumberEdges(), TotalNumberEdges());
			return Output::GenericError;
		}

		/// <li> Compute normal vector N
		planeNormal.setZero();
		for(unsigned int i = 0; i < totalNumberEdges; i++)
		{
			int previousEdgeIndex = (i == 0) ? totalNumberEdges - 1 : i - 1;

			Vector3d edgeOne = Vertex(EdgeEndIndex(i)) - Vertex(EdgeOriginIndex(i));
			Vector3d edgeTwo = Vertex(EdgeOriginIndex(previousEdgeIndex)) - Vertex(EdgeEndIndex(previousEdgeIndex));

			planeNormal.noalias() += edgeOne.cross(edgeTwo);
		}
		planeNormal.normalize();

		/// <li> Compute d
		planeTranslation = planeNormal.dot(vertices[0]);

		return Output::Success;

		/// </ul>
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain2D::ComputeRotationMatrix(const double& rotationTolerance)
	{
		if (NumberVertices() != TotalNumberVertices())
		{
			Output::PrintWarningMessage("Domain %d. Impossible to compute the geometric properties. It has %d vertices, expected %d", false, globalId, NumberVertices(), TotalNumberVertices());
			return Output::GenericError;
		}

		MatrixXd Z(3, totalNumberVertices);
		MatrixXd W(3, totalNumberVertices);
		Matrix3d H;
		Vector3d V1mV0 = vertices[1] - vertices[0];

		for (unsigned int i = 1; i < totalNumberVertices; i++)
		{
			Vector3d VimV0 = vertices[i] - vertices[0];
			Z.col(i - 1) = VimV0;

			double normVector = VimV0.norm();
			double angleBetweenVectors = ((VimV0 - V1mV0).norm() < rotationTolerance) ? 0.0 : acos(VimV0.dot(V1mV0) / (normVector * V1mV0.norm()));
			W.col(i - 1) << normVector * cos(angleBetweenVectors), normVector * sin(angleBetweenVectors), 0;
		}

		Z.col(totalNumberVertices - 1) = planeNormal;
		W.col(totalNumberVertices - 1)<< 0, 0, 1;
		H = W * Z.transpose();
		JacobiSVD<MatrixXd> svd(H, ComputeThinU | ComputeThinV);
		rotationMatrix = svd.matrixV() * (svd.matrixU()).transpose();

		SetRotationMatrix(rotationMatrix);

		return Output::Success;
	}
	// ***************************************************************************
	Output::ExitCodes GenericDomain2D::ComputeAreaAndCentroid(const double& areaTolerance)
	{
		if (NumberRotatedVertices() != TotalNumberVertices())
		{
			Output::PrintWarningMessage("Domain %d. Impossible to compute the geometric properties. It has %d vertices, expected %d.", false, globalId, NumberVertices(), TotalNumberVertices());
			return Output::GenericError;
		}

		for (unsigned int i = 0; i < totalNumberVertices; i++)
		{
			const Vector3d& vertex = rotatedVertices[i];
			const Vector3d& nextVertex = rotatedVertices[(i + 1) % totalNumberVertices];

			double localArea = vertex(0) * nextVertex(1) - nextVertex(0) * vertex(1);

			measure += localArea;
			centroid(0) += (vertex(0) + nextVertex(0)) * localArea;
			centroid(1) += (vertex(1) + nextVertex(1)) * localArea;
		}

		if (fabs(measure) < areaTolerance)
		{
			Output::PrintErrorMessage("Domain %d. Area too small: %.2e - tolerance %.2e", false, globalId, measure, areaTolerance);
			return Output::GenericError;
		}

		measure /= 2.0;
		centroid /=	(6.0 * measure);
		measure = (measure >= 0.0) ? measure : -1.0 * measure;

		centroid = RotatePoint(centroid, true, true);

		return Output::Success;
	}
	// ***************************************************************************
	bool GenericDomain2D::PointInDomainRotatedNoBoundary (const Vector3d& point, const double& tolerance) const
	{
		for(unsigned int pntVert = 0; pntVert < NumberVertices() ; pntVert++)
		{
			Vector3d tangentVectorEdge = rotatedVertices[(pntVert+1)%NumberVertices()] - rotatedVertices[pntVert];
			Vector3d tangentVectorDifference = point -  rotatedVertices[pntVert];

			double crossProd = tangentVectorEdge.x() * tangentVectorDifference.y() - tangentVectorDifference.x() * tangentVectorEdge.y();

			if(crossProd > tolerance)
				continue;
			if(crossProd < tolerance)
				return false;
			if(tangentVectorEdge.squaredNorm() < tangentVectorDifference.squaredNorm() )
				return false;
			if((tangentVectorEdge.x() * tangentVectorDifference.x() < -tolerance) || (tangentVectorEdge.y() * tangentVectorDifference.y() < -tolerance) )
				return false;

		}
		return true;
	}
	// ***************************************************************************
	// GenericDomain3D Implementation
	// ***************************************************************************
	GenericDomain3D::GenericDomain3D(const unsigned int& _globalId) : GenericDomain(_globalId)
	{
	}
	GenericDomain3D::GenericDomain3D(const unsigned int& _globalId, const unsigned int& _totalNumberVertices, const unsigned int& _totalNumberEdges, const unsigned int& _totalNumberFaces) : GenericDomain(_globalId, _totalNumberVertices, _totalNumberEdges, _totalNumberFaces)
	{
	}
	GenericDomain3D::~GenericDomain3D()
	{
	}
}
