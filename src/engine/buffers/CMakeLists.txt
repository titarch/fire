set(buffers_src_files
        BufHandler.cc BufHandler.hh

        BaseBuffer.cc BaseBuffer.hh
        VertexBuffer.cc VertexBuffer.hh
        VertexBufferLayout.hh
        IndexBuffer.cc IndexBuffer.hh
        VertexArray.cc VertexArray.hh
        StorageBuffer.cc StorageBuffer.hh
        )
add_library(buffers ${buffers_src_files})