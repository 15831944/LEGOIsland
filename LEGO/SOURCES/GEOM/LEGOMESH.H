#ifndef __LEGOMESH_H
#define __LEGOMESH_H

#include "LegoTypes.h"
#include "LegoColor.h"
#include "LegoVertex.h"
#include "LegoFace.h"
#include "LegoTextureVertex.h"

class LegoStorage;
class LegoTexture;

class LegoMesh {
public:
    enum {
        e_flat,
        e_gouraud,
    };

    LegoMesh();
    virtual ~LegoMesh();
    LegoColor GetColor() { return m_color; }
    void SetColor(LegoColor p_color) { m_color = p_color; }
    LegoU8 GetShading() { return m_shading; }
    void SetShading(LegoU8 p_shading) { m_shading = p_shading; }
    LegoU32 GetNumVertices() { return m_numVertices; }
    void SetNumVertices(LegoU32 p_numVertices) { m_numVertices = p_numVertices; }
    LegoVertex* GetVertices() { return m_vertices; }
    void SetVertices(LegoVertex* p_vertices) { m_vertices = p_vertices; }
    LegoVertex& GetVertex(LegoU32 p_i) { return m_vertices[p_i]; }
    void SetVertex(LegoU32 p_i, LegoVertex& p_vertex) { m_vertices[p_i] = p_vertex; }
    LegoU32 GetNumFaces() { return m_numFaces; }
    void SetNumFaces(LegoU32 p_numFaces) { m_numFaces = p_numFaces; }
    LegoFace* GetFaces() { return m_faces; }
    void SetFaces(LegoFace* p_faces) { m_faces = p_faces; }
    LegoFace& GetFace(LegoU32 p_i) { return m_faces[p_i]; }
    void SetFace(LegoU32 p_i, LegoFace& p_face) { m_faces[p_i] = p_face; }
    LegoU32 GetNumTextureVertices() { return m_numTextureVertices; }
    void SetNumTextureVertices(LegoU32 p_numTextureVertices) { m_numTextureVertices = p_numTextureVertices; }
    LegoTextureVertex* GetTextureVertices() { return m_textureVertices; }
    void SetTextureVertices(LegoTextureVertex* p_textureVertices) { m_textureVertices = p_textureVertices; }
    LegoTextureVertex& GetTextureVertex(LegoU32 p_i) { return m_textureVertices[p_i]; }
    void SetTextureVertex(LegoU32 p_i, LegoTextureVertex& p_textureVertex) { m_textureVertices[p_i] = p_textureVertex; }
    LegoTexture* GetTexture() { return m_texture; }
    void SetTexture(LegoTexture* p_texture) { m_texture = p_texture; }
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
protected:
    LegoColor m_color;
    LegoU8 m_shading;
    LegoU32 m_numVertices;
    LegoVertex* m_vertices;
    LegoU32 m_numFaces;
    LegoFace* m_faces;
    LegoU32 m_numTextureVertices;
    LegoTextureVertex* m_textureVertices;
    LegoTexture* m_texture;
};


#endif // __LEGOMESH_H

