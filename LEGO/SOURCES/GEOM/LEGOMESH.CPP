#include "LegoMesh.h"
#include "LegoVertex.h"
#include "LegoFace.h"
#include "LegoTexture.h"
#include "LegoStorage.h"

LegoMesh::LegoMesh()
{
    m_shading = e_flat;
    m_numVertices = 0;
    m_vertices = NULL;
    m_numFaces = 0;
    m_faces = NULL;
    m_numTextureVertices = 0;
    m_textureVertices = NULL;
    m_texture = NULL;
}

LegoMesh::~LegoMesh()
{
    if (m_vertices) {
        delete [] m_vertices;
    }
    if (m_faces) {
        delete [] m_faces;
    }
    if (m_textureVertices) {
        delete [] m_textureVertices;
    }
    if (m_texture) {
        delete m_texture;
    }
}

LegoResult 
LegoMesh::Read(LegoStorage* p_storage)
{
    LegoU32 i;
    LegoResult result;
    if ((result = m_color.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_shading, sizeof(m_shading))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_numVertices, sizeof(m_numVertices))) != SUCCESS) {
        return result;
    }
    if (m_vertices) {
        delete [] m_vertices;
    }
    m_vertices = new LegoVertex[m_numVertices];
    for (i = 0; i < m_numVertices; i++) {
        if ((result = m_vertices[i].Read(p_storage)) != SUCCESS) {
            return result;
        }
    }
    if ((result = p_storage->Read(&m_numFaces, sizeof(m_numFaces))) != SUCCESS) {
        return result;
    }
    if (m_faces) {
        delete [] m_faces;
    }
    m_faces = new LegoFace[m_numFaces];
    for (i = 0; i < m_numFaces; i++) {
        if ((result = m_faces[i].Read(p_storage)) != SUCCESS) {
            return result;
        }
    }
    if ((result = p_storage->Read(&m_numTextureVertices, sizeof(m_numTextureVertices))) != SUCCESS) {
        return result;
    }
    if (m_textureVertices) {
        delete [] m_textureVertices;
        m_textureVertices = NULL;
    }
    if (m_numTextureVertices) {
        m_textureVertices = new LegoTextureVertex[m_numTextureVertices];
        for (i = 0; i < m_numTextureVertices; i++) {
            if ((result = m_textureVertices[i].Read(p_storage)) != SUCCESS) {
                return result;
            }
        }
    }
    LegoBool hasTexture;
    if ((result = p_storage->Read(&hasTexture, sizeof(hasTexture))) != SUCCESS) {
        return result;
    }
    if (hasTexture) {
        m_texture = new LegoTexture();
        if ((result = m_texture->Read(p_storage)) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoResult 
LegoMesh::Write(LegoStorage* p_storage)
{
    LegoU32 i;
    LegoResult result;
    if ((result = m_color.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_shading, sizeof(m_shading))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_numVertices, sizeof(m_numVertices))) != SUCCESS) {
        return result;
    }
    for (i = 0; i < m_numVertices; i++) {
        if ((result = m_vertices[i].Write(p_storage)) != SUCCESS) {
            return result;
        }
    }
    if ((result = p_storage->Write(&m_numFaces, sizeof(m_numFaces))) != SUCCESS) {
        return result;
    }
    for (i = 0; i < m_numFaces; i++) {
        if ((result = m_faces[i].Write(p_storage)) != SUCCESS) {
            return result;
        }
    }
    if ((result = p_storage->Write(&m_numTextureVertices, sizeof(m_numTextureVertices))) != SUCCESS) {
        return result;
    }
    for (i = 0; i < m_numTextureVertices; i++) {
        if ((result = m_textureVertices[i].Write(p_storage)) != SUCCESS) {
            return result;
        }
    }
    LegoBool hasTexture = m_texture != NULL;
    if ((result = p_storage->Write(&hasTexture, sizeof(hasTexture))) != SUCCESS) {
        return result;
    }
    if (hasTexture) {
        if ((result = m_texture->Write(p_storage)) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}


