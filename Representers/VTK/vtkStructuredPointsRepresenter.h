/*
 * This file is part of the statismo library.
 *
 * Author: Marcel Luethi (marcel.luethi@unibas.ch)
 *
 * Copyright (c) 2011 University of Basel
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */



#ifndef VTKSTRUCTUREDPOINTSREPRESENTER_H_
#define VTKSTRUCTUREDPOINTSREPRESENTER_H_


#include "vtkStructuredPoints.h"
#include "vtkPoint.h"
#include "vtkPixel.h"
#include "statismo/CommonTypes.h"
#include "vtkSmartPointer.h"

#include <H5Cpp.h>

/**
 * \brief Representer class for vtkStructuredPoints of arbitrary scalar type and dimension
 */



template <class TPixel, unsigned TDimensions>
class vtkStructuredPointsRepresenter  {
public:



	typedef vtkStructuredPoints DatasetType;
	typedef vtkStructuredPoints* DatasetPointerType;
	typedef const vtkStructuredPoints* DatasetConstPointerType;

	//typedef double* PointType;
	typedef vtkPoint PointType;

	typedef vtkNDPixel<TPixel, TDimensions> ValueType;

	static vtkStructuredPointsRepresenter* Create(DatasetConstPointerType reference) { return new vtkStructuredPointsRepresenter(reference); }
	static vtkStructuredPointsRepresenter* Create(const std::string referenceFilename) { return new vtkStructuredPointsRepresenter(referenceFilename); }
	static vtkStructuredPointsRepresenter* Load(const H5::CommonFG& fg);
	vtkStructuredPointsRepresenter* Clone() const;


	virtual ~vtkStructuredPointsRepresenter();
	void Delete() const { delete this; }



	static unsigned GetDimensions() { return  TDimensions; }
	static std::string GetName() { return "vtkStructuredPointsRepresenter"; }

	const vtkStructuredPoints* GetReference() const { return m_reference; }


	statismo::VectorType DatasetToSampleVector(DatasetConstPointerType ds) const;
	DatasetPointerType SampleVectorToSample(const statismo::VectorType& sample) const;
	ValueType PointSampleToValue(const statismo::VectorType& pointSample) const;
	statismo::VectorType ValueToPointSample(const ValueType& v) const;
	unsigned GetPointIdForPoint(const PointType& pt) const;

	unsigned GetNumberOfPoints() const;
	void Save(const H5::CommonFG& fg) const;


    static DatasetPointerType ReadDataset(const std::string& filename);
	static void WriteDataset(const std::string& filename, DatasetConstPointerType sp);
	static DatasetPointerType  NewDataset();
	static void DeleteDataset(DatasetPointerType  d);
    static unsigned GetNumberOfPoints(DatasetPointerType  reference);

	 /* Maps a (Pointid,component) tuple to a component of the internal matrix.
	 * This is used to locate the place in the matrix to store the elements for a given point.
	 * @params ptId The point id
	 * @params the Component Index (range 0, Dimensionality)
	 * @returns an index.
	 */
	static unsigned MapPointIdToInternalIdx(unsigned ptId, unsigned componentInd) {
		return ptId * GetDimensions() + componentInd;
	}

private:

	vtkStructuredPointsRepresenter(DatasetConstPointerType reference);
	vtkStructuredPointsRepresenter(const std::string& referenceFilename);

	DatasetType* m_reference;
};

#include "vtkStructuredPointsRepresenter.txx"

#endif /* VTKSTRUCTUREDPOINTSREPRESENTER_H_ */
