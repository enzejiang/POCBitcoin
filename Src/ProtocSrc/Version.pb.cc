// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Version.proto

#include "Version.pb.h"

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

extern PROTOBUF_INTERNAL_EXPORT_Address_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_Address_Address_2eproto;
namespace Enze {
class VersionDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Version> _instance;
} _Version_default_instance_;
}  // namespace Enze
static void InitDefaultsVersion_Version_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Enze::_Version_default_instance_;
    new (ptr) ::Enze::Version();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Enze::Version::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<1> scc_info_Version_Version_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsVersion_Version_2eproto}, {
      &scc_info_Address_Address_2eproto.base,}};

void InitDefaults_Version_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_Version_Version_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_Version_2eproto[1];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_Version_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_Version_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_Version_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Enze::Version, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Enze::Version, utime_),
  PROTOBUF_FIELD_OFFSET(::Enze::Version, nversion_),
  PROTOBUF_FIELD_OFFSET(::Enze::Version, nservices_),
  PROTOBUF_FIELD_OFFSET(::Enze::Version, addrme_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Enze::Version)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::Enze::_Version_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_Version_2eproto = {
  {}, AddDescriptors_Version_2eproto, "Version.proto", schemas,
  file_default_instances, TableStruct_Version_2eproto::offsets,
  file_level_metadata_Version_2eproto, 1, file_level_enum_descriptors_Version_2eproto, file_level_service_descriptors_Version_2eproto,
};

::google::protobuf::internal::DescriptorTable descriptor_table_Version_2eproto = {
  false, InitDefaults_Version_2eproto, 
  "\n\rVersion.proto\022\004Enze\032\rAddress.proto\"\\\n\007"
  "Version\022\r\n\005uTime\030\001 \001(\003\022\020\n\010nVersion\030\002 \001(\005"
  "\022\021\n\tnServices\030\003 \001(\004\022\035\n\006addrMe\030\004 \001(\0132\r.En"
  "ze.Addressb\006proto3"
,
  "Version.proto", &assign_descriptors_table_Version_2eproto, 138,
};

void AddDescriptors_Version_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
    ::AddDescriptors_Address_2eproto,
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_Version_2eproto, deps, 1);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Version_2eproto = []() { AddDescriptors_Version_2eproto(); return true; }();
namespace Enze {

// ===================================================================

void Version::InitAsDefaultInstance() {
  ::Enze::_Version_default_instance_._instance.get_mutable()->addrme_ = const_cast< ::Enze::Address*>(
      ::Enze::Address::internal_default_instance());
}
class Version::HasBitSetters {
 public:
  static const ::Enze::Address& addrme(const Version* msg);
};

const ::Enze::Address&
Version::HasBitSetters::addrme(const Version* msg) {
  return *msg->addrme_;
}
void Version::clear_addrme() {
  if (GetArenaNoVirtual() == NULL && addrme_ != NULL) {
    delete addrme_;
  }
  addrme_ = NULL;
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Version::kUTimeFieldNumber;
const int Version::kNVersionFieldNumber;
const int Version::kNServicesFieldNumber;
const int Version::kAddrMeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Version::Version()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Enze.Version)
}
Version::Version(const Version& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_addrme()) {
    addrme_ = new ::Enze::Address(*from.addrme_);
  } else {
    addrme_ = NULL;
  }
  ::memcpy(&utime_, &from.utime_,
    static_cast<size_t>(reinterpret_cast<char*>(&nversion_) -
    reinterpret_cast<char*>(&utime_)) + sizeof(nversion_));
  // @@protoc_insertion_point(copy_constructor:Enze.Version)
}

void Version::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_Version_Version_2eproto.base);
  ::memset(&addrme_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&nversion_) -
      reinterpret_cast<char*>(&addrme_)) + sizeof(nversion_));
}

Version::~Version() {
  // @@protoc_insertion_point(destructor:Enze.Version)
  SharedDtor();
}

void Version::SharedDtor() {
  if (this != internal_default_instance()) delete addrme_;
}

void Version::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Version& Version::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_Version_Version_2eproto.base);
  return *internal_default_instance();
}


void Version::Clear() {
// @@protoc_insertion_point(message_clear_start:Enze.Version)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaNoVirtual() == NULL && addrme_ != NULL) {
    delete addrme_;
  }
  addrme_ = NULL;
  ::memset(&utime_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&nversion_) -
      reinterpret_cast<char*>(&utime_)) + sizeof(nversion_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Version::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<Version*>(object);
  ::google::protobuf::uint32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ::google::protobuf::uint32 tag;
    ptr = Varint::Parse32Inline(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int64 uTime = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::int64 value = val;
        msg->set_utime(value);
        break;
      }
      // int32 nVersion = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::int32 value = val;
        msg->set_nversion(value);
        break;
      }
      // uint64 nServices = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 24) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::uint64 value = val;
        msg->set_nservices(value);
        break;
      }
      // .Enze.Address addrMe = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 34) goto handle_unusual;
        ptr = Varint::Parse32Inline(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        parser_till_end = ::Enze::Address::_InternalParse;
        object = msg->mutable_addrme();
        if (size > end - ptr) goto len_delim_till_end;
        auto newend = ptr + size;
        bool ok = ctx->ParseExactRange({parser_till_end, object},
                                       ptr, newend);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ok);
        ptr = newend;
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
bool Version::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Enze.Version)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int64 uTime = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &utime_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 nVersion = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &nversion_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint64 nServices = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (24 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &nservices_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .Enze.Address addrMe = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (34 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
               input, mutable_addrme()));
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
  // @@protoc_insertion_point(parse_success:Enze.Version)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Enze.Version)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Version::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Enze.Version)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 uTime = 1;
  if (this->utime() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->utime(), output);
  }

  // int32 nVersion = 2;
  if (this->nversion() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->nversion(), output);
  }

  // uint64 nServices = 3;
  if (this->nservices() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->nservices(), output);
  }

  // .Enze.Address addrMe = 4;
  if (this->has_addrme()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, HasBitSetters::addrme(this), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Enze.Version)
}

::google::protobuf::uint8* Version::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Enze.Version)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 uTime = 1;
  if (this->utime() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->utime(), target);
  }

  // int32 nVersion = 2;
  if (this->nversion() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->nversion(), target);
  }

  // uint64 nServices = 3;
  if (this->nservices() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->nservices(), target);
  }

  // .Enze.Address addrMe = 4;
  if (this->has_addrme()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        4, HasBitSetters::addrme(this), deterministic, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Enze.Version)
  return target;
}

size_t Version::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Enze.Version)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .Enze.Address addrMe = 4;
  if (this->has_addrme()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSize(
        *addrme_);
  }

  // int64 uTime = 1;
  if (this->utime() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->utime());
  }

  // uint64 nServices = 3;
  if (this->nservices() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->nservices());
  }

  // int32 nVersion = 2;
  if (this->nversion() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->nversion());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Version::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Enze.Version)
  GOOGLE_DCHECK_NE(&from, this);
  const Version* source =
      ::google::protobuf::DynamicCastToGenerated<Version>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Enze.Version)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Enze.Version)
    MergeFrom(*source);
  }
}

void Version::MergeFrom(const Version& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Enze.Version)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_addrme()) {
    mutable_addrme()->::Enze::Address::MergeFrom(from.addrme());
  }
  if (from.utime() != 0) {
    set_utime(from.utime());
  }
  if (from.nservices() != 0) {
    set_nservices(from.nservices());
  }
  if (from.nversion() != 0) {
    set_nversion(from.nversion());
  }
}

void Version::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Enze.Version)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Version::CopyFrom(const Version& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Enze.Version)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Version::IsInitialized() const {
  return true;
}

void Version::Swap(Version* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Version::InternalSwap(Version* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(addrme_, other->addrme_);
  swap(utime_, other->utime_);
  swap(nservices_, other->nservices_);
  swap(nversion_, other->nversion_);
}

::google::protobuf::Metadata Version::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_Version_2eproto);
  return ::file_level_metadata_Version_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Enze
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::Enze::Version* Arena::CreateMaybeMessage< ::Enze::Version >(Arena* arena) {
  return Arena::CreateInternal< ::Enze::Version >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
