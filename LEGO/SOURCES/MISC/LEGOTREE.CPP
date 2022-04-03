#include <string.h>
#include "LegoTree.h"
#include "LegoStorage.h"

LegoTreeNode::LegoTreeNode()
{
    m_data = NULL;
    m_numChildren = 0;
    m_children = NULL;
}

LegoTreeNode::~LegoTreeNode()
{
    if (m_data) {
        delete m_data;
    }
    if (m_children) {
        delete [] m_children;
    }
}

LegoTreeNodeInfo::LegoTreeNodeInfo()
{
    m_nodeName = NULL;
    m_parentName = NULL;
    m_node = NULL;
}

LegoTreeNodeInfo::~LegoTreeNodeInfo()
{
    if (m_nodeName) {
        delete m_nodeName;
    }
    if (m_parentName) {
        delete m_parentName;
    }
}

void
LegoTreeNodeInfo::SetNodeName(const LegoChar* p_nodeName)
{
    if (m_nodeName) {
        delete m_nodeName;
    }
    m_nodeName = new LegoChar[strlen(p_nodeName) + 1];
    strcpy(m_nodeName, p_nodeName);
}

void
LegoTreeNodeInfo::SetParentName(const LegoChar* p_parentName)
{
    if (m_parentName) {
        delete m_parentName;
    }
    m_parentName = new LegoChar[strlen(p_parentName) + 1];
    strcpy(m_parentName, p_parentName);
}

LegoTree::LegoTree()
{
    m_root = NULL;
}

LegoTree::~LegoTree()
{
    if (m_root) {
        Delete(m_root);
    }
}

LegoResult 
LegoTree::Read(LegoStorage* p_storage)
{
    return Read(p_storage, m_root);
}

LegoResult 
LegoTree::Write(LegoStorage* p_storage)
{
    return Write(p_storage, m_root);
}

LegoResult 
LegoTree::Read(LegoStorage* p_storage, LegoTreeNode*& p_node)
{
    LegoResult result;
    p_node = new LegoTreeNode();
    p_node->SetData(CreateData());
    if ((result = p_node->GetData()->Read(p_storage)) != SUCCESS) {
        return result;
    }
    LegoU32 numChildren;
    if ((result = p_storage->Read(&numChildren, sizeof(numChildren))) != SUCCESS) {
        return result;
    }
    if (numChildren) {
        p_node->SetChildren(new LegoTreeNode*[numChildren]);
        for (LegoU32 i = 0; i < numChildren; i++) {
            LegoTreeNode* node;
            if ((result = Read(p_storage, node)) != SUCCESS) {
                return result;
            }
            p_node->SetNumChildren(p_node->GetNumChildren() + 1);
            p_node->SetChild(i, node);
        }
    }
    return SUCCESS;
}

LegoResult 
LegoTree::Write(LegoStorage* p_storage, LegoTreeNode* p_node)
{
    LegoResult result;
    if (p_node->GetData()) {
        if ((result = p_node->GetData()->Write(p_storage)) != SUCCESS) {
            return result;
        }
    }
    LegoU32 numChildren = p_node->GetNumChildren();
    if ((result = p_storage->Write(&numChildren, sizeof(numChildren))) != SUCCESS) {
        return result;
    }
    for (LegoU32 i = 0; i < p_node->GetNumChildren(); i++) {
        if ((result = Write(p_storage, p_node->GetChild(i))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

#ifdef _DEBUG
void
LegoTree::Dump(FILE* p_file)
{
    Dump(p_file, m_root, 0);
}

void 
LegoTree::Dump(FILE* p_file, LegoTreeNode* p_node, LegoU32 p_indent)
{
    LegoU32 i, j;
    for (i = 0; i < p_indent; i++) {
        for (j = 0; j < 2; j++) {
            fputc(' ', p_file);
        }
    }
    fputc('(', p_file);
    if (p_node->GetData()) {
        p_node->GetData()->Dump(p_file);
    }
    if (p_node->GetNumChildren()) {
        fputc('\n', p_file);
        for (i = 0; i < p_node->GetNumChildren(); i++) {
            Dump(p_file, p_node->GetChild(i), p_indent + 1);
        }
        for (i = 0; i < p_indent; i++) {
            for (j = 0; j < 2; j++) {
                fputc(' ', p_file);
            }
        }
    }
    fputc(')', p_file);
    fputc('\n', p_file);
}
#endif

void 
LegoTree::Delete(LegoTreeNode* p_node)
{
    for (LegoU32 i = 0; i < p_node->GetNumChildren(); i++) {
        Delete(p_node->GetChild(i));
    }
    delete p_node;
}


LegoTreeBuilder::LegoTreeBuilder()
{
    m_trees = NULL;
    m_numTrees = 0;
}

LegoTreeBuilder::~LegoTreeBuilder()
{
    if (m_trees) {
        for (LegoU32 i = 0; i < m_numTrees; i++) {
            delete m_trees[i];
        }
        delete [] m_trees;
    }
}

void 
LegoTreeBuilder::Build(LegoTreeNodeInfo* p_info, LegoU32 p_numNodes)
{
    LegoU32 i, j;
    for (i = 0; i < p_numNodes; i++) {
        Build(p_info, p_numNodes, i);
    }
    LegoU32 numNewTrees = 0;
    for (i = 0; i < p_numNodes; i++) {
        if (p_info[i].GetNode() && p_info[i].GetParentName()[0] == '\0') {
            numNewTrees++;
        }
    }
    LegoTree** trees = new LegoTree*[m_numTrees + numNewTrees];
    if (m_numTrees) {
        memcpy(trees, m_trees, m_numTrees * sizeof(LegoTree*));
        delete [] m_trees;
    }
    j = m_numTrees;
    for (i = 0; i < p_numNodes; i++) {
        if (p_info[i].GetNode() && p_info[i].GetParentName()[0] == '\0') {
            trees[j] = CreateTree();;
            trees[j]->SetRoot(p_info[i].GetNode());
            j++;
        }
    }
    m_trees = trees;
    m_numTrees += numNewTrees;
}

void 
LegoTreeBuilder::Build(LegoTreeNodeInfo* p_info, LegoU32 p_numNodes, LegoU32 p_index)
{
    if (p_info[p_index].GetNode()) {
        return;
    }
    if (p_info[p_index].GetParentName()[0] == '\0') {
        p_info[p_index].SetNode(new LegoTreeNode());
        return;
    }
    for (LegoU32 i = 0; i < p_numNodes; i++) {
        if (strcmp(p_info[i].GetNodeName(), p_info[p_index].GetParentName()) == 0) {
            if (!p_info[i].GetNode()) {
                Build(p_info, p_numNodes, i);
            }
            if (p_info[i].GetNode()) {
                p_info[p_index].SetNode(new LegoTreeNode());
                LegoU32 numChildren = p_info[i].GetNode()->GetNumChildren();
                LegoTreeNode** children = new LegoTreeNode*[numChildren + 1];
                if (numChildren) {
                    memcpy(children, p_info[i].GetNode()->GetChildren(), numChildren * sizeof(LegoTreeNode*));
                    delete [] p_info[i].GetNode()->GetChildren();
                }
                children[numChildren] = p_info[p_index].GetNode();
                p_info[i].GetNode()->SetNumChildren(numChildren + 1);
                p_info[i].GetNode()->SetChildren(children);
            }
            return;
        }
    }
}

