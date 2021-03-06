// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Hello.proto

#ifndef PROTOBUF_INCLUDED_Hello_2eproto
#define PROTOBUF_INCLUDED_Hello_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_Hello_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_Hello_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_Hello_2eproto();
class Person;
class PersonDefaultTypeInternal;
extern PersonDefaultTypeInternal _Person_default_instance_;
namespace google {
namespace protobuf {
template<> ::Person* Arena::CreateMaybeMessage<::Person>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class Person : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Person) */ {
 public:
  Person();
  virtual ~Person();

  Person(const Person& from);

  inline Person& operator=(const Person& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Person(Person&& from) noexcept
    : Person() {
    *this = ::std::move(from);
  }

  inline Person& operator=(Person&& from) noexcept {
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
  static const Person& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Person* internal_default_instance() {
    return reinterpret_cast<const Person*>(
               &_Person_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Person* other);
  friend void swap(Person& a, Person& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Person* New() const final {
    return CreateMaybeMessage<Person>(NULL);
  }

  Person* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Person>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Person& from);
  void MergeFrom(const Person& from);
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
  void InternalSwap(Person* other);
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

  // string m_strName = 1;
  void clear_m_strname();
  static const int kMStrNameFieldNumber = 1;
  const ::std::string& m_strname() const;
  void set_m_strname(const ::std::string& value);
  #if LANG_CXX11
  void set_m_strname(::std::string&& value);
  #endif
  void set_m_strname(const char* value);
  void set_m_strname(const char* value, size_t size);
  ::std::string* mutable_m_strname();
  ::std::string* release_m_strname();
  void set_allocated_m_strname(::std::string* m_strname);

  // uint32 m_iAge = 2;
  void clear_m_iage();
  static const int kMIAgeFieldNumber = 2;
  ::google::protobuf::uint32 m_iage() const;
  void set_m_iage(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Person)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr m_strname_;
  ::google::protobuf::uint32 m_iage_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Hello_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Person

// string m_strName = 1;
inline void Person::clear_m_strname() {
  m_strname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Person::m_strname() const {
  // @@protoc_insertion_point(field_get:Person.m_strName)
  return m_strname_.GetNoArena();
}
inline void Person::set_m_strname(const ::std::string& value) {
  
  m_strname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Person.m_strName)
}
#if LANG_CXX11
inline void Person::set_m_strname(::std::string&& value) {
  
  m_strname_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Person.m_strName)
}
#endif
inline void Person::set_m_strname(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  m_strname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Person.m_strName)
}
inline void Person::set_m_strname(const char* value, size_t size) {
  
  m_strname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Person.m_strName)
}
inline ::std::string* Person::mutable_m_strname() {
  
  // @@protoc_insertion_point(field_mutable:Person.m_strName)
  return m_strname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Person::release_m_strname() {
  // @@protoc_insertion_point(field_release:Person.m_strName)
  
  return m_strname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_m_strname(::std::string* m_strname) {
  if (m_strname != NULL) {
    
  } else {
    
  }
  m_strname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), m_strname);
  // @@protoc_insertion_point(field_set_allocated:Person.m_strName)
}

// uint32 m_iAge = 2;
inline void Person::clear_m_iage() {
  m_iage_ = 0u;
}
inline ::google::protobuf::uint32 Person::m_iage() const {
  // @@protoc_insertion_point(field_get:Person.m_iAge)
  return m_iage_;
}
inline void Person::set_m_iage(::google::protobuf::uint32 value) {
  
  m_iage_ = value;
  // @@protoc_insertion_point(field_set:Person.m_iAge)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_Hello_2eproto
