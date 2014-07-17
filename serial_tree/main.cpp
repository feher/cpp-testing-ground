#include <iostream>
#include <vector>
#include <cstdint>
#include <memory>
#include <iterator>

namespace SerialTree
{
    template<typename T>
    class Node_c
    {
    public:
        Node_c(T Type) : m_Type{Type}, m_NodeSize{sizeof(Node_c)}, m_SubtreeSize{sizeof(Node_c)} {}
    private:
        T m_Type; // The type of the node.
        size_t m_Size; // Node size in bytes.
        size_t m_SubtreeSize; // Subtree size in bytes.
    };

    class RootNode_c : public Node_c
    {
    };

    class NodePointer_i
    {
        void *m_Pointer;
    };

    template <typename T>
    class NodePointer_c : public NodePointer_i
    {
    public:
        NodePointer_c(T* Ptr) m_Pointer{Ptr} {}
    };

    template <typename T>
    class Iterator_c : public std::iterator<std::input_iterator_tag, Node_c<T>>
    {
    public:
        Iterator_c operator++()
        {
            auto Node = reinterpret_cast<Node_c>(m_Pointer);
            m_Pointer += ;
        }
    private:
        uint8_t *m_Pointer;
    };

    class Tree_c
    {
    public:
        NodePointer_c<RootNode_c> RootPointer() { return {reinterpret_cast<RootNode_c*>(m_Data.data())};  }

        //template<class _Ty,
        //class... _Types> inline
        //    shared_ptr<_Ty> make_shared(_Types&&... _Args)
        //{	// make a shared_ptr
        //        _Ref_count_obj<_Ty> *_Rx =
        //            new _Ref_count_obj<_Ty>(_STD forward<_Types>(_Args)...);

        //        shared_ptr<_Ty> _Ret;
        //        _Ret._Resetp0(_Rx->_Getptr(), _Rx);
        //        return (_Ret);
        //}

        template <typename T, typename ...TArgs>
        NodePointer_c<T> CreateChildAtFront(const NodePointer_i &NodePtr, TArgs&&... Args)
        {
            AllocateSpaceAt(0, sizeof(T));
            auto DataLocation = &(m_Data[0]);
            auto NewNode = new (DataLocation) T{std::forward<TArgs>(Args)...};
            return {NewNode};
        }

        Iterator_c begin()
        {
            return {m_Data[0]}
        }

        Iterator_c end()
        {

        }
    private:
        std::vector<uint8_t> m_Data;
    };

}

class FruitNode_c : public SerialTree::Node_c
{
public:
    FruitNode_c(const std::string &Text) { strncpy(m_Data, Text.c_str(), 2048); }
private:
    char m_Data[2048];
};

class AppleNode_c : public SerialTree::Node_c
{
public:
    AppleNode_c(const std::string &Text) { strncpy(m_Data, Text.c_str(), 2048); }
private:
    char m_Data[2048];
};

class OrangeNode_c : public SerialTree::Node_c
{
public:
    OrangeNode_c(const std::string &Text) { strncpy(m_Data, Text.c_str(), 2048); }
private:
    char m_Data[2048];
};

class MelonNode_c : public SerialTree::Node_c
{
public:
    MelonNode_c(const std::string &Text) { strncpy(m_Data, Text.c_str(), 2048); }
private:
    char m_Data[2048];
};


int main()
{
    auto Tree = SerialTree::Tree_c{};
    auto RootPtr = Tree.RootPointer();
    auto FruitPtr = Tree.CreateChildAtFront<FruitNode_t>(RootPtr, "Fruit");
    auto ApplePtr = Tree.CreateChildAtEnd<AppleNode_t>(FruitPtr, "Apple");
    auto OrangePtr = Tree.CreateChildAtEnd<OrangeNode_t>(FruitPtr, "Orange");
    auto OrangeApplePtr = Tree.CreateChildAtFront<AppleNode_t>(OrangePtr, "Orange Apple");
    auto OrangeMelonPtr = Tree.CreateChildAtEnd<MelonNode_t>(OrangePtr, "Orange Melon");
    auto MelonPtr = Tree.CreateChildAt<MelonNode_t>(FruitPtr, 1, "Melon");
    Tree.DeleteNode(OrangePtr);

    RootNode.AppendChild(Node);
    RootNode.PrependChild(Node);
    RootNode.InsertChildAt(3, Node);
    RootNode.DeleteChildAt(2);

    SerialTree::CreateChild<CustomNode_t>(RootNode, "Hello");

    auto NodePtr = RootNode.ReserveChildAtStart(2048);
    CustomNode_c::Create();
    NodePtr = RootNode.ReserveChildAtEnd(2048);
    NodePtr = RootNode.ReserveChildAt(3, 2048);
}
