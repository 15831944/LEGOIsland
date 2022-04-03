#ifndef __LEGOTREE_H
#define __LEGOTREE_H

#ifdef _DEBUG
#include <stdio.h>
#endif
#include "LegoTypes.h"

class LegoStorage;

class LegoTreeNodeData {
public:
    LegoTreeNodeData() {}
    virtual ~LegoTreeNodeData() {}
    virtual LegoResult Read(LegoStorage* p_storage) { return SUCCESS; }
    virtual LegoResult Write(LegoStorage* p_storage) { return SUCCESS; }
#ifdef _DEBUG
    virtual void Dump(FILE* p_file) {}
#endif
};

class LegoTreeNode {
public:
    LegoTreeNode();
    virtual ~LegoTreeNode();
    LegoTreeNodeData* GetData() { return m_data; }
    void SetData(LegoTreeNodeData* p_data) { m_data = p_data; }
    LegoU32 GetNumChildren() { return m_numChildren; }
    void SetNumChildren(LegoU32 p_numChildren) { m_numChildren = p_numChildren; }
    LegoTreeNode* GetChild(LegoU32 p_i) { return m_children[p_i]; }
    void SetChild(LegoU32 p_i, LegoTreeNode* p_child) { m_children[p_i] = p_child; }
    LegoTreeNode** GetChildren() { return m_children; }
    void SetChildren(LegoTreeNode** p_children) { m_children = p_children; }
protected:
    LegoTreeNodeData* m_data;
    LegoU32 m_numChildren;
    LegoTreeNode** m_children;
};

class LegoTree {
public:
    LegoTree();
    virtual ~LegoTree();
    LegoTreeNode* GetRoot() { return m_root; }
    void SetRoot(LegoTreeNode* p_root) { m_root = p_root; }
    virtual LegoResult Read(LegoStorage* p_storage);
    virtual LegoResult Write(LegoStorage* p_storage);
#ifdef _DEBUG
    void Dump(FILE* p_file);
#endif
protected:
    LegoResult Read(LegoStorage* p_storage, LegoTreeNode*& p_node);
    LegoResult Write(LegoStorage* p_storage, LegoTreeNode* p_node);
    void Delete(LegoTreeNode* p_node);
    virtual LegoTreeNodeData* CreateData() { return new LegoTreeNodeData(); }
#ifdef _DEBUG
    void Dump(FILE* p_file, LegoTreeNode* p_node, LegoU32 p_indent);
#endif    
    LegoTreeNode* m_root;
};

class LegoTreeNodeInfo {
public:
    LegoTreeNodeInfo();
    virtual ~LegoTreeNodeInfo();
    LegoChar* GetNodeName() { return m_nodeName; }
    void SetNodeName(const LegoChar* p_nodeName);
    LegoChar* GetParentName() { return m_parentName; }
    void SetParentName(const LegoChar* p_parentName);
    LegoTreeNode* GetNode() { return m_node; }
    void SetNode(LegoTreeNode* p_node) { m_node = p_node; }
protected:
    LegoChar* m_nodeName;
    LegoChar* m_parentName;
    LegoTreeNode* m_node;
};

class LegoTreeBuilder {
public:
    LegoTreeBuilder();
    virtual ~LegoTreeBuilder();
    void Build(LegoTreeNodeInfo* p_info, LegoU32 p_numNodes);
    LegoTree* GetTree(LegoU32 p_i) { return m_trees[p_i]; }
    void SetTree(LegoU32 p_i, LegoTree* p_tree) { m_trees[p_i] = p_tree; }
    LegoU32 GetNumTrees() { return m_numTrees; }
    void SetNumTrees(LegoU32 p_numTrees) { m_numTrees = p_numTrees; }
protected:
    void Build(LegoTreeNodeInfo* p_info, LegoU32 p_numNodes, LegoU32 p_index);
    virtual LegoTree* CreateTree() { return new LegoTree(); }
    LegoTree** m_trees;
    LegoU32 m_numTrees;
};

#endif // __LEGOTREE_H