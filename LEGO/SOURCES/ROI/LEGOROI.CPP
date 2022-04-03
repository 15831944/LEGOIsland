#include <stdio.h>
#include "LegoRoi.h"
#include "LegoStorage.h"
#include "LegoMesh.h"
#include "LegoAnim.h"
#include "LegoMatrix.h"
#include "LegoSphere.h"
#include "LegoTexture.h"
#include "LegoImage.h"
#include "LegoUtil.h"
#include "tgl.h"
#include "vec.h"
#include "float.h"  // FLT_EPSILON

//???
#if 0
extern void AfxTrace(const char*, ...);
#define TRACEX AfxTrace
#else
void foo(const char*, ...) {}
#define TRACEX foo
#endif

#ifdef USE_SMART_HEAP
#include "smrtheap.hpp"
#endif // USE_SMART_HEAP

using namespace Tgl;
using namespace std;

#pragma warning(disable: 4244)

LegoResult 
LegoCostInfo::Read(LegoStorage* p_storage)
{
    if (p_storage->Read(&m_pixelsCovered, sizeof(m_pixelsCovered)) != SUCCESS) {
        return FAILURE;
    }
    if (p_storage->Read(&m_cost, sizeof(m_cost)) != SUCCESS) {
        return FAILURE;
    }
    return SUCCESS;
}

LegoResult 
LegoCostInfo::Write(LegoStorage* p_storage)
{
    if (p_storage->Write(&m_pixelsCovered, sizeof(m_pixelsCovered)) != SUCCESS) {
        return FAILURE;
    }
    if (p_storage->Write(&m_cost, sizeof(m_cost)) != SUCCESS) {
        return FAILURE;
    }
    return SUCCESS;
}

LegoLOD::LegoLOD(Tgl::Renderer* p_renderer)
    : 
    ViewLOD(p_renderer)
{
    m_numMeshes = 0;
    m_meshes = NULL;
    m_numVertices = 0;
    m_averagePolyArea = 0.0;
    m_numCosts = 0;
    m_costs = NULL;
}

LegoLOD::~LegoLOD()
{
    if (m_meshes) {
        for (LegoU32 i = 0; i < m_numMeshes; i++) {
            delete m_meshes[i];
        }
        delete [] m_meshes;
    }
    if (m_costs) {
        delete [] m_costs;
    }
}

double 
LegoLOD::Cost(double p_pixelsCovered) const
{
	/*
    double cost;
    if (m_numCosts == 0) {
        cost = ViewLOD::Cost(p_pixelsCovered);
    }
    else if (m_numCosts == 1) {
        cost = m_costs[0].GetCost();
    }
    else {
        for (LegoU32 i = 0; i < m_numCosts && p_pixelsCovered > m_costs[i].GetPixelsCovered(); i++);
        if (i == 0) {
            cost = m_costs[0].GetCost();
        }
        else if (i >= m_numCosts) {
            cost = m_costs[m_numCosts - 1].GetCost();
        }
        else {
            cost = m_costs[i - 1].GetCost() + (p_pixelsCovered - m_costs[i - 1].GetPixelsCovered()) / (m_costs[i].GetPixelsCovered() - m_costs[i - 1].GetPixelsCovered()) * (m_costs[i].GetCost() - m_costs[i - 1].GetCost());
        }
    }
    return cost;
	*/
	return  p_pixelsCovered/(640*480)/10 + m_numVertices *.03/80;
}

LegoResult 
LegoLOD::Read(Tgl::Renderer* p_renderer, LegoStorage* p_storage, LegoBool p_writable)
{
    LegoResult result = FAILURE;
    Result tglResult;
    LegoU32 i, j;
    Mesh* tglMesh;
    Texture* tglTexture;
    float (*vertices)[3] = NULL;
    LegoBool verticesAllocated = FALSE;
    float (*textureVertices)[2] = NULL;
    LegoBool textureVerticesAllocated = FALSE;
    LegoU32* faces = NULL;
    PaletteEntry paletteEntries[256];
    ShadingModel shadingModel;

    if (p_storage->Read(&m_numVertices, sizeof(m_numVertices)) != SUCCESS) {
        goto done;
    }
    if (p_storage->Read(&m_averagePolyArea, sizeof(m_averagePolyArea)) != SUCCESS) {
        goto done;
    }
    if (p_storage->Read(&m_numCosts, sizeof(m_numCosts)) != SUCCESS) {
        goto done;
    }
    if (m_numCosts) {
        m_costs = new LegoCostInfo[m_numCosts];
        for (i = 0; i < m_numCosts; i++) {
            if (m_costs[i].Read(p_storage) != SUCCESS) {
                goto done;
            }
        }
    }
    if (p_storage->Read(&m_numMeshes, sizeof(m_numMeshes)) != SUCCESS) {
        goto done;
    }
    assert(m_meshGroup);
    m_meshes = new LegoMesh*[m_numMeshes];
    memset(m_meshes, 0, m_numMeshes * sizeof(LegoMesh*));
    for (i = 0; i < m_numMeshes; i++) {
        m_meshes[i] = new LegoMesh();
        if (m_meshes[i]->Read(p_storage) != SUCCESS) {
            goto done;
        }
        m_numPolys += m_meshes[i]->GetNumFaces();
        if (0) {
            // ??? ensure m_meshes[i]->GetVertices() really are array of 3 floats
            vertices = (float(*)[3]) m_meshes[i]->GetVertices();
            verticesAllocated = FALSE;
        }
        else {
            vertices = new float[m_meshes[i]->GetNumVertices()][3];
            verticesAllocated = TRUE;
            {
                LegoVertex* src = m_meshes[i]->GetVertices();
                float (*dst)[3] = vertices;
                LegoU32 n = m_meshes[i]->GetNumVertices();
                while (n--) {
                    (*dst)[0] = src->GetX();
                    (*dst)[1] = src->GetY();
                    (*dst)[2] = src->GetZ();
                    src++;
                    dst++;
                }
            }
        }
        faces = new LegoU32[m_meshes[i]->GetNumFaces() * 3];
        {
            LegoFace* src = m_meshes[i]->GetFaces();
            LegoU32* dst = faces;
            LegoU32 n = m_meshes[i]->GetNumFaces();
            while (n--) {
                *dst++ = src->GetVertexIndex(0);
                *dst++ = src->GetVertexIndex(1);
                *dst++ = src->GetVertexIndex(2);
                src++;
            }
        }
        if (m_meshes[i]->GetNumTextureVertices()) {
            if (0) {
                // ??? ensure m_meshes[i]->GetTextureVertices() really are array of 2 floats
                textureVertices = (float (*)[2]) m_meshes[i]->GetTextureVertices();
                textureVerticesAllocated = FALSE;
            }
            else {
                    textureVertices = new float[m_meshes[i]->GetNumTextureVertices()][2];
                    textureVerticesAllocated = TRUE;
                    LegoTextureVertex* src = m_meshes[i]->GetTextureVertices();
                    float (*dst)[2] = textureVertices;
                    LegoU32 n = m_meshes[i]->GetNumTextureVertices();
                    while (n--) {
                        (*dst)[0] = src->GetU();
                        (*dst)[1] = src->GetV();
                        src++;
                        dst++;
                    }
            }
        }
        switch (m_meshes[i]->GetShading())
        {
        case LegoMesh::e_flat:
            shadingModel = Flat;
            break;
        case LegoMesh::e_gouraud:
        default:
            shadingModel = Gouraud;
            break;
        }              
        if (!(tglMesh = p_renderer->CreateMesh(m_meshes[i]->GetNumVertices(), (const float (*)[3])vertices, (const float (*)[2])textureVertices, m_meshes[i]->GetNumFaces(), 3, faces)))
		{
            goto done;
        }
        tglResult = tglMesh->SetColor(
            (double) m_meshes[i]->GetColor().GetRed() / 255.0,
            (double) m_meshes[i]->GetColor().GetGreen() / 255.0,
            (double) m_meshes[i]->GetColor().GetBlue() / 255.0
        );
        assert(Succeeded(tglResult));
        tglResult = tglMesh->SetShadingModel(shadingModel);
        assert(Succeeded(tglResult));
        TRACEX("Shading: %s Color: [% .4f, % .4f, % .4f]\n",
                (const char*) (shadingModel == Flat) ? "Flat" : (shadingModel == Gouraud) ? "Gouraud" : "?",
                (double) m_meshes[i]->GetColor().GetRed() / 255.0,
                (double) m_meshes[i]->GetColor().GetGreen() / 255.0,
                (double) m_meshes[i]->GetColor().GetBlue() / 255.0);
        if (m_meshes[i]->GetTexture()) {
            for (j = 0; j < 256; j++) {
                paletteEntries[j].m_red = m_meshes[i]->GetTexture()->GetImage()->GetPaletteEntry(j).GetRed();
                paletteEntries[j].m_green = m_meshes[i]->GetTexture()->GetImage()->GetPaletteEntry(j).GetGreen();
                paletteEntries[j].m_blue = m_meshes[i]->GetTexture()->GetImage()->GetPaletteEntry(j).GetBlue();
            }
            tglTexture = p_renderer->CreateTexture(
                m_meshes[i]->GetTexture()->GetImage()->GetWidth(),
                m_meshes[i]->GetTexture()->GetImage()->GetHeight(),
                8,
                m_meshes[i]->GetTexture()->GetImage()->GetBits(),
                FALSE,
                256,
                paletteEntries
            );
            if (!tglTexture) {
                goto done;
            }
            tglResult = tglMesh->SetTexture(tglTexture);
            assert(Succeeded(tglResult));
            delete tglTexture;
        }
        tglResult = m_meshGroup->Add(tglMesh);
        assert(Succeeded(tglResult));
        delete tglMesh;
        tglMesh = NULL;
        if (textureVertices && textureVerticesAllocated) {
            delete [] textureVertices;
        }
        textureVertices = NULL;
        delete[] faces; 
        faces = NULL;
        if (vertices && verticesAllocated) {
            delete[] vertices;
        }
        vertices = NULL;
        if (!p_writable) {
            delete m_meshes[i]; 
            m_meshes[i] = NULL;
        }
    }

    result = SUCCESS;

done:
    if (faces) {
        delete[] faces;
    }
    if (vertices && verticesAllocated) {
        delete[] vertices;
    }
    if (textureVertices && textureVerticesAllocated) {
        delete [] textureVertices;
    }
    if (!p_writable) {
        if (m_meshes) {
            for (i = 0; i < m_numMeshes; i++) {
                if (m_meshes[i]) {
                    delete m_meshes[i];
                }
            }
            delete[] m_meshes;
            m_meshes = NULL;
        }
    }
    if (result != SUCCESS) {
        if (tglMesh) {
            delete tglMesh;
        }
    }
    return result;
}

LegoResult 
LegoLOD::Write(LegoStorage* p_storage)
{
    LegoResult result = FAILURE;
    LegoU32 i;

    if (!m_meshes) {
        goto done;
    }
    if (p_storage->Write(&m_numVertices, sizeof(m_numVertices)) != SUCCESS) {
        goto done;
    }
    if (p_storage->Write(&m_averagePolyArea, sizeof(m_averagePolyArea)) != SUCCESS) {
        goto done;
    }
    if (p_storage->Write(&m_numCosts, sizeof(m_numCosts)) != SUCCESS) {
        goto done;
    }
    for (i = 0; i < m_numCosts; i++) {
        if (m_costs[i].Write(p_storage) != SUCCESS) {
            goto done;
        }
    }
    if (p_storage->Write(&m_numMeshes, sizeof(m_numMeshes)) != SUCCESS) {
        goto done;
    }
    for (i = 0; i < m_numMeshes; i++) {
        if (m_meshes[i]->Write(p_storage) != SUCCESS) {
            goto done;
        }
    }

    result = SUCCESS;

done:
    return result;
}

LegoROI::LegoROI(Tgl::Renderer* p_renderer)
	:
	ViewROI(p_renderer, NULL) 
{ 
    m_name = NULL; 
}

LegoROI::LegoROI(Tgl::Renderer* p_renderer, ViewLODList* p_lodList) 
    : 
    ViewROI(p_renderer, p_lodList) 
{ 
    m_name = NULL; 
}


LegoROI::~LegoROI()
{
	if(comp) {
        CompoundObject::iterator iterator;

	    for (iterator = comp->begin(); !(iterator == comp->end()); ++iterator)
        {
            ROI* child = *iterator;

            delete child;
        }

        delete comp;
        comp = 0;
    }
    if (m_name) {
        delete m_name;
    }
}

LegoResult 
LegoROI::Read(Tgl::Renderer* p_renderer, ViewLODListManager* p_viewLODListManager,
              LegoStorage* p_storage, LegoBool p_writable)
{
    LegoResult result = FAILURE;
    LegoU32 i;
    LegoU32 numLODs;
    LegoROI* roi;
    LegoLOD* lod;
    ViewLODList* lodList;
    LegoU32 numROIs;
    LegoU32 length;
	LegoSphere tmp_sphere;

    if (p_storage->Read(&length, sizeof(length)) != SUCCESS) {
        goto done;
    }
    m_name = new LegoChar[length + 1];
    if (p_storage->Read(m_name, length) != SUCCESS) {
        goto done;
    }   
    m_name[length] = '\0';
    if (tmp_sphere.Read(p_storage) != SUCCESS) {
        goto done;
    }
	SET3(m_sphere.Center(), tmp_sphere.GetCenter());
	m_sphere.Radius() = tmp_sphere.GetRadius();
    // bounding_sphere.Center() gets set when local transforms are set 
    world_bounding_sphere.Radius() = m_sphere.Radius();
    if (p_storage->Read(&numLODs, sizeof(numLODs)) != SUCCESS) {
        goto done;
    }
    if (lodList = p_viewLODListManager->Lookup(m_name))
    {
        assert(lodList->Capacity() == numLODs);
        // skip over lods
        for (i = 0; i < numLODs; i++) {
            LegoLOD lod(p_renderer);
            if (lod.Read(p_renderer, p_storage, p_writable) != SUCCESS) {
                goto done;
            }
        }
    }
    else if (lodList = p_viewLODListManager->Create(m_name, numLODs)) {
        for (i = 0; i < numLODs; i++) {
            lod = new LegoLOD(p_renderer);
            if (lod->Read(p_renderer, p_storage, p_writable) != SUCCESS) {
                goto done;
            }
            lodList->PushBack(lod);
        }
    }
    else {
        goto done;
    }
    SetLODList(lodList);
    // NOTE: refCount is 1 when ViewLODListManager::Create() returns
    // SetLODList() increases refCount
    assert((lodList->AddRef(), lodList->Release()) >= 2);
    lodList->Release();
    if (p_storage->Read(&numROIs, sizeof(numROIs)) != SUCCESS) {
        goto done;
    }
	if(numROIs > 0) {
		comp = new CompoundObject;
	}
    for (i = 0; i < numROIs; i++) {
		// Create and initialize a sub-component
		roi = new LegoROI(p_renderer);
		if (roi->Read(p_renderer, p_viewLODListManager, p_storage, p_writable) != SUCCESS) {
			goto done;
		}
		// Add the new sub-component to this ROI's protected list
		comp->push_back(roi);
    }

    result = SUCCESS;

done:
    return result;
}

LegoResult 
LegoROI::Write(LegoStorage* p_storage)
{
    LegoResult result = FAILURE;
    LegoU32 i;
    LegoU32 numLODs;
    LegoROI* roi;
    LegoLOD* lod;
    LegoU32 numROIs;
    LegoU32 length = 0;
    CompoundObject::iterator compoundObjectIterator;
	LegoSphere tmp_sphere;

    if (m_name) {
        length = strlen(m_name);
    }
    if (p_storage->Write(&length, sizeof(length)) != SUCCESS) {
        goto done;
    }
    if (m_name) {
        if (p_storage->Write(m_name, length) != SUCCESS) {
            goto done;
        }   
    }
	SET3(tmp_sphere.GetCenter(), m_sphere.Center());
	tmp_sphere.SetRadius(m_sphere.Radius());
    if (tmp_sphere.Write(p_storage) != SUCCESS) {
        goto done;
    }
    numLODs = GetLODCount();
    if (p_storage->Write(&numLODs, sizeof(numLODs)) != SUCCESS) {
        goto done;
    }
    for (i = 0; i < numLODs; i++) {
        lod = (LegoLOD*) GetLOD(i);
        if (lod->Write(p_storage) != SUCCESS) {
            goto done;
        }
    }
    numROIs = comp ? comp->size() : 0;
    if (p_storage->Write(&numROIs, sizeof(numROIs)) != SUCCESS) {
        goto done;
    }
    if (comp) {
        for (compoundObjectIterator = comp->begin(); compoundObjectIterator != comp->end(); compoundObjectIterator++) {
            roi = (LegoROI*) *compoundObjectIterator;
            if (roi->Write(p_storage) != SUCCESS) {
                goto done;
            }
        }
    }

    result = SUCCESS;

done:
    return result;
}


static void DeleteTransformTreeList(TransformTreeNodeList *nodes)
{
	for(TransformTreeNodeList::iterator ti = nodes->begin(); !(ti == nodes->end()); ++ti)
	{
		TransformTreeNode &kid = *ti;
		if(kid.child_nodes != NULL)
			DeleteTransformTreeList(kid.child_nodes);
	}
	delete nodes;
}

LegoResult
LegoROI::SetFrame(LegoAnim* p_anim, LegoTime p_time)
{
    LegoResult result = FAILURE;
    CompoundObject::iterator iterator;
    LegoU32 i;
    LegoMatrixF4x4 matrix;
    TransformTreeNode* shadowTree;
    LegoTreeNode* animNode = p_anim->GetRoot();
    LegoAnimNodeData* data = (LegoAnimNodeData*) animNode->GetData();
    if (stricmp(m_name, data->GetName()) != 0) {
        goto done;
    }
    CreateLocalTransform(data, p_time, matrix);
	shadowTree = new TransformTreeNode();
	shadowTree->child_index = 0;
	shadowTree->use_this_matrix = FALSE;
	shadowTree->child_nodes = new TransformTreeNodeList;
    SETMAT4(shadowTree->local2parent, matrix);
	if(comp)
		for (
			iterator = comp->begin(), i = 0;
			iterator != comp->end();
			iterator++, i++)
		{
			TransformTreeNode node;
			node.child_index = i;
			node.use_this_matrix = FALSE;
			node.child_nodes = NULL;
			shadowTree->child_nodes->push_back(node);
		}
    for (i = 0; i < animNode->GetNumChildren(); i++) {
        if (CreateLocalTransformTree(animNode->GetChild(i), p_time, shadowTree, matrix)) {
            goto done;
        }
    }
	SetLocalTransformTree(*shadowTree);

    result = SUCCESS;

done:
	if(shadowTree->child_nodes != NULL) {
		DeleteTransformTreeList(shadowTree->child_nodes);
    }
	delete shadowTree;
	return result;
}

LegoResult 
LegoROI::CreateLocalTransformTree(LegoTreeNode* p_animNode, LegoTime p_time, TransformTreeNode* p_shadowTree, LegoMatrixF4x4 p_matrix)
{
    LegoU32 i;
    LegoAnimNodeData* data = (LegoAnimNodeData*) p_animNode->GetData();
    CompoundObject::iterator i1;
    TransformTreeNodeList::iterator i2;
    for (
        i1 = comp->begin(), i2 = p_shadowTree->child_nodes->begin();
        i1 != comp->end();
        i1++, i2++
    ) {
        LegoROI* roi = (LegoROI*) *i1;
        if (stricmp(roi->GetName(), data->GetName()) == 0) {
            break;
        }

    }
    if (i1 == comp->end()) {
        return FAILURE;
    }
    TransformTreeNode node = *i2;
    LegoMatrixF4x4 matrix;
    if (CreateLocalTransform(data, p_time, matrix) != SUCCESS) {
        return FAILURE;
    }
    MXM4d(p_matrix, matrix, p_matrix);
    SETMAT4(node.local2parent, p_matrix);
    node.use_this_matrix = TRUE;
    *i2 = node;
    for (i = 0; i < p_animNode->GetNumChildren(); i++) {
        if (CreateLocalTransformTree(p_animNode->GetChild(i), p_time, p_shadowTree, p_matrix) != SUCCESS) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

LegoResult LegoROI::CreateLocalTransform(LegoAnimNodeData* pAnimNodeData,
                                         LegoTime p_time,
                                         LegoMatrixF4x4& rLocalTransform)
{
    // creates a local transform from animation data

    LegoVectorF3        translation;
    LegoVectorF3        rotationAxis;
    LegoFloat           rotationAngle;
    const LegoVertex&   rPivotPoint = pAnimNodeData->GetPivot();
    LegoVectorF3        scale;

    pAnimNodeData->GetTranslation(p_time, EXPAND3(translation));
    pAnimNodeData->GetRotation(p_time, rotationAngle, EXPAND3(rotationAxis));
    pAnimNodeData->GetScale(p_time, EXPAND3(scale));

    // for now, we don't handle scaling
    assert(fabs(scale[0] - 1.0f) <= (4 * FLT_EPSILON));
    assert(fabs(scale[1] - 1.0f) <= (4 * FLT_EPSILON));
    assert(fabs(scale[2] - 1.0f) <= (4 * FLT_EPSILON));

#if 0
    rLocalTransform.SetTranslation(-rPivotPoint[0], -rPivotPoint[1], -rPivotPoint[2]);
    rLocalTransform.ApplyRotation(rotationAngle, EXPAND3(rotationAxis));
    rLocalTransform.ApplyTranslation(EXPAND3(rPivotPoint));
    rLocalTransform.ApplyScale(EXPAND3(scale));
    rLocalTransform.ApplyTranslation(EXPAND3(translation));
    // ??? apparantely LegoMatrixF4x4 uses column vector
    TRANSPOSE4d(rLocalTransform, rLocalTransform);
#else
#if 0
	// until converter is fixed
	VMV3(translation, translation, rPivotPoint);
#endif
    rLocalTransform.SetTranslation(EXPAND3(translation));
    rLocalTransform.ApplyScale(EXPAND3(scale));
    rLocalTransform.ApplyTranslation(EXPAND3(rPivotPoint));
    rLocalTransform.ApplyRotation(rotationAngle, EXPAND3(rotationAxis));
    rLocalTransform.ApplyTranslation(-rPivotPoint[0], -rPivotPoint[1], -rPivotPoint[2]);
    // ??? apparantely LegoMatrixF4x4 uses column vector
    TRANSPOSE4d(rLocalTransform, rLocalTransform);
#endif

    TRACEX("LegoROI::CreateLocalTransform(): \"%s\"\n", (const char*) m_name);
    TRACEX("   translation = [% .4f, % .4f, % .4f]\n", EXPAND3(translation));
    TRACEX("   rotation    = [% .4f, % .4f, % .4f] % .4f degrees\n", EXPAND3(rotationAxis), (double) rotationAngle);
    TRACEX("   pivot point = [% .4f, % .4f, % .4f]\n", EXPAND3(rPivotPoint));
    TRACEX("   scale       = [% .4f, % .4f, % .4f]\n", EXPAND3(scale));
    TRACEX("   Local Transform =\n");
    TRACEX("                 |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(rLocalTransform[0]));
    TRACEX("                 |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(rLocalTransform[1]));
    TRACEX("                 |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(rLocalTransform[2]));
    TRACEX("                 |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(rLocalTransform[3]));

    return SUCCESS;
}
