#pragma once

#include <memory>
#include <iostream>

namespace bintree {
    template <typename T>
    struct TNode {
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;

        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            return bool(parent);
        }

        T& getValue() {
            return value;
        }

        const T& getValue() const {
            return value;
        }

        TNodePtr getLeft() {
            return left;
        }

        TNodeConstPtr getLeft() const {
            return left;
        }

        TNodePtr getRight() {
            return right;
        }

        TNodeConstPtr getRight() const {
            return right;
        }

        TNodePtr getParent() {
            return parent;
        }

        TNodeConstPtr getParent() const {
            return parent;
        }

        static TNodePtr createLeaf(T v) {
            auto A = new TNode(v);
            return std::shared_ptr<TNode>(A);
        }

        static TNodePtr fork(T v, std::shared_ptr<TNode> left, std::shared_ptr<TNode> right) {
            auto A = new TNode(v, left, right);
            TNodePtr ptr = std::shared_ptr<TNode>(A);
            setParent(ptr->getLeft(), ptr);
            setParent(ptr->getRight(), ptr);
            return ptr;
        }

        

        TNodePtr replaceLeft(TNodePtr l) {
            setParent(l, TNodePtr(this));
            setParent(left, nullptr);
            std::swap(l, left);
            return l;
        }

        TNodePtr replaceRight(TNodePtr r) {
            setParent(r, TNodePtr(this));
            setParent(right, nullptr);
            std::swap(r, right);
            return r;
        }

        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }
        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }
    private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        TNodePtr parent = nullptr;

        TNode(T v)
            : value(v)
        {
        }
        TNode(T v, std::shared_ptr<TNode> left, std::shared_ptr<TNode> right)
            : value(v)
            , left(left)
            , right(right)
        {
        }

        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}
