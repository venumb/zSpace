// This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
// data analysis & visualization framework.
//
// Copyright (C) 2019 ZSPACE 
// 
// This Source Code Form is subject to the terms of the MIT License 
// If a copy of the MIT License was not distributed with this file, You can 
// obtain one at https://opensource.org/licenses/MIT.
//
// Author : Vishu Bhooshan <vishu.bhooshan@zaha-hadid.com>, Leo Bieling <leo.bieling@zaha-hadid.com>
//

#ifndef ZSPACE_TS_GEOMETRY_MESH_IMAGE_H
#define ZSPACE_TS_GEOMETRY_MESH_IMAGE_H

#pragma once

#include <headers/zInterface/functionsets/zFnMesh.h>

#include<headers/zCore/utilities/zUtilsBMP.h>


namespace zSpace
{

	/** \addtogroup zToolsets
	*	\brief Collection of toolsets for applications.
	*  @{
	*/

	/** \addtogroup zTsGeometry
	*	\brief tool sets for geometry related utilities.
	*  @{
	*/

	/*! \class zTsMeshImage
	*	\brief A function set for images holden mesh connectivity data.
	*	\since version 0.0.4
	*/

	/** @}*/

	/** @}*/

	class ZSPACE_TOOLS zTsMeshImage
	{
	protected:
		//--------------------------
		//---- PROTECTED ATTRIBUTES
		//--------------------------

		/*!	\brief core utilities Object  */
		zUtilsCore coreUtils;

		/*!	\brief pointer to form Object  */
		zObjMesh *meshObj;

	public:
		//--------------------------
		//---- PUBLIC ATTRIBUTES
		//--------------------------

		/*!	\brief form function set  */
		zFnMesh fnMesh;

		//--------------------------
		//---- CONSTRUCTOR
		//--------------------------

		/*! \brief Default constructor.
		*
		*	\since version 0.0.4
		*/
		zTsMeshImage();

		/*! \brief Overloaded constructor.
		*
		*	\param		[in]	_meshObj			- input mesh object.
		*	\since version 0.0.4
		*/
		zTsMeshImage(zObjMesh &_meshObj);

		//--------------------------
		//---- DESTRUCTOR
		//--------------------------

		/*! \brief Default destructor.
		*
		*	\since version 0.0.4
		*/
		~zTsMeshImage();

		/*! \brief This method writes an image to the defined path representing the mesh connecticity.
		*
		
		*	\param		[in]	path						- path to write the image file to.
		*	\param		[in]	connectivityType			- connectivity type (zVertexVertex, zVertexEdge, zFacexVertex, zFaceEdge)
		*	\since version 0.0.4
		*/
		void toBMP(string path, zConnectivityType connectivityType);

		/*! \brief This method writes an image to the defined path with additional vertex data from a vector.
		*
		
		*	\param		[in]	path						- path to write the image file to.
		*	\param		[in]	connectivityType			- connectivity type (zVertexVertex, zVertexEdge, zFacexVertex, zFaceEdge)
		*	\since version 0.0.4
		*/
		void toBMP(string path, vector<double> vertexData);
	};
}

#if defined(ZSPACE_STATIC_LIBRARY)  || defined(ZSPACE_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zToolsets/geometry/zTsMeshImage.cpp>
#endif

#endif