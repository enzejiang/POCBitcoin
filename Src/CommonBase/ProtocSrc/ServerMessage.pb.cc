// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ServerMessage.proto

#include "ServerMessage.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

extern PROTOBUF_INTERNAL_EXPORT_ServerMessage_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_endPoint_ServerMessage_2eproto;
namespace Enze {
class endPointDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<endPoint> _instance;
} _endPoint_default_instance_;
class ServMsgDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ServMsg> _instance;
} _ServMsg_default_instance_;
}  // namespace Enze
static void InitDefaultsendPoint_ServerMessage_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Enze::_endPoint_default_instance_;
    new (ptr) ::Enze::endPoint();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Enze::endPoint::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_endPoint_ServerMessage_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsendPoint_ServerMessage_2eproto}, {}};

static void InitDefaultsServMsg_ServerMessage_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Enze::_ServMsg_default_instance_;
    new (ptr) ::Enze::ServMsg();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Enze::ServMsg::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<1> scc_info_ServMsg_ServerMessage_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsServMsg_ServerMessage_2eproto}, {
      &scc_info_endPoint_ServerMessage_2eproto.base,}};

void InitDefaults_ServerMessage_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_endPoint_ServerMessage_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_ServMsg_ServerMessage_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_ServerMessage_2eproto[2];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_ServerMessage_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_ServerMessage_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_ServerMessage_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Enze::endPoint, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Enze::endPoint, ip_),
  PROTOBUF_FIELD_OFFSET(::Enze::endPoint, port_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Enze::ServMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Enze::ServMsg, eplist_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Enze::endPoint)},
  { 7, -1, sizeof(::Enze::ServMsg)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::Enze::_endPoint_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::Enze::_ServMsg_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_ServerMessage_2eproto = {
  {}, AddDescriptors_ServerMessage_2eproto, "ServerMessage.proto", schemas,
  file_default_instances, TableStruct_ServerMessage_2eproto::offsets,
  file_level_metadata_ServerMessage_2eproto, 2, file_level_enum_descriptors_ServerMessage_2eproto, file_level_service_descriptors_ServerMessage_2eproto,
};

::google::protobuf::internal::DescriptorTable descriptor_table_ServerMessage_2eproto = {
  false, InitDefaults_ServerMessage_2eproto, 
  "\n\023ServerMessage.proto\022\004Enze\"$\n\010endPoint\022"
  "\n\n\002ip\030\002 \001(\r\022\014\n\004port\030\003 \001(\r\")\n\007ServMsg\022\036\n\006"
  "epList\030\001 \003(\0132\016.Enze.endPointb\006proto3"
,
  "ServerMessage.proto", &assign_descriptors_table_ServerMessage_2eproto, 116,
};

void AddDescriptors_ServerMessage_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_ServerMessage_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_ServerMessage_2eproto = []() { AddDescriptors_ServerMessage_2eproto(); return true; }();
namespace Enze {

// ===================================================================

void endPoint::InitAsDefaultInstance() {
}
class endPoint::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int endPoint::kIpFieldNumber;
const int endPoint::kPortFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

endPoint::endPoint()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Enze.endPoint)
}
endPoint::endPoint(const endPoint& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&ip_, &from.ip_,
    static_cast<size_t>(reinterpret_cast<char*>(&port_) -
    reinterpret_cast<char*>(&ip_)) + sizeof(port_));
  // @@protoc_insertion_point(copy_constructor:Enze.endPoint)
}

void endPoint::SharedCtor() {
  ::memset(&ip_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&port_) -
      reinterpret_cast<char*>(&ip_)) + sizeof(port_));
}

endPoint::~endPoint() {
  // @@protoc_insertion_point(destructor:Enze.endPoint)
  SharedDtor();
}

void endPoint::SharedDtor() {
}

void endPoint::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const endPoint& endPoint::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_endPoint_ServerMessage_2eproto.base);
  return *internal_default_instance();
}


void endPoint::Clear() {
// @@protoc_insertion_point(message_clear_start:Enze.endPoint)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&ip_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&port_) -
      reinterpret_cast<char*>(&ip_)) + sizeof(port_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* endPoint::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<endPoint*>(object);
  ::google::protobuf::uint32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ::google::protobuf::uint32 tag;
    ptr = Varint::Parse32Inline(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // uint32 ip = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::uint32 value = val;
        msg->set_ip(value);
        break;
      }
      // uint32 port = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 24) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::uint32 value = val;
        msg->set_port(value);
        break;
      }
      default: {
      handle_unusual: (void)&&handle_unusual;
        if ((tag & 7) == 4 || tag == 0) {
          bool ok = ctx->ValidEndGroup(tag);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ok);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
len_delim_till_end: (void)&&len_delim_till_end;
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                                 {parser_till_end, object}, size);
group_continues: (void)&&group_continues;
  GOOGLE_DCHECK(ptr >= end);
  ctx->StoreGroup({_InternalParse, msg}, {parser_till_end, object}, depth);
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool endPoint::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Enze.endPoint)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // uint32 ip = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ip_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 port = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (24 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &port_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Enze.endPoint)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Enze.endPoint)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void endPoint::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Enze.endPoint)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 ip = 2;
  if (this->ip() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->ip(), output);
  }

  // uint32 port = 3;
  if (this->port() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->port(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Enze.endPoint)
}

::google::protobuf::uint8* endPoint::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Enze.endPoint)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 ip = 2;
  if (this->ip() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->ip(), target);
  }

  // uint32 port = 3;
  if (this->port() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->port(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Enze.endPoint)
  return target;
}

size_t endPoint::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Enze.endPoint)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 ip = 2;
  if (this->ip() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->ip());
  }

  // uint32 port = 3;
  if (this->port() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->port());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void endPoint::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Enze.endPoint)
  GOOGLE_DCHECK_NE(&from, this);
  const endPoint* source =
      ::google::protobuf::DynamicCastToGenerated<endPoint>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Enze.endPoint)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Enze.endPoint)
    MergeFrom(*source);
  }
}

void endPoint::MergeFrom(const endPoint& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Enze.endPoint)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.ip() != 0) {
    set_ip(from.ip());
  }
  if (from.port() != 0) {
    set_port(from.port());
  }
}

void endPoint::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Enze.endPoint)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void endPoint::CopyFrom(const endPoint& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Enze.endPoint)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool endPoint::IsInitialized() const {
  return true;
}

void endPoint::Swap(endPoint* other) {
  if (other == this) return;
  InternalSwap(other);
}
void endPoint::InternalSwap(endPoint* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(ip_, other->ip_);
  swap(port_, other->port_);
}

::google::protobuf::Metadata endPoint::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_ServerMessage_2eproto);
  return ::file_level_metadata_ServerMessage_2eproto[kIndexInFileMessages];
}


// ===================================================================

void ServMsg::InitAsDefaultInstance() {
}
class ServMsg::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ServMsg::kEpListFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ServMsg::ServMsg()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Enze.ServMsg)
}
ServMsg::ServMsg(const ServMsg& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      eplist_(from.eplist_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Enze.ServMsg)
}

void ServMsg::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_ServMsg_ServerMessage_2eproto.base);
}

ServMsg::~ServMsg() {
  // @@protoc_insertion_point(destructor:Enze.ServMsg)
  SharedDtor();
}

void ServMsg::SharedDtor() {
}

void ServMsg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ServMsg& ServMsg::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_ServMsg_ServerMessage_2eproto.base);
  return *internal_default_instance();
}


void ServMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:Enze.ServMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  eplist_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ServMsg::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<ServMsg*>(object);
  ::google::protobuf::uint32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ::google::protobuf::uint32 tag;
    ptr = Varint::Parse32Inline(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // repeated .Enze.endPoint epList = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 10) goto handle_unusual;
        do {
          ptr = Varint::Parse32Inline(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          parser_till_end = ::Enze::endPoint::_InternalParse;
          object = msg->add_eplist();
          if (size > end - ptr) goto len_delim_till_end;
          auto newend = ptr + size;
          bool ok = ctx->ParseExactRange({parser_till_end, object},
                                         ptr, newend);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ok);
          ptr = newend;
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 10 && (ptr += 1));
        break;
      }
      default: {
      handle_unusual: (void)&&handle_unusual;
        if ((tag & 7) == 4 || tag == 0) {
          bool ok = ctx->ValidEndGroup(tag);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ok);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
len_delim_till_end: (void)&&len_delim_till_end;
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                                 {parser_till_end, object}, size);
group_continues: (void)&&group_continues;
  GOOGLE_DCHECK(ptr >= end);
  ctx->StoreGroup({_InternalParse, msg}, {parser_till_end, object}, depth);
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool ServMsg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Enze.ServMsg)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .Enze.endPoint epList = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (10 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_eplist()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Enze.ServMsg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Enze.ServMsg)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ServMsg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Enze.ServMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .Enze.endPoint epList = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->eplist_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1,
      this->eplist(static_cast<int>(i)),
      output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Enze.ServMsg)
}

::google::protobuf::uint8* ServMsg::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Enze.ServMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .Enze.endPoint epList = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->eplist_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, this->eplist(static_cast<int>(i)), deterministic, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Enze.ServMsg)
  return target;
}

size_t ServMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Enze.ServMsg)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Enze.endPoint epList = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->eplist_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->eplist(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ServMsg::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Enze.ServMsg)
  GOOGLE_DCHECK_NE(&from, this);
  const ServMsg* source =
      ::google::protobuf::DynamicCastToGenerated<ServMsg>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Enze.ServMsg)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Enze.ServMsg)
    MergeFrom(*source);
  }
}

void ServMsg::MergeFrom(const ServMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Enze.ServMsg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  eplist_.MergeFrom(from.eplist_);
}

void ServMsg::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Enze.ServMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ServMsg::CopyFrom(const ServMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Enze.ServMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ServMsg::IsInitialized() const {
  return true;
}

void ServMsg::Swap(ServMsg* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ServMsg::InternalSwap(ServMsg* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  CastToBase(&eplist_)->InternalSwap(CastToBase(&other->eplist_));
}

::google::protobuf::Metadata ServMsg::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_ServerMessage_2eproto);
  return ::file_level_metadata_ServerMessage_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Enze
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::Enze::endPoint* Arena::CreateMaybeMessage< ::Enze::endPoint >(Arena* arena) {
  return Arena::CreateInternal< ::Enze::endPoint >(arena);
}
template<> PROTOBUF_NOINLINE ::Enze::ServMsg* Arena::CreateMaybeMessage< ::Enze::ServMsg >(Arena* arena) {
  return Arena::CreateInternal< ::Enze::ServMsg >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
