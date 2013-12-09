//
//  binary_tree.h
//  ds-ex3-tree
//
//  Created by Darren Liu on 13-11-27.
//  Copyright (c) 2013 Darren Liu. All rights reserved.
//

#ifndef ds_ex3_tree_binary_tree_h
#define ds_ex3_tree_binary_tree_h

#include <typeinfo>
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cstdio>

#if defined(__MINGW32__)
#   define ENDLINE '\n';
#else
#   define ENDLINE std::endl;
#endif

template <typename _Ty>
class BinaryTree {
public:
    BinaryTree() : _root(NULL) {}
    class Position {
    public:
        Position() : _pos(1) {}
        Position(unsigned long _pos) : _pos(_pos) {}
        static Position Root() {
            return Position();
        }
        Position goLeft() {
            _pos = _pos << 1;
            return *this;
        }
        Position goRight() {
            _pos = _pos << 1;
            _pos += 1;
            return *this;
        }
        Position goParent() {
            if (_pos == 1) {
                return *this;
            }
            _pos = _pos >> 1;
            return *this;
        }
        Position goPrevious() {
            if (_pos == 1) {
                return *this;
            }
            _pos--;
            return *this;
        }
        Position goNext() {
            _pos++;
            return *this;
        }
        Position returnRoot() {
            _pos = 1;
            return *this;
        }
        Position left() {
            return Position(_pos << 1);
        }
        Position right() {
            return Position((_pos << 1) + 1);
        }
        Position parent() {
            if (_pos == 1) {
                return Root();
            }
            return Position(_pos >> 1);
        }
        Position next() {
            return Position(_pos + 1);
        }
        Position previous() {
            if (_pos == 1) {
                return Position(_pos);
            }
            return Position(_pos - 1);
        }
        enum Tag {
            Self = 0,
            Left = 1,
            Right = 2
        };
        std::stack<Tag> getStack() const {
            std::stack<Tag> tagStack;
            for (unsigned long t = _pos; t != 1; t /= 2) {
                Tag tag = (t % 2) ? Right : Left;
                tagStack.push(tag);
            }
            return tagStack;
        }
    private:
        unsigned long _pos;
    };
    bool addData(const Position &pos, const _Ty &data) {
        std::stack<typename Position::Tag> tagStack = pos.getStack();
        if (!_root) {
            if (tagStack.empty()) {
                _root = new Node(data);
                return true;
            }
            return false;
        } else if (tagStack.empty()) {
            return false;
        }
        Node *p = _root;
        for (; tagStack.size() > 1; tagStack.pop()) {
            if (!p) {
                return false;
            }
            switch (tagStack.top()) {
                case Position::Left:
                    p = p -> left;
                    break;
                case Position::Right:
                    p = p -> right;
                    break;
                default:
                    break;
            }
        }
        if (!p) {
            return false;
        }
        switch (tagStack.top()) {
            case Position::Left:
                if (p -> left) {
                    return false;
                }
                p -> left = new Node(data);
                break;
            case Position::Right:
                if (p -> right) {
                    return false;
                }
                p -> right = new Node(data);
                break;
            default:
                return false;
        }
        return true;
    }
public:
    class Node {
    public:
        Node() : left(NULL), right(NULL) {}
        Node(const _Ty &data) : left(NULL), right(NULL), data(data) {}
        Node *left;
        Node *right;
        _Ty data;
    };
    static unsigned long _getDepth(const Node *root) {
        if (!root) {
            return 0;
        }
        unsigned long leftDepth = _getDepth(root -> left);
        unsigned long rightDepth = _getDepth(root -> right);
        return ((leftDepth > rightDepth) ? leftDepth : rightDepth) + 1;
    }
public:
    enum TraversalSequence {
        PreOrder,
        InOrder,
        PostOrder
    };
    enum TraversalType {
        Recursive,
        NonRecursive
    };
    void traversal(TraversalSequence sequence, TraversalType type, void visit(_Ty &)) {
        switch (type) {
            case Recursive:
                switch (sequence) {
                    case PreOrder:
                        preOrderRecursiveTraversal(visit, _root);
                        break;
                    case InOrder:
                        inOrderRecursiveTraversal(visit, _root);
                        break;
                    case PostOrder:
                        postOrderRecursiveTraversal(visit, _root);
                        break;
                    default:
                        break;
                }
                break;
            case NonRecursive:
                switch (sequence) {
                    case PreOrder:
                        preOrderNonRecursiveTraversal(visit, _root);
                        break;
                    case InOrder:
                        inOrderNonRecursiveTraversal(visit, _root);
                        break;
                    case PostOrder:
                        postOrderNonRecursiveTraversal(visit, _root);
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
public:
    void swapPosition() {
        recursiveSwapPosition(_root);
    }
private:
    static void preOrderRecursiveTraversal(void visit(_Ty &), Node *root = NULL) {
        if (!root) {
            return;
        }
        visit(root -> data);
        preOrderRecursiveTraversal(visit, root -> left);
        preOrderRecursiveTraversal(visit, root -> right);
    }
    static void inOrderRecursiveTraversal(void visit(_Ty &), Node *root = NULL) {
        if (!root) {
            return;
        }
        inOrderRecursiveTraversal(visit, root -> left);
        visit(root -> data);
        inOrderRecursiveTraversal(visit, root -> right);
    }
    static void postOrderRecursiveTraversal(void visit(_Ty &), Node *root = NULL) {
        if (!root) {
            return;
        }
        postOrderRecursiveTraversal(visit, root -> left);
        postOrderRecursiveTraversal(visit, root -> right);
        visit(root -> data);
    }
    static void preOrderNonRecursiveTraversal(void visit(_Ty &), Node *root = NULL) {
        std::stack<Node *> nodeStack;
        nodeStack.push(NULL);
        nodeStack.push(root);
        while (Node *node = nodeStack.top()) {
            nodeStack.pop();
            visit(node -> data);
            if (node -> right) {
                nodeStack.push(node -> right);
            }
            if (node -> left) {
                nodeStack.push(node -> left);
            }
        }
    }
    static void inOrderNonRecursiveTraversal(void visit(_Ty &), Node *root = NULL) {
        std::stack<Node *> nodeStack;
        nodeStack.push(NULL);
        nodeStack.push(root);
        while (Node *node = nodeStack.top()) {
            while (node -> left) {
                node = node -> left;
                nodeStack.push(node);
            }
            while ((node = nodeStack.top())) {
                visit(node -> data);
                nodeStack.pop();
                if (node -> right) {
                    break;
                }
            }
            if (node) {
                nodeStack.push(node -> right);
            }
        }
    }
    static void postOrderNonRecursiveTraversal(void visit(_Ty &), Node *root = NULL) {
        std::stack<Node *> nodeStack;
        std::stack<typename Position::Tag> tagStack;
        nodeStack.push(NULL);
        nodeStack.push(root);
        tagStack.push(Position::Left);
        while (Node *node = nodeStack.top()) {
            switch (tagStack.top()) {
                case Position::Left:
                    tagStack.pop();
                    tagStack.push(Position::Right);
                    if (node -> left) {
                        nodeStack.push(node -> left);
                        tagStack.push(Position::Left);
                    }
                    break;
                case Position::Right:
                    tagStack.pop();
                    tagStack.push(Position::Self);
                    if (node -> right) {
                        nodeStack.push(node -> right);
                        tagStack.push(Position::Left);
                    }
                    break;
                case Position::Self:
                    nodeStack.pop();
                    tagStack.pop();
                    visit(node -> data);
                    break;
                default:
                    break;
            }
        }
    }
    void recursiveSwapPosition(Node *root) {
        if (!root) {
            return;
        }
        recursiveSwapPosition(root -> left);
        recursiveSwapPosition(root -> right);
        Node *t = root -> left;
        root -> left = root -> right;
        root -> right = t;
    }
public:
    std::vector<Node *> getNodeVector() const {
        std::vector<Node *> nodeVector;
        unsigned long depth = getDepth();
        if (!depth) {
            return nodeVector;
        }
        nodeVector.push_back(_root);
        for (unsigned long i = 0; i < depth - 1; i++) {
            for (unsigned long j = (unsigned long)pow(2, i) - 1; j < (unsigned long)pow(2, i + 1) - 1; j++) {
                Node *p = nodeVector[j];
                if (!p) {
                    nodeVector.push_back(NULL);
                    nodeVector.push_back(NULL);
                    continue;
                }
                if (p -> left) {
                    nodeVector.push_back(p -> left);
                } else {
                    nodeVector.push_back(NULL);
                }
                if (p -> right) {
                    nodeVector.push_back(p -> right);
                } else {
                    nodeVector.push_back(NULL);
                }
            }
        }
        return nodeVector;
    }
public:
    unsigned long getDepth() const {
        return _getDepth(_root);
    }
    friend std::ostream &operator<<(std::ostream &cout, const BinaryTree<_Ty> &tree) {
        unsigned long depth = tree.getDepth();
        std::vector<Node *> nodeVector = tree.getNodeVector();
        typename std::vector<Node *>::iterator p;
        unsigned long i = 0;
        unsigned int length = (unsigned int)pow(2, depth - 1) - 1;
        for (i = 0; i < length; i++) {
            std::cout << ' ';
        }
        for (i = 0, p = nodeVector.begin(); p != nodeVector.end(); p++, i++) {
            int layer = 0;
            bool last = true;
            long long t = i;
            for (long long j = 0; t > 0; j++, t -= (unsigned long)pow(2, j), layer++);
            if (t != 0) {
                last = false;
            }
            if (*p) {
                std::cout << (*p) -> data;
            }
            else {
                std::cout << ' ';
            }
            if (last) {
                std::cout << ENDLINE;
                length = (unsigned int)pow(2, depth - layer - 2);
                if (length > 0) {
                    length--;
                }
                for (unsigned int j = 0; j < length; j++) {
                    std::cout << ' ';
                }
            }
            else {
                length = (unsigned int)pow(2, depth - layer);
                if (length > 0) {
                    length--;
                }
                for (unsigned int j = 0; j < length; j++) {
                    std::cout << ' ';
                }
            }
        }
        return cout;
    }
private:
    Node *_root;
};

#endif
