set(buffers_src_files
        BufHandler.hh
        BufHandler.cc
        BaseBuffer.hh
        BaseBuffer.cc
        VertexBuffer.cc
        VertexBuffer.hh
        IndexBuffer.cc
        IndexBuffer.hh
        VertexBufferLayout.hh
        VertexArray.cc
        VertexArray.hh)
add_library(buffers ${buffers_src_files})