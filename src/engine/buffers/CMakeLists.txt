set(buffers_src_files
        BufHandler.hh
        BufHandler.cc BaseBuffer.cc BaseBuffer.hh VertexBuffer.cc VertexBuffer.hh IndexBuffer.cc IndexBuffer.hh)
add_library(buffers ${buffers_src_files})