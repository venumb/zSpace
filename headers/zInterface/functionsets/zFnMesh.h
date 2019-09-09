// This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
// data analysis & visualization framework.
//
// Copyright (C) 2019 ZSPACE 
// 
// This Source Code Form is subject to the terms of the MIT License 
// If a copy of the MIT License was not distributed with this file, You can 
// obtain one at https://opensource.org/licenses/MIT.
//
// Author : Vishu Bhooshan <vishu.bhooshan@zaha-hadid.com>
//

#ifndef ZSPACE_FN_MESH_H
#define ZSPACE_FN_MESH_H

#pragma once


#include<headers/zInterface/objects/zObjMesh.h>
#include<headers/zInterface/objects/zObjGraph.h>
#include<headers/zInterface/functionsets/zFn.h>

#include<headers/zInterface/iterators/zItMesh.h>


namespace zSpace
{
	/** \addtogroup zInterface
	*	\brief The Application Program Interface of the library.
	*  @{
	*/

	/** \addtogroup zFuntionSets
	*	\brief The function set classes of the library.
	*  @{
	*/

	/*! \class zFnMesh
	*	\brief A mesh function set.
	*	\since version 0.0.2
	*/

	/** @}*/

	/** @}*/

	class ZSPACE_API zFnMesh : public zFn
	{

	protected:

		/*!	\brief core utilities Object  */
		zUtilsCore coreUtils;

		/*!	\brief pointer to a mesh object  */
		zObjMesh *meshObj;

	public:
		
		//--------------------------
		//---- CONSTRUCTOR
		//--------------------------

		/*! \brief Default constructor.
		*
		*	\since version 0.0.2
		*/
		zFnMesh();

		/*! \brief Overloaded constructor.
		*
		*	\param		[in]	_meshObj			- input mesh object.
		*	\since version 0.0.2
		*/
		zFnMesh(zObjMesh &_meshObj);

		//--------------------------
		//---- DESTRUCTOR
		//--------------------------

		/*! \brief Default destructor.
		*
		*	\since version 0.0.2
		*/
		~zFnMesh();

		//--------------------------
		//---- OVERRIDE METHODS
		//--------------------------

		zFnType getType() override;

		void from(string path, zFileTpye type, bool staticGeom = false) override;

		void to(string path, zFileTpye type) override;

		void clear() override;
		
		//--------------------------
		//---- CREATE METHODS
		//--------------------------

		/*! \brief This method reserves memorm for the mesh element containers. 
		*
		*	\param		[in]	_n_v			- size of vertices.
		*	\param		[in]	_n_e			- size of edges.
		*	\param		[in]	_n_f			- size of faces.		
		*	\since version 0.0.2
		*/
		void reserve(int _n_v, int  _n_e, int _n_f);
				
		/*! \brief This method creates a mesh from the input containers.
		*
		*	\param		[in]	_positions		- container of type zVector containing position information of vertices.
		*	\param		[in]	polyCounts		- container of type integer with number of vertices per polygon.
		*	\param		[in]	polyConnects	- polygon connection list with vertex ids for each face.
		*	\param		[in]	staticMesh		- makes the mesh fixed. Computes the static edge and face vertex positions if true.
		*	\since version 0.0.2
		*/
		void create(vector<zVector>(&_positions), vector<int>(&polyCounts), vector<int>(&polyConnects), bool staticMesh = false);
				
		/*! \brief This method adds a vertex to the mesh. 
		*
		*	\param		[in]	_pos				- zVector holding the position information of the vertex.
		*	\param		[in]	checkDuplicates		- checks for duplicates if true.
		*	\param		[out]	vertex			- vertex iterator of the new vertex or existing if it is a duplicate.
		*	\return				bool				- true if the vertex container is resized.
		*	\note	 The vertex pointers will need to be computed/ set.
		*	\since version 0.0.2
		*/
		bool addVertex(zVector &_pos, bool checkDuplicates, zItMeshVertex &vertex);

		/*! \brief This method adds an edge and its symmetry edge to the mesh.
		*
		*	\param		[in]	v1			- start vertex index of the edge.
		*	\param		[in]	v2			- end vertex index of the edge.
		*	\param		[out]	halfEdge	- hafedge iterator of the new halfedge or existing if it is a duplicate.
		*	\return				bool		- true if the edges container is resized.
		*	\note	 The half edge pointers will need to be computed/ set.
		*	\since version 0.0.2
		*/
		bool addEdges(int &v1, int &v2, bool checkDuplicates, zItMeshHalfEdge &halfEdge);

		/*! \brief This method adds a face to the mesh.
		*
		*	\param		[in]	fVertices	- array of ordered vertex index that make up the polygon.
		*	\param		[out]	face		- face iterator of the new face
		*	\return				bool		- true if the faces container is resized.
		*	\since version 0.0.2
		*/
		bool addPolygon(vector<int> &fVertices, zItMeshFace &face);

		/*! \brief This method adds a face to the mesh.
		*
		*	\param		[in]	fVertices	- array of ordered vertex positions that make up the polygon.
		*	\param		[out]	face		- face iterator of the new face
		*	\return				bool		- true if the faces container is resized.
		*	\since version 0.0.2
		*/
		bool addPolygon(vector<zVector> &fVertices, zItMeshFace &face);

		/*! \brief This method adds a face to the mesh.
		*
		*	\param		[out]	face		- face iterator of the new face
		*	\return				bool		- true if the faces container is resized.
		*	\note	 The face pointers will need to be computed/ set.
		*	\since version 0.0.2
		*/
		bool addPolygon(zItMeshFace &face);

		//--------------------------
		//--- TOPOLOGY QUERY METHODS 
		//--------------------------
		
		/*! \brief This method returns the number of vertices in the mesh.
		*	\return				int - number of vertices.
		*	\since version 0.0.2
		*/
		int numVertices();

		/*! \brief This method returns the number of half edges in the mesh.
		*	\return				int - number of edges.
		*	\since version 0.0.2
		*/
		int numEdges();

		/*! \brief This method returns the number of half edges in the mesh.
		*	\return				int - number of half edges.
		*	\since version 0.0.2
		*/
		int numHalfEdges();

		/*! \brief This method returns the number of polygons in the mesh
		*
		*	\return		int		-	number of polygons
		*	\since version 0.0.2
		*/
		int numPolygons();

		/*! \brief This method detemines if a vertex already exists at the input position
		*
		*	\param		[in]		pos			- position to be checked.
		*	\param		[out]		outVertexId	- stores vertexId if the vertex exists else it is -1.
		*	\param		[in]		precisionfactor	- input precision factor.
		*	\return		[out]		bool		- true if vertex exists else false.
		*	\since version 0.0.2
		*/
		bool vertexExists(zVector pos, zItMeshVertex &outVertex, int precisionfactor = 6);

		/*! \brief This method detemines if an edge already exists between input vertices.
		*
		*	\param		[in]	v1			-  vertexId 1.
		*	\param		[in]	v2			-  vertexId 2.
		*	\param		[out]	outHalfEdgeId	-  half edge id.
		*	\return		[out]	bool		-  true if edge exists else false.
		*	\since version 0.0.2
		*/
		bool halfEdgeExists(int v1, int v2, int &outHalfEdgeId);
				
		/*! \brief This method detemines if an edge already exists between input vertices.
		*
		*	\param		[in]	v1			-  vertexId 1.
		*	\param		[in]	v2			-  vertexId 2.
		*	\param		[out]	outEdgeId	-  half edge iterator if edge exists.
		*	\return		[out]	bool		-  true if edge exists else false.
		*	\since version 0.0.2
		*/
		bool halfEdgeExists(int v1, int v2, zItMeshHalfEdge &outHalfEdge);

		/*! \brief This method computes the mesh laplcaian operator.
		*
		*	\details Based on http://www.cs.jhu.edu/~misha/Fall07/Papers/Nealen06.pdf and http://mgarland.org/files/papers/ssq.pdf
		*	\return			MatrixXd	- output mesh laplacian matrix.		
		*	\since version 0.0.2
		*/
		zSparseMatrix getTopologicalLaplacian();

		/*!	\brief This method returns the cotangent weight of the indexed half edge.
		*
		*	\param		[in]	index	- index in the edge container.
		*	\return				double	- output edge contangent weight.
		*	\since version 0.0.2
		*/
		double getEdgeCotangentWeight(zItMeshHalfEdge &he);
		
		//--------------------------
		//--- COMPUTE METHODS 
		//--------------------------				

		/*! \brief This method computes the Edge colors based on the vertex colors.
		*
		*	\since version 0.0.2
		*/
		void computeEdgeColorfromVertexColor();

		/*! \brief This method computes the vertex colors based on the face colors.
		*
		*	\since version 0.0.2
		*/
		void computeVertexColorfromEdgeColor();

		/*! \brief This method computes the face colors based on the vertex colors.
		*
		*	\since version 0.0.2
		*/
		void computeFaceColorfromVertexColor();

		/*! \brief This method computes the vertex colors based on the face colors.
		*
		*	\since version 0.0.2
		*/
		void computeVertexColorfromFaceColor();

		/*! \brief This method smoothens the color attributes.
		*	\param		[in]	smoothVal		- number of iterations to run the smooth operation.
		*	\param		[in]	type			- zVertexData or zEdgeData or zFaceData.
		*	\since version 0.0.2
		*/
		void smoothColors(int smoothVal = 1, zHEData type = zVertexData);

		/*! \brief This method computes the vertex normals based on the face normals.
		*
		*	\since version 0.0.2
		*/
		void computeVertexNormalfromFaceNormal();

		/*! \brief This method computes the normals assoicated with vertices and polygon faces .
		*
		*	\since version 0.0.2
		*/
		void computeMeshNormals();
		
		/*! \brief This method averages the positions of vertex except for the ones on the boundary.
		*
		*	\param		[in]	numSteps	- number of times the averaging is carried out.
		*	\since version 0.0.2
		*/
		void averageVertices(int numSteps = 1);
		
		/*! \brief This method removes inactive elements from the containers connected with the input type.
		*
		*	\param		[in]	type			- zVertexData or zEdgeData or zHalfEdgeData or zFaceData .
		*	\since version 0.0.2
		*/
		void garbageCollection(zHEData type);

		/*! \brief This method makes the mesh a static mesh. Makes the mesh fixed and computes the static edge and face vertex positions if true.
		*	
		*	\since version 0.0.2
		*/
		void makeStatic();

		//--------------------------
		//--- SET METHODS 
		//--------------------------
		
		/*! \brief This method sets vertex positions of all the vertices.
		*
		*	\param		[in]	pos				- positions  contatiner.
		*	\since version 0.0.2
		*/
		void setVertexPositions(vector<zVector>& pos);

		/*! \brief This method sets vertex color of all the vertices to the input color.
		*
		*	\param		[in]	col				- input color.
		*	\param		[in]	setFaceColor	- face color is computed based on the vertex color if true.
		*	\since version 0.0.2
		*/
		void setVertexColor(zColor col, bool setFaceColor = false);

		/*! \brief This method sets vertex color of all the vertices with the input color contatiner.
		*
		*	\param		[in]	col				- input color  contatiner. The size of the contatiner should be equal to number of vertices in the mesh.
		*	\param		[in]	setFaceColor	- face color is computed based on the vertex color if true.
		*	\since version 0.0.2
		*/
		void setVertexColors(vector<zColor>& col, bool setFaceColor = false);

		/*! \brief This method sets face color of all the faces to the input color.
		*
		*	\param		[in]	col				- input color.
		*	\param		[in]	setVertexColor	- vertex color is computed based on the face color if true.
		*	\since version 0.0.2
		*/
		void setFaceColor(zColor col, bool setVertexColor = false);

		/*! \brief This method sets face color of all the faces to the input color contatiner.
		*
		*	\param		[in]	col				- input color contatiner. The size of the contatiner should be equal to number of faces in the mesh.
		*	\param		[in]	setVertexColor	- vertex color is computed based on the face color if true.
		*	\since version 0.0.2
		*/
		void setFaceColors(vector<zColor>& col, bool setVertexColor = false);

		/*! \brief This method sets face color of all the faces based on face normal angle to the input light vector.
		*
		*	\param		[in]	lightVec		- input light vector.
		*	\param		[in]	setVertexColor	- vertex color is computed based on the face color if true.
		*	\since version 0.0.2
		*/
		void setFaceColorOcclusion(zVector &lightVec, bool setVertexColor = false);

		/*! \brief This method sets face normals of all the faces to the input normal.
		*
		*	\param		[in]	fNormal			- input normal.
		*	\since version 0.0.2
		*/
		void setFaceNormals(zVector &fNormal);

		/*! \brief This method sets face normals of all the faces to the input normals contatiner.
		*
		*	\param		[in]	fNormals		- input normals contatiner. The size of the contatiner should be equal to number of faces in the mesh.
		*	\since version 0.0.2
		*/
		void setFaceNormals(vector<zVector> &fNormals);

		/*! \brief This method sets edge color of all the edges to the input color.
		*
		*	\param		[in]	col				- input color.
		*	\param		[in]	setVertexColor	- vertex color is computed based on the edge color if true.
		*	\since version 0.0.2
		*/
		void setEdgeColor(zColor col, bool setVertexColor = false);

		/*! \brief This method sets edge color of all the edges with the input color contatiner.
		*
		*	\param		[in]	col				- input color  contatiner. The size of the contatiner should be equal to number of half edges in the mesh.
		*	\param		[in]	setVertexColor	- vertex color is computed based on the edge color if true.
		*	\since version 0.0.2
		*/
		void setEdgeColors(vector<zColor>& col, bool setVertexColor);

		/*! \brief This method sets edge weight of of the input edge and its symmetry edge to the input weight.
		*
		*	\param		[in]	index					- input edge index.
		*	\param		[in]	wt						- input wight.
		*	\since version 0.0.2
		*/
		void setEdgeWeight(int index, double wt);

		/*! \brief This method sets edge weights of all the edges with the input weight contatiner.
		*
		*	\param		[in]	wt				- input weight  contatiner. The size of the contatiner should be equal to number of half edges in the mesh.
		*	\since version 0.0.2
		*/
		void setEdgeWeights(vector<double>& wt);
		
		//--------------------------
		//--- GET METHODS 
		//--------------------------				

		/*! \brief This method gets vertex positions of all the vertices.
		*
		*	\param		[out]	pos				- positions  contatiner.
		*	\since version 0.0.2
		*/
		void getVertexPositions(vector<zVector>& pos);

		/*! \brief This method gets pointer to the internal vertex positions container.
		*
		*	\return				zVector*					- pointer to internal vertex position container.
		*	\since version 0.0.2
		*/
		zVector* getRawVertexPositions();

		/*! \brief This method gets vertex positions of all the vertices.
		*
		*	\param		[out]	norm				- normals  contatiner.
		*	\since version 0.0.2
		*/
		void getVertexNormals(vector<zVector>& norm);

		/*! \brief This method gets pointer to the internal vertex normal container.
		*
		*	\return				zVector*					- pointer to internal vertex normal container.
		*	\since version 0.0.2
		*/
		zVector* getRawVertexNormals();

		/*! \brief This method gets vertex color of all the vertices.
		*
		*	\param		[out]	col				- color  contatiner. 
		*	\since version 0.0.2
		*/
		void getVertexColors(vector<zColor>& col);

		/*! \brief This method gets pointer to the internal vertex color container.
		*
		*	\return				zColor*					- pointer to internal vertex color container.
		*	\since version 0.0.2
		*/
		zColor* getRawVertexColors();

		/*! \brief This method gets edge color of all the edges.
		*
		*	\param		[out]	col				- color  contatiner.
		*	\since version 0.0.2
		*/
		void getEdgeColors(vector<zColor>& col);

		/*! \brief This method gets pointer to the internal edge color container.
		*
		*	\return				zColor*					- pointer to internal edge color container.
		*	\since version 0.0.2
		*/
		zColor* getRawEdgeColors();

		/*! \brief This method gets face normals of all the faces.
		*
		*	\param		[out]	norm			- normals  contatiner.
		*	\since version 0.0.2
		*/
		void getFaceNormals(vector<zVector>& norm);

		/*! \brief This method gets pointer to the internal face normal container.
		*
		*	\return				zVector*					- pointer to internal face normal container.
		*	\since version 0.0.2
		*/
		zVector* getRawFaceNormals();

		/*! \brief This method gets face color of all the faces.
		*
		*	\param		[out]	col				- color  contatiner.
		*	\since version 0.0.2
		*/
		void getFaceColors(vector<zColor>& col);

		/*! \brief This method gets pointer to the internal face color container.
		*
		*	\return				zColor*					- pointer to internal face color container.
		*	\since version 0.0.2
		*/
		zColor* getRawFaceColors();

		/*! \brief This method computes the center the mesh.
		*
		*	\return		zVector					- center .
		*	\since version 0.0.2
		*/
		zVector getCenter();

		/*! \brief This method computes the centers of a all edges or faces of the mesh.
		*
		*	\param		[in]	type					- zEdgeData or zFaceData.
		*	\param		[out]	centers					- vector of centers of type zVector.
		*	\since version 0.0.2
		*/
		void getCenters(zHEData type, vector<zVector> &centers);

		/*! \brief This method returns the dual mesh of the input mesh.
		*
		*	\param		[out]	dualMeshObj				- output dual mesh object.
		*	\param		[out]	inEdge_dualEdge			- container storing the corresponding dual mesh edge per input mesh edge.
		*	\param		[out]	dualEdge_inEdge			- container storing the corresponding input mesh edge per dual mesh edge.
		*	\param		[in]	excludeBoundary			- true if boundary faces are to be ignored.
		*	\param		[in]	rotate90				- true if dual mesh is to be roatated by 90. Generally used for planar mesh for 2D graphic statics application.
		*	\since version 0.0.2
		*/
		void getDualMesh(zObjMesh &dualMeshObj, vector<int> &inEdge_dualEdge, vector<int> &dualEdge_inEdge, bool excludeBoundary, bool keepExistingBoundary = false, bool rotate90 = false);

		/*! \brief This method returns the dual graph of the input mesh.
		*
		*	\param		[out]	dualGraphObj			- output dual graph object.
		*	\param		[out]	inEdge_dualEdge			- container storing the corresponding dual graph edge per input mesh edge.
		*	\param		[out]	dualEdge_inEdge			- container storing the corresponding input mesh edge per dual graph edge.
		*	\param		[in]	excludeBoundary			- true if boundary faces are to be ignored.
		*	\param		[in]	PlanarMesh				- true if input mesh is planar.
		*	\param		[in]	rotate90				- true if dual mesh is to be roatated by 90.
		*	\since version 0.0.2
		*/
		void getDualGraph(zObjGraph &dualGraphObj, vector<int> &inEdge_dualEdge, vector<int> &dualEdge_inEdge, bool excludeBoundary = false, bool PlanarMesh = false, bool rotate90 = false);
		   	
		/*! \brief This method returns the rainflow graph of the input mesh.
		*
		*	\param		[out]	rainflowGraphObj		- output rainflow graph object.
		*	\param		[in]	excludeBoundary			- true if boundary vertices are to be ignored.
		*	\since version 0.0.2
		*/
		void getRainflowGraph(zObjGraph &rainflowGraphObj, bool excludeBoundary = false);


		/*! \brief This method computes the triangles of each face of the input mesh and stored in 2 dimensional container.
		*
		*	\param		[out]	faceTris		- container of index array of each triangle associated per face.
		*	\since version 0.0.2
		*/
		void getMeshTriangles(vector<vector<int>> &faceTris);

		/*! \brief This method computes the volume of the input mesh.
		*
		*	\return				double			- volume of input mesh.
		*	\since version 0.0.2
		*/
		double getMeshVolume();

		/*! \brief This method computes the volume of the polyhedras formed by the face vertices and the face center for each face of the mesh.
		*
		*	\param		[in]	faceTris		- container of index array of each triangle associated per face.  It will be computed if the container is empty.
		*	\param		[in]	fCenters		- container of centers associated per face.  It will be computed if the container is empty.
		*	\param		[out]	faceVolumes		- container of volumes of the polyhedras formed by the face vertices and the face center per face.
		*	\param		[in]	absoluteVolumes	- will make all the volume values positive if true.
		*	\since version 0.0.2
		*/
		void getMeshFaceVolumes(vector<vector<int>> &faceTris, vector<zVector> &fCenters, vector<double> &faceVolumes, bool absoluteVolumes = true);

		/*! \brief This method computes the principal curvatures of the mesh vertices.
		*
		*	\param		[out]	vertexCurvature		- container of vertex curvature.
		*	\since version 0.0.2
		*/
		void getPrincipalCurvatures(vector<zCurvature> &vertexCurvatures);

		/*! \brief This method computes the gaussian curvature of the mesh vertices.
		*
		*	\param		[out]	vertexCurvature		- container of vertex curvature.
		*	\since version 0.0.2
		*/
		void getGaussianCurvature(vector<double> &vertexCurvatures);

		/*! \brief This method computes the dihedral angle per edge of mesh.
		*
		*	\param		[out]	dihedralAngles		- vector of edge dihedralAngles.
		*	\since version 0.0.2
		*/
		void getEdgeDihedralAngles(vector<double> &dihedralAngles);

		/*! \brief This method computes the lengths of all the half edges of a the mesh.
		*
		*	\param		[out]	halfEdgeLengths				- vector of halfedge lengths.
		*	\return				double						- total edge lengths.
		*	\since version 0.0.2
		*/
		double getHalfEdgeLengths(vector<double> &halfEdgeLengths);

		/*! \brief This method computes the lengths of all the  edges of a the mesh.
		*
		*	\param		[out]	EdgeLengths		- vector of edge lengths.
		*	\return				double				- total edge lengths.
		*	\since version 0.0.2
		*/
		double getEdgeLengths(vector<double> &edgeLengths);		

		/*! \brief This method computes the area around every vertex of a mesh based on face centers.
		*
		*	\param		[in]	inMesh			- input mesh.
		*	\param		[in]	faceCenters		- vector of face centers of type zVector.
		*	\param		[in]	edgeCenters		- vector of edge centers of type zVector.
		*	\param		[out]	vertexAreas		- vector of vertex Areas.
		*	\return				double			- total area of the mesh.
		*	\since version 0.0.2
		*/
		double getVertexAreas(vector<zVector> &faceCenters, vector<zVector> &edgeCenters, vector<double> &vertexAreas);

		/*! \brief This method computes the area of every face of the mesh. It works only for if the faces are planar.
		*
		*	\details	Based on http://geomalgorithms.com/a01-_area.html.
		*	\param		[out]	faceAreas		- vector of vertex Areas.
		*	\return				double			- total area of the mesh.
		*	\since version 0.0.2
		*/
		double getPlanarFaceAreas(vector<double> &faceAreas);		

		/*! \brief This method stores mesh face connectivity information in the input containers
		*
		*	\param		[out]	polyConnects	- stores list of polygon connection with vertex ids for each face.
		*	\param		[out]	polyCounts		- stores number of vertices per polygon.
		*	\since version 0.0.2
		*/
		void getPolygonData(vector<int>(&polyConnects), vector<int>(&polyCounts));

		/*! \brief This method stores mesh edge connectivity information in the input containers
		*
		*	\param		[out]	edgeConnects	- stores list of esdge connection with vertex ids for each edge.
		*	\since version 0.0.2
		*/
		void getEdgeData(vector<int> &edgeConnects);

		/*! \brief This method creates a duplicate of the mesh.
		*
		*	\param		[out]	out			- duplicate mesh object.
		*	\since version 0.0.2
		*/
		void getDuplicate(zObjMesh &out);

		/*! \brief This method gets VBO vertex index of the mesh.
		*
		*	\return				int			- VBO Vertex Index.
		*	\since version 0.0.2
		*/
		int getVBOVertexIndex();
		
		/*! \brief This method gets VBO edge index of the mesh.
		*
		*	\return				int			- VBO Edge Index.
		*	\since version 0.0.2
		*/
		int getVBOEdgeIndex();

		/*! \brief This method gets VBO edge index of the mesh.
		*
		*	\return				int			- VBO Face Index.
		*	\since version 0.0.2
		*/
		int getVBOFaceIndex();

		/*! \brief This method gets VBO vertex color index of the mesh.
		*
		*	\return				int			- VBO Vertex Color Index.
		*	\since version 0.0.2
		*/
		int getVBOVertexColorIndex();

		//--------------------------
		//---- TRI-MESH MODIFIER METHODS
		//--------------------------		

		/*! \brief This method triangulates the input face of the mesh.
		*
		*	\param		[in]	faceIndex		- face index  of the face to be triangulated in the faces container.
		*	\since version 0.0.2
		*/
		void faceTriangulate(zItMeshFace &face);

		/*! \brief This method triangulates the input mesh.
		*
		*	\since version 0.0.2
		*/
		void triangulate();

		//--------------------------
		//---- DELETE MODIFIER METHODS
		//--------------------------
	
		/*! \brief This method deletes the mesh vertex given by the input vertex index.
		*
		*	\param		[in]	index					- index of the vertex to be removed.
		*	\param		[in]	removeInactiveElems	- inactive elements in the list would be removed if true.
		*	\since version 0.0.2
		*/
		void deleteVertex(int index, bool removeInactiveElems = true);

		/*! \brief This method deletes the mesh face given by the input face index.
		*
		*	\param		[in]	index					- index of the face to be removed.
		*	\param		[in]	removeInactiveElems	- inactive elements in the list would be removed if true.
		*	\since version 0.0.2
		*/
		void deleteFace(int index, bool removeInactiveElems = true);

		/*! \brief This method deletes the mesh edge given by the input face index.
		*
		*	\param		[in]	index					- index of the edge to be removed.
		*	\param		[in]	removeInactiveElements	- inactive elements in the list would be removed if true.
		*	\since version 0.0.2
		*/
		void deleteEdge( int index, bool removeInactiveElements = true);

		//--------------------------
		//---- TOPOLOGY MODIFIER METHODS
		//--------------------------

		/*! \brief This method collapses an edge into a vertex.
		*
		*	\param		[in]	index					- index of the edge to be collapsed.
		*	\param		[in]	edgeFactor				- position factor of the remaining vertex after collapse on the original egde. Needs to be between 0.0 and 1.0.
		*	\param		[in]	removeInactiveElems	- inactive elements in the list would be removed if true.
		*	\since version 0.0.2
		*/
		void collapseEdge(int index, double edgeFactor = 0.5, bool removeInactiveElems = true);

		/*! \brief This method splits an edge and inserts a vertex along the edge at the input factor.
		*
		*	\param		[in]	edge			- iterator of edge to be split.
		*	\param		[in]	edgeFactor		- factor in the range [0,1] that represent how far along each edge must the split be done.
		*	\return				zItMeshVertex	- iterator to new vertex added after splitting the edge.
		*	\since version 0.0.2
		*/
		zItMeshVertex splitEdge(zItMeshEdge &edge, double edgeFactor = 0.5);

		/*! \brief This method detaches an edge.
		*
		*	\param		[in]	index			- index of the edge to be split.
		*	\since version 0.0.2
		*/
		int detachEdge(int index);

		/*! \brief This method flips the edge shared bettwen two rainglua faces.
		*
		*	\param		[in]	edgeList	- indicies of the edges to be collapsed.
		*	\since version 0.0.2
		*/
		void flipTriangleEdge(int &index);

		/*! \brief This method splits a set of edges and faces of a mesh in a continuous manner.
		*
		*	\param		[in]	edgeList		- indicies of the edges to be split.
		*	\param		[in]	edgeFactor		- array of factors in the range [0,1] that represent how far along each edge must the split be done. This array must have the same number of elements as the edgeList array.
		*	\since version 0.0.2
		*/
		void splitFaces(vector<int> &edgeList, vector<double> &edgeFactor);

		/*! \brief This method subdivides all the faces and edges of the mesh.
		*
		*	\param		[in]	numDivisions	- number of subdivision to be done on the mesh.
		*	\since version 0.0.2
		*/
		void subdivideMesh(int numDivisions);

		/*! \brief This method applies Catmull-Clark subdivision to the mesh.
		*
		*	\details Based on https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface and https://rosettacode.org/wiki/Catmull%E2%80%93Clark_subdivision_surface.
		*	\param		[in]	numDivisions	- number of subdivision to be done on the mesh.
		*	\param		[in]	smoothCorner	- corner vertex( only 2 Connected Edges) is also smothed if true.
		*	\since version 0.0.2
		*/
		void smoothMesh(int numDivisions = 1, bool smoothCorner = false);

		/*! \brief This method returns an extruded mesh from the input mesh.
		*
		*	\param		[in]	extrudeThickness	- extrusion thickness.
		*	\param		[in]	thicknessTris		- true if the cap needs to be triangulated.
		*	\retrun				zMesh				- extruded mesh.
		*	\since version 0.0.2
		*/
		zObjMesh extrudeMesh(float extrudeThickness, bool thicknessTris = false);
			   		 	  	  		
		//--------------------------
		//---- TRANSFORM METHODS OVERRIDES
		//--------------------------
		
		void setTransform(zTransform &inTransform, bool decompose = true, bool updatePositions = true) override;
				
		void setScale(double3 &scale) override;
				
		void setRotation(double3 &rotation, bool appendRotations = false) override;
		
		void setTranslation(zVector &translation, bool appendTranslations = false) override;
		
		void setPivot(zVector &pivot) override;

		void getTransform(zTransform &transform) override;

	protected:

		//--------------------------
		//---- TRANSFORM  METHODS
		//--------------------------
		void transformObject(zTransform &transform) override;

		//--------------------------
		//---- FACTORY METHODS
		//--------------------------

		/*! \brief This method exports zMesh as an OBJ file.
		*
		*	\param [in]		outfilename			- output file name including the directory path and extension.
		*	\since version 0.0.2
		*/
		void toOBJ(string outfilename);

		/*! \brief This method exports zMesh to a JSON file format using JSON Modern Library.
		*
		*	\param [in]		outfilename			- output file name including the directory path and extension.
		*	\since version 0.0.2
		*/
		void toJSON(string outfilename);

		/*! \brief This method imports zMesh from an OBJ file.
		*
		*	\param	[in]		infilename			- input file name including the directory path and extension.
		*	\return 			bool				- true if the file was read succesfully.
		*	\since version 0.0.2
		*/
		bool fromOBJ(string infilename);

		/*! \brief This method imports zMesh from a JSON file format using JSON Modern Library.
		*
		*	\param [in]		infilename			- input file name including the directory path and extension.
		*	\return 		bool			- true if the file was read succesfully.
		*	\since version 0.0.2
		*/
		bool fromJSON(string infilename);

	private:
			
		//--------------------------
		//---- PRIVATE METHODS
		//--------------------------

		/*! \brief This method sets the edge and face vertex position conatiners for static meshes.
		*
		*	\since version 0.0.2
		*/
		void setStaticContainers();

		//--------------------------
		//---- DEACTIVATE AND REMOVE METHODS
		//--------------------------

		/*! \brief This method adds input half edge and corresponding symmety edge from the halfEdgesMap.
		*
		*	\param		[in]	zItMeshHalfEdge			- half edge iterator.
		*	\since version 0.0.2
		*/
		void addToHalfEdgesMap(zItMeshHalfEdge &he);

		/*! \brief This method removes input half edge and corresponding symmety edge from the halfEdgesMap.
		*
		*	\param		[in]	zItMeshHalfEdge			- half edge iterator.
		*	\since version 0.0.2
		*/
		void removeFromHalfEdgesMap(zItMeshHalfEdge &he);

		/*! \brief This method removes inactive elements from the container connected with the input type.
		*
		*	\param		[in]	type			- zVertexData or zHalfEdgeData or zEdgeData or zFaceData.
		*	\since version 0.0.2
		*/
		void removeInactive(zHEData type);

	};



}


#if defined(ZSPACE_STATIC_LIBRARY)  || defined(ZSPACE_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zInterface/functionsets/zFnMesh.cpp>
#endif

#endif