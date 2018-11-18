// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ServerMessage.proto

#ifndef PROTOBUF_INCLUDED_ServerMessage_2eproto
#define PROTOBUF_INCLUDED_ServerMessage_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3006001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ServerMessage_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_ServerMessage_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_ServerMessage_2eproto();
namespace Enze {
class ServMsg;
class ServMsgDefaultTypeInternal;
extern ServMsgDefaultTypeInternal _ServMsg_default_instance_;
class endPoint;
class endPointDefaultTypeInternal;
extern endPointDefaultTypeInternal _endPoint_default_instance_;
}  // namespace Enze
namespace google {
namespace protobuf {
template<> ::Enze::ServMsg* Arena::CreateMaybeMessage<::Enze::ServMsg>(Arena*);
template<> ::Enze::endPoint* Arena::CreateMaybeMessage<::Enze::endPoint>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace Enze {

// ===================================================================

class endPoint : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Enze.endPoint) */ {
 public:
  endPoint();
  virtual ~endPoint();

  endPoint(const endPoint& from);

  inline endPoint& operator=(const endPoint& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  endPoint(endPoint&& from) noexcept
    : endPoint() {
    *this = ::std::move(from);
  }

  inline endPoint& operator=(endPoint&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const endPoint& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const endPoint* internal_default_instance() {
    return reinterpret_cast<const endPoint*>(
               &_endPoint_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(endPoint* other);
  friend void swap(endPoint& a, endPoint& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline endPoint* New() const final {
    return CreateMaybeMessage<endPoint>(NULL);
  }

  endPoint* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<endPoint>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const endPoint& from);
  void MergeFrom(const endPoint& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(endPoint* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint32 ip = 2;
  void clear_ip();
  static const int kIpFieldNumber = 2;
  ::google::protobuf::uint32 ip() const;
  void set_ip(::google::protobuf::uint32 value);

  // uint32 port = 3;
  void clear_port();
  static const int kPortFieldNumber = 3;
  ::google::protobuf::uint32 port() const;
  void set_port(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Enze.endPoint)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 ip_;
  ::google::protobuf::uint32 port_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ServerMessage_2eproto;
};
// -------------------------------------------------------------------

class ServMsg : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Enze.ServMsg) */ {
 public:
  ServMsg();
  virtual ~ServMsg();

  ServMsg(const ServMsg& from);

  inline ServMsg& operator=(const ServMsg& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ServMsg(ServMsg&& from) noexcept
    : ServMsg() {
    *this = ::std::move(from);
  }

  inline ServMsg& operator=(ServMsg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const ServMsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ServMsg* internal_default_instance() {
    return reinterpret_cast<const ServMsg*>(
               &_ServMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(ServMsg* other);
  friend void swap(ServMsg& a, ServMsg& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ServMsg* New() const final {
    return CreateMaybeMessage<ServMsg>(NULL);
  }

  ServMsg* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ServMsg>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ServMsg& from);
  void MergeFrom(const ServMsg& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ServMsg* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .Enze.endPoint epList = 1;
  int eplist_size() const;
  void clear_eplist();
  static const int kEpListFieldNumber = 1;
  ::Enze::endPoint* mutable_eplist(int index);
  ::google::protobuf::RepeatedPtrField< ::Enze::endPoint >*
      mutable_eplist();
  const ::Enze::endPoint& eplist(int index) const;
  ::Enze::endPoint* add_eplist();
  const ::google::protobuf::RepeatedPtrField< ::Enze::endPoint >&
      eplist() const;

  // @@protoc_insertion_point(class_scope:Enze.ServMsg)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::Enze::endPoint > eplist_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ServerMessage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// endPoint

// uint32 ip = 2;
inline void endPoint::clear_ip() {
  ip_ = 0u;
}
inline ::google::protobuf::uint32 endPoint::ip() const {
  // @@protoc_insertion_point(field_get:Enze.endPoint.ip)
  return ip_;
}
inline void endPoint::set_ip(::google::protobuf::uint32 value) {
  
  ip_ = value;
  // @@protoc_insertion_point(field_set:Enze.endPoint.ip)
}

// uint32 port = 3;
inline void endPoint::clear_port() {
  port_ = 0u;
}
inline ::google::protobuf::uint32 endPoint::port() const {
  // @@protoc_insertion_point(field_get:Enze.endPoint.port)
  return port_;
}
inline void endPoint::set_port(::google::protobuf::uint32 value) {
  
  port_ = value;
  // @@protoc_insertion_point(field_set:Enze.endPoint.port)
}

// -------------------------------------------------------------------

// ServMsg

// repeated .Enze.endPoint epList = 1;
inline int ServMsg::eplist_size() const {
  return eplist_.size();
}
inline void ServMsg::clear_eplist() {
  eplist_.Clear();
}
inline ::Enze::endPoint* ServMsg::mutable_eplist(int index) {
  // @@protoc_insertion_point(field_mutable:Enze.ServMsg.epList)
  return eplist_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::Enze::endPoint >*
ServMsg::mutable_eplist() {
  // @@protoc_insertion_point(field_mutable_list:Enze.ServMsg.epList)
  return &eplist_;
}
inline const ::Enze::endPoint& ServMsg::eplist(int index) const {
  // @@protoc_insertion_point(field_get:Enze.ServMsg.epList)
  return eplist_.Get(index);
}
inline ::Enze::endPoint* ServMsg::add_eplist() {
  // @@protoc_insertion_point(field_add:Enze.ServMsg.epList)
  return eplist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Enze::endPoint >&
ServMsg::eplist() const {
  // @@protoc_insertion_point(field_list:Enze.ServMsg.epList)
  return eplist_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Enze

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_ServerMessage_2eproto
