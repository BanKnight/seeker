#pragma once

#include <string>
#include <vector>
#include "event/EventTarget.hpp"

namespace seeker
{
    //https://dom.spec.whatwg.org/#node
    class Node : public EventTarget
    {
    private:
        std::string _name;
        std::string _value;
        std::vector<NodePtr> _childNodes;
        NodePtr _prev;
        NodePtr _next;

    public:
        Node();
        virtual ~Node();

    public:
        /**
         * @brief 
         * 返回一个表示base URL的DOMString。不同语言中的base URL的概念都不一样。 在HTML中，base URL表示协议和域名，以及一直到最后一个'/'之前的文件目录。
         * @return std::string 
         */
        std::string baseURI() const;

        /**
         * @brief 返回子节点
         * 
         * @return const std::vector<NodePtr>& 
         */
        const std::vector<NodePtr> &childNodes() const;

        /**
         * @brief 返回该节点的第一个子节点Node，如果该节点没有子节点则返回null。
         * 
         * @return NodePtr 
         */
        NodePtr firstChild() const;

        /**
         * @brief 
         * 返回一个布尔值用来检测该节点是否已连接(直接或者间接)到一个上下文对象上，比如通常DOM情况下的Document对象，或者在shadow DOM情况下的ShadowRoot对象。
         * @return true 
         * @return false 
         */
        bool isConnected() const;

        /**
         * @brief 
         * 返回该节点的最后一个子节点Node，如果该节点没有子节点则返回null。
         * @return NodePtr 
         */
        NodePtr lastChild() const;
        /**
         * @brief 
         * 返回与该节点同级的下一个节点 Node，如果没有返回null。
         * @return NodePtr 
         */
        NodePtr nextSibling() const;

        /**
         * @brief 
         * 返回一个当前节点同辈的前一个节点( Node) ，或者返回null（如果不存在这样的一个节点的话）。
         * @return NodePtr 
         */
        NodePtr previousSibling() const;
        /**
         * @brief 
         * 返回一个包含该节点名字的DOMString。节点的名字的结构和节点类型不同。比如HTMLElement的名字跟它所关联的标签对应，就比如HTMLAudioElement的就是
         * 'audio' ，Text节点对应的是 '#text' 还有Document节点对应的是 '#document'。
         * @return std::string 
         */
        std::string nodeName() const;
        /**
         * @brief 
         * 返回一个与该节点类型对应的无符号短整型的值，可能的值如下：
         * @return int32_t 
         */
        int32_t NodeType() const;

        // Name	Value
        // ELEMENT_NODE	1
        // ATTRIBUTE_NODE 	2
        // TEXT_NODE	3
        // CDATA_SECTION_NODE	4
        // ENTITY_REFERENCE_NODE 	5
        // ENTITY_NODE 	6
        // PROCESSING_INSTRUCTION_NODE	7
        // COMMENT_NODE	8
        // DOCUMENT_NODE	9
        // DOCUMENT_TYPE_NODE	10
        // DOCUMENT_FRAGMENT_NODE	11
        // NOTATION_NODE 	12

        /**
     * @brief 
     * 返回或设置当前节点的值。
     * @return std::string 
     */
        std::string nodeValue() const;
        /**
     * @brief Set the Node Value object
     * 
     * @param value 
     */
        void setNodeValue(const std::string &value);

        // Node.ownerDocument 只读
        // 返回这个元素属于的 Document对象 。 如果没有Document对象与之关联，返回null。
        // Node.parentNode 只读
        // 返回一个当前节点 Node的父节点 。如果没有这样的节点，比如说像这个节点是树结构的顶端或者没有插入一棵树中， 这个属性返回null。
        // Node.parentElement 只读
        // 返回一个当前节点的父节点 Element 。 如果当前节点没有父节点或者说父节点不是一个元素(Element), 这个属性返回null。

        /**
     * @brief 
     * 返回或一个元素内所有子节点及其后代的文本内容。
     * @return std::string 
     */
        std::string textContent() const;
        /**
     * @brief 设置一个元素内所有子节点及其后代的文本内容。
     * 
     * @param value 
     */
        void setTextContent(const std::string &value);

        // Node.localName (en-US) 只读
        // 返回一个表示元素名称的本土化表示方法的 DOMString 。
        // Note: 在Firefox 3.5以及更早的版本中, HTML 元素的 localName 属性的返回值都是大写的（XHTML 例外）。在后续版本中，这种情况就不存在了。无论是 HTML 还是 XHTML 中，均返回小写的 localName。

        // Node.namespaceURI (en-US) 只读
        // 该节点命名空间的URL，如果没有命名空间则为null。
        // Note: 在Firefox 3.5以及更早的版本中, HTML 的元素都没有命名空间. 而在最新的版本中, 无论是 HTML 还是 XML 文档树 ，所有元素的命名空间统一为 http://www.w3.org/1999/xhtml/。

        // Node.prefix (en-US) 只读
        // 返回一个节点命名空间的前缀 DOMString , 当前缀不存在时返回 null 。
        // Node.rootNode (en-US) 只读
        // 返回一个DOM 树中顶层节点的  Node 对象，如果顶层节点不DOM 树中，则返回当前节点。该属性已被 Node.getRootNode() 方法所代替。
        // 方法
        // 从其父类型 EventTarget[1] 继承方法。

        /**
     * @brief 将指定的 childNode 参数作为最后一个子节点添加到当前节点。
     * 
     * @param child 
     */
        void appendChild(const NodePtr &child);
        /**
     * @brief Node，并且可以选择是否克隆这个节点下的所有内容。默认情况下，节点下的内容会被克隆。
     * 
     * @return NodePtr 
     */
        NodePtr cloneNode() const;
        // Node.compareDocumentPosition()
        // 比较当前节点与文档中的另一节点的位置。

        /**
         * @brief 返回一个 Boolean 布尔值，来表示传入的节点是否为该节点的后代节点。
         * 
         */
        bool contains(const NodePtr &other);
        //
        // Node.getRootNode()
        // 返回上下文对象的根节点。如果shadow root节点存在的话，也可以在返回的节点中包含它。
        /**
         * @brief 返回一个Boolean 布尔值，来表示该元素是否包含有子节点。
         * 
         * @return true 
         * @return false 
         */
        bool hasChildNodes()const;
        /**
         * @brief 在当前节点下增加一个子节点 Node，并使该子节点位于参考节点的前面。
         * 
         * @param node 
         * @param child 
         */
        NodePtr insertBefore(const NodePtr & node,const NodePtr & child);
        // Node.isDefaultNamespace()
        // 返回一个 Boolean 类型值。接受一个命名空间 URI 作为参数，当参数所指代的命名空间是默认命名空间时返回 true，否则返回 false。
        // Node.isEqualNode()
        // 返回一个 Boolean 类型值。当两个 node 节点为相同类型的节点且定义的数据点匹配时（即属性和属性值相同，节点值相同）返回 true，否则返回 false。
        // Node.isSameNode()
        // 返回一个 Boolean 类型值。返回这两个节点的引用比较结果。
        // Node.lookupPrefix()
        // 返回包含参数 URI 所对应的命名空间前缀的 DOMString，若不存在则返回 null。如果存在多个可匹配的前缀，则返回结果和浏览器具体实现有关。
        // Node.lookupNamespaceURI()
        // 接受一个前缀，并返回前缀所对应节点命名空间 URI 。如果 URI 不存在则返回 null。传入 null 作为 prefix 参数将返回默认命名空间。
        // Node.normalize()
        // 对该元素下的所有文本子节点进行整理，合并相邻的文本节点并清除空文本节点。
        // Node.removeChild()
        // 移除当前节点的一个子节点。这个子节点必须存在于当前节点中。
        // Node.replaceChild()
    };
}