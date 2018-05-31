#pragma once

#include "GraphNode.h"
#include "EnumUtility.h"

namespace oak
    {
    //////////////////////////////////////////////////////////////////////////
    enum class NodeFileType
        {
        not_a_file,
        unknown,
        config,
        script,
        image,
        sound,
        shader,
        executable,
        library,
        font,
        };

    DECLARE_ENUM_ENTRY(NodeFileType);

    //////////////////////////////////////////////////////////////////////////
    class RootNode : public GraphNode
        {
        public:
            using Ptr = std::shared_ptr<RootNode>;

        public:
            RootNode(const std::string & n = "");
            virtual ~RootNode();
        };

    //////////////////////////////////////////////////////////////////////////
    class DirectoryNode : public GraphNode
        {
        public:
            using Ptr = std::shared_ptr<DirectoryNode>;

        public:
            DirectoryNode(const std::string & n = "");
            virtual ~DirectoryNode();

            const std::string & FullPath() const { return m_full_path; }
//            void FullPath(const std::string & n) { m_full_path = n; }

        protected:
            std::string     m_full_path;
        };

    //////////////////////////////////////////////////////////////////////////
    class FileNode : public GraphNode
        {
        public:
            using Ptr = std::shared_ptr<FileNode>;

        public:
            FileNode(const std::string & n = "");
            virtual ~FileNode();

            const std::string & FullPath() const { return m_full_path; }
//            void FullPath(const std::string & n) { m_full_path = n; }

            const NodeFileType & FileType() const { return m_file_type; }
            void FileType(NodeFileType n) { m_file_type = n; }

        protected:
            std::string     m_full_path;
            NodeFileType    m_file_type;
        };

    //////////////////////////////////////////////////////////////////////////
    class IncludeNode : public GraphNode
        {
        public:
            using Ptr = std::shared_ptr<IncludeNode>;

        public:
            IncludeNode(const std::string & n = "");
            virtual ~IncludeNode();
        };

    //////////////////////////////////////////////////////////////////////////
    class SectionNode : public GraphNode
        {
        public:
            using Ptr = std::shared_ptr<SectionNode>;

        public:
            SectionNode(const std::string & n = "");
            virtual ~SectionNode();
        };

    //////////////////////////////////////////////////////////////////////////
    class PropertyNode : public GraphNode
        {
        public:
            using Ptr = std::shared_ptr<PropertyNode>;

        public:
            PropertyNode(const std::string & n = "", const std::string & v = "");
            virtual ~PropertyNode();

        public:
            const std::string & Value() const { return m_value; }
            void Value(const std::string & n) { m_value = n; }

        protected:
            std::string     m_value;

        };


    }
