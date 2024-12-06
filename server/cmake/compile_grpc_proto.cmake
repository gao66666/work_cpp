# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.21)

function(compile_grpc_proto target_name proto_name proto_file)
  # Get absolute path and directory of the .proto file
  get_filename_component(hw_proto "${proto_file}" ABSOLUTE)
  get_filename_component(hw_proto_path "${hw_proto}" PATH)

  # Generated sources
  set(hw_proto_sources "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.pb.cc")
  set(hw_proto_headers "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.pb.h")
  set(hw_grpc_sources "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.grpc.pb.cc")
  set(hw_grpc_headers "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.grpc.pb.h")

  # Custom command to generate the files
  add_custom_command(
    OUTPUT "${hw_proto_sources}" "${hw_proto_headers}" "${hw_grpc_sources}" "${hw_grpc_headers}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
      --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
      -I "${hw_proto_path}"
      --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
      "${hw_proto}"
    DEPENDS "${hw_proto}")

  # Include generated headers
  include_directories("${CMAKE_CURRENT_BINARY_DIR}")

  # Create library for generated files
  add_library(${target_name}
    ${hw_grpc_sources}
    ${hw_grpc_headers}
    ${hw_proto_sources}
    ${hw_proto_headers})
  
  # Link necessary libraries
  target_link_libraries(${target_name}
    absl::check
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})

endfunction()
